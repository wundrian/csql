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
#include<HeapAllocator.h>

const char* Database::getName()
{
    return metaData_->dbName_;
}

int Database::getDatabaseID()
{
    return metaData_->dbID_;
}

long Database::getMaxSize()
{
    return metaData_->maxSize_;
}

long Database::getCurrentSize()
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
int Database::getNoOfChunks()
{
    return metaData_->noOfChunks_;
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
void Database::setCurrentSize(long size)
{
    metaData_->curSize_ = size;
}
void Database::setCurrentPage(Page *page)
{
    //metaData_->curPage_ = page;
    Mutex::CASL((long*)&metaData_->curPage_, (long)metaData_->curPage_, (long)page);
}
void Database::setFirstPage(Page *page)
{
    metaData_->firstPage_ = page;
}
void Database::setMaxSize(long size)
{
    metaData_->maxSize_ = size;
}
void Database::setNoOfChunks(int chunks)
{
    metaData_->noOfChunks_ = chunks;
}
void Database::setHashIndexChunk(Chunk *ch)
{
    metaData_->hashIndexChunk_ = ch;
}


int Database::initAllocDatabaseMutex()
{
    return metaData_->dbAllocMutex_.init("allocdb");
}
DbRetVal Database::getAllocDatabaseMutex(bool procAccount) 
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->dbAllocMutex_.getLock(procSlot, procAccount);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;
}
DbRetVal Database::releaseAllocDatabaseMutex(bool procAccount)
{
    metaData_->dbAllocMutex_.releaseLock(procSlot, procAccount);
    return OK;
}

int Database::initPrepareStmtMutex()
{
    return metaData_->dbPrepareStmtMutex_.init("prepstmt");
}
DbRetVal Database::getPrepareStmtMutex(bool procAccount) 
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->dbPrepareStmtMutex_.getLock(procSlot, procAccount);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}
DbRetVal Database::releasePrepareStmtMutex(bool procAccount)
{
    metaData_->dbPrepareStmtMutex_.releaseLock(procSlot, procAccount);
    return OK;
}

int Database::initTransTableMutex()
{
    return metaData_->dbTransTableMutex_.init("transtable");
}
DbRetVal Database::getTransTableMutex()
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->dbTransTableMutex_.getLock(procSlot);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}
DbRetVal Database::releaseTransTableMutex()
{
    metaData_->dbTransTableMutex_.releaseLock(procSlot);
    return OK;
}



int Database::initProcessTableMutex()
{
    return metaData_->dbProcTableMutex_.init("proctable");
}
DbRetVal Database::getProcessTableMutex(bool procAccount)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->dbProcTableMutex_.getLock(procSlot, procAccount);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}
DbRetVal Database::releaseProcessTableMutex(bool procAccount)
{
    metaData_->dbProcTableMutex_.releaseLock(procSlot, procAccount);
    return OK;
}

int Database::initCheckpointMutex()
{
    return metaData_->ckptMutex_.init("checkpoint");
}
DbRetVal Database::getSCheckpointMutex(bool procAccount)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->ckptMutex_.getShareLock(procSlot, procAccount);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}
DbRetVal Database::getXCheckpointMutex(bool procAccount)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = metaData_->ckptMutex_.getExclusiveLock(procSlot, procAccount);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}
DbRetVal Database::releaseCheckpointMutex(bool procAccount)
{
    metaData_->ckptMutex_.releaseShareLock(procSlot, procAccount);
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
    //Page* page = getCurrentPage();
    //printDebug(DM_Alloc, "Database::getFreePage firstPage:%x",page);
    printDebug(DM_Alloc, "Database::getFreePage currentpage:%x",page);
    PageInfo* pageInfo = ((PageInfo*)page);
    char* endAddr = ((char*)getMetaDataPtr())  + getMaxSize();
    int pageSize = PAGE_SIZE;
    bool isEndAddchk=false;
    while( 1 == pageInfo->isUsed_)
    {
        //If any pages are merged to store data larger than PAGE_SIZE
        //move to the next page after the merge and check whether it is used
        if ( pageInfo->nextPageAfterMerge_ == NULL) {
            pageInfo = (PageInfo*)((char*)pageInfo + pageSize);
            printDebug(DM_Alloc,"Normal Page:Moving to page:%x",pageInfo);
        }
        else {
            pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
            printDebug(DM_Alloc,"Merged Page:Moving to page:%x",pageInfo);
        }
        
        if((((char*) pageInfo) + pageSize) >= endAddr )
        {
            if(!isEndAddchk){ 
                isEndAddchk=true; 
                pageInfo=(PageInfo *)getFirstPage(); 
            }
            else
               break;
        }
        if ((char*)pageInfo >= endAddr)
        {
            //printError(ErrSysInternal,"Invalid address %x",pageInfo);
            return NULL;
        }

    }
    if (!isValidAddress(((char*) pageInfo) + pageSize))
    {
        printError(ErrSysInternal, "Invalid address %x",((char*) pageInfo) + pageSize);
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
    printDebug(DM_Alloc, "Database::getFreePage firstPage:%x size:%ld",page, size);
    char* endAddr = ((char*)getMetaDataPtr())  + getMaxSize();
    int pageSize = PAGE_SIZE;
    bool isEndAddchk = false;
    while(true){
        while( 1 == pageInfo->isUsed_)
        {
            //If any pages are merged to store data larger than PAGE_SIZE
            //move to the next page after the merge and check whether it is used
            if ( pageInfo->nextPageAfterMerge_ == NULL) {
                pageInfo = (PageInfo*)((char*)pageInfo + pageSize);
                printDebug(DM_Alloc,"Normal Page:Moving to page:%x",pageInfo);
            }
            else {
                pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
                printDebug(DM_Alloc,"Merged Page:Moving to page:%x",pageInfo);
            }
            if((((char*) pageInfo) + offset) >= endAddr )
            {
                if(!isEndAddchk){ 
                    isEndAddchk=true; 
                    pageInfo=(PageInfo *)getFirstPage(); 
                }
                else
                   break;
            }
        }
        int i = 0;
        PageInfo *pInfo = pageInfo;
        if ((((char*)pInfo) + offset) >= endAddr)
        {
            printError(ErrSysInternal,"Invalid address %x",((char*)pInfo) + offset);
            return NULL;
        }
        for (i = 0; i< multiple + 1; i++)
        {
            if (1 == pInfo->isUsed_) break;
            pInfo = (PageInfo*)((char*)pInfo + pageSize);
        }
        if ( i == (multiple + 1))  break;
        pageInfo = (PageInfo*)((char*)pInfo + pageSize);
    }

    printDebug(DM_Alloc,"Database::getFreePage returning page:%x",pageInfo);
    setCurrentPage((Page*) pageInfo);
    return (Page*) pageInfo ;
}

void Database::printStatistics()
{
    Page* page = getFirstPage();
    PageInfo* pageInfo = ((PageInfo*)page);
    int usedPageCount =0, usedMergedPageCount =0, totalPages=0;
    int totalDirtyPages=0;
    printf("<DatabaseStatistics>\n");
    printf("  <Database Name>  %s </Database Name>\n", getName());
    printf("  <Max Size> %ld </Max Size>\n", getMaxSize());
    printf("  <First Page> %x </First Page>\n", getFirstPage());
    while(isValidAddress((char*) pageInfo))
    {
        if (pageInfo == NULL) break;
        //if (pageInfo > getCurrentPage()) break;
        if (1 == pageInfo->isUsed_) {
           if ( pageInfo->nextPageAfterMerge_ == NULL) {
              if (BITSET(pageInfo->flags, IS_DIRTY)) totalDirtyPages++;
              pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
              usedPageCount++; totalPages++;
              printDebug(DM_Alloc, "Normal Page:Moving to page:%x\n",pageInfo);
              continue;
           }
           else {
              if (BITSET(pageInfo->flags, IS_DIRTY)) totalDirtyPages++;
              pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
              usedMergedPageCount++; totalPages++;
              printDebug(DM_Alloc,"Merged Page:Moving to page:%x\n",pageInfo);
              continue;
           }
        } else if (BITSET(pageInfo->flags, IS_DIRTY)) totalDirtyPages++;
        pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
        printDebug(DM_Alloc,"Normal Page not used:Moving to page:%x\n",pageInfo);
        totalPages++;
    }
    printf("  <Total Pages> %d </Total Pages>\n", totalPages);
    if (Conf::config.useDurability())
        printf("  <Dirty Pages> %d </Dirty Pages>\n", totalDirtyPages);
    printf("  <Used Normal Pages> %d </Used Normal Pages>\n", usedPageCount);
    printf("  <Used Merged Pages> %d </Used Merged Pages>\n", usedMergedPageCount);
    printf("  <Chunks Used> %d </Chunks Used>\n", getNoOfChunks());
    printf("</DatabaseStatistics>\n");

    return ;
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

    chunk->setChunkNameForSystemDB(id);

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
    firstPageInfo->setFirstPageAsUsed();
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
    incrementChunk();
    //releaseDatabaseMutex();
    return OK;
}

//This is never called currently. If situation arises will be coded later.
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
    decrementChunk();
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

    createSystemTables();
    createMetaDataTables();
}
void Database::createSystemTables()
{
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
}
void Database::createMetaDataTables()
{
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CDATABASEFILE), DatabaseTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CUSER), UserTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CTABLE), TableTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CFIELD), FieldTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CACCESS), AccessTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CINDEX), IndexTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CINDEXFIELD), IndexFieldTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CFK), ForeignKeyTableId);
    createSystemDatabaseChunk(FixedSizeAllocator,
                                  sizeof(CFKFIELD), ForeignKeyFieldTableId);
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

bool Database::isValidAddress(void* addr)
{
    if ((char*) addr >= ((char*)getMetaDataPtr())  + getMaxSize())
        return false;
    else
        return true;
}

//should be called only on system database
void* Database::allocLockHashBuckets()
{
    Chunk *chunk = getSystemDatabaseChunk(LockTableHashBucketId);
    DbRetVal rv=OK;
    void *ptr = chunk->allocate(this, &rv);
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
void Database::setUniqueChunkID(int id)
{
    (metaData_->chunkUniqueID_).setID(id);
}

int Database::getUniqueIDForChunk()
{
    return ((metaData_->chunkUniqueID_).getID());
}

DbRetVal Database::recoverMutex(Mutex *mut)
{
    //TODO: operations need to be undone before recovering the mutex.
    mut->recoverMutex();    
    return OK;
}
DbRetVal Database::writeDirtyPages(char *dataFile)
{
    int fd = os::openFile(dataFile, fileOpenCreat, 0);
    lseek(fd, 0, SEEK_SET);
    void *buf = (void *) metaData_;
    int sizeToWrite = os::alignLong(sizeof(DatabaseMetaData));
    size_t retSize = os::write(fd, (char*)buf, sizeToWrite);
    if (-1 == retSize)
    {
       printError(ErrWarning, "Warning:Unable to write metadata");
       return ErrSysInternal;
    }
    PageInfo *pageInfo = (PageInfo*) getFirstPage();
    long pageSize =PAGE_SIZE;
    int pagesWritten=0, writeOffset=0;
    long long totalBytesWritten=0;
    while(isValidAddress((char*) pageInfo))
    {
        if ( NULL == pageInfo ) break;
        if (pageInfo > getCurrentPage()) {
           char *a="0";
           ::lseek(fd, getMaxSize() -1, SEEK_SET);
           if ( -1 == os::write(fd, a, 1)) {
               printError(ErrSysInternal, "Unable to extend chkpt file");
               os::close(fd);
               return ErrSysInternal;
           }
           break;
        }
        if (BITSET(pageInfo->flags, IS_DIRTY)) {
            if (NULL == pageInfo->nextPageAfterMerge_)
                pageSize = PAGE_SIZE;
            else
                pageSize = (long)pageInfo->nextPageAfterMerge_ - (long)pageInfo;
            writeOffset = (long) pageInfo - (long) metaData_;
            ::lseek(fd, writeOffset, SEEK_SET);
            CLEARBIT(pageInfo->flags, IS_DIRTY);
            retSize = os::write(fd, (char*)pageInfo, pageSize);
            if ( -1  == retSize ) {
                printError(ErrSysInternal, "Unable to write dirty page %x", pageInfo);
                os::close(fd);
                return ErrSysInternal;
            }
            totalBytesWritten= totalBytesWritten + retSize;
            pagesWritten++;
        }
        if ( pageInfo->nextPageAfterMerge_ == NULL) {
           pageInfo = (PageInfo*)((char*)pageInfo + PAGE_SIZE);
        } else {
           pageInfo = (PageInfo*)pageInfo->nextPageAfterMerge_;
        }
    }
    //printf("Total Dirty pages written %d %lld\n", pagesWritten, totalBytesWritten);
    logFine(Conf::logger, "Total Dirty pages written %d\n", pagesWritten);
    os::close(fd);
    return OK;
}

DbRetVal Database::checkPoint()
{
    char dataFile[MAX_FILE_LEN];
    char cmd[MAX_FILE_LEN];
    char dbRedoFileName[MAX_FILE_LEN];
    sprintf(dbRedoFileName, "%s/csql.db.cur", Conf::config.getDbFile());
    if (!Conf::config.useMmap()) {
       // sprintf(dataFile, "%s/db.chkpt.data1", Conf::config.getDbFile());
        sprintf(dataFile, "%s/db.chkpt.data", Conf::config.getDbFile());
        FILE *fp = NULL;
        if (fp = fopen(dataFile, "r")) {
            fclose(fp);
            int ret = ::unlink(dataFile);
            if (ret != OK) {
                printError(ErrOS, "Unable to delete old chkpt file. Failure");
                return ErrOS;
            }
        }
        int fd = ::open(dataFile, O_WRONLY|O_CREAT, 0644);
        void *buf = (void *) metaData_;
        os::lseek(fd, 0, SEEK_SET);
        os::write(fd, (char*) buf, Conf::config.getMaxDbSize());
        os::close(fd);  
        sprintf(cmd, "cp -f %s/db.chkpt.data %s/db.chkpt.data1", Conf::config.getDbFile(), Conf::config.getDbFile());
        int ret = system(cmd);
        if (ret != 0) {
            printError(ErrOS, "Unable to take checkpoint back up file");
            return ErrOS;
        }
    } else {
        file_desc fd = getChkptfd();
        if (!os::fdatasync(fd)) { 
            logFine(Conf::logger, "fsync succedded"); 
        }
        filterAndRemoveStmtLogs();
        int ret = os::truncate(dbRedoFileName);
        if (ret != 0) {
            os::close(fd);  
            printError(ErrSysInternal, "Unable to truncate redo log file");
            printError(ErrSysInternal, "Delete %s manually and restart the server", dbRedoFileName);
            return ErrOS;
        }
        //switch the checkpoint so that during recovery, fsynced checkpoint is
        //used during recovery if the below step(writeDirtyPages)
        //is not completed succesfully.
        if (Database::getCheckpointID() == 0)
            Database::setCheckpointID(1);
        else
            Database::setCheckpointID(0);

        int val=Database::getCheckpointID();

        sprintf(dataFile, "%s/db.chkpt.data%d", Conf::config.getDbFile(), val);
        DbRetVal rv = writeDirtyPages(dataFile);
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to write dirty pages");
            os::closeFile(fd);  
            return rv;
        }

        //Note: do not change order, chkpt id should be switched only after 
        //all dirty pages are written to disk. otherwise(if server crashes
        //when it writes these dirty pages) recovery should use
        //mapped file as fsync is already done on that file.
        if (Database::getCheckpointID() == 0)
            Database::setCheckpointID(1);
        else
            Database::setCheckpointID(0);

        os::closeFile(fd);  
        return OK;
    }
    filterAndRemoveStmtLogs();
    int ret = os::truncate(dbRedoFileName);
    if (ret != 0) {
        printError(ErrSysInternal, "Unable to truncate redo log file. Delete and restart the server\n");
       return ErrOS;
    }
    return OK;
}
DbRetVal Database::filterAndRemoveStmtLogs()
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    file_desc fdRead = os::openFile(fName, fileOpenReadOnly,0);
    if ((file_desc)-1 == fdRead) { return OK; }
    if (::stat(fName, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        os::closeFile(fdRead);
        return ErrSysInternal;
    }
    if (st.st_size ==0) {
        os::closeFile(fdRead);
        return OK;
    }
   void *startAddr = os::mmap(NULL, st.st_size, mapProtRead, mapPrivate, fdRead, 0);
    if ((void*) MAP_FAILED == startAddr) {
        printError(ErrSysInternal, "Unable to mmap stmt log file\n");
        return ErrSysInternal;
    }
    sprintf(fName, "%s/csql.db.stmt1", Conf::config.getDbFile());
    int fd = os::openFileForAppend(fName, O_CREAT|O_TRUNC);
    char *iter = (char*)startAddr;
    char *logStart = NULL, *logEnd = NULL;
    int logType;
    int stmtID;
    int len =0, ret =0;
    int txnID, loglen;
    DbRetVal rv = OK;
    HashMap stmtMap;
    stmtMap.setKeySize(sizeof(int));
    //PASS-I load all prepare stmts and free them 
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        logStart = iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            len = *(int*) iter;
            iter = iter + 2 * sizeof(int);
            stmtID = *(int*)iter;
            stmtMap.insert(iter);
            iter = logStart+ len;
            ret =0;
        }
        else if(logType == -3) { //free
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            stmtMap.remove(iter);
            iter = iter + sizeof(int);
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }
    //PASS-II take the prepared statements which are not freed into another backup file
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        logStart = iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            len = *(int*) iter;
            iter = iter + 2 * sizeof(int);
            stmtID = *(int*)iter;
            iter = logStart+ len;
            ret =0;
            if (stmtMap.find(&stmtID))
                ret = os::write(fd, logStart, len);
            if (-1 == ret) {
                printError(ErrSysInternal, "Unable to write statement logs");
            }
        }
        else if(logType == -3) { //free
            iter = logStart + 4 *sizeof(int);
            //neglet free stmt logs in this pass
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }

    os::close(fd);
    os::munmap((char*)startAddr, st.st_size);
    os::closeFile(fdRead);
    stmtMap.removeAll();
    char cmd[MAX_FILE_LEN *2];
    sprintf(cmd, "mv %s/csql.db.stmt1 %s/csql.db.stmt",
                  Conf::config.getDbFile(), Conf::config.getDbFile());
    ret = system(cmd);
    return rv;
}
int Database::getCheckpointID()
{
    int id=0;
    char curCkptFile[MAX_FILE_LEN];
    sprintf(curCkptFile, "%s/db.chkpt.cur", Conf::config.getDbFile());
    FILE *fp = fopen(curCkptFile, "r");
    if (NULL == fp) { setCheckpointID(0); return 0; }
    fscanf(fp, "%d", &id);
    fclose(fp);
    return id;
}
void Database::setCheckpointID(int id)
{
    char curCkptFile[MAX_FILE_LEN];
    sprintf(curCkptFile, "%s/db.chkpt.cur", Conf::config.getDbFile());
    FILE *fp = fopen(curCkptFile, "w");
    if (NULL == fp) { 
 
        printError(ErrSysInternal, "Unable to set checkpointID");
        return;
    }
    fprintf(fp, "%d", id);
    logFine(Conf::logger, "Current checkpoint set to %d", id);
    fclose(fp);
    return;
}


//used only by the user database not the system database
DbRetVal Database::recoverUserDB()
{
    char dataFile[MAX_FILE_LEN];
    char cmd[MAX_FILE_LEN];
    sprintf(dataFile, "%s/db.chkpt.data", Conf::config.getDbFile());
    int fd = os::openFile(dataFile, fileOpenReadOnly, 0);
    if (-1 == fd) { return OK; }
    void *buf = (void *) metaData_;
    int readbytes = read(fd, buf, Conf::config.getMaxDbSize());
    if (readbytes == -1) { os::closeFile(fd); return ErrOS; }
    os::closeFile(fd);
    return OK;
}

//used only by the system database 
DbRetVal Database::recoverSystemDB()
{
    char mapFile[MAX_FILE_LEN];
    sprintf(mapFile, "%s/db.chkpt.map", Conf::config.getDbFile());
    int fd = open(mapFile, O_RDONLY);
    if (-1 == fd) { return OK; }
    CatalogTableTABLE cTable(this);
    CatalogTableINDEX cIndex(this);
    struct Object buf;
    while (read(fd, &buf, sizeof(buf))) {
        if (buf.type == Tbl) {
            cTable.setChunkPtr(buf.name, buf.firstPage, buf.curPage);
        }
        else if (buf.type == hIdx || buf.type == tIdx) {
            cIndex.setChunkPtr(buf.name, buf.type, buf.bucketChunk, buf.firstPage, buf.curPage);
        }
    }
    return OK;
}
