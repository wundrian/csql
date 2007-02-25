/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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

/*class LockList
{
    LockHashNode *head;
    public:
    LockList(){ head = NULL;}
    LockList(LockHashNode *h){ head = h; }
    int insert(Chunk *chunk, Database *db, void *key, void *tuple);
    int remove(Chunk *chunk, Database *db, void *key);
    LockListIter getIterator()
    {
        LockListIter it;
        it.iter = head;
        return it;
    }
};*/

class TransHasNode
{
    public:
    LockHashNode *node_;
    TransHasNode *next_;
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
};


#endif
