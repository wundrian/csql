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

// sets the size of the Chunk allocator for fixed size
// allocator
// we need one integer to store book keeping information
// whether the storage allocation unit is used of not
// when it is deleted this flag is only set to unused
void Chunk::setSize(size_t size)
{

    size_t needSize = size + sizeof(InUse);
    size_t multiple = (size_t) os::floor(needSize / sizeof(size_t));
    size_t rem = needSize % sizeof(size_t);
    if (0 == rem)
        allocSize_ = needSize;
    else
        allocSize_  = (multiple + 1) * sizeof(size_t);
}

void* Chunk::allocateForLargeDataSize(Database *db)
{
    PageInfo* pageInfo = ((PageInfo*)curPage_);
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
        return NULL;
    }

    //check whether we have space in curPage 
    if (BITSET(pageInfo->flags, HAS_SPACE))
    {
        char *data = ((char*)curPage_) + sizeof(PageInfo);
        int oldVal = pageInfo->flags;
        int newVal = oldVal;
        CLEARBIT(newVal, HAS_SPACE);
        int retVal = Mutex::CAS(&pageInfo->flags, oldVal, newVal);
        if (retVal !=0) printError(ErrSysFatal, "Unable to set flags");
        *((InUse*)data) = 1;
        //Mutex::CAS((InUse*)data , 0, 1);
        db->releaseAllocDatabaseMutex();
        return data + sizeof(InUse);
    }

    //no space in curpage , get new page from database 
    pageInfo = (PageInfo*)db->getFreePage(allocSize_);
    if (NULL == pageInfo)
    {
        db->releaseAllocDatabaseMutex();
        printError(ErrNoMemory,"No more free pages in the database");
        return NULL;
    }
    printDebug(DM_Alloc, "Chunk ID:%d Large Data Item newPage:%x",
                                       chunkID_, pageInfo);
    int multiple = (int) os::floor(allocSize_ / PAGE_SIZE);
    int offset = ((multiple + 1) * PAGE_SIZE);

    pageInfo->setPageAsUsed(offset);
    setPageDirty(pageInfo);
    

    //create the link
    //((PageInfo*)curPage_)->nextPage_ = (Page*) pageInfo;
    int retVal = Mutex::CASL((long*) &(((PageInfo*)curPage_)->nextPage_), 
               (long)(((PageInfo*)curPage_)->nextPage_), (long)pageInfo);
    if(retVal !=0) {
        printError(ErrLockTimeOut, "Fatal: Unable to create page link.");
    }

    //Make this as current page
    //curPage_ = (Page*) pageInfo;
    retVal = Mutex::CASL((long*) &curPage_, (long)curPage_, (long)pageInfo);
    if(retVal !=0) {
        printError(ErrLockTimeOut, "Fatal:Unable to set current page");
    }

    char* data = ((char*)curPage_) + sizeof(PageInfo);
    int oldVal = pageInfo->flags;
    int newVal = oldVal;
    CLEARBIT(newVal, HAS_SPACE);
    retVal = Mutex::CAS(&pageInfo->flags, oldVal, newVal);
    if(retVal !=0) {
        printError(ErrLockTimeOut, "Fatal:Unable to set flags");
    }
    *((InUse*)data) = 1;
    //Mutex::CASL((InUse*)data , 0, 1);
    db->releaseAllocDatabaseMutex();
    return data + sizeof(InUse);

}

void* Chunk::allocateFromFirstPage(Database *db, int noOfDataNodes, DbRetVal *status)
{
    PageInfo *pageIter = ((PageInfo*)firstPage_);
    printDebug(DM_Alloc, "Chunk ID:%d. No free page in database",
                                                       chunkID_);
    printDebug(DM_Alloc, "Scan from firstPage:%x for free nodes",
                                                     firstPage_);
    char *data = NULL;
    int i = 0;
    //scan from first page to locate a free node available
    while(NULL != pageIter)
    {
        data = ((char*)pageIter) + sizeof(PageInfo);
        if (BITSET(pageIter->flags, HAS_SPACE))
        {
            for (i = 0; i< noOfDataNodes ; i++)
            {
                if (1 == *((InUse*)data))
                    data = data + allocSize_;
                else break;
            }
            if (i != noOfDataNodes) break;
        }
        printDebug(DM_Alloc, "Chunk ID: %d Page :%x does not have free nodes",
                                                           chunkID_, pageIter);
        pageIter = (PageInfo*)((PageInfo*) pageIter)->nextPage_;
    }
    if (NULL == pageIter) { 
        *status = ErrNoMemory;
        return NULL;
    }
    printDebug(DM_Alloc,"ChunkID:%d Scan for free node End:Page :%x",
                                                  chunkID_, pageIter);
    //*((InUse*)data) = 1;
#if defined(__sparcv9)
    int ret = Mutex::CASL((InUse*)data , 0, 1);
#else
    int ret = Mutex::CAS((InUse*)data , 0, 1);
#endif
    if(ret !=0) {
        *status = ErrLockTimeOut;
        //printError(ErrLockTimeOut, "Unable to allocate from first page. Retry...");
        return NULL;
    }
    return data + sizeof(InUse);
}

void* Chunk::allocateFromNewPage(Database *db, DbRetVal *status)
{
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printDebug(DM_Warning,"Unable to acquire alloc database Mutex Chunkid:%d", chunkID_);
        *status = ErrLockTimeOut;
        return NULL;
    }
    //get a new page from db
    Page *page = db->getFreePage();
    if (page == NULL) {
        printError(ErrNoMemory, "Unable to allocate page");
        db->releaseAllocDatabaseMutex();
        *status = ErrNoMemory;
        return NULL;
    }
    printDebug(DM_Alloc, "ChunkID:%d Normal Data Item newPage:%x",
                                                  chunkID_, page);
    //Initialize pageInfo for this new page
    PageInfo *pInfo = (PageInfo*)page;
    pInfo->setPageAsUsed(0);
    setPageDirty(pInfo);

    char* data = ((char*)page) + sizeof(PageInfo);
    *((InUse*)data) = 1;
    //Mutex::CAS((int*)data , 0, 1);

    //create the link between old page and the newly created page
    PageInfo* pageInfo = ((PageInfo*)curPage_);

    long oldPage = (long)pageInfo->nextPage_;
    //pageInfo->nextPage_ = page;
    int retVal = Mutex::CASL((long*)&pageInfo->nextPage_ , (long)pageInfo->nextPage_, (long)page);
    if(retVal !=0) {
        *((InUse*)data) = 0;
        pInfo->setPageAsFree();
        printDebug(DM_Warning, "Unable to get lock to set chunk list.");
        *status = ErrLockTimeOut;
        return NULL;
    }

    //make this new page as the current page
    //curPage_ = page;
    retVal = Mutex::CASL((long*)&curPage_ , (long)curPage_, (long)page);
    if(retVal !=0) {
        *((InUse*)data) = 0;
        pInfo->setPageAsFree();
        retVal = Mutex::CASL((long*)&pageInfo->nextPage_ , (long)pageInfo->nextPage_, (long)oldPage);
        if (retVal !=0) printError(ErrSysFatal, "Fatal: Unable to reset the nextPage");
        printDebug(DM_Warning, "Unable to get lock to set curPage");
        *status = ErrLockTimeOut;
        return NULL;
    }

    db->releaseAllocDatabaseMutex();
    return data + sizeof(InUse);
}

//Allocates memory to store data
//TODO::check whether it is locked before allocating.
//delete tuple will set the usedflag to true, but locks will be held
//till commit and it shall be rolledback.So make sure that it does not
//allocate deleted tuple which is yet to be commited.

void* Chunk::allocate(Database *db, DbRetVal *status)
{
    PageInfo* pageInfo = ((PageInfo*)curPage_);

    int noOfDataNodes=(int) os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
    char *data = ((char*)curPage_) + sizeof(PageInfo);
    printDebug(DM_Alloc, "Chunk::allocate id:%d curPage:%x noOfDataNodes:%d",
                         chunkID_, curPage_, noOfDataNodes);
    
    //1.scan through data list and find if any is free to use in current page
    //2.If there is none then
    //    a) get new free page from db. set the prev->next to point
    //       to this new page
    //4.  b) initialize the free page to zero and get first data ptr.
    //5.If there is one, return that

    //For allocation more than PAGE_SIZE
    if (0 == noOfDataNodes)
    {
        data = (char*) allocateForLargeDataSize(db);
        return data;
    }

    /*int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        if (status != NULL) *status = ErrLockTimeOut;
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return NULL;
    }*/
    int i = noOfDataNodes;
    if (BITSET(pageInfo->flags, HAS_SPACE))
    {
        for (i = 1; i< noOfDataNodes; i++)
        {
            if (*((InUse*)data) == 1) data = data + allocSize_;
            else break;
        }

    }
    printDebug(DM_Alloc, "ChunkID:%d Node which might be free is %d",
                                                        chunkID_, i);
    //It comes here if the pageInfo hasFreeSpace 
    //or there are no free data space in this page
    if (i == noOfDataNodes && *((InUse*)data) == 1)
    {

        printDebug(DM_Alloc, "ChunkID:%d curPage does not have free nodes.", chunkID_);
        //there are no free data space in this page
        int oldVal = pageInfo->flags;
        int newVal = oldVal;
        CLEARBIT(newVal, HAS_SPACE);
        int ret = Mutex::CAS(&pageInfo->flags, oldVal, newVal);
        if(ret !=0) {
            *status = ErrLockTimeOut;
            printDebug(DM_Warning, "Unable to set hasFreespace");
            return NULL;
        }
       *status = OK;
       data = (char*) allocateFromFirstPage(db, noOfDataNodes, status);
       if (NULL == data && *status != ErrLockTimeOut)
       {
          *status = OK;
          data = (char*) allocateFromNewPage(db, status);
          if (data == NULL && *status != ErrLockTimeOut)
          {
            printError(ErrNoMemory, "No memory in any of the pages:Increase db size");
            *status = ErrNoMemory;
          }
        }
        setPageDirty(db, data);
        return data;
    }
    //*((InUse*)data) = 1;
#if defined(__sparcv9)
    int ret = Mutex::CASL((InUse*)data , 0, 1);
#else
    int ret = Mutex::CAS((InUse*)data , 0, 1);
#endif
    if(ret !=0) {
        *status = ErrLockTimeOut;
        printDebug(DM_Warning, "Unable to set isUsed : retry...");
        return NULL;
    }
    setPageDirty(db, data);
    return data + sizeof(InUse);
}

void Chunk::setPageDirty(Database *db, void *ptr)
{
    if (chunkID_ < LastCatalogID) return;
    PageInfo *pageInfo = getPageInfo(db, ptr);
    if (NULL == pageInfo)
    {
        printError(ErrSysFatal,"Fatal: pageInfo is NULL", pageInfo );
        return;
    }
    SETBIT(pageInfo->flags, IS_DIRTY);
    return;
}
void Chunk::setPageDirty(PageInfo *pInfo)
{
    if (chunkID_ < LastCatalogID) return;
    SETBIT(pInfo->flags, IS_DIRTY);
}

void* Chunk::allocateForLargeDataSize(Database *db, size_t size)
{
    //no need to take chunk mutexes for this, as we are taking alloc database mutex
    int multiple = (int) os::floor(size / PAGE_SIZE);
    int offset = ((multiple + 1) * PAGE_SIZE);
    PageInfo* pageInfo = ((PageInfo*)curPage_);
    if(0==allocSize_) 
        pageInfo = (PageInfo*)db->getFreePage(size);
    else
        pageInfo = (PageInfo*)db->getFreePage(allocSize_);
    if (NULL == pageInfo)
    {
        printError(ErrNoMemory,"No more free pages in the database:Increase db size");
        return NULL;
    }
    printDebug(DM_VarAlloc,"Chunk::alnextPageAfterMerge_locate Large Data Item id:%d Size:%d curPage:%x ",
                                            chunkID_, size, curPage_);
    //TODO:: logic pending
    if(allocSize_!=0){
        //large size allocate for FixedSize data
        pageInfo->nextPageAfterMerge_ = ((char*)pageInfo + offset);
        ((PageInfo*)curPage_)->nextPage_ = (Page*) pageInfo;
        curPage_ = (Page*) pageInfo;
        char* data = ((char*)curPage_) + sizeof(PageInfo);
        //*((InUse*)data) = 1;
#if defined(__sparcv9) 
        int ret = Mutex::CASL((InUse*)data , 0, 1);
#else
        int ret = Mutex::CAS((InUse*)data , 0, 1);
#endif
        if(ret !=0) {
             printError(ErrLockTimeOut, "Lock Timeout: retry...");
             return NULL;
        }
        pageInfo->isUsed_=1;
        int oldVal = pageInfo->flags;
        int newVal = oldVal;
        CLEARBIT(newVal, HAS_SPACE);
        SETBIT(newVal, IS_DIRTY);
        ret = Mutex::CAS(&pageInfo->flags, oldVal, newVal);
        if (ret !=0) printError(ErrSysFatal, "Unable to set flags");
        return data + sizeof(InUse);
    }else{
        //large size allocate for varSize data
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)pageInfo) + sizeof(PageInfo));
        pageInfo->nextPageAfterMerge_ = ((char*)pageInfo + offset);
        ((PageInfo*)curPage_)->nextPage_ = (Page*) pageInfo;
        curPage_ = (Page*) pageInfo;
        varInfo->size_= size;
        int ret = Mutex::CAS(&varInfo->isUsed_ , varInfo->isUsed_, 1);
        if(ret !=0) {
             printError(ErrLockTimeOut, "Unable to get lock for var alloc. Retry...");
             return NULL;
        }
        pageInfo->isUsed_=1;
        SETBIT(pageInfo->flags, IS_DIRTY);
        return (char *) varInfo + sizeof(VarSizeInfo);
    }
    //REDESIGN MAY BE REQUIRED:Lets us live with this for now.
    //what happens to the space lets say 10000 bytes is allocated
    //it needs 2 pages,= 16000 bytes, 6000 bytes should not be wasted
    //in this case.So need to take of this.
    //Will be coded at later stage as this is developed to support
    //undo logging and currently we shall assume that the logs generated
    //wont be greater than PAGE_SIZE.
    return NULL;
}



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
    if ( 0 != getChunkMutex(pslot)) { *rv = ErrLockTimeOut; return NULL; }
    while ((char*) varInfo < ((char*)page + PAGE_SIZE))
    {
        if (0 == varInfo->isUsed_)
        {
            if( size + sizeof(VarSizeInfo) < varInfo->size_)
            {
                if (1 == splitDataBucket(varInfo, size, pslot, rv))
                {
                    printDebug(DM_Warning, "Unable to split the data bucket");
                    releaseChunkMutex(pslot);
                    return NULL;
                }
                printDebug(DM_VarAlloc, "Chunkid:%d splitDataBucket: Size: %d Item:%x ",
                                                         chunkID_, size, varInfo);
                releaseChunkMutex(pslot);
                return (char*)varInfo + sizeof(VarSizeInfo);
            }
            else if (size == varInfo->size_) {
                //varInfo->isUsed_ = 1;
                int ret = Mutex::CAS(&varInfo->isUsed_ , 0, 1);
                if(ret !=0) {
                     printDebug(DM_Warning, "Unable to get lock for var alloc size:%d ", size);
                     *rv = ErrLockTimeOut;
                      releaseChunkMutex(pslot);
                     return NULL;
                }
                releaseChunkMutex(pslot);
                return (char *) varInfo + sizeof(VarSizeInfo);
            }

        }
        varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
    }
    releaseChunkMutex(pslot);
    return NULL;
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
    /*int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        *status = ErrLockTimeOut;
        return NULL;
    }*/
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
    //releaseChunkMutex(db->procSlot);
    return data;
}

//Assumes chunk mutex is already taken, before calling this
void* Chunk::varSizeFirstFitAllocate(size_t size, int pslot, DbRetVal *rv)
{
    printDebug(DM_VarAlloc, "Chunk::varSizeFirstFitAllocate size:%d firstPage:%x",
                                               size, firstPage_);

    Page *page = ((PageInfo*)firstPage_);
    size_t alignedSize = os::alignLong(size);
    if ( 0 != getChunkMutex(pslot)) { *rv = ErrLockTimeOut; return NULL; }
    while(NULL != page)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
        while ((char*) varInfo < ((char*)page + PAGE_SIZE))
        {
            if (0 == varInfo->isUsed_)
            {
                if( alignedSize +sizeof(VarSizeInfo) < varInfo->size_)
                {
                    if( 1 == splitDataBucket(varInfo, alignedSize, pslot, rv))
                    {
                        printDebug(DM_Warning, "Unable to split the data bucket");
                        releaseChunkMutex(pslot);
                        return NULL;
                    }
                    releaseChunkMutex(pslot);
                    return ((char*)varInfo) + sizeof(VarSizeInfo);
                }
                else if (alignedSize == varInfo->size_) {
                    //varInfo->isUsed_ = 1;
                    int ret = Mutex::CAS((int*)&varInfo->isUsed_, 0,  1);
                    if(ret !=0) {
                       printDebug(DM_Warning,"Unable to get lock to set isUsed flag.");
                       *rv = ErrLockTimeOut;
                       releaseChunkMutex(pslot);
                       return NULL;
                    }
                    printDebug(DM_VarAlloc, "VarSizeFirstFitAllocate returning %x", ((char*)varInfo) +sizeof(VarSizeInfo));
                    releaseChunkMutex(pslot);
                    return ((char *) varInfo) + sizeof(VarSizeInfo);
                }
            }
            varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
        }
        printDebug(DM_VarAlloc, "Chunk:This page does not have free data nodes page:%x", page);
        page = ((PageInfo*) page)->nextPage_;
    }
    releaseChunkMutex(pslot);
    return NULL;
}

void Chunk::freeForVarSizeAllocator(void *ptr, int pslot)
{
    /*int ret = getChunkMutex(pslot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }*/
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
             return ;
        }
         if(curPage_== pageInfo) {curPage_ = prev ; }
         pageInfo->isUsed_ = 0;
         pageInfo->nextPageAfterMerge_ = NULL; 
         CLEARBIT(pageInfo->flags, IS_DIRTY);
         SETBIT(pageInfo->flags, HAS_SPACE);
         prev->nextPage_ = pageInfo->nextPage_;
    }
    int ret = Mutex::CAS((int*)&varInfo->isUsed_, 1, 0);
    if(ret !=0) {
        printError(ErrAlready, "Fatal: Varsize double free for %x", ptr);
    }
    //TODO
    //setPageDirty(ptr);
    printDebug(DM_VarAlloc,"chunkID:%d Unset isUsed for %x", chunkID_, varInfo);
    //releaseChunkMutex(pslot);
    return;

}

void Chunk::freeForLargeAllocator(void *ptr, int pslot)
{
    //There will be max only one data element in a page.
    //PageInfo is stored just before the data.
    int ret = getChunkMutex(pslot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }
    PageInfo *pageInfo = (PageInfo*)(((char*)
                         ptr) - (sizeof(PageInfo) + sizeof(InUse)));
    PageInfo *pInfo = (PageInfo*)firstPage_, *prev = (PageInfo*)firstPage_;
    bool found = false;
    while(!found)
    {
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
    os::memset(((char*)pageInfo+sizeof(PageInfo)),  0 , allocSize_);
    if(((PageInfo*)firstPage_)->nextPage_ != NULL){
      pageInfo->nextPageAfterMerge_ = NULL;
      //pageInfo->isUsed_ = 0;
      ret = Mutex::CAS((int*)&pageInfo->isUsed_, pageInfo->isUsed_, 0);
      if (ret != 0) printError(ErrSysFatal, "Unable to set isUsed flag");
      int oldVal = pageInfo->flags;
      int newVal = oldVal;
      SETBIT(newVal, HAS_SPACE);
      ret = Mutex::CAS((int*)&pageInfo->flags, oldVal, newVal);
      if (ret != 0) printError(ErrSysFatal, "Unable to set flags");
      if(pageInfo == firstPage_ && ((PageInfo*)firstPage_)->nextPage_ != NULL)
      {
        //firstPage_ = pageInfo->nextPage_ ;
        ret = Mutex::CASL((long*)&firstPage_, (long) firstPage_, 
                                      (long)pageInfo->nextPage_);
        if (ret != 0) printError(ErrSysFatal, "Unable to set firstPage");
        SETBIT(((PageInfo*)firstPage_)->flags , IS_DIRTY);
      }
      else { 
        //prev->nextPage_ = pageInfo->nextPage_;
        ret = Mutex::CASL((long*)&prev->nextPage_, (long) prev->nextPage_, 
                                       (long)pageInfo->nextPage_);
        if (ret != 0) printError(ErrSysFatal, "Unable to set nextPage");
        SETBIT(prev->flags, IS_DIRTY);
      }
    }
    SETBIT(pageInfo->flags, IS_DIRTY);
    releaseChunkMutex(pslot);
    return;
}

//Frees the memory pointed by ptr
void Chunk::free(Database *db, void *ptr)
{
    if (0 == allocSize_)
    {
        freeForVarSizeAllocator(ptr, db->procSlot);
        return;
    }
    int noOfDataNodes =(int) os::floor((PAGE_SIZE - sizeof(PageInfo)) / allocSize_);

    if (0 == noOfDataNodes)
    {
        freeForLargeAllocator(ptr, db->procSlot);
        return;
    }
    /*int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }*/
     //below is the code for freeing in fixed size allocator

     //unset the used flag
    //*((int*)ptr -1 ) = 0;
    if (*((InUse*)ptr -1 ) == 0) {
        printError(ErrSysFatal, "Fatal:Data node already freed %x Chunk:%d", ptr, chunkID_);
        //return; 
    }
#if defined(__sparcv9)
    int ret = Mutex::CASL(((InUse*)ptr -1), 1, 0);
#else
    int ret = Mutex::CAS(((InUse*)ptr -1), 1, 0);
#endif
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to get lock to free for %x", ptr);
        return; 
    }
    PageInfo *pageInfo;
    pageInfo = getPageInfo(db, ptr);
    if (NULL == pageInfo)
    {
        printError(ErrSysFatal,"Fatal: pageInfo is NULL", pageInfo );
        //releaseChunkMutex(db->procSlot);
        return;
    }
    //set the pageinfo where this ptr points
    int oldVal = pageInfo->flags;
    int newVal = oldVal;
    SETBIT(newVal, HAS_SPACE);
    SETBIT(newVal, IS_DIRTY);
    ret = Mutex::CAS((int*)&pageInfo->flags, oldVal, newVal);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to get lock to set flags");
    }
    //releaseChunkMutex(db->procSlot);
    return;
}

//returns the pageInfo of the page where this ptr points
//This works only if the data size is less than PAGE_SIZE
//If ptr points to data which is more than PAGE_SIZE,then
//calling this might lead to memory corruption
//Note:IMPORTANT::assumes db lock is taken before calling this
PageInfo* Chunk::getPageInfo(Database *db, void *ptr)
{
    if (allocSize_ < PAGE_SIZE - sizeof(PageInfo)) { 
       int rem = (long) ptr % PAGE_SIZE;
       return (PageInfo*)(((char*)ptr) - rem);
    } else {
        //large size allocator
        char *inPtr = (char*)ptr;
        PageInfo* pageInfo = ((PageInfo*)firstPage_);

        while( pageInfo != NULL )
        {
          if (inPtr > (char*) pageInfo && pageInfo->nextPageAfterMerge_ >inPtr)
            return pageInfo;
        pageInfo = (PageInfo*)pageInfo->nextPage_ ;
        }
    }
    return NULL;
}

//If called on chunk used to store tuples, it returns the total number of rows
//present in the table
long Chunk::getTotalDataNodes()
{
    long totalNodes =0;
    if (0 == allocSize_) //->variable size allocator
    {
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

    //TODO::for large size allocator
    if (allocSize_ >PAGE_SIZE)//->each page has only one data node
    {
	Page *page = ((PageInfo*)firstPage_);
        while(NULL != page)
        {
                //current it page wise  later this will done
                if(1==*(int*)(((char*)page)+sizeof(PageInfo)))
                        totalNodes++;
                page = ((PageInfo*) page)->nextPage_;
        }
        return totalNodes;
    }    

    int noOfDataNodes=(int) os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    char *data = ((char*)firstPage_) + sizeof(PageInfo);
    int i=0;
    while( pageInfo != NULL )
    {
        data = ((char*)pageInfo) + sizeof(PageInfo);
        for (i = 0; i< noOfDataNodes; i++)
        {
            if (*((InUse*)data) == 1) { totalNodes++;}
            data = data + allocSize_;
        }
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
    }
    return totalNodes;
}

//TODO::for other type of allocators
int Chunk::compact(int procSlot)
{
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    PageInfo* prevPage = pageInfo;
    if (NULL == pageInfo) 
    {
        return 0;
    }
    int ret = getChunkMutex(procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return ret;
    }
    pageInfo = (PageInfo*)pageInfo->nextPage_;
    if (0 == allocSize_) 
    {
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
    }else if (allocSize_ < PAGE_SIZE)
    {
      while( pageInfo != NULL )
      {
        bool flag = false;
        int noOfDataNodes=(int) os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
        char *data = ((char*)pageInfo) + sizeof(PageInfo);
        for (int i = 0; i< noOfDataNodes ; i++)
        {
            if (1 == *((InUse*)data)) { flag = true; break; }
            data = data +allocSize_;
        }
        if (!flag) {
            printDebug(DM_Alloc,"Freeing unused page in fixed allocator %x\n", pageInfo);
            prevPage->nextPage_ = pageInfo->nextPage_;
            pageInfo->isUsed_ = 0;
            pageInfo = (PageInfo*)(((PageInfo*)prevPage)->nextPage_) ;
        }else{
            prevPage = pageInfo;
            pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
        }
        printDebug(DM_Alloc,"compact iter %x\n", pageInfo);
      }
    }
    releaseChunkMutex(procSlot);
    return 0;
}

int Chunk::totalPages()
{
    //logic is same for variable size and for large data node allocator. 
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    int totPages=0;
    while( pageInfo != NULL )
    {
        totPages++;
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
    }
    return totPages;
}
int Chunk::totalDirtyPages()
{
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    int dirtyPages=0;
    while( pageInfo != NULL )
    {
        if(BITSET(pageInfo->flags, IS_DIRTY)) dirtyPages++;
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
    }
    return dirtyPages;
}


int Chunk::initMutex()
{
    return chunkMutex_.init("Chunk");
}
int Chunk::getChunkMutex(int procSlot)
{
    return chunkMutex_.getLock(procSlot);
}
int Chunk::releaseChunkMutex(int procSlot)
{
    return chunkMutex_.releaseLock(procSlot);
}
int Chunk::destroyMutex()
{
    return chunkMutex_.destroy();
}
int Chunk::splitDataBucket(VarSizeInfo *varInfo, size_t needSize, int pSlot, DbRetVal *rv)
{
    int remSpace = varInfo->size_ - sizeof(VarSizeInfo) - needSize;
    //varInfo->isUsed_ = 1;
    int ret = Mutex::CAS((int*)&varInfo->isUsed_ , 0, 1);
    if(ret !=0) {
        printDebug(DM_Warning, "Unable to set I isUsed flag");
        *rv = ErrLockTimeOut;
        return 1;
    }
    //varInfo->size_ = needSize;
    ret = Mutex::CAS((int*)&varInfo->size_, varInfo->size_ , needSize);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set I size flag");
        ret = Mutex::CAS((int*)&varInfo->isUsed_ , varInfo->isUsed_, 0);
        if (ret !=0) printError(ErrSysFatal, "Unable to reset isUsed flag");
        *rv = ErrSysFatal;
        return 1;    
    }
    VarSizeInfo *varInfo2 = (VarSizeInfo*)((char*)varInfo +
               sizeof(VarSizeInfo) +  varInfo->size_);
    //varInfo2->isUsed_ = 0;
    ret = Mutex::CAS((int*)&varInfo2->isUsed_ , varInfo2->isUsed_, 0);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set II isUsed flag");
        ret = Mutex::CAS((int*)&varInfo->isUsed_ , varInfo->isUsed_, 0);
        if (ret !=0) printError(ErrSysFatal, "Unable to reset isUsed flag");
        *rv = ErrSysFatal;
        return 1;
    }
    //varInfo2->size_  = remSpace;
    ret = Mutex::CAS((int*)&varInfo2->size_, varInfo2->size_ , remSpace);
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to set II size flag");
        ret = Mutex::CAS((int*)&varInfo->isUsed_ , varInfo->isUsed_, 0);
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
    int ret = Mutex::CAS((int*)&varInfo->isUsed_ , varInfo->isUsed_, 0);
    if(ret !=0) {
        printError(ErrSysFatal, "Fatal:Unable to get lock to set isUsed flag");
    }
    //varInfo->size_ = PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo);
    ret = Mutex::CAS((int*)&varInfo->size_, varInfo->size_ , 
                       PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo));
    if(ret !=0) {
        printError(ErrSysFatal, "Unable to get lock to set size");
    }
    DbRetVal rv =OK;
    return splitDataBucket(varInfo, needSize, pslot, &rv);
}
void Chunk::setChunkNameForSystemDB(int id)
{
                strcpy(chunkName,ChunkName[id]);
}

void Chunk::print()
{
    printf("        <Chunk Id> %d </Chunk Id> \n",chunkID_);
    printf("                <TotalPages> %d </TotalPages> \n",totalPages());
    if (Conf::config.useDurability())
        printf("                <DirtyPages> %d </DirtyPages> \n",totalDirtyPages());
    printf("                <ChunkName > %s </ChunkName> \n",getChunkName());
    printf("                <TotalDataNodes> %d </TotalDataNodes> \n",getTotalDataNodes());
    printf("                <SizeOfDataNodes> %d </SizeOfDataNodes> \n",getSize());
    printf("                <Allocation Type> ");
    if(allocType_==0)
    {
        printf("FixedSizeAllocator ");
    }else if(allocType_==1)
    {
        printf("VariableSizeAllocator ");
    }else
    {
        printf("UnknownAllocator ");
    }
    printf("</Allocation Type>\n");
}
