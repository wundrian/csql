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
#ifndef DATABASE_H
#define DATABASE_H
#include<os.h>
#include<Allocator.h>
#include<Debug.h>
#include<Util.h>
#include<Process.h>

class Bucket;
class Transaction;

class DatabaseMetaData
{
    public:
    int dbID_;
    char dbName_[IDENTIFIER_LENGTH];

    //TODO:: move this from here to system database
    //as only sys db has the limit and user
    //database does not have any limit for chunks
    int noOfChunks_;

    long maxSize_; //maximum size of database
    long curSize_; //current size of database

    //current page, this is used by the allocator to get new free page
    Page *curPage_;

    //first page, usually after this database meta data
    //getFreePage function uses this to get the free page in this database
    Page *firstPage_;


    //This mutex is taken if pageInfo is accessed or modified for
    //this database
    Mutex dbAllocMutex_;

    Mutex ckptMutex_;

    Mutex dbTransTableMutex_;

    Mutex dbProcTableMutex_;

    // This mutex is taken for prepare in SqlStatement
    Mutex dbPrepareStmtMutex_;

    //To generate unique id
    UniqueID chunkUniqueID_;

    //This is where all hash index nodes are stored for all the
    //indexes in this database
    Chunk *hashIndexChunk_;

    unsigned char reserved_[996];
};


class DatabaseManagerImpl;
class Table;
class ProcInfo;
class ThreadInfo;
class Transaction;

class Database
{
    private:
    //Only DatabaseManager creates this object
    //initialization is done only in DatabaseManager during
    //create, delete, open, close database methods
    Database() { metaData_ = NULL; procSlot = -1; fdChkpt = -1; thrInfoOffset=0;}
    DatabaseMetaData *metaData_;
    int fdChkpt;
    int thrInfoOffset;


    public:

    DbRetVal createSystemDatabaseChunk(AllocType type = FixedSizeAllocator,
                                      size_t size = 0, int chunkID=-1);
    DbRetVal deleteSystemDatabaseChunk(int id);

    Chunk* getSystemDatabaseChunk(int id);
    Transaction* getSystemDatabaseTrans(int slot);
    inline void setThrInfoOffset() {
        thrInfoOffset = os::alignLong(sizeof (DatabaseMetaData)) +
                        os::alignLong( MAX_CHUNKS  * sizeof (Chunk)) +
               os::alignLong( Conf::config.getMaxProcs()*sizeof(Transaction));
    }
    inline ThreadInfo* getThreadInfo(int slot){
        if (!thrInfoOffset) setThrInfoOffset();
        size_t off = thrInfoOffset + slot * sizeof (ThreadInfo);
        return (ThreadInfo*)(((char*) metaData_) +  off);
    }

    //ThreadInfo* getThreadInfo(int pidSlot, int thrSlot);
    bool isLastThread();

    void createAllCatalogTables();
    void createSystemTables();
    void createMetaDataTables();

    void* allocLockHashBuckets();
    Bucket* getLockHashBuckets();

    void incrementChunk() { (metaData_->noOfChunks_)++;}
    void decrementChunk() { (metaData_->noOfChunks_)--;}

    int getUniqueIDForChunk();

    const char* getName();
    int getDatabaseID();
    long getMaxSize();
    long getCurrentSize();
    Page* getCurrentPage();
    int getNoOfChunks();
    DatabaseMetaData* getMetaDataPtr() { return metaData_; }
    Page* getFirstPage();
    Chunk* getHashIndexChunk();
    int getChkptfd() { return fdChkpt; }

    void setDatabaseID(int id);
    void setName(const char *name);
    void setCurrentSize(long size);
    void setCurrentPage(Page *page);
    void setMaxSize(long size);
    void setNoOfChunks(int maxChunks);
    void setMetaDataPtr(DatabaseMetaData *ptr) {metaData_ = ptr; }
    void setFirstPage(Page *ptr);
    void setHashIndexChunk(Chunk* chunk);
    void setUniqueChunkID(int id);
    void setChkptfd(int fd) { fdChkpt = fd; }

    // Gets the free page
    // Each page is segmented by PAGE_SIZE, so it checks the pageInfo
    // of each page to determine if the page is free
    Page* getFreePage();
    Page* getFreePage(size_t size);

    void printStatistics();

    int initAllocDatabaseMutex();
    DbRetVal getAllocDatabaseMutex(bool procAccount = true);
    DbRetVal releaseAllocDatabaseMutex(bool procAccount = true);

    int initTransTableMutex();
    DbRetVal getTransTableMutex();
    DbRetVal releaseTransTableMutex();

    int initCheckpointMutex();
    DbRetVal getSCheckpointMutex(bool procAccount = true);
    DbRetVal getXCheckpointMutex(bool procAccount = true);
    DbRetVal releaseCheckpointMutex(bool procAccount = true);

    int initProcessTableMutex();
    DbRetVal getProcessTableMutex(bool procAccount = true);
    DbRetVal releaseProcessTableMutex(bool procAccount = true);

    int initPrepareStmtMutex();
    DbRetVal getPrepareStmtMutex(bool procAccount = true);
    DbRetVal releasePrepareStmtMutex(bool procAccount = true);

    DbRetVal recoverMutex(Mutex *mut);  
    
    int procSlot;
    void setProcSlot(int slot) { procSlot =slot;}
    //checks whether the ptr falls in the range of the database file size
    bool isValidAddress(void *ptr);

    DbRetVal writeDirtyPages(char *chkptFile);
    DbRetVal checkPoint();
    DbRetVal filterAndRemoveStmtLogs();
    DbRetVal recoverUserDB();
    DbRetVal recoverSystemDB();
    static int getCheckpointID();
    static void setCheckpointID(int id);

    friend class DatabaseManagerImpl;
    friend class Table;
    friend class TreeIndex;
    friend class HashIndex;
    friend class Transaction;

};

#endif
