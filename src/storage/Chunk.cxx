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

    size_t needSize = size + sizeof(int);
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
    if (pageInfo->hasFreeSpace_ == 1)
    {
        char *data = ((char*)curPage_) + sizeof(PageInfo);
        pageInfo->hasFreeSpace_ =0;
        *((int*)data) = 1;
        db->releaseAllocDatabaseMutex();
        return data + sizeof(int);
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
    int multiple = os::floor(allocSize_ / PAGE_SIZE);
    int offset = ((multiple + 1) * PAGE_SIZE);

    pageInfo->setPageAsUsed(offset);

    //create the link
   ((PageInfo*)curPage_)->nextPage_ = (Page*) pageInfo;
    //Make this as current page
    curPage_ = (Page*) pageInfo;
    char* data = ((char*)curPage_) + sizeof(PageInfo);
    //TODO::check whether it is locked
    *((int*)data) = 1;
    db->releaseAllocDatabaseMutex();
    return data + sizeof(int);

}

void* Chunk::allocateFromFirstPage(Database *db, int noOfDataNodes)
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
        if (pageIter->hasFreeSpace_ == 1)
        {
            for (i = 0; i< noOfDataNodes -1; i++)
            {
                if (1 == *((int*)data))
                    data = data + allocSize_;
                else break;
            }
            if (i != noOfDataNodes -1) break;
        }
        printDebug(DM_Alloc, "Chunk ID: %d Page :%x does not have free nodes",
                                                           chunkID_, pageIter);
        pageIter = (PageInfo*)((PageInfo*) pageIter)->nextPage_;
    }
    if (NULL == pageIter) return NULL;
    printDebug(DM_Alloc,"ChunkID:%d Scan for free node End:Page :%x",
                                                  chunkID_, pageIter);
    *((int*)data) = 1;
    return data + sizeof(int);

}

void* Chunk::allocateFromNewPage(Database *db)
{
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
        return NULL;
    }
    //get a new page from db
    Page *page = db->getFreePage();
    if (page == NULL)
    {
        db->releaseAllocDatabaseMutex();
        return NULL;
    }
    printDebug(DM_Alloc, "ChunkID:%d Normal Data Item newPage:%x",
                                                  chunkID_, page);
    //Initialize pageInfo for this new page
    PageInfo *pInfo = (PageInfo*)page;
    pInfo->setPageAsUsed(0);

    //create the link between old page and the newly created page
    PageInfo* pageInfo = ((PageInfo*)curPage_);
    pageInfo->nextPage_ = page;

    //make this new page as the current page
    curPage_ = page;

    char* data = ((char*)page) + sizeof(PageInfo);
    *((int*)data) = 1;
    db->releaseAllocDatabaseMutex();
    return data + sizeof(int);
}

//Allocates memory to store data
//TODO::check whether it is locked before allocating.
//delete tuple will set the usedflag to true, but locks will be held
//till commit and it shall be rolledback.So make sure that it does not
//allocate deleted tuple which is yet to be commited.

void* Chunk::allocate(Database *db, DbRetVal *status)
{
    PageInfo* pageInfo = ((PageInfo*)curPage_);

    int noOfDataNodes=os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
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

    int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        if (status != NULL) *status = ErrLockTimeOut;
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return NULL;
    }
    int i = noOfDataNodes;
    if (pageInfo->hasFreeSpace_ == 1)
    {
        for (i = 1; i< noOfDataNodes; i++)
        {
            if (*((int*)data) == 1) data = data + allocSize_;
            else break;
        }

    }
    printDebug(DM_Alloc, "ChunkID:%d Node which might be free is %d",
                                                        chunkID_, i);
    //It comes here if the pageInfo->hasFreeSpace ==0
    //or there are no free data space in this page
    if (i == noOfDataNodes && *((int*)data) == 1)
    {

        printDebug(DM_Alloc, "ChunkID:%d curPage does not have free nodes.", chunkID_);
        //there are no free data space in this page
        pageInfo->hasFreeSpace_ = 0;
        if (chunkID_ == LockTableId || chunkID_ == TransHasTableId) 
        {
           data = (char*) allocateFromFirstPage(db, noOfDataNodes);
           if (NULL == data)
           {
              data = (char*) allocateFromNewPage(db);
              if (data == NULL)
              {
                printError(ErrNoMemory, "No memory in any of the pages:Increase db size");
                if (status != NULL) *status = ErrNoMemory;
              }
           }
        } 
        else 
        {
           data = (char*) allocateFromNewPage(db);
           if (NULL == data)
           {
              data = (char*) allocateFromFirstPage(db, noOfDataNodes);
              if (data == NULL)
              {
                printError(ErrNoMemory, "No memory in any of the pages:Increase db size");
                if (status != NULL) *status = ErrNoMemory;
              }
           }
        }
        releaseChunkMutex(db->procSlot);
        return data;
    }
    *((int*)data) = 1;
    releaseChunkMutex(db->procSlot);
    return data + sizeof(int);
}


void* Chunk::allocateForLargeDataSize(Database *db, size_t size)
{
    //no need to take chunk mutexes for this, as we are taking alloc database mutex
    int multiple = os::floor(size / PAGE_SIZE);
    int offset = ((multiple + 1) * PAGE_SIZE);
    PageInfo* pageInfo = ((PageInfo*)curPage_);
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
        return NULL;
    }
    pageInfo = (PageInfo*)db->getFreePage(allocSize_);
    if (NULL == pageInfo)
    {
        db->releaseAllocDatabaseMutex();
        printError(ErrNoMemory,"No more free pages in the database:Increase db size");
        return NULL;
    }
    printDebug(DM_VarAlloc,"Chunk::allocate Large Data Item id:%d Size:%d curPage:%x ",
                                            chunkID_, size, curPage_);
    //TODO:: logic pending


    //REDESIGN MAY BE REQUIRED:Lets us live with this for now.
    //what happens to the space lets say 10000 bytes is allocated
    //it needs 2 pages,= 16000 bytes, 6000 bytes should not be wasted
    //in this case.So need to take of this.
    //Will be coded at later stage as this is developed to support
    //undo logging and currently we shall assume that the logs generated
    //wont be greater than PAGE_SIZE.
    db->releaseAllocDatabaseMutex();
    return NULL;

}



void* Chunk::allocFromNewPageForVarSize(Database *db, size_t size)
{
    //Should be called only for data items <PAGE_SIZE
    DbRetVal ret = db->getAllocDatabaseMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
        return NULL;
    }

    void *vnode = varSizeFirstFitAllocate(size);
    if (vnode != NULL)
    {
       db->releaseAllocDatabaseMutex();
       return vnode;
    }

    Page *newPage = db->getFreePage();
    db->releaseAllocDatabaseMutex();
    if (NULL == newPage)
    {
        return NULL;
    }

    printDebug(DM_VarAlloc, "ChunkID:%d New Page: %x ", chunkID_, newPage);
    PageInfo *pInfo = (PageInfo*) newPage;
    pInfo->setPageAsUsed(0);
    createDataBucket(newPage, PAGE_SIZE, size);

    ((PageInfo*)curPage_)->nextPage_ = newPage;
    curPage_ = newPage;
    char *data= ((char*)newPage) + sizeof(PageInfo) + sizeof(VarSizeInfo);
    return data;
}

//Allocates from the current page of the chunk.
//Scans through the VarSizeInfo objects in the page and gets the free slot
void* Chunk::allocateFromCurPageForVarSize(size_t size)
{
    //Should be called only for data items <PAGE_SIZE
    Page *page = ((PageInfo*)curPage_);
    printDebug(DM_VarAlloc, "Chunk::allocate Normal Data Item id:%d Size:%d curPage:%x ",
                                               chunkID_, size, curPage_);
    VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) +
                                                sizeof(PageInfo));
    while ((char*) varInfo < ((char*)page + PAGE_SIZE))
    {
        if (0 == varInfo->isUsed_)
        {
            if( size + sizeof(VarSizeInfo) < varInfo->size_)
            {
                splitDataBucket(varInfo, size);
                printDebug(DM_VarAlloc, "Chunkid:%d splitDataBucket: Size: %d Item:%x ",
                                                         chunkID_, size, varInfo);
                return (char*)varInfo + sizeof(VarSizeInfo);
            }
            else if (size == varInfo->size_) {
                varInfo->isUsed_ = 1;
                return (char *) varInfo + sizeof(VarSizeInfo);
            }

        }
        varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
    }
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

    size_t alignedSize = os::align(size);
    void *data = NULL;
    int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        *status = ErrLockTimeOut;
        return NULL;
    }
    if (alignedSize > PAGE_SIZE)
    {
        data =  allocateForLargeDataSize(db, alignedSize);
    }
    else
    {
        data = allocateFromCurPageForVarSize(alignedSize);
        if (NULL == data) {
            //No available spaces in the current page.
            //allocate new page
            data= allocFromNewPageForVarSize(db, alignedSize);
            if (NULL == data) {
                printError(ErrNoMemory, "No memory in any of the pages:Increase db size");
                if (status != NULL) *status = ErrNoMemory;
            }
        }
    }
    releaseChunkMutex(db->procSlot);
    return data;
}

//Assumes chunk mutex is already taken, before calling this
void* Chunk::varSizeFirstFitAllocate(size_t size)
{
    printDebug(DM_VarAlloc, "Chunk::varSizeFirstFitAllocate size:%d firstPage:%x",
                                               size, firstPage_);

    Page *page = ((PageInfo*)firstPage_);
    size_t alignedSize = os::align(size);
    while(NULL != page)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
        while ((char*) varInfo < ((char*)page + PAGE_SIZE))
        {
            if (0 == varInfo->isUsed_)
            {
                if( alignedSize +sizeof(VarSizeInfo) < varInfo->size_)
                {
                    splitDataBucket(varInfo, alignedSize);
                    return ((char*)varInfo) + sizeof(VarSizeInfo);
                }
                else if (alignedSize == varInfo->size_) {
                    varInfo->isUsed_ = 1;
                    printDebug(DM_VarAlloc, "VarSizeFirstFitAllocate returning %x", ((char*)varInfo) +sizeof(VarSizeInfo));
                    return ((char *) varInfo) + sizeof(VarSizeInfo);
                }
            }
            varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
        }
        printDebug(DM_VarAlloc, "Chunk:This page does not have free data nodes page:%x", page);
        page = ((PageInfo*) page)->nextPage_;
    }
    return NULL;
}

void Chunk::freeForVarSizeAllocator(void *ptr, int pslot)
{
    int ret = getChunkMutex(pslot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }
    VarSizeInfo *varInfo = (VarSizeInfo*)((char*)ptr- sizeof(VarSizeInfo));
    varInfo->isUsed_ = 0;
    printDebug(DM_VarAlloc,"chunkID:%d Unset isUsed for %x", chunkID_, varInfo);
    releaseChunkMutex(pslot);
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
                         ptr) - (sizeof(PageInfo) + sizeof(int)));
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
    prev->nextPage_ = pageInfo->nextPage_;
    pageInfo->nextPageAfterMerge_ = NULL;
    pageInfo->isUsed_ = 0;
    os::memset(pageInfo,  0 , allocSize_);
    pageInfo->hasFreeSpace_ = 1;
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
    int noOfDataNodes =os::floor((PAGE_SIZE - sizeof(PageInfo)) / allocSize_);

    if (0 == noOfDataNodes)
    {
        freeForLargeAllocator(ptr, db->procSlot);
        return;
    }
    int ret = getChunkMutex(db->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }
     //below is the code for freeing in fixed size allocator

     //unset the used flag
    *((int*)ptr -1 ) = 0;
    PageInfo *pageInfo;
    pageInfo = getPageInfo(db, ptr);
    if (NULL == pageInfo)
    {
        printError(ErrSysFatal,"Probable Data corruption: pageInfo is NULL", pageInfo );
        releaseChunkMutex(db->procSlot);
        return;
    }
    //set the pageinfo where this ptr points
    pageInfo->hasFreeSpace_ = 1;
    releaseChunkMutex(db->procSlot);
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
       int rem = (long) ptr % 8192;
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

    int noOfDataNodes=os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    char *data = ((char*)firstPage_) + sizeof(PageInfo);
    int i=0;
    while( pageInfo != NULL )
    {
        data = ((char*)pageInfo) + sizeof(PageInfo);
        for (i = 0; i< noOfDataNodes; i++)
        {
            if (*((int*)data) == 1) { totalNodes++;}
            data = data + allocSize_;
        }
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
    }
    return totalNodes;
}

//TODO::for other type of allocators
int Chunk::compact()
{
    PageInfo* pageInfo = ((PageInfo*)firstPage_);
    PageInfo* prevPage = pageInfo;
    if (NULL == pageInfo) 
    {
        return 0;
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
        int noOfDataNodes=os::floor((PAGE_SIZE - sizeof(PageInfo))/allocSize_);
        char *data = ((char*)pageInfo) + sizeof(PageInfo);
        for (int i = 0; i< noOfDataNodes -1; i++)
        {
            if (1 == *((int*)data)) { flag = true; break; }
            data = data +allocSize_;
        }
        if (!flag) {
            printDebug(DM_Alloc,"Freeing unused page in fixed allocator %x\n", pageInfo);
            prevPage->nextPage_ = pageInfo->nextPage_;
            pageInfo->isUsed_ = 0;
        }
        prevPage = pageInfo;
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
        printDebug(DM_Alloc,"compact iter %x\n", pageInfo);
      }
    }
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
void Chunk::splitDataBucket(VarSizeInfo *varInfo, size_t needSize)
{
    int remSpace = varInfo->size_ - sizeof(VarSizeInfo) - needSize;
    varInfo->isUsed_ = 1;
    varInfo->size_ = needSize;
    varInfo = (VarSizeInfo*)((char*)varInfo +
               sizeof(VarSizeInfo) +  varInfo->size_);
    varInfo->isUsed_ = 0;
    varInfo->size_  = remSpace;
    printDebug(DM_VarAlloc, "Remaining space is %d\n", remSpace);
    return;
}


void Chunk::createDataBucket(Page *page, size_t totalSize, size_t needSize)
{
    VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
    varInfo->isUsed_ = 0;
    varInfo->size_ = PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo);
    splitDataBucket(varInfo, needSize);
    return;
}
void Chunk::setChunkNameForSystemDB(int id)
{
                strcpy(chunkName,ChunkName[id]);
}

void Chunk::print()
{
        printf("        <Chunk Id> %d </Chunk Id> \n",chunkID_);
        printf("                <TotalPages> %d </TotalPages> \n",totalPages());
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



