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
#ifndef INDEX_H
#define INDEX_H
#include<DataType.h>
#include<Debug.h>
#include<Info.h>


class Chunk;
class Database;
class Transaction;
class TableImpl;

class Bucket
{
    public:
    Mutex mutex_;
    void *bucketList_;
};
class HashIndexNode
{
    public:
    void *ptrToKey_;
    void *ptrToTuple_;
    HashIndexNode *next_;
};
class BucketIter
{
    HashIndexNode *iter;
    public:
    BucketIter(){}
    BucketIter(HashIndexNode *head) { iter = head;}
    HashIndexNode* next();
    friend class BucketList;
};
class BucketList
{
    HashIndexNode *head;
    public:
    BucketList(){ head = NULL;}
    BucketList(HashIndexNode *h){ head = h; }
    DbRetVal insert(Chunk *chunk, Database *db, void *key, void *tuple);
    DbRetVal remove(Chunk *chunk, Database *db, void *key);
    BucketIter getIterator()
    {
        BucketIter it;
        it.iter = head;
        return it;
    }

};
class HashIndex;

class Index
{
    static HashIndex *hIdx;
    public:
    static Index* getIndex(IndexType type);
    static void destroy() { delete hIdx; }
    virtual DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple)=0;
    virtual DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple)=0; 
    virtual DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple)=0;
};

class HashIndex : public Index
{

    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, void *tuple);
    static unsigned int computeHashBucket(DataType type, void *key, int noOfBuckets);

};

enum IndexIntType
{
        hashOneField = 1,
        hash = 2,
        tree = 3

};
class IndexInfo
{
    public:
    IndexType type;
};

//Used by TableImpl to cache information related to hash indexes on that table
class SingleFieldHashIndexInfo :public IndexInfo
{
    public:
    char  *fldName;
    DataType type ;
    char *indexPtr;
    int noOfBuckets;
    Bucket* buckets;
    int fldPos;
};
#endif

