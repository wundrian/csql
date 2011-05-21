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
#ifndef LOCK_H
#define LOCK_H
#include<os.h>
#include<Index.h>
class Chunk;
class Database;
class Transaction;

class LockInfo
{
    public:
    InUse noOfReaders_;
    //-1 indicates write lock is taken

    InUse waitReaders_;
    InUse waitWriters_;
    LockInfo() { noOfReaders_ = 0; waitReaders_ = 0; waitWriters_ = 0; }

};

class LockHashNode
{
    public:
    void *ptrToTuple_;
    LockInfo lInfo_;
    LockHashNode *next_;
    void print() 
    { 
        printf("<Lock Node>\n");
        printf("  <Tuple> %x </Tuple>\n", ptrToTuple_);
        printf("  <NoOfReaders> %d </NoOfReaders>\n", lInfo_.noOfReaders_);
        printf("  <WaitReaders> %x </WaitReaders>\n", lInfo_.waitReaders_);
        printf("  <WaitWriters> %x </WaitWriters>\n", lInfo_.waitWriters_);
        printf("</Lock Node>\n");
    }
};

class LockTable
{
    Bucket *lockBuckets;
    Database *systemDatabase_;

    //Each thread contains its own DatabaseManager object which inturn contains
    //LockManager and which inturn contains LockTable. So this is thread 
    //specific and contains cached current bucket for which lock needs to be 
    //obtained or released
    Bucket *curBucket;

    public:
    LockHashNode* allocLockNode(LockInfo &info, void *tuple, DbRetVal *rv);
    DbRetVal deallocLockNode(LockHashNode *head, Bucket *bucket);
    void deallocLockNode(LockHashNode *head);
    DbRetVal addNewLockNode(void *tuple, Transaction **trans,
                                   LockInfo &info);
    DbRetVal releaseLock(LockHashNode *node);
    LockHashNode* getLockNode(void *tuple, DbRetVal &rv, bool takeLock=true);

    LockTable();
    ~LockTable();
    void setDb(Database *sysDb);
    Bucket* getLockBucket(void *tuple);

    DbRetVal getBucketMutex();
    void releaseBucketMutex();
    void printUsageStatistics();
    void printDebugInfo();
    void printMutexInfo();
};

class TransHasNode
{
    public:
    LockHashNode *node_;
    TransHasNode *next_;
    void print() { node_->print(); }
};

class DatabaseManagerImpl;
//singleton
//DatabaseManager has this object and give reference to it to
//Table interface and so on.
class DllExport LockManager
{
    public:
    Database *systemDatabase_;
    LockTable lockTable;

    private:
    LockHashNode* allocLockNode(LockInfo &info, void *tuple, DbRetVal *rv);
    DbRetVal deallocLockNode(LockHashNode *head, Bucket *bucket);
    void deallocLockNode(LockHashNode *head);
    Bucket* getLockBucket(void *tuple);
    DbRetVal createFirstNodeInBucket(void *tuple, Transaction **trans, 
                                     Bucket *bucket, LockInfo &info);
    DbRetVal addNewNodeToBucket(void *tuple, Transaction **trans, 
                                     Bucket *bucket, LockInfo &info);
    DbRetVal retryExclusiveLock(Transaction **trans, 
                                     LockHashNode *node);
    DbRetVal takeXLockNotInUse(Transaction **trans, LockHashNode *node);
    bool takeXLockOneReader(Transaction **trans, LockHashNode *node);
    bool takeXLockOneWriter(Transaction **trans, LockHashNode *node);
    DbRetVal releaseLock(Bucket *bucket, LockHashNode *node);

    public:

    LockManager(Database *sysDb_);
    DbRetVal getSharedLock(void *tuple, Transaction **trans);
    DbRetVal getExclusiveLock(void * tuple, Transaction **trans);
    DbRetVal releaseLock(void *tuple);
    DbRetVal isExclusiveLocked(void *tuple, Transaction **trans, bool &status);
    DbRetVal getBucketMutex(Bucket *bucket, int procslot);
    void printUsageStatistics();
    void printDebugInfo();
    void printMutexInfo();
};


#endif
