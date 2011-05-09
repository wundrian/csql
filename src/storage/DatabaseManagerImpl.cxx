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
#include<TableConfig.h>
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
/*    
    if (isMmapNeeded && !Conf::config.useDurability()) {
        printError(ErrBadArg, "If MMAP is set to true. Durability must be true.");
        return ErrBadArg;
    }
*/
    file_desc fd = (file_desc)-1;
    char cmd[1024];
    char dbMapFile[MAX_FILE_LEN];
    struct stat st;
    long fixAddr = 399998976L;
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
            if (errno == EEXIST) 
#if (defined MMDB && defined EMBED)
                printError(ErrOS, "One application is already running.");
            return ErrOS;
#else
                printError(ErrOS, "Shared Memory already exists");
#endif
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
        /*if (FILE *file = fopen(dbMapFile, "r")) {
            fclose(file);
            sprintf(cmd, "cp %s %s/db.chkpt.data", dbMapFile, Conf::config.getDbFile());
            int ret = system(cmd);
            if (ret != 0) { 
                printError(ErrOS, "could not copy data file to map file");
                return ErrOS;
            }
        }
        sprintf(dbMapFile, "%s/db.chkpt.data", Conf::config.getDbFile());
        */

        
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

    //TODO:for user database do not have transtable and processtable mutex
    db_->setMetaDataPtr((DatabaseMetaData*)rtnAddr);
    db_->setDatabaseID(1);
    db_->setName(name);
    db_->setMaxSize(size);
    db_->setNoOfChunks(0);
    db_->initAllocDatabaseMutex();
    db_->initTransTableMutex();
    db_->initCheckpointMutex();
    db_->initProcessTableMutex();
    db_->initPrepareStmtMutex();
    db_->setUniqueChunkID(100);                        
    //compute the first page after book keeping information
    size_t offset = os::alignLong(sizeof (DatabaseMetaData));
    //Only for system db chunk array, trans array and proc array will be there
    if (0 == strcmp(name, SYSTEMDB))
    {
        db_->setCanTakeCheckPoint(true);
        offset = offset + os::alignLong( MAX_CHUNKS  * sizeof (Chunk));
        offset = offset + os::alignLong( Conf::config.getMaxProcs()   * sizeof(Transaction));
        offset = offset + os::alignLong( Conf::config.getMaxProcs() * sizeof(ThreadInfo));
    }
    int multiple = os::floor(offset / PAGE_SIZE);
    char *curPage = (((char*)rtnAddr) + ((multiple + 1) * PAGE_SIZE));

    db_->setCurrentPage(curPage);
    db_->setFirstPage(curPage);

    if (0 == strcmp(name, SYSTEMDB)) return OK;

    /*Allocate new chunk to store hash index nodes
    Chunk *chunkInfo = createUserChunk(sizeof(IndexNode));
    if (NULL == chunkInfo)
    {
        printError(ErrSysInternal, "Failed to allocate hash index nodes chunk");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Creating Chunk for storing Hash index nodes %x",
                                                                  chunkInfo);

    db_->setHashIndexChunk(chunkInfo);*/
    return OK;
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
    char dbMapFile[1024];
    file_desc fd = (file_desc)-1;
    long size = Conf::config.getMaxSysDbSize();
    char *startaddr = (char*)Conf::config.getMapAddress();
    long fixAddr = 399998976L;
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

    //TODO::Generate chunkid::use tableid
    chunkInfo->setChunkID(db_->getUniqueIDForChunk());
    db_->incrementChunk();
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

//-1 -> Unable to create chunk. No memory
//-2 -> Unable to update the catalog tables
DbRetVal DatabaseManagerImpl::createTable(const char *name, TableDef &def)
{
    DbRetVal rv = OK;
    if (!Util::isIdentifier((char*)name)) {
        printError(ErrBadArg, "Invalid character for index name");
        return ErrBadArg;
    }
    int fldCount = def.getFieldCount();
    if(0==fldCount)
    {
        printError(ErrNotExists,"Table can't be created without Field");
        return ErrNotExists;
    }

    //If total field count is within 32, then 1 integer is used to store all 
    // null information, if it is more then 1 char is used to store null 
    // information of each field
    //This is to done to reduce cpu cycles for small tables
    int addSize = 0;
    if (fldCount <= 32) addSize = 4; else addSize = os::align(fldCount);
    size_t sizeofTuple = os::alignLong(def.getTupleSize()+addSize);
    rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv ) {
        printError(rv, "Unable to get Database mutex");
        return rv;
    }

    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;

    //check whether table already exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(name, chunk, tptr, vcchunk);
    if (NULL != tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrAlready, "Table %s already exists", name);
        return ErrAlready;
    }

    //create a chunk to store the tuples
    Chunk *ptr = createUserChunk(sizeofTuple);
    if (NULL  == ptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNoResource, "Unable to create user chunk");
        return ErrNoResource;
    }
    printDebug(DM_Database,"Created UserChunk:%x", ptr);
    ptr->setChunkName(name);
    //add row to TABLE
    int tblID = ((Chunk*)ptr)->getChunkID();

    //check whether varchar is present in table
    FieldIterator fiter = def.getFieldIterator();
    bool isVarcharPresent = def.isVarcharPresentInSchema(fiter);
    Chunk *vcptr = NULL;
    if (isVarcharPresent) {
        //creat chunk to store varchar values
        vcptr = createUserChunk();
        if (NULL  == vcptr)
        {
            deleteUserChunk(ptr);
            systemDatabase_->releaseCheckpointMutex();
            printError(ErrNoResource, "Unable to create user chunk for varchar");
            return ErrNoResource;
        }
        printDebug(DM_Database,"Created UserChunk for Varchar:%x", vcptr);
        vcptr->setChunkName(name);
    }
    rv = cTable.insert(name, tblID, sizeofTuple,
                                   def.getFieldCount(), ptr, tptr, vcptr);
    if (OK != rv)
    {
        deleteUserChunk(ptr);
        if (vcptr) deleteUserChunk(vcptr);
        systemDatabase_->releaseCheckpointMutex();
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
        if (vcptr) deleteUserChunk(vcptr);
        void *cptr, *ttptr;//Dummy as remove below needs both these OUT params
        cTable.remove(name, cptr, ttptr);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to update catalog table FIELD");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Inserted into FIELD:%s",name);
    systemDatabase_->releaseCheckpointMutex();
    printDebug(DM_Database,"Table Created:%s",name);
    logFinest(Conf::logger, "Table Created %s" , name);
    return OK;
}
DbRetVal DatabaseManagerImpl::renameTable(const char *oldName,const char *newName)
{
    void *chunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex for rename table");
        return ErrSysInternal;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    rv = cTable.renameTable(oldName,newName);
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to rename table");
        systemDatabase_->releaseCheckpointMutex();
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    return OK;
}
DbRetVal DatabaseManagerImpl::renameIndex(const char *oldName,const char *newName)
{
    void *chunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex for rename table");
        return ErrSysInternal;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    rv = cTable.renameIndex(oldName,newName);
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to rename table");
        systemDatabase_->releaseCheckpointMutex();
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    return OK;
}

DbRetVal DatabaseManagerImpl::renameField(const char *tableName,const char *oldName,const char *newName)
{
   DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex for rename table");
        return ErrSysInternal;
    }
    CatalogTableFIELD fTable(systemDatabase_);
    rv = fTable.renameField(tableName, oldName, newName);
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to rename field.");
        systemDatabase_->releaseCheckpointMutex();
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    return rv;
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
    void *vcchunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }
    //remove the entry in TABLE
    CatalogTableTABLE cTable(systemDatabase_);
    rv = cTable.getChunkAndTblPtr(name, chunk, tptr, vcchunk);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Table %s does not exist", name);
        return ErrSysInternal;
    }
    CatalogTableFK cFK(systemDatabase_);
    int noOfRelation =cFK.getNumFkTable(tptr);
    if(noOfRelation)
    {
        printError(ErrSysInternal, "Unable to drop table due to relation exist.Drop child table...");
        systemDatabase_->releaseCheckpointMutex();
        return ErrSysInternal;
    }
    rv = lMgr_->getExclusiveLock(chunk, NULL);
    if (rv !=OK)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrLockTimeOut, "Unable to acquire exclusive lock on the table\n");
        return rv;
    }

    rv = cTable.remove(name, chunk, tptr);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to update catalog table TABLE");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from TABLE:%s",name);

    //remove the entries in the FIELD table
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.remove(tptr);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to update catalog table FIELD");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from FIELD:%s",name);

    rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
        printError(rv, "Unable to delete the chunk");
        return rv;
    }
    printDebug(DM_Database,"Deleted UserChunk:%x", chunk);
   
    if (vcchunk != NULL) {
        rv = deleteUserChunk((Chunk*)vcchunk);
        if (OK != rv) {
            systemDatabase_->releaseCheckpointMutex();
            printError(rv, "Unable to delete the chunk");
            return rv;
        }
        printDebug(DM_Database,"Deleted UserChunk for Varchar:%x", chunk);
    }

    //TODO::check whether indexes are available and drop that also.
    CatalogTableINDEX cIndex(systemDatabase_);
    int noIndexes = cIndex.getNumIndexes(tptr);
    for (int i =1 ; i<= noIndexes; i++) {
        char *idxName = cIndex.getIndexName(tptr, 1);
        dropIndexInt(idxName, false);
    }
    bool isFkExist=cFK.isFkTable(tptr);
    if(isFkExist)
    {
       dropForeignKey(tptr,false);
    }
    systemDatabase_->releaseCheckpointMutex();
    printDebug(DM_Database, "Deleted Table %s" , name);
    logFinest(Conf::logger, "Deleted Table %s" , name);
    rv = lMgr_->releaseLock(chunk);
    if (rv !=OK)
    {
        printError(ErrLockTimeOut, "Unable to release exclusive lock on the table\n");
        return rv;
    }
    return OK;
}

//Return values: NULL for table not found
Table* DatabaseManagerImpl::openTable(const char *name,bool checkpkfk)
{
    DbRetVal ret = OK;
    //TODO::store table handles in list so that if it is
    //not closed by the application. destructor shall close it.
    TableImpl *table = new TableImpl();
    table->setDB(db_);
    table->setSystemDB(systemDatabase_);
    table->setLockManager(lMgr_);
    table->setTrans(ProcessManager::getThreadTransAddr(systemDatabase_->procSlot));

    //to store the chunk pointer of table
    void *chunk = NULL;
    void *vcchunk = NULL;

    //to store the tuple pointer of the table
    void *tptr =NULL;

    //TODO::need to take shared lock on the table so that
    //all ddl operation will be denied on that table
    //which includes index creation, alter table

    DbRetVal rv = systemDatabase_->getAllocDatabaseMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get database mutex");
        delete table;
        return NULL;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    ret = cTable.getChunkAndTblPtr(name, chunk, tptr, vcchunk);
    if ( OK != ret)
    {
        systemDatabase_->releaseAllocDatabaseMutex();
        delete table;
        printError(ErrNotExists, "Table not exists %s", name);
        return NULL;
    }
    CTABLE *tTuple = (CTABLE*)tptr;
    table->setTableInfo(tTuple->tblName_, tTuple->tblID_, tTuple->length_,
                        tTuple->numFlds_, tTuple->numIndexes_, 
                        tTuple->chunkPtr_, tTuple->varcharChunkPtr_);
    /*rv = table->lock(true); //take shared lock
    if (rv !=OK)
    {
        printError(ErrLockTimeOut, "Unable to acquire shared lock on the table\n");
        systemDatabase_->releaseAllocDatabaseMutex();
        delete table;
        return NULL;
    }*/


    if (tTuple->numFlds_ <= 32) 
    { 
        table->isIntUsedForNULL = true;
        table->iNullInfo = 0;
        table->iNotNullInfo =0;
    }
    else
    {
        table->isIntUsedForNULL = false;
        int noFields = os::align(tTuple->numFlds_);
        table->cNullInfo = (char*) malloc(noFields);
        table->cNotNullInfo = (char*) malloc(noFields);
        for (int i =0 ; i < noFields; i++) table->cNullInfo[i] =0;
        for (int i =0 ; i < noFields; i++) table->cNotNullInfo[i] =0;

    }

    //get field information from FIELD table
    CatalogTableFIELD cField(systemDatabase_);
    table->ptrToAuto = cField.getFieldInfo(tptr, table->fldList_);

    //populate the notnull info
    FieldIterator fIter = table->fldList_.getIterator();
    int fldpos=1;
    while (fIter.hasElement())
    {
        FieldDef *def = fIter.nextElement();
        if (table->isIntUsedForNULL) {
            if (def->isNull_) SETBIT(table->iNotNullInfo, fldpos-1);
        }
        else {
            if (def->isNull_) table->cNotNullInfo[fldpos-1] = 1;
        }
        fldpos++;
   } 

    //get the number of indexes on this table
    //and populate the indexPtr array
    CatalogTableINDEX cIndex(systemDatabase_);
    table->numIndexes_ = cIndex.getNumIndexes(tptr);
    if (table->numIndexes_) {
        table->indexPtr_ = new char*[table->numIndexes_];
        table->idxInfo = new IndexInfo*[table->numIndexes_];
    }
    else
    {
        table->indexPtr_ = NULL;
    }
    cIndex.getIndexPtrs(tptr, table->indexPtr_);
    for (int i =0 ; i < table->numIndexes_; i++ )
    {
        HashIndexInfo *hIdxInfo = new HashIndexInfo();
        CatalogTableINDEXFIELD cIndexField(systemDatabase_);
        cIndexField.getFieldInfo(table->indexPtr_[i], hIdxInfo->idxFldList);
        ChunkIterator citer = CatalogTableINDEX::getIterator(table->indexPtr_[i]);
        hIdxInfo->indexPtr = table->indexPtr_[i];
        hIdxInfo->indType = ((CINDEX*)hIdxInfo->indexPtr)->indexType_;
        hIdxInfo->noOfBuckets = CatalogTableINDEX::getNoOfBuckets(table->indexPtr_[i]);
        FieldIterator fIter = hIdxInfo->idxFldList.getIterator();
        bool firstFld = true;
        while (fIter.hasElement())
        {
            FieldDef *def = fIter.nextElement();
            if (firstFld)
            {
                hIdxInfo->fldOffset = table->fldList_.getFieldOffset(def->fldName_);
                hIdxInfo->type = table->fldList_.getFieldType(def->fldName_);
                hIdxInfo->compLength = table->fldList_.getFieldLength(def->fldName_);
                firstFld = false;
            }else {
                hIdxInfo->type = typeComposite;
                hIdxInfo->compLength = hIdxInfo->compLength +
                         table->fldList_.getFieldLength(def->fldName_);
            }
        }

        hIdxInfo->isUnique = CatalogTableINDEX::getUnique(table->indexPtr_[i]);
        hIdxInfo->buckets = (Bucket*)citer.nextElement();
        table->idxInfo[i] = (IndexInfo*) hIdxInfo;
    }
    systemDatabase_->releaseAllocDatabaseMutex();
    //Foreign key Operation
    if(checkpkfk){
        CatalogTableFK cFk(systemDatabase_);
        int totalFld=0;
        table->numFkRelation_ = cFk.getNumFkTable(tptr);
        if (table->numFkRelation_) {
            table->isPkTbl=true;//TODO:for Delete In casecade
            totalFld=cFk.getNoOfFkTable(tptr);
            //printDebug(DM_TEST,"Total table is %d\n",totalFld);
            char **fptr = new char* [totalFld];
            cFk.getFkTableName(tptr,fptr);
            for(int count=0; count < totalFld; count++){
               //printDebug(DM_TEST,"FK Name is %s\n",fptr[count]);
               Table *pkTable=openTable(fptr[count],false);
               if (pkTable) table->tblFkList.append(pkTable);
               else {
                   printError(ErrSysInternal, "Unable to open foreign key tables");
                   delete[] fptr;
                   pkTable->close();
                   return NULL;
               }
            }
            delete[] fptr;
        
        }
        char *tblName = NULL;
        table->isFkTbl = cFk.isFkTable(tptr);
        if(table->isFkTbl)
        {
            totalFld=cFk.getNoOfPkTable(tptr);
            char **fptr = new char* [totalFld];
            cFk.getPkTableName(tptr,fptr);
            for(int count=0; count<totalFld; count++){
                //printDebug(DM_TEST,"Parent Name is %s\n",fptr[count]);
                Table *fkTable = openTable(fptr[count],false);
                if (fkTable) table->tblList.append(fkTable);
                else {
                   printError(ErrSysInternal, "Unable to open foreign key tables");
                   delete[] fptr;
                   fkTable->close();
                   return NULL;
               }
            }
            delete[] fptr;
        }
    }
    printDebug(DM_Database,"Opening table handle name:%s chunk:%x numIndex:%d",
                                         name, chunk, table->numIndexes_);
    logFinest(Conf::logger, "Opening Table %s" , name);
    return table;
}

List DatabaseManagerImpl::getAllTableNames(int *retval)
{
    DbRetVal ret = OK;
    //to store the tuple pointer of the table
    void *tptr =NULL;

    /*DbRetVal rv = systemDatabase_->getSCheckpointMutex();
    if (OK != rv) {
        printError(ErrSysInternal, "Unable to get checkpoint mutex");
        if(retval) *retval = rv;
        List tableList;
        return tableList;
    }*/
    CatalogTableTABLE cTable(systemDatabase_);
    List tableList = cTable.getTableList();
    //systemDatabase_->releaseCheckpointMutex();
    return tableList;
}




//Return values: -1 for table not found
void DatabaseManagerImpl::closeTable(Table *table)
{
    printDebug(DM_Database,"Closing table handle: %x", table);
    if (NULL == table) return;
    //table->unlock();
 /*   TableImpl *fkTbl =NULL;
    ListIterator tblIter = ((TableImpl*)table)->tblList.getIterator();
    tblIter.reset();
    while (tblIter.hasElement()){
        fkTbl = (TableImpl *) tblIter.nextElement();
        closeTable(fkTbl);
    }
    ((TableImpl*)table)->tblList.reset();
    tblIter = ((TableImpl*)table)->tblFkList.getIterator();
    tblIter.reset();
    while (tblIter.hasElement()){
        fkTbl = (TableImpl *) tblIter.nextElement();
        closeTable(fkTbl);
    }
    ((TableImpl*)table)->tblFkList.reset();*/
    if (table) delete table; table = NULL;
    logFinest(Conf::logger, "Closing Table");
}

DbRetVal DatabaseManagerImpl::createIndex(const char *indName, IndexInitInfo *info)
{
    DbRetVal rv = OK;
    if (!info->isUnique && info->isPrimary) 
    {
        printError(ErrBadCall, "Primary key cannot be non unique\n");
        return ErrBadCall;
    }
    if (!Util::isIdentifier((char*)indName)) {
        printError(ErrBadArg, "Invalid character for index name");
        return ErrBadArg;
    }

    if (info->indType == hashIndex)
    {
        //Assumes info is of type HashIndexInitInfo
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createHashIndex(indName, info->tableName, info->list, hInfo->bucketSize,
                             info->isUnique, info->isPrimary);
    }
    else if (info->indType == treeIndex)
    {
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createTreeIndex(indName, info->tableName, info->list, 
                          hInfo->bucketSize, info->isUnique, info->isPrimary);
    }
    else if (info->indType == trieIndex)
    {
        HashIndexInitInfo *hInfo = (HashIndexInitInfo*) info;
        rv = createTrieIndex(indName, info->tableName, info->list, 
                          info->isUnique, info->isPrimary);

    }else {
        printError(ErrBadCall, "Index type not supported\n");
        return ErrBadCall;
    }
    return rv;
}


//-1 -> Table does not exists
//-2 -> Field does not exists
//-3 -> bucketSize is not valid
DbRetVal DatabaseManagerImpl::createHashIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, int bucketSize, bool isUnique, bool isPrimary)
{
    //validate the bucket size
    if (bucketSize < 100 || bucketSize > 200000)
    {
        printError(ErrBadRange, "Index Bucket size %d not in range 100-200000",
                                 bucketSize);
        return ErrBadRange;
    }
    int totFlds = fldList.size();
    if (totFlds == 0) 
    {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
    }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //check whether table exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }

    //check whether field exists
    char **fptr = new char* [totFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(fldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        //TODO::check test cases of dbapi/Index, they give wrong results
        //if (rv == ErrBadCall) {
        ////    if (isPrimary) printError(ErrBadCall, "Field can have NULL values");
        //} else {
        //printError(ErrNotExists, "Field does not exist");
        //} 
        //return ErrBadCall;
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    for (int i=0; i <totFlds; i++)
    {
        CFIELD* fInfo = (CFIELD*)fptr[i];
        if (fInfo->type_ == typeFloat || fInfo->type_ == typeDouble || fInfo->type_ == typeTimeStamp) 
        {
            printError(ErrBadArg, "HashIndex cannot be created for float or double or timestamp type");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
        if (!fInfo->isNull_ && isPrimary ) 
        {
            printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
	 if(isPrimary){fInfo->isPrimary_=true;fInfo->isUnique_=true;}
	 if(isUnique){fInfo->isUnique_=true;}
    }
    //create chunk to store the meta data of the index created
    //for latches and bucket pointers
    printDebug(DM_HashIndex, "Creating chunk for storing hash buckets of size %d\n", 
                             bucketSize * sizeof(Bucket));
    Chunk* chunkInfo = createUserChunk(bucketSize * sizeof(Bucket));
    if (NULL == chunkInfo)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk");
        return ErrSysInternal;
    }
    chunkInfo->setChunkName(indName);
    //create memory for holding the bucket pointers
    void *buckets = chunkInfo->allocate(db_, &rv);
    if (NULL == buckets)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(rv, "Unable to allocate memory for bucket");
        return rv;
    }
    Bucket *buck = (Bucket*) buckets;
    initHashBuckets(buck, bucketSize);

    //create chunk to store the hash index nodes
    Chunk* hChunk = createUserChunk(sizeof(IndexNode));
    if (NULL == hChunk)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk for storing hash index nodes");
        return ErrSysInternal;
    }

     hChunk->setChunkName(indName);
    //add row to INDEX
    void *tupleptr = NULL;
    CatalogTableINDEX cIndex(systemDatabase_);
    rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, bucketSize, hChunk, tupleptr);
    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    //add rows to INDEXFIELD
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);

    if (OK != rv)
    {
        delete[] fptr;
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        deleteUserChunk(hChunk);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    delete[] fptr;
    systemDatabase_->releaseCheckpointMutex();
    
    //TODO:: Take table lock

    // Following code is written by Kishor Amballi
    TableImpl *tbl = (TableImpl *) openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    if (! tbl->numTuples()) { 
        printDebug(DM_Database, "Creating Hash Index Name:%s tblname:%s buckets:%x", indName, tblName, buckets);
        logFinest(Conf::logger, "Creating HashIndex %s on %s with bucket size %d", indName, tblName, buckets);
        closeTable(tbl);
        return OK;
    }
    HashIndexInfo *indxInfo = NULL;
    int i = 0;
    for (i = 0; i < tbl->numIndexes_; i++) {
        if(((HashIndexInfo *)tbl->idxInfo[i])->indexPtr == tupleptr) {
            indxInfo = (HashIndexInfo *) tbl->idxInfo[i];  
            break;
        }
    }
    void *recPtr = NULL;
    ChunkIterator chIter = ((Chunk *)chunk)->getIterator();
    tbl->setLoading(true);
    while ((recPtr = chIter.nextElement()) != NULL) {
        rv = tbl->insertIndexNode(*tbl->trans, tupleptr, indxInfo, recPtr);
        if (rv == ErrUnique) {
            closeTable(tbl);
            dropIndex(indName);
            return rv;
        }
    }
    closeTable(tbl);
    printDebug(DM_Database, "Creating Hash Index Name:%s tblname:%s buckets:%x", indName, tblName, buckets);
    logFinest(Conf::logger, "Creating HashIndex %s on %s with bucket size %d", indName, tblName, buckets);
    return OK;
}


DbRetVal DatabaseManagerImpl::createTreeIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, int nodeSize, bool isUnique, bool isPrimary)
{
    if (nodeSize < 20 || nodeSize > 20000)
    {
        printError(ErrBadRange,"Tree Index Node size %d not in range 20-20000",
                                 nodeSize);
        return ErrBadRange;
    }
    int totFlds = fldList.size();
    if (totFlds == 0) {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
    }else if (totFlds != 1) {
        printError(ErrBadCall, "Composite index not supported for Tree");
        return ErrBadCall;
    }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    DbRetVal rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }
    //check whether table exists
    
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }
    char **fptr = new char* [totFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(fldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    for (int i=0; i <totFlds; i++)
    {
        CFIELD* fInfo = (CFIELD*)fptr[i];
        if (!fInfo->isNull_ && isPrimary )
        {
            printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
            delete[] fptr;
            systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }
        if (fInfo->type_ == typeVarchar)
        {
            printError(ErrBadArg, "Tree Index not supported for varchar type. Use char data type instead.");
            delete[] fptr;
           systemDatabase_->releaseCheckpointMutex();
            return ErrBadArg;
        }

    }
    int chunkSize = sizeof(TreeNode)+(nodeSize * sizeof(void*));
    printDebug(DM_HashIndex, "Creating chunk for storing tree nodes of size %d\n", chunkSize);

    Chunk* chunkInfo = createUserChunk(chunkSize);
    if (NULL == chunkInfo)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create chunk");
        return ErrSysInternal;
    }


    void *tupleptr = NULL;

    CatalogTableINDEX cIndex(systemDatabase_);
    rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, nodeSize, NULL, tupleptr);
    if (OK != rv)
    {
        delete[] fptr;
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);

    if (OK != rv)
    {
        delete[] fptr;
        void *hChunk = NULL;
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    delete[] fptr;
    systemDatabase_->releaseCheckpointMutex();
    //TODO::if tuples already present in this table, then create tree index '
    //nodes
    TableImpl *tbl = (TableImpl *) openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return ErrSysInternal;
    }
    if (! tbl->numTuples()) {
        printDebug(DM_Database, "Creating Tree Index Name:%s tblname:%s node size:%x",indName, tblName, nodeSize);
        logFinest(Conf::logger, "Creating TreeIndex %s on %s with node size %d",indName, tblName, nodeSize);
        closeTable(tbl);
        return OK;
    }
    HashIndexInfo *indxInfo = NULL;
    int i = 0;
    for (i = 0; i < tbl->numIndexes_; i++) {
        if(((HashIndexInfo *)tbl->idxInfo[i])->indexPtr == tupleptr) {
            indxInfo = (HashIndexInfo *) tbl->idxInfo[i];
            break;
        }
    }
    void *recPtr = NULL;
    ChunkIterator chIter = ((Chunk *)chunk)->getIterator();
    tbl->setLoading(true);
    while ((recPtr = chIter.nextElement()) != NULL) {
        rv = tbl->insertIndexNode(*tbl->trans, tupleptr, indxInfo, recPtr);
        if (rv == ErrUnique) {
            dropIndex(indName);
            closeTable(tbl);
            return rv;
        }
    }
    closeTable(tbl);
    printDebug(DM_Database, "Creating Tree Index Name:%s tblname:%s node size:%x",
                                   indName, tblName, nodeSize);
    logFinest(Conf::logger, "Creating TreeIndex %s on %s with node size %d",
                                   indName, tblName, nodeSize);
    return OK;
}

DbRetVal DatabaseManagerImpl::createTrieIndex(const char *indName, const char *tblName,
                      FieldNameList &fldList, bool isUnique, bool isPrimary)
{
    int totFlds = fldList.size();
    void *tptr =NULL;
    char **fptr = new char* [totFlds];
    DbRetVal rv = validateIndex(tblName, fldList, &tptr, &fptr, isPrimary);
    if (OK != rv)
    {
        delete[] fptr;
        return rv;
    }
    rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }

    //below statements are actually setting values in the catalog table
    //thats why mutex is taken before this stmt. Do not change the order
    CFIELD* fInfo = (CFIELD*)fptr[0];
    if(isPrimary){fInfo->isPrimary_=true;fInfo->isUnique_=true;}
    if(isUnique){fInfo->isUnique_=true;}

    printDebug(DM_TrieIndex, "Creating chunk for storing trie nodes\n" );
    Chunk* chunkInfo = createUserChunk(sizeof(TrieNode));

    //chunk to store the linked list of trie values 
    Chunk* hChunk = createUserChunk(sizeof(IndexNode));
    if (NULL == chunkInfo || NULL == hChunk)
    {
        delete[] fptr;
        if (chunkInfo) deleteUserChunk(chunkInfo);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Unable to create trie node chunk");
        return ErrSysInternal;
    }
    chunkInfo->setChunkName(indName);
    hChunk->setChunkName(indName);
    rv = updateIndexCatalogTables(indName,tptr, fptr, fldList, isUnique,
                                  chunkInfo, hChunk );
    delete[] fptr;
    if (OK != rv) {
        printError(ErrSysInternal, "Catalog table updation failed");
        deleteUserChunk(chunkInfo);
        deleteUserChunk(hChunk);
        systemDatabase_->releaseCheckpointMutex();
        return rv;
    }
    systemDatabase_->releaseCheckpointMutex();
    //TODO:: create index nodes if records already exist in the table
    return OK;
}
DbRetVal DatabaseManagerImpl::validateIndex(const char *tblName, 
                             FieldNameList &fldList, void **tptr, char ***fptr,
                             bool isPrimary)
{
    int totFlds = fldList.size();
    if (totFlds != 1)
    {
        printError(ErrBadCall, "No Field name specified or composite fields specified");
        return ErrBadCall;
    }
    void *chunk = NULL;
    void *vcchunk = NULL;
    //check whether table exists
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(tblName, chunk, *tptr, vcchunk);
    if (NULL == tptr)
    {
        printError(ErrNotExists, "Table does not exist %s", tblName);
        return ErrNotExists;
    }

    //check whether field exists
    CatalogTableFIELD cField(systemDatabase_);
    DbRetVal rv = cField.getFieldPtrs(fldList, *tptr, *fptr);
    if (OK != rv)
    {
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    CFIELD* fInfo = (CFIELD*)*fptr[0];
    if (!(fInfo->type_ == typeInt || fInfo->type_ == typeLongLong || fInfo->type_ == typeString || fInfo->type_ == typeVarchar))
    {
        printError(ErrBadArg, "Trie Index cannot be created for float or double or timestamp type");
        return ErrBadArg;
    }
    if (!fInfo->isNull_ && isPrimary )
    {
        printError(ErrBadArg, "Primary Index cannot be created on field without NOTNULL constraint");
        return ErrBadArg;
    }

    return OK;
}

DbRetVal DatabaseManagerImpl::updateIndexCatalogTables(const char *indName,
                        void *tptr, char **fptr, FieldNameList &fldList, 
                        bool isUnique, Chunk* chunkInfo, Chunk* hChunk ) 
{
    void *tupleptr = NULL;
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = cIndex.insert(indName, tptr, fldList.size(), isUnique,
                        chunkInfo, 0, hChunk, tupleptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed in INDEX table");
        return ErrSysInternal;
    }
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.insert(fldList, tupleptr, tptr, fptr);
    if (OK != rv)
    {
        //rollback the previous operation
        cIndex.remove(indName, (void *&)chunkInfo, (void *&)hChunk, (void *&)tupleptr);
        printError(ErrSysInternal, "Catalog table updation failed in INDEXFIELD table");
        return ErrSysInternal;
    }
    return rv;
}

DbRetVal DatabaseManagerImpl::removeIndexCatalogTables(const char *name, void *&chunk, void *&hchunk, void *&tptr)
{
    //remove the entry in INDEX
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = cIndex.remove(name, chunk, hchunk, tptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEX %s",name);
    //remove the entries in the INDEXFIELD table
    CatalogTableINDEXFIELD cIndexField(systemDatabase_);
    rv = cIndexField.remove(tptr);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
        return ErrSysInternal;
    }
    printDebug(DM_Database, "Removing from INDEXFIELD %s",name);
    return OK;
}
DbRetVal DatabaseManagerImpl::removeIndexChunks(void* chunk, void* hchunk, IndexType iType)
{
    DbRetVal rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to delete the index chunk");
        return ErrSysInternal;
    }
    //delete the index hash node chunk
    if (iType == hashIndex || iType == trieIndex) {
        rv = deleteUserChunk((Chunk*)hchunk);
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to delete the index hash node chunk");
            return ErrSysInternal;
        }
    }
    return OK;
}

void DatabaseManagerImpl::initHashBuckets(Bucket *buck, int bucketSize)
{
    os::memset((void*)buck, 0, bucketSize * sizeof(Bucket));

    for (int i=0; i < bucketSize ; i++)
    {
        buck[i].mutex_.init("Bucket");
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
        rv = systemDatabase_->getXCheckpointMutex();
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to get database mutex");
            return ErrSysInternal;
        }
    }
    rv = removeIndexCatalogTables(name, chunk, hchunk, tptr);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseCheckpointMutex();
        return rv;
    }

    CINDEX *iptr = (CINDEX*)tptr;
    rv = removeIndexChunks(chunk, hchunk, iptr->indexType_);
    if (OK != rv)
    {
        if (takeLock) systemDatabase_->releaseCheckpointMutex();
        return rv;
    }
    if (takeLock) systemDatabase_->releaseCheckpointMutex();

    printDebug(DM_Database, "Dropped index %s",name);
    logFinest(Conf::logger, "Deleted Index %s", name);
    return OK;
}
DbRetVal DatabaseManagerImpl::createForeignKey(char *fKName,ForeignKeyInfo *info)
{
   DbRetVal rv = OK;
   int totFkFlds = info->fkFldList.size();
   int totPkFlds = info->pkFldList.size();
   if (totFkFlds==0 && totPkFlds==0) {
        printError(ErrBadCall, "No Field name specified");
        return ErrBadCall;
   }
    void *tptr =NULL;
    void *chunk = NULL;
    void *vcchunk = NULL;
    rv = systemDatabase_->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to get database mutex");
        return ErrSysInternal;
    }
    CatalogTableTABLE cTable(systemDatabase_);
    cTable.getChunkAndTblPtr(info->fkTableName, chunk, tptr, vcchunk);
    if (NULL == tptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", info->fkTableName);
        return ErrNotExists;
    }
    char **fptr = new char* [totFkFlds];
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.getFieldPtrs(info->fkFldList, tptr, fptr);
    if (OK != rv)
    {
        delete[] fptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    void *tPkptr =NULL;
    void *chunkPk = NULL;
    void *vcchunkPk = NULL;
    CatalogTableTABLE c2Table(systemDatabase_);
    c2Table.getChunkAndTblPtr(info->pkTableName, chunkPk, tPkptr, vcchunkPk);
    if (NULL == tPkptr)
    {
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrNotExists, "Table does not exist %s", info->pkTableName);
        return ErrNotExists;
    }
    char **fPkptr = new char* [totPkFlds];
    CatalogTableFIELD c2Field(systemDatabase_);
    rv = c2Field.getFieldPtrs(info->pkFldList, tPkptr, fPkptr);
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        systemDatabase_->releaseCheckpointMutex();
        if (rv != ErrBadCall) {
            printError(ErrNotExists, "Field does not exist");
            return ErrNotExists;
        }
    }
    //Create New chunkdatanode
    CatalogTableFK cFK(systemDatabase_);
    rv = cFK.insert(fKName, tptr, tPkptr);//TODO
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in CFK table");
        return ErrSysInternal;
    }

    CatalogTableFKFIELD cFKField(systemDatabase_);
    rv = cFKField.insert(fKName,fptr,fPkptr,totFkFlds);
    if (OK != rv)
    {
        delete[] fptr;
        delete[] fPkptr;
        cFK.remove(tptr);
        systemDatabase_->releaseCheckpointMutex();
        printError(ErrSysInternal, "Catalog table updation failed in CFKFIELD table");
        return ErrSysInternal;
    }
    systemDatabase_->releaseCheckpointMutex();
    delete[] fptr;    
    delete[] fPkptr;
    return rv;
}
DbRetVal DatabaseManagerImpl::dropForeignKey(void *tptr,bool trylock)
{
    DbRetVal rv = OK;
    if(trylock){
        rv = systemDatabase_->getXCheckpointMutex();
        if (OK != rv)
        {
            printError(ErrSysInternal, "Unable to get database mutex");
            return ErrSysInternal;
        }
    }
    void *fkChunk=NULL;
    CatalogTableFK cFK(systemDatabase_);
    int total = cFK.getNoOfPkTable(tptr);
    //printDebug(DM_TEST,"total fk chunk %d",total);
    for (int i=0;i< total; i++)
    {
         fkChunk = cFK.getFkCTable(tptr);
         if(NULL==fkChunk)
         {
            if(trylock){
                systemDatabase_->releaseCheckpointMutex();
            }
            printError(ErrSysInternal, "Catalog table not finds CFKFIELD table");
            return ErrSysInternal;
         }
         CatalogTableFKFIELD cFKField(systemDatabase_);
         rv = cFKField.remove(fkChunk);
         if (OK != rv)
         {
             if(trylock){
                systemDatabase_->releaseCheckpointMutex();
             }
             printError(ErrSysInternal, "Catalog table updation failed in CFKFIELD table");
             return ErrSysInternal;
         } 
         rv =cFK.remove(fkChunk);
         if (OK != rv)
         {
            if(trylock){
                systemDatabase_->releaseCheckpointMutex();
            }
            printError(ErrSysInternal, "Catalog table updation failed for INDEX table");
            return ErrSysInternal;
         }
    }  
    if(trylock){
        systemDatabase_->releaseCheckpointMutex();
    }
    return rv;
}

void DatabaseManagerImpl::printTreeIndexNodeInfo(char *name, bool flag)
{
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    rv = cIndex.get(name, chunk, hchunk, tptr);
    if (OK != rv) return;
    IndexType iType = CatalogTableINDEX::getType(tptr);
    if (treeIndex != iType)
    {
       printf("%s is not a tree index\n ");
       return;
    }
    Chunk *ch = (Chunk*) chunk;
    if(flag){  if(hchunk)((TreeNode*) hchunk)->displayAll(); }
    else { 
        int offset = CatalogTableINDEX::getOffsetOfFirstField(tptr);
        //if(typeInt != offset) { printf("%s is not on Integer Type Field. To see info Index should be on integer type field. \n "); return;}       
        if(hchunk) ((TreeNode*) hchunk)->displayAll(offset);
    }
}

DbRetVal DatabaseManagerImpl::printIndexInfo(char *name)
{
    CatalogTableINDEX cIndex(systemDatabase_);
    DbRetVal rv = OK;
    void *chunk = NULL, *hchunk = NULL;
    void *tptr =NULL;
    rv = cIndex.get(name, chunk, hchunk, tptr);
    if (OK != rv) return rv;
    printf("<IndexName> %s </IndexName>\n", name);
    printf("<Unique> %d </Unique>\n", CatalogTableINDEX::getUnique(tptr));
    IndexType iType = CatalogTableINDEX::getType(tptr);
    if(hashIndex == iType)
        printf("<Type> Hash Index </Type>\n");
    else if (treeIndex == iType)
        printf("<Type> Tree Index </Type>\n");
    else if (trieIndex == iType)
        printf("<Type> Trie Index </Type>\n");
    else
        printf("<Type> Unknown Index </Type>\n");

    Chunk *ch = (Chunk*) chunk;
    printf("<HashBucket>\n");
    printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
    printf("  <TotalBuckets> %d </TotalBuckets> \n", CatalogTableINDEX::getNoOfBuckets(tptr));
    printf("</HashBucket>\n");
    printf("<IndexNodes>\n");
    if(hashIndex == iType){
        ch = (Chunk*) hchunk;
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %d </TotalNodes>\n", ch->getTotalDataNodes());
    } else if (treeIndex == iType) {
        printf("  <TotalNodes> %d </TotalNodes>\n", ch->getTotalDataNodes());
        if(hchunk)
            printf("  <TotalElements> %lld </TotalElements>\n",((TreeNode*) hchunk)->getTotalElements());
        else
            printf("  <TotalElements> 0 </TotalElements>\n");
    } else if (trieIndex == iType)
    {
        printf(" <TrieNodes> \n");
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %d </TotalNodes>\n", ch->getTotalDataNodes());
        printf(" </TrieNodes> \n <TrieValues>\n");
        ch = (Chunk*) hchunk;
        printf("  <TotalPages> %d </TotalPages>\n", ch->totalPages());
        printf("  <TotalNodes> %d </TotalNodes>\n", ch->getTotalDataNodes());
        printf(" </TrieValues>\n");
    } else 
    {
        printf("Unknown Index type\n");
    }
    printf("<IndexNodes>\n");
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
void DatabaseManagerImpl::printDebugChunkInfo()
{
    printf("<NotYetImplemented> </NotYetImplemented>\n");
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

int DatabaseManagerImpl::getNoOfPagesForTable(char *tblName)
{
    Table *tbl = openTable(tblName);
    if (NULL == tbl) {
        printError(ErrSysInternal, "Unable to open table %s", tblName);
        return 0;
    }
    TableImpl *tb = (TableImpl *) tbl;
    int pages = 0;
    if (tb->numTuples()) pages = tb->pagesUsed();
    closeTable(tbl);
    return pages;
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
            delete ((FieldName *) fNameIter.nextElement());
        fNameList.reset();

        fprintf(fp, ");\n");
        table->printSQLIndexString(fp, fd);
        delete info;
        closeTable(table);
    }
    ListIterator tIter = tableList.getIterator();
    tIter.reset();
    while (tIter.hasElement())
        delete ((FieldName *) tIter.nextElement());
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
