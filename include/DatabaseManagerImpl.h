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
#ifndef DATABASE_MANAGER_IMPL_H
#define DATABASE_MANAGER_IMPL_H
#include<os.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<DatabaseManager.h>
#include<Process.h>
#include<Util.h>
//Note::DatabaseManagerImpl is used to hide functionalites from normal database user. 
//User is exposed to DatabaseManagerImpl, for our tools we shall type cast DatabaseManager 
//to DatabaseManagerImpl to retreive internal information such as db statistics, etc
class Database;
class SessionImpl;
class TableDef;
class Table;
class FieldNameList;
class ChunkIterator;
class Chunk;
class TransactionManager;
class CSqlProcInfo
{
    public:
    CSqlProcInfo() { sysDbAttachAddr = userDbAttachAddr = NULL;}
    void *sysDbAttachAddr;
    void *userDbAttachAddr;
};

//Global object
static CSqlProcInfo csqlProcInfo;

class DatabaseManagerImpl : public DatabaseManager
{
    private:
    Database* systemDatabase_;
    //pointer to system Database

    Database* db_;
    //pointer to database

    LockManager *lMgr_;

    TransactionManager *tMgr_;


    ProcessManager *pMgr_;
    int procSlot;
 
    //only SessionImpl creates object of this class
    DatabaseManagerImpl() { systemDatabase_ = NULL; tMgr_ = NULL; lMgr_ =  NULL; 
                            pMgr_ = NULL; db_ = NULL; }
    ~DatabaseManagerImpl();

    DbRetVal openSystemDatabase();
    DbRetVal closeSystemDatabase();
    ChunkIterator getSystemTableIterator(CatalogTableID id);
    Chunk* getSystemTableChunk(CatalogTableID id);

    void createLockManager();
    void createTransactionManager();

    Chunk* createUserChunk(size_t size = 0);
    DbRetVal deleteUserChunk(Chunk *chunk);

    
    DbRetVal createHashIndex(const char *indName, const char *tableName,
                        FieldNameList &fldList, int bucketSize, bool isUnique, bool isPrimary = false);
    DbRetVal createTreeIndex(const char *indName, const char *tableName,
             FieldNameList &fldList, int bucketSize, bool isUnique, bool isPrimary = false);
    void initHashBuckets(Bucket *buck, int bucketSize);

    DbRetVal dropIndexInt(const char *name, bool takeLock);
    DbRetVal writeSchemaFile();
    public:

    Database* db() { return db_; }
    Database* sysDb() { return systemDatabase_; }
    void setSysDb(Database *db) { systemDatabase_ = db; }
    void setDb(Database *db) { db_ = db; }

    void setProcSlot();
    TransactionManager* txnMgr() { return tMgr_; }
    LockManager* lockMgr() { return lMgr_; }

    //for user database file there is no limit for the number
    //of tables or chunks
    DbRetVal createDatabase(const char *name, size_t size);
    DbRetVal deleteDatabase(const char *name);

    DbRetVal openDatabase(const char *name);
    DbRetVal closeDatabase();

    void setCanTakeCheckPoint(bool ctcp);
    bool getCanTakeCheckPoint();

    DbRetVal createTable(const char *name, TableDef &def);
    DbRetVal dropTable(const char *name);
    DbRetVal renameTable(const char *oldName,const char *newName);
    DbRetVal renameField(const char *tableName,const char *oldName,const char *newName);
    Table* openTable(const char *name, bool checkpkfk=true);
    void closeTable(Table *table);
    DbRetVal createIndex(const char *indName, IndexInitInfo *info);
    DbRetVal dropIndex(const char *name);
    DbRetVal createForeignKey(char *kfName,ForeignKeyInfo *info);
    DbRetVal dropForeignKey(void *ctptr,bool trylock);
    List getAllTableNames(int *rv=NULL);
    void sendSignal(int signal);

    DbRetVal registerThread();
    DbRetVal deregisterThread();
    bool isAnyOneRegistered();
    void printUsageStatistics();
    void printDebugLockInfo();
    void printDebugTransInfo();
    void printDebugChunkInfo();
    void printDebugProcInfo();
    int getNoOfPagesForTable(char *tblName);
    DbRetVal loadRecords(char *tblName, char *buffer);
    DbRetVal pasteRecords(char *tblName, void *buffer);
    DbRetVal checkPoint();
    DbRetVal recover();
    DbRetVal printIndexInfo(char *name);
    void printTreeIndexNodeInfo(char *name,bool flag);
    friend class SessionImpl;
};
#endif
