/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include<Allocator.h>
#include<Database.h>
#include<os.h>
#include<Debug.h>
#include<Config.h>
#include<CatalogTables.h>


//Will check from first page to current page and do first fit allocate
//if no space available, allocates new page
void* Chunk::allocFromNewPageForVarSize(Database *db, size_t size, int pslot, DbRetVal *rv)
{
    //Should be called only for data items <PAGE_SIZE
    void *vnode = varSizeFirstFitAllocate(size, pslot, rv);
    if (vnode != NULL)
    {
       return vnode;
    }
    printDebug(DM_Warning, "No free space in any of the pages already being used");
    *rv =OK;
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
        return NULL;
    }
    Page *newPage = db->getFreePage();
    if (NULL == newPage)
    {
        db->releaseAllocDatabaseMutex();
        return NULL;
    }

    printDebug(DM_VarAlloc, "ChunkID:%d New Page: %x ", chunkID_, newPage);
    PageInfo *pInfo = (PageInfo*) newPage;
    pInfo->setPageAsUsed(0);
    setPageDirty(pInfo);
    SETBIT(pInfo->flags, HAS_SPACE);
    if (1 == createDataBucket(newPage, PAGE_SIZE, size, pslot))
    {
        printError(ErrSysFatal, "Split failed in new page...Should never happen");
        *rv = ErrSysFatal;
        db->releaseAllocDatabaseMutex();
        return NULL;
    }
    long oldPage = (long)((PageInfo*)curPage_)->nextPage_;
    //((PageInfo*)curPage_)->nextPage_ = newPage;
    int retVal = Mutex::CASL((long*) &(((PageInfo*)curPage_)->nextPage_), 
               (long)(((PageInfo*)curPage_)->nextPage_), (long)newPage);
    if(retVal !=0) {
        printError(ErrSysFatal, "Unable to get lock to set chunk next page");
        pInfo->setPageAsFree();
        db->releaseAllocDatabaseMutex();
        *rv = ErrSysFatal;
        return NULL;
    }
    //curPage_ = newPage;
    retVal = Mutex::CASL((long*) &curPage_, (long)curPage_, (long)newPage);
    if(retVal !=0) {
        printError(ErrSysFatal, "Unable to get lock to set curPage");
        retVal = Mutex::CASL((long*) &(((PageInfo*)curPage_)->nextPage_), 
               (long)(((PageInfo*)curPage_)->nextPage_), (long)oldPage);
        if (retVal !=0 ) printError(ErrSysFatal, "Unable to reset curPage");
        pInfo->setPageAsFree();
        db->releaseAllocDatabaseMutex();
        *rv = ErrSysFatal;
        return NULL;
    }
    db->releaseAllocDatabaseMutex();
    char *data= ((char*)newPage) + sizeof(PageInfo) + sizeof(VarSizeInfo);
    return data;
}

//Allocates from the current page of the chunk.
//Scans through the VarSizeInfo objects in the page and gets the free slot
void* Chunk::allocateFromCurPageForVarSize(size_t size, int pslot, DbRetVal *rv)
{
    //Should be called only for data items <PAGE_SIZE
    Page *page = ((PageInfo*)curPage_);
    printDebug(DM_VarAlloc, "Chunk::allocate Normal Data Item id:%d Size:%d curPage:%x ",
                                               chunkID_, size, curPage_);
    VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) +
                                                sizeof(PageInfo));
    //if ( 0 != getChunkMutex(pslot)) { *rv = ErrLockTimeOut; return NULL; }
    int pageSize = PAGE_SIZE;
    bool hasSpace= false;
    while ((char*) varInfo < ((char*)page + pageSize))
    {
        if (0 == varInfo->isUsed_)
        {
            hasSpace= true;
            if( size + sizeof(VarSizeInfo) < varInfo->size_)
            {
                if (1 == splitDataBucket(varInfo, size, pslot, rv))
                {
                    printDebug(DM_Warning, "Unable to split the data bucket");
                    //releaseChunkMutex(pslot);
                    return NULL;
                }
                printDebug(DM_VarAlloc, "Chunkid:%d splitDataBucket: Size: %d Item:%x ",
                                                         chunkID_, size, varInfo);
                //releaseChunkMutex(pslot);
                return (char*)varInfo + sizeof(VarSizeInfo);
            }
            else if (size == varInfo->size_) {
                //varInfo->isUsed_ = 1;
                int ret = Mutex::CASGen(&varInfo->isUsed_ , 0, 1);
                if(ret !=0) {
                     printDebug(DM_Warning, "Unable to get lock for var alloc size:%d ", size);
                     *rv = ErrLockTimeOut;
                     //releaseChunkMutex(pslot);
                     return NULL;
                }
                //releaseChunkMutex(pslot);
                return (char *) varInfo + sizeof(VarSizeInfo);
            }

        }
        varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
    }
    if (!hasSpace) CLEARBIT(((PageInfo*)curPage_)->flags, HAS_SPACE);
    if (hasSpace && size < MIN_VARCHAR_ALLOC_SIZE) 
                   CLEARBIT(((PageInfo*)curPage_)->flags, HAS_SPACE);
    //releaseChunkMutex(pslot);
    return NULL;
}

void* Chunk::allocateForVarLargeSize(PageInfo *pageInfo, size_t size, int offset)
{
    //large size allocate for varSize data
    VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)pageInfo) + sizeof(PageInfo));
    pageInfo->nextPageAfterMerge_ = ((char*)pageInfo + offset);
    ((PageInfo*)curPage_)->nextPage_ = (Page*) pageInfo;
    curPage_ = (Page*) pageInfo;
    varInfo->size_= size;
    int ret = Mutex::CASGen(&varInfo->isUsed_ , varInfo->isUsed_, 1);
    if(ret !=0) {
       printError(ErrLockTimeOut, "Unable to get lock for var alloc. Retry...");
       return NULL;
    }
    pageInfo->isUsed_=1;
    setPageDirty(pageInfo);
    return (char *) varInfo + sizeof(VarSizeInfo);
}

//Allocates memory to store data of variable size
void* Chunk::allocate(Database *db, size_t size, DbRetVal *status)
{
    if (0 == size) return NULL;
    //check if the size is more than PAGE_SIZE
    //if it is more than the PAGE_SIZE, then allocate new
    //page using database and then link the curPage to the
    //newly allocated page
    //if it is less than PAGE_SIZE, then check the curpage for
    //free memory of specified size
    //if not available, then scan from the firstPage for the free
    //space

    //TODO::During the scan, merge nearby nodes if both are free
    //if not available then allocate new page

    size_t alignedSize = os::alignLong(size);
    void *data = NULL;
    int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        *status = ErrLockTimeOut;
        return NULL;
    }
    if (alignedSize > PAGE_SIZE )
    {
        data =  allocateForLargeDataSize(db, alignedSize);
    }
    else
    {
        data = allocateFromCurPageForVarSize(alignedSize, db->procSlot, status);
        if (NULL == data) {
            *status = OK;
            //No available spaces in the current page.
            //allocate new page
            data= allocFromNewPageForVarSize(db, alignedSize, db->procSlot, status);
            if (NULL == data && *status !=ErrLockTimeOut) {
                printError(ErrNoMemory, "No memory in any of the pages:Increase db size");
                *status = ErrNoMemory;
            }
        }
    }
    releaseChunkMutex(db->procSlot);
    return data;
}

//Assumes chunk mutex is already taken, before calling this
void* Chunk::varSizeFirstFitAllocate(size_t size, int pslot, DbRetVal *rv)
{
    printDebug(DM_VarAlloc, "Chunk::varSizeFirstFitAllocate size:%d firstPage:%x",
                                               size, firstPage_);

    Page *page = ((PageInfo*)firstPage_);
    size_t alignedSize = os::alignLong(size);
    //if ( 0 != getChunkMutex(pslot)) { *rv = ErrLockTimeOut; return NULL; }
    int pageSize = PAGE_SIZE;
    bool hasSpace=false;
    while(NULL != page)
    {
      VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
      hasSpace=false;
      if (BITSET(((PageInfo*)page)->flags, HAS_SPACE)){
        while ((char*) varInfo < ((char*)page + pageSize))
        {
            if (0 == varInfo->isUsed_)
            {
                hasSpace=true;
                if( alignedSize +sizeof(VarSizeInfo) < varInfo->size_)
                {
                    if( 1 == splitDataBucket(varInfo, alignedSize, pslot, rv))
                    {
                        printDebug(DM_Warning, "Unable to split the data bucket");
                        //releaseChunkMutex(pslot);
                        return NULL;
                    }
                    //releaseChunkMutex(pslot);
                    return ((char*)varInfo) + sizeof(VarSizeInfo);
                }
                else if (alignedSize == varInfo->size_) {
                    //varInfo->isUsed_ = 1;
                    int ret = Mutex::CASGen(&varInfo->isUsed_, 0, 1);
                    if(ret !=0) {
                       printDebug(DM_Warning,"Unable to get lock to set isUsed flag.");
                       *rv = ErrLockTimeOut;
                       //releaseChunkMutex(pslot);
                       return NULL;
                    }
                    printDebug(DM_VarAlloc, "VarSizeFirstFitAllocate returning %x", ((char*)varInfo) +sizeof(VarSizeInfo));
                    //releaseChunkMutex(pslot);
                    return ((char *) varInfo) + sizeof(VarSizeInfo);
                }
            }
            varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
        }
        if (!hasSpace) CLEARBIT(((PageInfo*)page)->flags, HAS_SPACE);
        if (hasSpace && size < MIN_VARCHAR_ALLOC_SIZE) 
                                  CLEARBIT(((PageInfo*)page)->flags, HAS_SPACE);
      }
      printDebug(DM_VarAlloc, "Chunk:This page does not have free data nodes page:%x", page);
      page = ((PageInfo*) page)->nextPage_;
    }
    //releaseChunkMutex(pslot);
    return NULL;
}

void Chunk::freeForVarSizeAllocator(Database *db, void *ptr, int pslot)
{
    int ret = getChunkMutex(pslot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }
    VarSizeInfo *varInfo = (VarSizeInfo*)((char*)ptr- sizeof(VarSizeInfo));
    //varInfo->isUsed_ = 0;
    if(varInfo->size_ > (PAGE_SIZE - (sizeof(VarSizeInfo)+sizeof(PageInfo)))) {
        PageInfo *pageInfo = (PageInfo*)((char*)varInfo - sizeof(PageInfo));
        PageInfo *pInfo = (PageInfo*)firstPage_, *prev = (PageInfo*)firstPage_;
        bool found = false;
        while(!found)
        {
            if(NULL==pInfo) break;
            if (pInfo == pageInfo) {found = true;  break; }
            prev = pInfo;
            pInfo = (PageInfo*)pInfo->nextPage_;
        }
        if (!found)
        {
             printError(ErrSysFatal,"Page %x not found in page list:Logical error", pageInfo );
             releaseChunkMutex(pslot);
             return ;
        }
         if(curPage_== pageInfo) {curPage_ = prev ; }
         pageInfo->isUsed_ = 0;
         pageInfo->nextPageAfterMerge_ = NULL; 
         setPageDirty(pageInfo);
         SETBIT(pageInfo->flags, HAS_SPACE);
         prev->nextPage_ = pageInfo->nextPage_;
    }
    int retVal = Mutex::CASGen(&varInfo->isUsed_, 1, 0);
    if(retVal !=0) {
        printError(ErrAlready, "Fatal: Varsize double free for %x", ptr);
    }
    PageInfo *pageInfo = getPageInfo(db, ptr);
    if (NULL == pageInfo)
    {
        printError(ErrSysFatal,"Fatal: pageInfo is NULL", pageInfo );
        releaseChunkMutex(db->procSlot);
        return;
    }
    SETBIT(pageInfo->flags, HAS_SPACE);
    SETBIT(pageInfo->flags, IS_DIRTY);
    printDebug(DM_VarAlloc,"chunkID:%d Unset isUsed for %x", chunkID_, varInfo);
    releaseChunkMutex(pslot);
    return;

}

int Chunk::splitDataBucket(VarSizeInfo *varInfo, size_t needSize, int pSlot, DbRetVal *rv)
{
    InUse remSpace = varInfo->size_ - sizeof(VarSizeInfo) - needSize;
    //varInfo->isUsed_ = 1;
    int ret = Mutex::CASGen(&varInfo->isUsed_ , 0, 1);
    if(ret !=0) {
        printDebug(DM_Warning, "Unable to set I isUsed flag");
        *rv = ErrLockTimeOut;
        return 1;
    }
    //varInfo->size_ = needSize;
    ret = Mutex::CASGen(&varInfo->size_, varInfo->size_ , needSize);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set I size flag");
        ret = Mutex::CASGen(&varInfo->isUsed_ , varInfo->isUsed_, 0);
        if (ret !=0) printError(ErrSysFatal, "Unable to reset isUsed flag");
        *rv = ErrSysFatal;
        return 1;    
    }
    VarSizeInfo *varInfo2 = (VarSizeInfo*)((char*)varInfo +
               sizeof(VarSizeInfo) +  varInfo->size_);
    //varInfo2->isUsed_ = 0;
    ret = Mutex::CASGen(&varInfo2->isUsed_ , varInfo2->isUsed_, 0);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set II isUsed flag");
        ret = Mutex::CASGen(&varInfo->isUsed_ , varInfo->isUsed_, 0);
        if (ret !=0) printError(ErrSysFatal, "Unable to reset isUsed flag");
        *rv = ErrSysFatal;
        return 1;
    }
    //varInfo2->size_  = remSpace;
    ret = Mutex::CASGen(&varInfo2->size_, varInfo2->size_ , remSpace);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set II size flag");
        ret = Mutex::CASGen((int*)&varInfo->isUsed_ , varInfo->isUsed_, 0);
        if (ret !=0) printError(ErrSysFatal, "Unable to reset isUsed flag");
        *rv = ErrSysFatal;
        return 1;
    }
    printDebug(DM_VarAlloc, "Remaining space is %d\n", remSpace);
    return 0;
}

int Chunk::createDataBucket(Page *page, size_t totalSize, size_t needSize, int pslot)
{
    //already db alloc mutex is taken
    VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
    //varInfo->isUsed_ = 0;
    int ret = Mutex::CASGen(&varInfo->isUsed_ , varInfo->isUsed_, 0);
    if(ret !=0) {
        printError(ErrSysFatal, "Fatal:Unable to get lock to set isUsed flag");
    }
    //varInfo->size_ = PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo);
    ret = Mutex::CASGen(&varInfo->size_, varInfo->size_ , 
                       PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo));
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to get lock to set size");
    }
    DbRetVal rv =OK;
    return splitDataBucket(varInfo, needSize, pslot, &rv);
}

long Chunk::getVarTotalDataNodes()
{
    long totalNodes=0;
    Page *page = ((PageInfo*)firstPage_);
    while(NULL != page)
    {
       VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
       while ((char*) varInfo < ((char*)page + PAGE_SIZE))
       {
          if (1 == varInfo->isUsed_) totalNodes++;
          varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                 +varInfo->size_);
       }
       page = ((PageInfo*) page)->nextPage_;
    }
    return totalNodes;
}

void Chunk::varCompact()
{
   PageInfo* pageInfo = ((PageInfo*)firstPage_);
   PageInfo* prevPage = pageInfo;
   //first page is not null as it is already checked in Chunk::compact
   pageInfo = (PageInfo*)pageInfo->nextPage_;
   while( pageInfo != NULL )
   {
      bool flag = false;
      VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)pageInfo) +
                                            sizeof(PageInfo));
      while ((char*) varInfo < ((char*)pageInfo + PAGE_SIZE))
      {
         if (1 == varInfo->isUsed_) {flag=true; break;}
         varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                   +varInfo->size_);
      }
      if (!flag) {
         printDebug(DM_VarAlloc,"Freeing unused page in varsize allocator %x\n", pageInfo);
         prevPage->nextPage_ = pageInfo->nextPage_;
         pageInfo->isUsed_ = 0;
      }
      prevPage = pageInfo;
      pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
      printDebug(DM_VarAlloc,"compact iter %x\n", pageInfo);
   }
   return;
}
