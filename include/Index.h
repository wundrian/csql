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
class CINDEX;

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

class IndexInfo;
class TreeNode
{
    public:
    Mutex mutex_;
    void *min_;
    void *max_;
    int noElements_;
    int balance_;
    TreeNode *next_;
    TreeNode *prev_;
    //Note::after this array of pointer to tuples are stored

    DbRetVal insert(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    DbRetVal insert(int position, Database *db, IndexInfo *indInfo, CINDEX *iptr, void *tuple, TreeNode *iter);
    DbRetVal remove(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    DbRetVal update(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    void displayAll(IndexInfo *indInfo, void *indexPtr);
    void displayAll(int offset);
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
    void *getBucketListHead(){ return head;}
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
class IndexInfo;
class HashIndexInfo;
class TreeIndex;
class Index
{
    // create (one) object for each indexing mechanisms here 
    // Also need to make changes to getIndex() and destroy() methods 
    // accordingly for new index machanism.
    static HashIndex *hIdx;
    static TreeIndex *tIdx;
    static long usageCount;
    public:
    static Index* getIndex(IndexType type);
    static void init() { usageCount++; }
    static void destroy() { 
	 usageCount--;
         if(!usageCount) {
            if(!hIdx) { delete hIdx; hIdx=NULL; }
	 }
    }
    virtual DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0;
    virtual DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0; 
    virtual DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0;
};
class HashIndex : public Index
{

    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    static unsigned int computeHashBucket(DataType type, void *key, int noOfBuckets, int length=0);

};

class TreeIndex : public Index
{

    TreeNode* locateNode(TreeNode *iter, void *tuple, IndexInfo *indInfo);
    DbRetVal removeElement(Database *db, TreeNode *iter, void *tuple, HashIndexInfo *info);
    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);

};
class TreeIter
{
    TreeNode *iter;
    int fldOffset;
    DataType type;
    int length;
    ComparisionOp op;
    bool asc;
    void *searchKey;
    bool firstCall;
    int nodeOffset;
    bool recordsOver;

    void* locateNode();
    void* locateElement();

    public:
    TreeIter(){}
    TreeIter(TreeNode *head) { iter = head; firstCall = true; recordsOver=false;}
    void setSearchKey(void *key, ComparisionOp cop, bool ascending = true)
    {
        searchKey = key; op = cop; asc =ascending;
    }
    void setFldOffset(int off) { fldOffset = off; }
    void setTypeLength(DataType t, int l) { type =t ; length =l; }
    void* prev();
    void* next();
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
    IndexType indType;
};

//Used by TableImpl to cache information related to hash indexes on that table
class HashIndexInfo :public IndexInfo
{
    public:
    FieldList idxFldList;
    char *indexPtr;
    int noOfBuckets;
    Bucket* buckets;
    int fldOffset;
    bool isUnique;
    DataType type;
    int compLength;
    void print() 
    {
        printf("HashIndexInfo indexPtr:%x noOfBuckets:%d buckets:%x \n",indexPtr, noOfBuckets, buckets);
    }
};
#endif

