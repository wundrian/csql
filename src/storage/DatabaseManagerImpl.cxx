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
//#include<TableConfig.h>
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
void DatabaseManagerImpl::setProcSlot()
{
    systemDatabase_->setProcSlot(procSlot);
    db_->setProcSlot(procSlot);
}
DbRetVal DatabaseManagerImpl::openSystemDatabase()
{
    DbRetVal rv = openDatabase(SYSTEMDB);
    if (rv != OK) return rv;
    systemDatabase_ = db_;
    db_ = NULL;
    printDebug(DM_Database, "Opened system database");
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
    return OK;
}

DbRetVal DatabaseManagerImpl::createDatabase(const char *name, size_t size)
{
    bool isMmapNeeded = Conf::config.useMmap();
    file_desc fd = (file_desc)-1;
    char cmd[1024];
    char dbMapFile[MAX_FILE_LEN];
    struct stat st;
    long fixAddr = MAP_ADDR_VALUE;
    bool firstTimeServer = false;
    if (NULL != db_ )
    {
        printError(ErrAlready, "Database is already created");
        return ErrAlready;
    }
    caddr_t rtnAddr = (caddr_t) NULL;
    void *mapAddr = NULL;
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
    if (!isMmapNeeded || (isMmapNeeded && 0 == strcmp(name, SYSTEMDB))) {
        shm_id = os::shm_create(key, size, 0660);  
        if (-1 == shm_id) {
            if (errno == EEXIST) {
#if (defined MMDB && defined EMBED)
                printError(ErrOS, "One application is already running.");
                return ErrOS;
#else
                printError(ErrOS, "Shared Memory already exists");
#endif
            }
            printError(ErrOS, "Shared memory create failed");
            exit(0);
        }
    } else {
        //switch the checkpoint
        if (Database::getCheckpointID() == 0)
            Database::setCheckpointID(1);
        else
            Database::setCheckpointID(0);
        int chkptID=Database::getCheckpointID();


        sprintf(dbMapFile, "%s/db.chkpt.data%d", Conf::config.getDbFile(), chkptID);
        fd = os::openFile(dbMapFile, fileOpenCreat, 0660);
        if ((file_desc) -1 == fd) { 
            printError(ErrOS, "Mmap file could not be opened");
            return ErrOS;
        }
        if(::stat(dbMapFile, &st) == -1) {
            printf("Unable to retrieve the db File data\n");
            os::closeFile(fd);
            db_->setChkptfd((file_desc)-1);
            return ErrOS;
        }
#ifdef WINNT
        int localfd = os::open(dbMapFile, fileOpenCreat,0);
#else
        int localfd = fd;
#endif
        if (st.st_size == 0 || st.st_size < size) {
            firstTimeServer = true;
            off_t flSize = os::lseek(localfd, size - 1, SEEK_SET); 
        }
        char *a = "0";
        int wSize = os::write(localfd, a, 1);
#ifdef WINNT
        os::close(localfd);
#endif
        mapAddr = os::mmap((void *)(fixAddr + Conf::config.getMaxSysDbSize()), size, 
				mapProtRead | mapProtWrite, mapFixed | mapShared, fd, 0);
        rtnAddr = (caddr_t) mapAddr;
        printDebug(DM_Database, "Mapped db file address = %x", mapAddr); 
    }
    void *shm_ptr = NULL;
    if (!isMmapNeeded || isMmapNeeded && 0 == strcmp(name, SYSTEMDB)) {
        shm_ptr = os::shm_attach(shm_id, startaddr, SHM_RND);
        rtnAddr  = (caddr_t) shm_ptr;
        if (rtnAddr < 0 || shm_ptr == (char*)0xffffffff)
        {
            printError(ErrOS, "Shared memory attach returned -ve value %d", rtnAddr);
            return ErrOS;
        }
# if (defined MMDB && defined EMBED)
        if (0 == strcmp(name, SYSTEMDB)) ProcessManager::sysAddr = rtnAddr;
        else ProcessManager::usrAddr = rtnAddr;
# endif
    }
    db_ = new Database();
    printDebug(DM_Database, "Creating database:%s",name);
    
    /*if (!isMmapNeeded || isMmapNeeded && 0 == strcmp(name, SYSTEMDB)) {
        memset(shm_ptr, 0, size );
    }*/

    db_->setMetaDataPtr((DatabaseMetaData*)rtnAddr);
    db_->setDatabaseID(1);
    db_->setName(name);
    db_->setMaxSize(size);
    initMutexes(db_);
    db_->setUniqueChunkID(100);                        
    //compute the first page after book keeping information
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    //Only for system db chunk array, trans array and proc array will be there
    if (0 == strcmp(name, SYSTEMDB))
    {
        db_->setCanTakeCheckPoint(true);
        offset = computeSysDbOffset();
    }
    int multiple = os::floor(offset / PAGE_SIZE);
    char *curPage = (((char*)rtnAddr) + ((multiple + 1) * PAGE_SIZE));

    db_->setCurrentPage(curPage);
    db_->setFirstPage(curPage);

    return OK;
}
size_t DatabaseManagerImpl::computeSysDbOffset()
{
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    offset = offset + os::alignLong(MAX_CHUNKS  * sizeof (Chunk));
    offset = offset + os::alignLong(Conf::config.getMaxProcs() * sizeof(Transaction));
    offset = offset + os::alignLong(Conf::config.getMaxProcs() * sizeof(ThreadInfo));
    return offset;
}
void DatabaseManagerImpl::initMutexes(Database *db_)
{
    //TODO:for user database do not have transtable and processtable mutex
    db_->setNoOfChunks(0);
    db_->initAllocDatabaseMutex();
    db_->initTransTableMutex();
    db_->initCheckpointMutex();
    db_->initProcessTableMutex();
    db_->initPrepareStmtMutex();
    return;
}

DbRetVal DatabaseManagerImpl::deleteDatabase(const char *name)
{
    shared_memory_id shm_id = 0;
    if (0 == strcmp(name, SYSTEMDB))
    {
        shm_id = os::shm_open(Conf::config.getSysDbKey(), 100, 0660);
        os::shm_remove(shm_id);
		delete systemDatabase_;
		systemDatabase_ = NULL;
    } else {
        shm_id = os::shm_open(Conf::config.getUserDbKey(), 100, 0660);
        os::shm_remove(shm_id);
		delete db_;
		db_ = NULL;
    }
    return OK;
}

DbRetVal DatabaseManagerImpl::openDatabase(const char *name)
{
    bool isMmapNeeded = Conf::config.useMmap();
    char dbMapFile[MAX_FILE_LEN];
    file_desc fd = (file_desc)-1;
    long size = Conf::config.getMaxSysDbSize();
    char *startaddr = (char*)Conf::config.getMapAddress();
    long fixAddr = MAP_ADDR_VALUE;
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
        fixAddr += Conf::config.getMaxSysDbSize();
    }
    if (NULL != db_)
    {
        printError(ErrAlready, "User Database already open");
        return ErrAlready;
    }
    //system db should be opened before user database files 
    caddr_t rtnAddr = (caddr_t) NULL;
    
    shared_memory_id shm_id = 0;
    shared_memory_key key = 0;

    if (0 == strcmp(name, SYSTEMDB))
        key = Conf::config.getSysDbKey();
    else
        key = Conf::config.getUserDbKey();


    void *shm_ptr = NULL;
    void *mapAddr = NULL;
    bool firstThread = false;
    if ( ( ProcessManager::noThreads == 0 && 0 == strcmp(name, SYSTEMDB) || 
          ProcessManager::noThreads == 1 && 0 != strcmp(name, SYSTEMDB) ) )
   {
        if(isMmapNeeded && 0 != strcmp(name, SYSTEMDB)){
            //: Attach to Map File 
            int curChkptID = Database::getCheckpointID();
            sprintf(dbMapFile, "%s/db.chkpt.data%d", Conf::config.getDbFile(), 
                                                     curChkptID);
            fd = os::openFile(dbMapFile, fileOpenReadWrite, 0660);
            if ((file_desc)-1 == fd) {
                printError(ErrOS, "Mmap file could not be opened");
                return ErrOS;
            }
            mapAddr = os::mmap((void *)fixAddr, size, mapProtRead | mapProtWrite, 
				mapFixed | mapShared, fd, 0);

            shm_ptr= (caddr_t) mapAddr;
            printDebug(DM_Database, "Mapped db file address = %x", mapAddr);
        }else
        {
            shm_id = os::shm_open(key, size, 0660);
            if (shm_id == -1 )
            {
                printError(ErrOS, "Shared memory open failed");
                return ErrOS;
            }
            shm_ptr = os::shm_attach(shm_id, startaddr, SHM_RND);
        }
        if (0 == strcmp(name, SYSTEMDB))
        {
            firstThread = true;
            ProcessManager::sysAddr = (char*) shm_ptr;
        }
        else
        {
            ProcessManager::usrAddr = (char*) shm_ptr;
        }
    } else {
        if (0 == strcmp(name, SYSTEMDB)) shm_ptr = ProcessManager::sysAddr;
        else shm_ptr = ProcessManager::usrAddr;
    }
    
    rtnAddr  = (caddr_t) shm_ptr;
#if defined (x86_64)
    if (rtnAddr < 0 || shm_ptr == (char*)0xffffffffffffffff)
    {
        printError(ErrOS, "Shared memory attach returned -ve value %x %d", shm_ptr, errno);
        return ErrOS;
    }
#else
    if (rtnAddr < 0 || shm_ptr == (char*)0xffffffff)
    {
        printError(ErrOS, "Shared memory attach returned -ve value %x %d", shm_ptr, errno);
        return ErrOS;
    }
#endif

    db_ = new Database();
    db_->setMetaDataPtr((DatabaseMetaData*)rtnAddr);
    db_->setChkptfd(fd);

    if (firstThread) ProcessManager::systemDatabase = db_;

    printDebug(DM_Database, "Opening database: %s", name);
    return OK;
}

DbRetVal DatabaseManagerImpl::closeDatabase()
{

    if (NULL == db_) 
    {
        //Database is already closed
        return OK;
    }
    printDebug(DM_Database, "Closing database: %s",(char*)db_->getName());
    //check if this is the last thread to be deregistered
    int ret =0;// ProcessManager::mutex.getLock(-1, false);
    //If you are not getting lock ret !=0, it means somebody else is there.
    //he will close the database.
    if (0 != strcmp((char*)db_->getName(),  SYSTEMDB)) {
        file_desc fd = db_->getChkptfd();
        os::closeFile(fd);
    }
    if (ret == 0) {
    if (ProcessManager::noThreads == 0 && 0 == strcmp((char*)db_->getName(), SYSTEMDB)
       || ProcessManager::noThreads == 1 && 0 != strcmp((char*)db_->getName(),  SYSTEMDB) )  {
                os::shm_detach((char*)db_->getMetaDataPtr());
            }
    }
    // ProcessManager::mutex.releaseLock(-1, false);
    delete db_;
    db_ = NULL;
    return OK;
}

//Assumes that system database mutex is taken before calling this.
Chunk* DatabaseManagerImpl::createUserChunk(size_t size)
{
    //Allocate new node in system database to store
    Chunk *chunk = getSystemTableChunk(UserChunkTableId);
    DbRetVal rv = OK;
    void *ptr = chunk->allocate(systemDatabase_, &rv);
    if (NULL == ptr)
    {
         printError(rv, "Allocation failed for User chunk catalog table");
         return NULL;
    }
    Chunk *chunkInfo = (Chunk*)ptr;
    int id = db_->getUniqueIDForChunk();
    db_->incrementChunk();
    chunkInfo->initMutex(id);
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
    {
        firstPageInfo->setPageAsUsed(chunkInfo->allocSize_);
        char *data = ((char*)firstPageInfo) + sizeof(PageInfo);
        *(InUse*)data =0;
    }
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

    chunkInfo->setChunkID(id);
    chunkInfo->setPageDirty(firstPageInfo);
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
        if(NULL == pageInfo->nextPageAfterMerge_){
            os::memset(prev, 0, PAGE_SIZE);
            SETBIT(prev->flags, IS_DIRTY);
            
        }
        else
        {
            int size = (char*) pageInfo->nextPageAfterMerge_ - (char*) pageInfo;
            char *iter = (char*)prev, *end=(char*)pageInfo->nextPageAfterMerge_;
            os::memset(prev, 0, size);
            //set dirty bit for all pages in merged pages
            while(iter <= end)
            {
                PageInfo *info = (PageInfo*) iter;
                SETBIT(info->flags, IS_DIRTY);
                iter = iter  + PAGE_SIZE;
            }
        }
        printDebug(DM_Database,"deleting user chunk:%x clearing page %x",chunk, prev);
    }
    //The above loop wont execute for the last page
    //and for the case where table has only one page
    if(NULL == pageInfo->nextPageAfterMerge_) {
        os::memset(pageInfo, 0, PAGE_SIZE);
        SETBIT(pageInfo->flags, IS_DIRTY);
    }
    else
    {
        int size = (char*) pageInfo->nextPageAfterMerge_ - (char*) pageInfo;
        char *iter = (char*)pageInfo, *end=(char*)pageInfo->nextPageAfterMerge_;
        os::memset(pageInfo, 0, size);
        //set dirty bit for all pages in merged pages
        while(iter <= end)
        {
            PageInfo *info = (PageInfo*) iter;
            SETBIT(info->flags, IS_DIRTY);
            iter = iter  + PAGE_SIZE;
        }
    }
    printDebug(DM_Database,"deleting user chunk:%x clearing page %x",chunk, pageInfo);
    chunk->chunkID_ = -1;
    chunk->allocSize_ = 0;
    chunk->curPage_ = NULL;
    chunk->firstPage_ = NULL;
    chunk->destroyMutex();
    db_->decrementChunk();
    Chunk *userChunk = getSystemTableChunk(UserChunkTableId);
    userChunk->free(systemDatabase_,chunk);
    printDebug(DM_Database,"deleting user chunk:%x",chunk);
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
    pMgr_ = new ProcessManager();
    rv = pMgr_->registerThread();
    if (rv ==OK) { 
        procSlot = pMgr_->getProcSlot();
        systemDatabase_->setProcSlot(procSlot);
        printDebug(DM_Process, "Process registed with slot %d\n", procSlot);
    }
    return rv;
}

DbRetVal DatabaseManagerImpl::deregisterThread()
{
    DbRetVal rv = OK;
    if (pMgr_ != NULL) 
    {
        rv = pMgr_->deregisterThread(procSlot);
        delete pMgr_;
        pMgr_ = NULL;
    }
    return rv;
}

bool DatabaseManagerImpl::isAnyOneRegistered()
{
    if (pMgr_ != NULL) return pMgr_->isAnyOneRegistered();
    return true;
}


void DatabaseManagerImpl::printUsageStatistics()
{
    pMgr_->printUsageStatistics();
    tMgr_->printUsageStatistics();
    lMgr_->printUsageStatistics();
}

void DatabaseManagerImpl::printDebugLockInfo()
{
    lMgr_->printDebugInfo();
}

void DatabaseManagerImpl::printDebugTransInfo()
{
    tMgr_->printDebugInfo(systemDatabase_);
}
void DatabaseManagerImpl::printDebugProcInfo()
{
    pMgr_->printDebugInfo();
}
void DatabaseManagerImpl::printDebugMutexInfo()
{
    Database *db = sysDb();
    db->printDebugMutexInfo();
    Chunk *chunk;
    int id=1;
    printf("<Chunk Mutexes>\n");
    chunk=db->getSystemDatabaseChunk(UserChunkTableId);
    while(id<MAX_CHUNKS)
    {
       chunk=db->getSystemDatabaseChunk(id);
       if((chunk->getChunkID())!=0){
          chunk->printMutexInfo();
       }
       id++;
    }
    chunk=db->getSystemDatabaseChunk(UserChunkTableId);
    size_t size=chunk->getSize();
    int noOfDataNodes=os::floor((PAGE_SIZE - sizeof(PageInfo))/size);
    Page* page=chunk->getFirstPage();
    int i=0;
    Chunk *chk;
    while(page)
    {
        char *data = ((char*)page) + sizeof(PageInfo);
        for (i = 0; i< noOfDataNodes; i++)
        {
            if (*((InUse*)data) == 1)
            {
                chk=(Chunk*)((InUse*)data+1);
                chk->printMutexInfo();
            }
            data = data + size;
        }
        page = (PageInfo*)(((PageInfo*)page)->nextPage_) ;
    }
    printf("</Chunk Mutexes>\n");
    lMgr_->printMutexInfo();
}
void DatabaseManagerImpl::printDebugChunkInfo()
{
    Database *db = sysDb();
    Chunk *chunk;
    int id=1;
    printf("<Chunk information>\n");
    printf("  <System Chunk >\n");
    chunk=db->getSystemDatabaseChunk(UserChunkTableId);
    chunk->print();
    while(id<MAX_CHUNKS)
    {
       chunk=db->getSystemDatabaseChunk(id);
       if((chunk->getChunkID())!=0){
          chunk->print();
       }
       id++;
    }
    printf("  </System Chunk >\n");
    printf("  <User Chunk >\n");
    chunk=db->getSystemDatabaseChunk(UserChunkTableId);
    size_t size=chunk->getSize();
    int noOfDataNodes=os::floor((PAGE_SIZE - sizeof(PageInfo))/size);
    Page* page=chunk->getFirstPage();
    int i=0;
    Chunk *chk;
    while(page)
    {
        char *data = ((char*)page) + sizeof(PageInfo);
        for (i = 0; i< noOfDataNodes; i++)
        {
            if (*((InUse*)data) == 1)
            {
                chk=(Chunk*)((InUse*)data+1);
                chk->print();
            }
            data = data + size;
        }
        page = (PageInfo*)(((PageInfo*)page)->nextPage_) ;
    }
    printf("  </User Chunk >\n");
    printf("</Chunk information>\n");
    return;
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

DbRetVal DatabaseManagerImpl::loadRecords(char *tblName, char *buffer)
{
    // buffer should be as big as the no of pages occupied by the records
    Table *tbl = openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    TableImpl *tb = (TableImpl *) tbl;
    char *bufIter = buffer;
    int pages = *(int *) bufIter; bufIter += sizeof(int);
    Page *firstPage = ((Chunk *)(tb->chunkPtr_))->getFirstPage(); 
    PageInfo *pi = (PageInfo *) firstPage;
    memcpy(bufIter, pi, PAGE_SIZE); 
    bufIter += PAGE_SIZE;
    for (int i = 0; i < pages - 1; i++) {
        Page *nPage = pi->nextPage_;
        memcpy(bufIter, nPage, PAGE_SIZE);
        bufIter += PAGE_SIZE;
        pi = (PageInfo *) nPage;
    }         
    closeTable(tbl);
    return OK;
}

DbRetVal DatabaseManagerImpl::pasteRecords(char *tblName, void *buffer)
{
    // buffer should be as big as the no of pages occupied by the records
    Table *tbl = openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    TableImpl *tb = (TableImpl *) tbl;
    Database *db = tb->getDB();
    char *bufIter = (char *) buffer;
    int pages = *(int *) bufIter;
    bufIter += sizeof(int);

    Page *firstPage = ((Chunk *)(tb->chunkPtr_))->getFirstPage(); 
    PageInfo *pi = (PageInfo *) firstPage;
    memcpy(pi, bufIter, PAGE_SIZE);
    bufIter += PAGE_SIZE; 
    while (--pages != 0) {
        //get a new page allocated
        Page *newPage = db->getFreePage();
        memcpy(newPage, bufIter, PAGE_SIZE);
        pi->nextPage_ = newPage;
        pi = (PageInfo *) newPage;
    }
    // initialize chunk details and pageInfo
    ((Chunk *)tb->chunkPtr_)->curPage_ = pi;
    closeTable(tbl);
    return OK;
}

void DatabaseManagerImpl::setCanTakeCheckPoint(bool ctcp)
{ systemDatabase_->setCanTakeCheckPoint(ctcp); }

bool DatabaseManagerImpl::getCanTakeCheckPoint()
{ return systemDatabase_->getCanTakeCheckPoint(); }

DbRetVal DatabaseManagerImpl::checkPoint()
{
    if (!systemDatabase_->getCanTakeCheckPoint()) {
        printf("Load / Cache / Replication process might be running. CheckPoint not taken\n");
        return ErrLoadingOn;
    }
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv ) {
        printError(rv, "Unable to get checkpoint mutex");
        return ErrLockTimeOut;
    }
    if (tMgr_ && !tMgr_->isTransactionConsistent(systemDatabase_)) {
        printf("not in transaction consistent point\n");
        systemDatabase_->releaseCheckpointMutex();
        return ErrLockTimeOut;
    }
    rv = writeSchemaFile();
    if (rv != OK) { 
        printError(ErrSysInternal, "checkpoint error"); 
    }
    rv = db()->checkPoint();
    systemDatabase_->releaseCheckpointMutex();
    return rv;
}

DbRetVal DatabaseManagerImpl::writeSchemaFile()
{
    DbRetVal rv = OK;
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    int fd = -1;
    char schFile[MAX_FILE_LEN];
    char mapFile[MAX_FILE_LEN];
    sprintf(schFile, "%s/db.chkpt.schema1", Conf::config.getDbFile());
    sprintf(mapFile, "%s/db.chkpt.map1", Conf::config.getDbFile());
    fp = fopen(schFile, "r");
    if (fp != NULL) {
        fclose(fp);
        int ret = unlink(schFile);
        if( ret != 0) { 
            printError(ErrOS, "checkpoint: delete schema file failed");
            return ErrOS;
        }
    }
    fp = fopen(schFile, "w+");
    if (fp == NULL) {
            printError(ErrOS, "Unable to create schema file for chkpt.");
            return ErrOS;
    }
    fp1 = fopen(mapFile, "r");
    if (fp1 != NULL) {
        fclose(fp1);
        int ret = unlink(mapFile);
        if( ret != 0) {
            printError(ErrOS, "checkpoint: delete schema file failed");
            return ErrOS;
        }
    }
    fd = open(mapFile, O_WRONLY|O_CREAT, 0644);
    if (fd == -1) { 
        printError(ErrOS, "checkpoint: Unable to create map file.");
        return ErrOS;
    }
    List tableList = getAllTableNames();
    ListIterator iter = tableList.getIterator();
    Identifier *elem = NULL;
    int count =0;
    while (iter.hasElement()) {
        elem = (Identifier*) iter.nextElement();
//        if (TableConf::config.isTableCached(elem->name) == OK) continue;
        fprintf(fp, "CREATE TABLE %s (", elem->name);
        Table *table = openTable(elem->name);
        if (NULL == table) {
            printError(ErrSysInternal, "Unable to open table %s", elem->name);
            return ErrSysInternal;
        }
        void *chunk = NULL; void *tptr = NULL; void *vcchunk = NULL;
        CatalogTableTABLE cTable(systemDatabase_);
        rv = cTable.getChunkAndTblPtr(elem->name, chunk, tptr, vcchunk);
        struct Object obj;
        strcpy(obj.name, elem->name);
        obj.type = Tbl;
        obj.bucketChunk = NULL;
        obj.firstPage = ((Chunk *)chunk)->getFirstPage();
        obj.curPage = ((Chunk *)chunk)->getCurrentPage();
        void *buf = &obj;
        write(fd, buf, sizeof(obj));
        FieldInfo *info = new FieldInfo();
        List fNameList = table->getFieldNameList();
        ListIterator fNameIter = fNameList.getIterator();
        count++;
        bool firstField=true;
        char fieldName[IDENTIFIER_LENGTH];
        while (fNameIter.hasElement()) {
            elem = (Identifier*) fNameIter.nextElement();
            Table::getFieldNameAlone(elem->name, fieldName);
            rv = table->getFieldInfo(elem->name, info);
            if (rv !=OK)  {
                printf("unable to retrive info for table %s\n", elem->name);
            }
            if (firstField) {
                fprintf(fp, "%s %s ", fieldName, AllDataType::getSQLString(info->type));
                firstField = false;
            } else
                fprintf(fp, ", %s %s ", fieldName, AllDataType::getSQLString(info->type));
            if (info->type == typeString || info->type == typeVarchar || 
                                                      info->type == typeBinary)
                fprintf(fp, "(%d)",info->length);
            if (info->isNull) fprintf(fp, " NOT NULL ");
            if (info->isDefault) fprintf(fp, " DEFAULT '%s' ", info->defaultValueBuf);
            if (info->isAutoIncrement) fprintf(fp, " AUTO_INCREMENT ");
        }
        fNameIter.reset();
        while (fNameIter.hasElement())
            delete ((Identifier *) fNameIter.nextElement());
        fNameList.reset();

        fprintf(fp, ");\n");
        table->printSQLIndexString(fp, fd);
        delete info;
        closeTable(table);
    }
    ListIterator tIter = tableList.getIterator();
    tIter.reset();
    while (tIter.hasElement())
        delete ((Identifier *) tIter.nextElement());
    tableList.reset();

    fclose(fp);
    close(fd);
    return OK;
}

DbRetVal DatabaseManagerImpl::recover()
{
    DbRetVal rv = OK;
    rv = sysDb()->recoverSystemDB();
    if (rv != OK) return rv;
    if (!Conf::config.useMmap())rv = db()->recoverUserDB();  
    return rv;
}

void DatabaseManagerImpl::sendSignal(int signal)
{
    ThreadInfo* tInfo = sysDb()->getThreadInfo(0);
    for (int i=0; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ !=0) os::kill(tInfo->pid_, signal);
        tInfo++;
    }
}
