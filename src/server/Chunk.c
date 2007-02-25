/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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

// sets the size of the Chunk allocator for fixed size
// allocator
// we need one integer to store book keeping information
// whether the storage allocation unit is used of not
// when it is deleted this flag is only set to unused
void Chunk::setSize(size_t size)
{

    size_t needSize = size + sizeof(int);
    size_t multiple = os::floor(needSize / sizeof(size_t));
    size_t rem = needSize % sizeof(size_t);
    if (0 == rem)
        allocSize_ = needSize;
    else
        allocSize_  = (multiple + 1) * sizeof(size_t);
}

//Allocates memory to store data
//TODO::check whether it is locked before allocating.
//delete tuple will set the usedflag to true, but locks will be held
//till commit and it shall be rolledback.So make sure that it does not
//allocate deleted tuple which is yet to be commited.

void* Chunk::allocate(Database *db)
{
    int ret = getChunkMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return NULL;
    }
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
        ret = db->getAllocDatabaseMutex();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
            return NULL;
        }
        pageInfo = (PageInfo*)db->getFreePage(allocSize_);
        if (NULL == pageInfo)
        {
            releaseChunkMutex();
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
        data = ((char*)curPage_) + sizeof(PageInfo);
        //TODO::check whether it is locked
        *((int*)data) = 1;
        releaseChunkMutex();
        db->releaseAllocDatabaseMutex();
        return data + sizeof(int);

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
        ret = db->getAllocDatabaseMutex();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
            return NULL;
        } 

       //there are no free data space in this page
        pageInfo->hasFreeSpace_ = 0;
        //get a new page from db
        printDebug(DM_Alloc, "ChunkID:%d curPage does not have free nodes.", chunkID_);
        Page *page = db->getFreePage();
        if (page == NULL)
        {
            PageInfo *pageIter = ((PageInfo*)firstPage_);
            printDebug(DM_Alloc, "Chunk ID:%d. No free page in database",
                                                               chunkID_);
            printDebug(DM_Alloc, "Scan from firstPage:%x for free nodes",
                                                             firstPage_);
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
            if (NULL == pageIter)
            {
                releaseChunkMutex();
                db->releaseAllocDatabaseMutex();
                printError(ErrNoMemory,"No more free pages in the database:Increase db size");
                return NULL;
            }
            printDebug(DM_Alloc,"ChunkID:%d Scan for free node End:Page :%x",
                                                          chunkID_, pageIter);
            *((int*)data) = 1;
            releaseChunkMutex();
            db->releaseAllocDatabaseMutex();
            return data + sizeof(int);
        }
        db->releaseAllocDatabaseMutex();
        //os::memset(page, 0, PAGE_SIZE);
        printDebug(DM_Alloc, "ChunkID:%d Normal Data Item newPage:%x",
                                                      chunkID_, page);
        //Initialize pageInfo for this new page
        PageInfo *pInfo = (PageInfo*)page;
        pInfo->setPageAsUsed(0);

        //create the link between old page and the newly created page
        data = ((char*)page) + sizeof(PageInfo);
        pageInfo->nextPage_ = page;

        //make this new page as the current page
        curPage_ = page;

    }
    *((int*)data) = 1;
    releaseChunkMutex();
    return data + sizeof(int);
}

//Allocates memory to store data
void* Chunk::allocate(Database *db, size_t size)
{

    if (0 == size) return NULL;
    //align the size first
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
    int ret = getChunkMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return NULL;
    }
    size_t alignedSize = os::align(size);

    if (size > PAGE_SIZE)
    {
        int multiple = os::floor(alignedSize / PAGE_SIZE);
        int offset = ((multiple + 1) * PAGE_SIZE);
        PageInfo* pageInfo = ((PageInfo*)curPage_);
        ret = db->getAllocDatabaseMutex();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
            return NULL;
        } 
        pageInfo = (PageInfo*)db->getFreePage(allocSize_);
        if (NULL == pageInfo)
        {
            releaseChunkMutex();
            db->releaseAllocDatabaseMutex();
            printError(ErrNoMemory,"No more free pages in the database:Increase db size");
            return NULL;
        }
        printDebug(DM_VarAlloc,"Chunk::allocate Large Data Item id:%d Size:%d curPage:%x ",
                                            chunkID_, alignedSize, curPage_);
        //TODO:: logic pending
        //what happens to the space lets say 10000 bytes is allocated
        //it needs 2 pages,= 16000 bytes, 6000 bytes should not be wasted
        //in this case.So need to take of this.
        //Will be coded at later stage as this is developed to support
        //undo logging and currently we shall assume that the logs generated
        //wont be greater than PAGE_SIZE.
        printf("data size greater than page size\n");
        releaseChunkMutex();
        db->releaseAllocDatabaseMutex();
        return NULL;
    }
    else
    {
        Page *page = ((PageInfo*)curPage_);
        printDebug(DM_VarAlloc, "Chunk::allocate Normal Data Item id:%d Size:%d curPage:%x ",
                                               chunkID_, alignedSize, curPage_);
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) +
                                                    sizeof(PageInfo));
        while ((char*) varInfo < ((char*)page + PAGE_SIZE))
        {
            if (0 == varInfo->isUsed_)
            {
                if( alignedSize < varInfo->size_)
                 {
                    splitDataBucket(varInfo, alignedSize);
                    releaseChunkMutex();
                    printDebug(DM_VarAlloc, "Chunkid:%d splitDataBucket: Size: %d Item:%x ",
                                                         chunkID_, alignedSize, varInfo);
                    return (char*)varInfo + sizeof(VarSizeInfo);
                }
            }
            varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
        }
        //No available spaces in the current page.
        //allocate new page
        ret = db->getAllocDatabaseMutex();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire alloc database Mutex");
            return NULL;
        }
        Page *newPage = db->getFreePage();
        if (NULL == newPage)
        {
            void *data = varSizeFirstFitAllocate(size);
            releaseChunkMutex();
            db->releaseAllocDatabaseMutex();
            if (NULL == data)
                printError(ErrNoMemory,"No more free space in the database:Increase db size");
            return data;
        }
        db->releaseAllocDatabaseMutex();

        printDebug(DM_VarAlloc, "ChunkID:%d New Page: %x ", chunkID_, newPage);
        PageInfo *pInfo = (PageInfo*) newPage;
        pInfo->setPageAsUsed(0);
        createDataBucket(newPage, PAGE_SIZE, alignedSize);

        ((PageInfo*)curPage_)->nextPage_ = newPage;
        curPage_ = newPage;
        releaseChunkMutex();
        char *data= ((char*)newPage) + sizeof(PageInfo) + sizeof(VarSizeInfo);
        return data;
    }
}

//Assumes chunk mutex is already taken, before calling this
void* Chunk::varSizeFirstFitAllocate(size_t size)
{
    Page *page = ((PageInfo*)firstPage_);
    size_t alignedSize = os::align(size);
    while(NULL != page)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)page) + sizeof(PageInfo));
        while ((char*) varInfo < ((char*)page + PAGE_SIZE))
        {
            if (0 == varInfo->isUsed_)
            {
                if( alignedSize < varInfo->size_)
                {
                    splitDataBucket(varInfo, alignedSize);
                    return (char*)varInfo + sizeof(VarSizeInfo);
                }
            }
            varInfo = (VarSizeInfo*)((char*)varInfo + sizeof(VarSizeInfo)
                                    +varInfo->size_);
        }
        page = ((PageInfo*) page)->nextPage_;
    }
    return NULL;
}



//Frees the memory pointed by ptr
void Chunk::free(Database *db, void *ptr)
{
    int ret = getChunkMutex();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire chunk Mutex");
        return;
    }
    if (0 == allocSize_)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)((char*)ptr- sizeof(VarSizeInfo));
        varInfo->isUsed_ = 0;
        printDebug(DM_VarAlloc,"chunkID:%d Unset isUsed for %x", chunkID_, varInfo);
        //return from here for variable size allocator
        releaseChunkMutex();
        return;
    }
     //unset the used flag
    *((int*)ptr -1 ) = 0;
    int noOfDataNodes =os::floor((PAGE_SIZE - sizeof(PageInfo)) / allocSize_);

    if (0 == noOfDataNodes)
    {
        //means tuple larger than PAGE_SIZE
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
            printError(ErrSysFatal,"Page %x not found in page list:Logic error", pageInfo );
            releaseChunkMutex();
            return ;
        }
        prev->nextPage_ = pageInfo->nextPage_;
        pageInfo->nextPageAfterMerge_ = NULL;
        pageInfo->isUsed_ = 0;
        os::memset(pageInfo,  0 , allocSize_);
        pageInfo->hasFreeSpace_ = 1;
        releaseChunkMutex();
        return;
    }
    PageInfo *pageInfo;
    pageInfo = getPageInfo(db, ptr);
    if (NULL == pageInfo)
    {
        printError(ErrSysFatal,"Probable Data corruption: pageInfo is NULL", pageInfo );
        releaseChunkMutex();
        return;
    }
    //set the pageinfo where this ptr points
    pageInfo->hasFreeSpace_ = 1;
    releaseChunkMutex();
    return;
}

//returns the pageInfo of the page where this ptr points
//This works only if the data size is less than PAGE_SIZE
//If ptr points to data which is more than PAGE_SIZE,then
//calling this might lead to memory corruption
//Note:IMPORTANT::assumes db lock is taken before calling this
PageInfo* Chunk::getPageInfo(Database *db, void *ptr)
{
    char *inPtr = (char*)ptr;
    PageInfo* pageInfo = ((PageInfo*)firstPage_);

    while( pageInfo != NULL )
    {
        if (inPtr > (char*) pageInfo && ((char*)pageInfo + PAGE_SIZE) >inPtr)
            return pageInfo;
        pageInfo = (PageInfo*)(((PageInfo*)pageInfo)->nextPage_) ;
    }
    return NULL;
}

int Chunk::initMutex()
{
    return chunkMutex_.init();
}
int Chunk::getChunkMutex()
{
    return chunkMutex_.tryLock();
}
int Chunk::releaseChunkMutex()
{
    return chunkMutex_.releaseLock();
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



