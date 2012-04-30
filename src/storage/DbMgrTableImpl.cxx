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
                                   def.getFieldCount(), ptr, tptr, vcptr, userName);
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
    txnMgr()->rollback(lockMgr());
    txnMgr()->startTransaction(lockMgr(), READ_COMMITTED);
    Transaction **trans = ProcessManager::getThreadTransAddr(systemDatabase_->procSlot);
    rv = lMgr_->getExclusiveLock(chunk, trans);
    if (rv !=OK)
    {
        systemDatabase_->releaseCheckpointMutex();
        txnMgr()->rollback(lockMgr());
        printError(ErrLockTimeOut, "Unable to acquire exclusive lock on the table\n");
        return rv;
    }
    rv = cTable.remove(name, chunk, tptr);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
	txnMgr()->rollback(lockMgr());
        printError(ErrSysInternal, "Unable to update catalog table TABLE");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from TABLE:%s",name);

    //remove the entries in the FIELD table
    CatalogTableFIELD cField(systemDatabase_);
    rv = cField.remove(tptr);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
	txnMgr()->rollback(lockMgr());
        printError(ErrSysInternal, "Unable to update catalog table FIELD");
        return ErrSysInternal;
    }
    printDebug(DM_Database,"Deleted from FIELD:%s",name);

    rv = deleteUserChunk((Chunk*)chunk);
    if (OK != rv) {
        systemDatabase_->releaseCheckpointMutex();
	txnMgr()->rollback(lockMgr());
        printError(rv, "Unable to delete the chunk");
        return rv;
    }
    printDebug(DM_Database,"Deleted UserChunk:%x", chunk);
   
    if (vcchunk != NULL) {
        rv = deleteUserChunk((Chunk*)vcchunk);
        if (OK != rv) {
            systemDatabase_->releaseCheckpointMutex();
	    txnMgr()->rollback(lockMgr());
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
    rv = txnMgr()->commit(lockMgr());
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
    rv = table->lock(true); //take shared lock
    if (rv !=OK)
    {
        printError(ErrLockTimeOut, "Unable to acquire shared lock on the table\n");
        systemDatabase_->releaseAllocDatabaseMutex();
        delete table;
        return NULL;
    }

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
    table->unlock();
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

