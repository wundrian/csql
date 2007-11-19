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
    int maxChunks_;

    size_t maxSize_; //maximum size of database
    size_t curSize_; //current size of database

    //current page, this is used by the allocator to get new free page
    Page *curPage_;

    //first page, usually after this database meta data
    //getFreePage function uses this to get the free page in this database
    Page *firstPage_;


    //This mutex is taken if pageInfo is accessed or modified for
    //this database
    Mutex dbAllocMutex_;

    Mutex dbMutex_;

    Mutex dbTransTableMutex_;

    Mutex dbProcTableMutex_;

    //This is where all hash index nodes are stored for all the
    //indexes in this database
    Chunk *hashIndexChunk_;

    unsigned char reserved_[1024];
};


class DatabaseManagerImpl;
class Table;
class ProcInfo;
class ThreadInfo;

class Database
{
    private:
    //Only DatabaseManager creates this object
    //initialization is done only in DatabaseManager during
    //create, delete, open, close database methods
    Database() { metaData_ = NULL; }
    DatabaseMetaData *metaData_;


    public:

    DbRetVal createSystemDatabaseChunk(AllocType type = FixedSizeAllocator,
                                      size_t size = 0, int chunkID=-1);
    DbRetVal deleteSystemDatabaseChunk(int id);

    Chunk* getSystemDatabaseChunk(int id);
    Transaction* getSystemDatabaseTrans(int slot);

    ThreadInfo* getThreadInfo(int slot);
    //ThreadInfo* getThreadInfo(int pidSlot, int thrSlot);
    bool isLastThread();

    void createAllCatalogTables();
    void createSystemTables();
    void createMetaDataTables();

    void* allocLockHashBuckets();
    Bucket* getLockHashBuckets();

    //TODO
    int getNoOfChunks(){ return 0;}

    const char* getName();
    int getDatabaseID();
    size_t getMaxSize();
    size_t getCurrentSize();
    Page* getCurrentPage();
    int getMaxChunks();
    DatabaseMetaData* getMetaDataPtr() { return metaData_; }
    Page* getFirstPage();
    Chunk* getHashIndexChunk();

    void setDatabaseID(int id);
    void setName(const char *name);
    void setCurrentSize(size_t size);
    void setCurrentPage(Page *page);
    void setMaxSize(size_t size);
    void setMaxChunks(int maxChunks);
    void setMetaDataPtr(DatabaseMetaData *ptr) {metaData_ = ptr; }
    void setFirstPage(Page *ptr);
    void setHashIndexChunk(Chunk* chunk);


    // Gets the free page
    // Each page is segmented by PAGE_SIZE, so it checks the pageInfo
    // of each page to determine if the page is free
    Page* getFreePage();
    Page* getFreePage(size_t size);

    int initAllocDatabaseMutex();
    DbRetVal getAllocDatabaseMutex(bool procAccount = true);
    DbRetVal releaseAllocDatabaseMutex(bool procAccount = true);

    int initTransTableMutex();
    DbRetVal getTransTableMutex();
    DbRetVal releaseTransTableMutex();

    int initDatabaseMutex();
    DbRetVal getDatabaseMutex(bool procAccount = true);
    DbRetVal releaseDatabaseMutex(bool procAccount = true);

    int initProcessTableMutex();
    DbRetVal getProcessTableMutex(bool procAccount = true);
    DbRetVal releaseProcessTableMutex(bool procAccount = true);

    //checks whether the ptr falls in the range of the database file size
    bool isValidAddress(void *ptr);
    friend class DatabaseManagerImpl;
    friend class Table;

};

#endif
