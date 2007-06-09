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
#include<Database.h>
#include<os.h>
#include<CatalogTables.h>
#include<Transaction.h>
#include<Lock.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>
extern pid_t appPid;

const char* Database::getName()
{
    return metaData_->dbName_;
}

int Database::getDatabaseID()
{
    return metaData_->dbID_;
}

size_t Database::getMaxSize()
{
    return metaData_->maxSize_;
}

size_t Database::getCurrentSize()
{
    return metaData_->curSize_;

}
Page* Database::getCurrentPage()
{
    return metaData_->curPage_;

}
Page* Database::getFirstPage()
{
    return metaData_->firstPage_;

}
int Database::getMaxChunks()
{
    return metaData_->maxChunks_;
}
Chunk* Database::getHashIndexChunk()
{
    return metaData_->hashIndexChunk_;
}

void Database::setDatabaseID(int id)
{
    metaData_->dbID_ = id;
}
void Database::setName(const char *name)
{
    strcpy(metaData_->dbName_ , name);
}
void Database::setCurrentSize(size_t size)
{
    metaData_->curSize_ = size;
}
void Database::setCurrentPage(Page *page)
{
    metaData_->curPage_ = page;
}
void Database::setFirstPage(Page *page)
{
    metaData_->firstPage_ = page;
}
void Database::setMaxSize(size_t size)
{
    metaData_->maxSize_ = size;
}
void Database::setMaxChunks(int chunks)
{
    metaData_->maxChunks_ = chunks;
}
void Database::setHashIndexChunk(Chunk *ch)
{
    metaData_->hashIndexChunk_ = ch;
}


int Database::initAllocDatabaseMutex()
{
    return metaData_->dbAllocMutex_.init();
}
DbRetVal Database::getAllocDatabaseMutex()
{
    int ret= metaData_->dbAllocMutex_.tryLock();
    if (ret) return ErrSysInternal; else return OK;
}
DbRetVal Database::releaseAllocDatabaseMutex()
{
    metaData_->dbAllocMutex_.releaseLock();
    return OK;
}



int Database::initTransTableMutex()
{
    return metaData_->dbTransTableMutex_.init();
}
DbRetVal Database::getTransTableMutex()
{
    int ret = metaData_->dbTransTableMutex_.tryLock();
    if (ret) return ErrSysInternal; else return OK;
}
DbRetVal Database::releaseTransTableMutex()
{
    metaData_->dbTransTableMutex_.releaseLock();
    return OK;
}



int Database::initProcessTableMutex()
{
    return metaData_->dbProcTableMutex_.init();
}
DbRetVal Database::getProcessTableMutex()
{
    int ret = metaData_->dbProcTableMutex_.tryLock();
    if (ret) return ErrSysInternal; else return OK;
}
DbRetVal Database::releaseProcessTableMutex()
{
    metaData_->dbProcTableMutex_.releaseLock();
    return OK;
}



int Database::initDatabaseMutex()
{
    return metaData_->dbMutex_.init();
}
DbRetVal Database::getDatabaseMutex()
{
    int ret = metaData_->dbMutex_.tryLock();
    if (ret) return ErrSysInternal; else return OK;
}
DbRetVal Database::releaseDatabaseMutex()
{
    metaData_->dbMutex_.releaseLock();
    return OK;
}

// Gets the free page
// Each page is segmented by PAGE_SIZE, so it checks the pageInfo
// of each page to determine if the page is free
// Algorithm is to scan through the pageInfo objects stored at
// address (db start address + i * PAGE_SIZE) where i = 1..n till end
// database
// But in case of large tuples, pages are merged, so there wont be
// PageInfo object on pages which are merged.
// These pages are skipped by checking the nextPageAfterMerge_ of PageInfo

//NOTE::IMPORTANT::assumes alloc database lock is taken before calling this
Page* Database::getFreePage()
{
    Page* page = getFirstPage();
    printDebug(DM_Alloc, "Database::getFreePage firstPage:%x",page);
    PageInfo* pageInfo = ((PageInfo*)page);

    while( 1 == pageInfo->isUsed_)
    {
        //If any pages are merged to store data larger than PAGE_SIZE
        //move to the next page after the merge and check whether it is used
        if ( pageInfo->nextPageAfterMerge_ == NULL) {
            pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
            printDebug(DM_Alloc,"Normal Page:Moving to page:%x",pageInfo);
        }
        else {
            pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
            printDebug(DM_Alloc,"Merged Page:Moving to page:%x",pageInfo);
        }
        if (!isValidAddress((char*) pageInfo))
        {
            printError(ErrSysInternal,"Invalid address %x",pageInfo);
            return NULL;
        }

    }
    if (!isValidAddress(((char*) pageInfo) + PAGE_SIZE))
    {
        printError(ErrSysInternal, "Invalid address %x",((char*) pageInfo) + PAGE_SIZE);
        return NULL;
    }
    setCurrentPage((Page*) pageInfo);
    printDebug(DM_Alloc,"Database::getFreePage returning page:%x",pageInfo);
    return (Page*) pageInfo ;
}

//Used by tuples more than PAGE_SIZE
//NOTE::IMPORTANT::assumes alloc database lock is taken before calling this
Page* Database::getFreePage(size_t size)
{
    Page* page = getFirstPage();
    PageInfo* pageInfo = ((PageInfo*)page);
    int multiple = size / PAGE_SIZE;
    int offset = ((multiple + 1) * PAGE_SIZE);
    printDebug(DM_Alloc, "Database::getFreePage firstPage:%x size:%d",page, size);

    while(true){
        while( 1 == pageInfo->isUsed_)
        {
            //If any pages are merged to store data larger than PAGE_SIZE
            //move to the next page after the merge and check whether it is used
            if ( pageInfo->nextPageAfterMerge_ == NULL) {
                pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
                printDebug(DM_Alloc,"Normal Page:Moving to page:%x",pageInfo);
            }
            else {
                pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
                printDebug(DM_Alloc,"Merged Page:Moving to page:%x",pageInfo);
            }
        }
        int i = 0;
        PageInfo *pInfo = pageInfo;
        if (!isValidAddress(((char*)pInfo) + offset))
        {
            printError(ErrSysInternal,"Invalid address %x",((char*)pInfo) + offset);
            return NULL;
        }
        for (i = 0; i< multiple + 1; i++)
        {
            if (1 == pInfo->isUsed_) break;
            pInfo = (PageInfo*)((char*)pInfo + PAGE_SIZE);
        }
        if ( i == (multiple + 1))  break;
    }

    printDebug(DM_Alloc,"Database::getFreePage returning page:%x",pageInfo);
    setCurrentPage((Page*) pageInfo);
    return (Page*) pageInfo ;
}


//called only in case of system database to create and initialize the chunk
//information
DbRetVal Database::createSystemDatabaseChunk(AllocType type, size_t size, int id)
{

    Chunk *chunk;
    if (-1 == id )
    {
        printError(ErrSysFatal, "Database ID corrupted");
        return ErrSysFatal;
    }
    chunk = getSystemDatabaseChunk(id);

    if (FixedSizeAllocator == type) chunk->setSize(size);
    //getDatabaseMutex();
    if (chunk->allocSize_ > PAGE_SIZE)
        chunk->curPage_ = getFreePage(chunk->allocSize_);
    else
         chunk->curPage_ = getFreePage();
    if ( chunk->curPage_ == NULL)
    {
       //releaseDatabaseMutex();
       printError(ErrNoMemory, "No free pages in database: Database full");
       return ErrNoMemory;
    }

    chunk->firstPage_ = chunk->curPage_;
    PageInfo* firstPageInfo = ((PageInfo*)chunk->firstPage_);
    firstPageInfo->isUsed_ = 1;
    firstPageInfo->hasFreeSpace_ = 1;
    firstPageInfo->nextPageAfterMerge_ = NULL;
    firstPageInfo->nextPage_ = NULL;
    chunk->setChunkID(id);
    chunk->setAllocType(type);
    printDebug(DM_Database, "Creating System Database Chunk:%d Size:%d",id, chunk->allocSize_);
    if (chunk->allocSize_ > PAGE_SIZE)
    {
        int multiple = os::floor(chunk->allocSize_ / PAGE_SIZE);
        int offset = ((multiple + 1) * PAGE_SIZE);
        firstPageInfo->nextPageAfterMerge_ = ((char*)firstPageInfo)+ offset;
    }

    if (0 == size)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)firstPageInfo) + sizeof(PageInfo));
        varInfo->isUsed_ = 0;
        varInfo->size_ = PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo);

    }
    //releaseDatabaseMutex();
    return OK;
}

//This will never be called. If situation arises will be coded later.
DbRetVal Database::deleteSystemDatabaseChunk(int id)
{
    Chunk *chunk = getSystemDatabaseChunk(id);
    chunk->setChunkID(-1);
    chunk->setSize(0);
    chunk->setAllocType(UnknownAllocator);
    //TODO::
    //chunk->pageList_
    //walk though the pageList ptr and get all the page pointers
    //then free all the pages used to store this by setting the
    //start of page to notused
    chunk->firstPage_ = NULL;
    chunk->curPage_ = NULL;
    return OK;
}


void Database::createAllCatalogTables()
{
    //These are special chunks which hold catalog tables and other information
    //
    // chunk id 0 ->userChunkTable
    // chunk id 1 ->lockBucketHash
    // chunk id 2 ->lockTable
    //
    // chunk id 10->DATABASE
    // chunk id 11->USER
    // chunk id 12->TABLE
    // chunk id 13->FIELD
    // chunk id 14->ACCESS

    // chunk id 30->hash index on tblName_ of TABLE
    // chunk id 31->hash index on fldName_ of FIELD
    // chunk id 32->hash index on userName_ of ACCESS
    // chunk id 33->hash index on userName_ of USER
    // chunk id 34->hash index on dbName_ of DATABASE
    // chunk id 35->hash index on tblID_ of FIELD
    //
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(Chunk), UserChunkTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(Bucket) * LOCK_BUCKET_SIZE,
                                  LockTableHashBucketId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(Mutex)* LOCK_BUCKET_SIZE,
                                  LockTableMutexId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(LockHashNode), LockTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(TransHasNode), TransHasTableId);

    createSystemDatabaseChunk(VariableSizeAllocator,
                                  0, UndoLogTableID);

    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(DATABASEFILE), DatabaseTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(USER), UserTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(TABLE), TableTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(FIELD), FieldTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(ACCESS), AccessTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(INDEX), IndexTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(INDEXFIELD), IndexFieldTableId);
    
}

//used in case of system database
Chunk* Database::getSystemDatabaseChunk(int id)
{
    size_t offset = os::alignLong(sizeof (DatabaseMetaData)) +
                        id * sizeof (Chunk);
    return (Chunk*)(((char*) metaData_) +  offset);
}


//used in case of system database
Transaction* Database::getSystemDatabaseTrans(int slot)
{
    size_t offset = os::alignLong(sizeof (DatabaseMetaData)) +
                    os::alignLong(MAX_CHUNKS * sizeof (Chunk)) +
                        slot  * sizeof (Transaction);
    return (Transaction*)(((char*) metaData_) +  offset);
}

//used in case of system database
ProcInfo* Database::getProcInfo(int pidSlot)
{
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    offset = offset + os::alignLong( MAX_CHUNKS  * sizeof (Chunk));
    offset = offset + os::alignLong( config.getMaxTrans()   * sizeof(Transaction));
    offset = offset + pidSlot * sizeof (ProcInfo);
    return (ProcInfo*)(((char*) metaData_) +  offset);
}
//used in case of system database
ThreadInfo* Database::getThreadInfo(int pidSlot, int thrSlot)
{
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    offset = offset + os::alignLong( MAX_CHUNKS  * sizeof (Chunk));
    offset = offset + os::alignLong( config.getMaxTrans()   * sizeof(Transaction));
    offset = offset + os::alignLong( config.getMaxProcs() * sizeof(ProcInfo));
    offset = offset + pidSlot * thrSlot  * sizeof (ThreadInfo);
    return (ThreadInfo*)(((char*) metaData_) +  offset);
}

bool Database::isLastThread()
{
    DbRetVal rv = getProcessTableMutex();
    if (OK != rv)
    {
        printError(rv, "Unable to get process table mutex from Database::isLastThread()");
        return false;
    }
    pid_t pid = appPid;

    ThreadInfo *tInfo = getThreadInfo(pid, 0);
    int regThr = 0;
    for (int i=0; i < config.getMaxThreads(); i++)
    {
        if (0 != tInfo->thrid_) regThr++;
        tInfo++;
    }
    releaseProcessTableMutex();
    if (regThr < 1) return true;
    return false;
}


bool Database::isValidAddress(void* addr)
{
    if ((char*) addr > ((char*)getMetaDataPtr())  + getMaxSize())
        return false;
    else
        return true;
}

//should be called only on system database
void* Database::allocLockHashBuckets()
{
    Chunk *chunk = getSystemDatabaseChunk(LockTableHashBucketId);
    void *ptr = chunk->allocate(this);
    if (NULL == ptr)
    {
        printError(ErrNoMemory, "Chunk Allocation failed for lock hash bucket catalog table");
    }
    return ptr;
}

Bucket* Database::getLockHashBuckets()
{
    Chunk *tChunk = getSystemDatabaseChunk(LockTableHashBucketId);
    ChunkIterator iter = tChunk->getIterator();
    return (Bucket*)iter.nextElement();
}

