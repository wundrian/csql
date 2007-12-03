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
    signed int noOfReaders_;
    //-1 indicates write lock is taken

    unsigned char waitReaders_;
    unsigned char waitWriters_;
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

class LockListIter
{
    LockHashNode *iter;
    public:
    LockListIter(){}
    LockListIter(LockHashNode *head) { iter = head;}
    LockHashNode* next();
    friend class LockList;
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
class LockManager
{
    public:
    Database *systemDatabase_;

    private:
    LockHashNode* allocLockNode(LockInfo &info, void *tuple);
    void deallocLockNode(LockHashNode *head, Bucket *bucket);
    Bucket* getLockBucket(void *tuple);

    public:

    LockManager(Database *sysDb_){ systemDatabase_ = sysDb_;}
    DbRetVal getSharedLock(void *tuple, Transaction **trans);
    DbRetVal getExclusiveLock(void * tuple, Transaction **trans);
    DbRetVal releaseLock(void *tuple);
    DbRetVal isExclusiveLocked(void *tuple, Transaction **trans, bool &status);
    void printUsageStatistics();
    void printDebugInfo();
};


#endif
