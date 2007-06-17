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
#include<DatabaseManager.h>
#include<DatabaseManagerImpl.h>
#include<os.h>
#include<Table.h>
#include<TableImpl.h>
#include<Transaction.h>
#include<CatalogTables.h>
#include<Index.h>
#include<Lock.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>


DatabaseManagerImpl::~DatabaseManagerImpl()
{
    //Note:Databases are closed by the session interface
    delete tMgr_;
    delete lMgr_;
}

void DatabaseManagerImpl::createLockManager()
{
    lMgr_ = new LockManager(systemDatabase_);
    return;
}

void DatabaseManagerImpl::createTransactionManager()
{

    tMgr_ = new TransactionManager();
    tMgr_->setFirstTrans(systemDatabase_->getSystemDatabaseTrans(0));
    return;
}

DbRetVal DatabaseManagerImpl::openSystemDatabase()
{
    DbRetVal rv = openDatabase(SYSTEMDB);
    if (rv != OK) return rv;
    systemDatabase_ = db_;
    db_ = NULL;
    if (NULL == systemDatabase_)
    {
        printError(ErrAlready, "Database is already opened");
        return ErrAlready;
    }
    printDebug(DM_Database, "Opened system database");
    logFinest(logger, "Opened system database");
    return OK;
}

DbRetVal DatabaseManagerImpl::closeSystemDatabase()
{
    Database *db  = db_;
    //make them to point to system database file descriptor
    //and database pointer
    db_ = systemDatabase_;
    closeDatabase();
    db_ = db;
    printDebug(DM_Database, "Closed system database");
    logFinest(logger, "Closed System database");
    return OK;
}

DbRetVal DatabaseManagerImpl::createDatabase(const char *name, size_t size)
{
    if (NULL != db_ )
    {
        printError(ErrAlready, "Database is already created");
        return ErrAlready;
    }
    caddr_t rtnAddr = (caddr_t) NULL;
    shared_memory_id shm_id = 0;

    char *startaddr = (char*)Conf::config.getMapAddress();
    shared_memory_key key = 0;
    if (0 == strcmp(name, SYSTEMDB))
    {
        
        key = Conf::config.getSysDbKey();
    }
    else
    {
        startaddr = startaddr + Conf::config.getMaxSysDbSize();
        key = Conf::config.getUserDbKey();
    }
    shm_id = os::shm_create(key, size, 0666);
    if (-1 == shm_id)
    {
        printError(ErrOS, "Shared memory create failed");
        return ErrOS;
    }

    void *shm_ptr = os::shm_attach(shm_id, startaddr, SHM_RND);
    rtnAddr  = (caddr_t) shm_ptr;
    if (rtnAddr < 0 || shm_ptr == (char*)0xffffffff)
    {
        printError(ErrOS, "Shared memory attach returned -ve value %d", rtnAddr);
        return ErrOS;
    }
    memset(shm_ptr, 0, size );
    db_ = new Database();
    printDebug(DM_Database, "Creating database:%s",name);

    //TODO:for user database do not have transtable and processtable mutex
    db_->setMetaDataPtr((DatabaseMetaData*)rtnAddr);
    db_->setDatabaseID(1);
    db_->setName(name);
    db_->setMaxSize(size);
    db_->setMaxChunks(MAX_CHUNKS);
    db_->initAllocDatabaseMutex();
    db_->initTransTableMutex();
    db_->initDatabaseMutex();
    db_->initProcessTableMutex();

    //compute the first page after book keeping information
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    //Only for system db chunk array, trans array and proc array will be there
    if (0 == strcmp(name, SYSTEMDB))
    {
        offset = offset + os::alignLong( MAX_CHUNKS  * sizeof (Chunk));
        offset = offset + os::alignLong( Conf::config.getMaxTrans()   * sizeof(Transaction));
        offset = offset + os::alignLong( Conf::config.getMaxProcs() * sizeof(ProcInfo));
        offset = offset + os::alignLong( Conf::config.getMaxProcs() * 
                                         Conf::config.getMaxThreads() * sizeof(ThreadInfo));
    }
    int multiple = os::floor(offset / PAGE_SIZE);
    char *curPage = (((char*)rtnAddr) + ((multiple + 1) * PAGE_SIZE));

    db_->setCurrentPage(curPage);
    db_->setFirstPage(curPage);

    if (0 == strcmp(name, SYSTEMDB)) return OK;

    //Allocate new chunk to store hash index nodes
    Chunk *chunkInfo = createUserChunk(sizeof(HashIndexNode));
    if (NULL == chunkInfo)
    {
        printError(ErrSysInternal, "Failed to allocate hash index nodes chunk");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Creating Chunk for storing Hash index nodes %x",
                                                                  chunkInfo);

    db_->setHashIndexChunk(chunkInfo);
    logFinest(logger, "Created database %s" , name);

    return OK;
}

DbRetVal DatabaseManagerImpl::deleteDatabase(const char *name)
{
    shared_memory_id shm_id = 0;
    if (0 == strcmp(name, SYSTEMDB))
    {
        shm_id = os::shm_open(Conf::config.getSysDbKey(), 100, 0666);
        os::shmctl(shm_id, IPC_RMID);
    } else {
        shm_id = os::shm_open(Conf::config.getUserDbKey(), 100, 0666);
        os::shmctl(shm_id, IPC_RMID);
    }
    logFinest(logger, "Deleted database %s" , name);
    return OK;
}


DbRetVal DatabaseManagerImpl::openDatabase(const char *name)
{
    long size = Conf::config.getMaxSysDbSize();
    char *startaddr = (char*)Conf::config.getMapAddress();
    if (0 == strcmp(name , SYSTEMDB))
    {
        if (NULL !=systemDatabase_)
        {
            printError(ErrAlready, "System Database already open");
            return ErrAlready;
        }
    }
    else
    {
        if (NULL ==systemDatabase_)
        {
            printError(ErrNotOpen, "System Database not open");
            return ErrNotOpen;
        }
        size = Conf::config.getMaxDbSize();
        startaddr = startaddr +  Conf::config.getMaxSysDbSize();
    }
    if (NULL != db_)
    {
        printError(ErrAlready, "User Database already open");
        return ErrAlready;
    }
    caddr_t attAddr;
    if (0 == strcmp(name, SYSTEMDB))
          attAddr = ProcessManager::sysAddr;
    else
          attAddr = ProcessManager::usrAddr;

    if (ProcessManager::noThreads == 0) 
    {
        //system db should be opened before user database files 
        caddr_t rtnAddr = (caddr_t) NULL;

        shared_memory_id shm_id = 0;
        shared_memory_key key = 0;

        if (0 == strcmp(name, SYSTEMDB))
            key = Conf::config.getSysDbKey();
        else
            key = Conf::config.getUserDbKey();
        shm_id = os::shm_open(key, size, 0666);
        if (shm_id == -1 )
        {
            printError(ErrOS, "Shared memory open failed");
            return ErrOS;
        }

        void *shm_ptr = os::shm_attach(shm_id, startaddr, SHM_RND);

        rtnAddr  = (caddr_t) shm_ptr;

        if (rtnAddr < 0 || shm_ptr == (char*)0xffffffff)
        {
            printError(ErrOS, "Shared memory attach returned -ve value %x %d", shm_ptr, errno);
            return ErrOS;
        } 
        else 
        {
            db_ = new Database();
            db_->setMetaDataPtr((DatabaseMetaData*)rtnAddr);
            if (0 == strcmp(name, SYSTEMDB))
                  ProcessManager::sysAddr = rtnAddr;
            else
                  ProcessManager::usrAddr = rtnAddr;

            printDebug(DM_Database, "Opening database: %s", name);
            logFinest(logger, "Opened database %s" , name);
            return OK;
        }
    }

    db_ = new Database();
    printDebug(DM_Database, "Opening database: %s", name);
    db_->setMetaDataPtr((DatabaseMetaData*)attAddr);
    logFinest(logger, "Opened database %s" , name);
    return OK;
}

DbRetVal DatabaseManagerImpl::closeDatabase()
{
    printDebug(DM_Database, "Closing database: %s",(char*)db_->getName());
    logFinest(logger, "Closed database");
    if (NULL == db_) 
    {
        printError(ErrAlready, "Database is already closed\n");
        return ErrAlready;
    }
    //check if this is the last thread to be deregistered. 
    if (ProcessManager::noThreads == 1)
    {
        os::shm_detach((char*)db_->getMetaDataPtr());
    }
    delete db_;
    db_ = NULL;
}
//Assumes that system database mutex is taken before calling this.
Chunk* DatabaseManagerImpl::createUserChunk(size_t size)
{
    //Allocate new node in system database to store
    Chunk *chunk = getSystemTableChunk(UserChunkTableId);
    void *ptr = chunk->allocate(systemDatabase_);
    if (NULL == ptr)
    {
         printError(ErrNoMemory, "Allocation failed for User chunk catalog table");
         return NULL;
    }
    Chunk *chunkInfo = (Chunk*)ptr;
    chunkInfo->initMutex();
    if (0 != size) chunkInfo->setSize(size);
    if (chunkInfo->allocSize_ > PAGE_SIZE)
        chunkInfo->curPage_ = db_->getFreePage(chunkInfo->allocSize_);
    else
        chunkInfo->curPage_ = db_->getFreePage();
    if ( NULL == chunkInfo->curPage_)
    {
        chunkInfo->destroyMutex();
        chunk->free(db_, ptr);
        printError(ErrNoMemory, "Database full: No space to allocate from database");
        return NULL;
    }
    PageInfo* firstPageInfo = ((PageInfo*)chunkInfo->curPage_);
    if (chunkInfo->allocSize_ > PAGE_SIZE)
    {
        int multiple = os::floor(chunkInfo->allocSize_ / PAGE_SIZE);
        int offset = ((multiple + 1) * PAGE_SIZE);
        firstPageInfo->setPageAsUsed(offset);
    }
    else
        firstPageInfo->setPageAsUsed(chunkInfo->allocSize_);
    if (0 == size)
    {
        VarSizeInfo *varInfo = (VarSizeInfo*)(((char*)firstPageInfo) + sizeof(PageInfo));
        varInfo->isUsed_ = 0;
        varInfo->size_ = PAGE_SIZE - sizeof(PageInfo) - sizeof(VarSizeInfo);

    }
    chunkInfo->firstPage_ = chunkInfo->curPage_;

    if (0 == size)
        chunkInfo->setAllocType(VariableSizeAllocator);
    else
        chunkInfo->setAllocType(FixedSizeAllocator);

    //TODO::Generate chunkid::use tableid
    chunkInfo->setChunkID(-1);
    printDebug(DM_Database, "Creating new User chunk chunkID:%d size: %d firstPage:%x",
                               -1, chunkInfo->allocSize_, firstPageInfo);

    return chunkInfo;
}


//Assumes that system database mutex is taken before calling this.
DbRetVal DatabaseManagerImpl::deleteUserChunk(Chunk *chunk)
{
    //Go to the pages and set them to notUsed
    Page *page = chunk->firstPage_;
    PageInfo* pageInfo = ((PageInfo*)page);
    //Here...sure that atleast one page will be there even no tuples
    //are inserted.so not checking if pageInfo == NULL
    while( pageInfo->nextPage_ != NULL)
    {
        PageInfo *prev = pageInfo;
        pageInfo = (PageInfo*)(pageInfo->nextPage_);
        //sets pageInfo->isUsed_ = 0 and pageInfo->hasFreeSpace_ = 0
        //and initializes the page content to zero
        if(NULL == pageInfo->nextPageAfterMerge_)
            os::memset(prev, 0, PAGE_SIZE);
        else
        {
            int size = (char*) pageInfo->nextPageAfterMerge_ - (char*) pageInfo;
            os::memset(prev, 0, size);
        }
        printDebug(DM_Database,"deleting user chunk:%x clearing page %x",chunk, prev);
    }
    //The above loop wont execute for the last page
    //and for the case where table has only one page
    if(NULL == pageInfo->nextPageAfterMerge_)
        os::memset(pageInfo, 0, PAGE_SIZE);
    else
    {
        int size = (char*) pageInfo->nextPageAfterMerge_ - (char*) pageInfo;
        os::memset(pageInfo, 0, size);
    }
    printDebug(DM_Database,"deleting user chunk:%x clearing page %x",chunk, pageInfo);
    chunk->chunkID_ = -1;
    chunk->allocSize_ = 0;
    chunk->curPage_ = NULL;
    chunk->firstPage_ = NULL;
    chunk->destroyMutex();
    printDebug(DM_Database,"deleting user chunk:%x",chunk);
    return OK;
}

//-1 -> Unable to create chunk. No memory
//-2 -> Unable to update the catalog tables
DbRetVal DatabaseManagerImpl::createTable(const char *name, TableDef &def)
{
    DbRetVal rv = OK;
    size_t sizeofTuple = def.getTupleSize();
    rv = systemDatabase_->getDatabaseMutex();
    if (OK != rv ) {
        printError(rv, "Unable to get Database mutex");
        return rv;
    }
    //create a chunk to store the tuples
    Chunk *ptr = createUserChunk(sizeofTuple);
    if (NULL  == ptr)
    {
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrNoResource, "Unable to create user chunk");
        return ErrNoResource;
    }
    printDebug(DM_Database,"Created UserChunk:%x", ptr);
    //add row to TABLE
    CatalogTableTABLE cTable(systemDatabase_);
    int tblID = ((Chunk*)ptr)->getChunkID();
    void *tptr = NULL;
    rv = cTable.insert(name, tblID, sizeofTuple,
                                   def.getFieldCount(), ptr, tptr);
    if (OK != rv)
    {
        deleteUserChunk(ptr);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to update catalog table TABLE");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Inserted into TABLE:%s",name);
    //add rows to FIELD
    FieldIterator iter = def.getFieldIterator();
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.insert(iter, tblID ,tptr);
    if (OK != rv)
    {
        deleteUserChunk(ptr);
        void *cptr, *ttptr;//Dummy as remove below needs both these OUT params
        cTable.remove(name, cptr, ttptr);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to update catalog table FIELD");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Inserted into FIELD:%s",name);
    systemDatabase_->releaseDatabaseMutex();
    printDebug(DM_Database,"Table Created:%s",name);
    logFinest(logger, "Table Created %s" , name);
    return OK;
}

//TODO::If any operation fails in between, then we may have some 
//dangling tuples, say we have have rows in INDEX table 
//which will not have any corresponding entries in TABLE 
//CHANGE the sequence so that it deletes from the bottom as 
//opposed to start from top as is written now
DbRetVal DatabaseManagerImpl::dropTable(const char *name)
{
    void *chunk = NULL;
    void *tptr =NULL;
    DbRetVal rv = systemDatabase_->getDatabaseMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //remove the entry in TABLE
    CatalogTableTABLE cTable(systemDatabase_);
    rv = cTable.remove(name, chunk, tptr);
    if (OK != rv) {
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to update catalog table TABLE");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from TABLE:%s",name);

    //remove the entries in the FIELD table
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.remove(tptr);
    if (OK != rv) {
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to update catalog table FIELD");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from FIELD:%s",name);

    rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv) {
        systemDatabase_->releaseDatabaseMutex();
        printError(rv, "Unable to delete the chunk");
        return rv;
    }
    printDebug(DM_Database,"Deleted UserChunk:%x", chunk);

    //TODO::check whether indexes are available and drop that also.
    CatalogTableINDEX cIndex(systemDatabase_);
    int noIndexes = cIndex.getNumIndexes(tptr);
    char *idxName;
    for (int i =1 ; i<= noIndexes; i++) {
        idxName = cIndex.getIndexName(tptr, i);
        dropIndexInt(idxName, false);
    }
    Chunk *chunkNode = systemDatabase_->getSystemDatabaseChunk(UserChunkTableId);
    chunkNode->free(systemDatabase_, (Chunk *) chunk);
    systemDatabase_->releaseDatabaseMutex();
    printDebug(DM_Database, "Deleted Table %s" , name);
    logFinest(logger, "Deleted Table %s" , name);
    return OK;
}

//Return values: NULL for table not found
Table* DatabaseManagerImpl::openTable(const char *name)
{
    DbRetVal ret = OK;
    //TODO::store table handles in list so that if it is
    //not closed by the application. destructor shall close it.
    TableImpl *table = new TableImpl();
    table->setDB(db_);
    table->setSystemDB(systemDatabase_);
    table->setLockManager(lMgr_);
    table->setTrans(&(tMgr_->trans));

    //to store the chunk pointer of table
    void *chunk = NULL;

    //to store the tuple pointer of the table
    void *tptr =NULL;

    //TODO::need to take shared lock on the table so that
    //all ddl operation will be denied on that table
    //which includes index creation, alter table

    DbRetVal rv = systemDatabase_->getDatabaseMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex");
        return NULL;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    ret = cTable.getChunkAndTblPtr(name, chunk, tptr);
    if ( OK != ret)
    {
        printError(ErrNotExists, "Table not exists %s", name);
        return NULL;
    }
    TABLE *tTuple = (TABLE*)tptr;
    table->setTableInfo(tTuple->tblName_, tTuple->tblID_, tTuple->length_,
                        tTuple->numFlds_, tTuple->numIndexes_, tTuple->chunkPtr_);

    //get field information from FIELD table
    CatalogTableFIELD cField(systemDatabase_);
    cField.getFieldInfo(tptr, table->fldList_);

    //get the number of indexes on this table
    //and populate the indexPtr array
    CatalogTableINDEX cIndex(systemDatabase_);
    table->numIndexes_ = cIndex.getNumIndexes(tptr);
    if (table->numIndexes_)
        table->indexPtr_ = new char*[table->numIndexes_];
    else
        table->indexPtr_ = NULL;
    cIndex.getIndexPtrs(tptr, table->indexPtr_);

    //HACK:Below works only for one hash index on table
    if (table->numIndexes_ == 1)
    {
        SingleFieldHashIndexInfo *hIdxInfo = new SingleFieldHashIndexInfo();
        CatalogTableINDEXFIELD cIndexField(systemDatabase_);
        cIndexField.getFieldNameAndType(table->indexPtr_[0], hIdxInfo->fldName,
                                                      hIdxInfo->type);
        ChunkIterator citer = CatalogTableINDEX::getIterator(table->indexPtr_[0]);
        hIdxInfo->noOfBuckets = CatalogTableINDEX::getNoOfBuckets(table->indexPtr_[0]);
        hIdxInfo->buckets = (Bucket*)citer.nextElement();

        table->idxInfo = (IndexInfo*) hIdxInfo;
    }
    systemDatabase_->releaseDatabaseMutex();
    printDebug(DM_Database,"Opening table handle name:%s chunk:%x numIndex:%d",
                                         name, chunk, table->numIndexes_);
    logFinest(logger, "Opening Table %s" , name);

    return table;
}

//Return values: -1 for table not found
void DatabaseManagerImpl::closeTable(Table *table)
{
    printDebug(DM_Database,"Closing table handle: %x", table);
    if (NULL == table) return;
    delete table;
    logFinest(logger, "Closing Table");
}

DbRetVal DatabaseManagerImpl::createIndex(const char *indName, IndexInitInfo *info)
{
    DbRetVal rv = OK;
    if (info->indType == hashIndex)
    {
        //Assumes info is of type HashIndexInitInfo
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createHashIndex(indName, info->tableName, info->list, hInfo->bucketSize);
    }
    else
    {
        //TODO::tree index
    }
    return rv;
}


//-1 -> Table does not exists
//-2 -> Field does not exists
//-3 -> bucketSize is not valid
DbRetVal DatabaseManagerImpl::createHashIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, int bucketSize)
{
    //validate the bucket size
    if (bucketSize < 100 || bucketSize > 200000)
    {
        printError(ErrBadRange, "Index Bucket size %d not in range 100-200000",
                                 bucketSize);
        return ErrBadRange;
    }
    void *tptr =NULL;
    void *chunk = NULL;
    DbRetVal rv = systemDatabase_->getDatabaseMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //check whether table exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr);
    if (NULL == tptr)
    {
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }
    int totFlds = fldList.size();

    //check whether field exists
    char **fptr = new char* [totFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(fldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrNotExists, "Field does not exist");
        return ErrNotExists;
    }

    //create chunk to store the meta data of the index created
    //for latches and bucket pointers
    Chunk* chunkInfo = createUserChunk(bucketSize * sizeof(Bucket));
    if (NULL == chunkInfo)
    {
        delete[] fptr;
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to create chunk");
        return ErrSysInternal;
    }
    //create memory for holding the bucket pointers
    void *buckets = chunkInfo->allocate(db_);
    if (NULL == buckets)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrNoMemory, "Unable to allocate memory for bucket");
        return ErrNoMemory;
    }
    Bucket *buck = (Bucket*) buckets;
    initHashBuckets(buck, bucketSize);

    //create chunk to store the hash index nodes
    Chunk* hChunk = createUserChunk(sizeof(HashIndexNode));
    if (NULL == hChunk)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to create chunk for storing hash index nodes");
        return ErrSysInternal;
    }


    //add row to INDEX
    void *tupleptr = NULL;
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal ret = cIndex.insert(indName, tptr, fldList.size(),
                        chunkInfo, bucketSize, hChunk, tupleptr);
    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    //add rows to INDEXFIELD
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    ret = cIndexField.insert(fldList, tupleptr, tptr, fptr);

    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    delete[] fptr;
    //TODO::If tuples present in this table, then
    //create hash index nodes and store it
    //Take table lock
    systemDatabase_->releaseDatabaseMutex();
    printDebug(DM_Database, "Creating Hash Index Name:%s tblname:%s buckets:%x",
                                   indName, tblName, buckets);
    logFinest(logger, "Creating HashIndex %s on %s with bucket size %d", 
                                   indName, tblName, buckets);
    return OK;
}

void DatabaseManagerImpl::initHashBuckets(Bucket *buck, int bucketSize)
{
    os::memset((void*)buck, 0, bucketSize * sizeof(Bucket));

    for (int i=0; i < bucketSize ; i++)
    {
        buck[i].mutex_.init();
    }
    return;
}

DbRetVal DatabaseManagerImpl::dropIndex(const char *name)
{
    return dropIndexInt(name, true);
}

DbRetVal DatabaseManagerImpl::dropIndexInt(const char *name, bool takeLock)
{
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    int ret = 0;
    if (takeLock) {
        rv = systemDatabase_->getDatabaseMutex();
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to get database mutex");
            return ErrSysInternal;
        }
    }

    //remove the entry in INDEX
    CatalogTableINDEX cIndex(systemDatabase_);
    rv = cIndex.remove(name, chunk, hchunk, tptr);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEX %s",name);
    //remove the entries in the INDEXFIELD table
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.remove(tptr);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEXFIELD %s",name);

    //delete the index chunk
    rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to delete the index chunk");
        return ErrSysInternal;
    }
    //delete the index hash node chunk
    rv = deleteUserChunk((Chunk*)hchunk);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseDatabaseMutex();
        printError(ErrSysInternal, "Unable to delete the index hash node chunk");
        return ErrSysInternal;
    }
    if (takeLock) systemDatabase_->releaseDatabaseMutex();
    Chunk *chunkNode = systemDatabase_->getSystemDatabaseChunk(UserChunkTableId);
    chunkNode->free(systemDatabase_, (Chunk *) chunk);
    chunkNode->free(systemDatabase_, (Chunk *) hchunk);

    //TODO::If tuples present in this table, then
    //free all hash index nodes for this table.
    //free all nodes in list of all buckets
    //Take table lock

    printDebug(DM_Database, "Dropped hash index %s",name);
    logFinest(logger, "Deleted Index %s", name);
    return OK;
}

DbRetVal DatabaseManagerImpl::registerThread()
{
    DbRetVal rv = OK;
    if (pMgr_ != NULL) 
    {
        printError(ErrAlready, "Process already registered\n");
        return ErrAlready;
    }
    pMgr_ = new ProcessManager(sysDb());
    return pMgr_->registerThread();
}

DbRetVal DatabaseManagerImpl::deregisterThread()
{
    if (pMgr_ == NULL) 
    {
        printError(ErrBadCall, "Process already deregistered or never registered\n");
        return ErrBadCall;
    }
    DbRetVal rv = pMgr_->deregisterThread();
    delete pMgr_;
    pMgr_ = NULL;
    return rv;
}

ChunkIterator DatabaseManagerImpl::getSystemTableIterator(CatalogTableID id)
{
    Chunk *fChunk = systemDatabase_->getSystemDatabaseChunk(id);
    return fChunk->getIterator();
}

Chunk* DatabaseManagerImpl::getSystemTableChunk(CatalogTableID id)
{
    return systemDatabase_->getSystemDatabaseChunk(id);
}
