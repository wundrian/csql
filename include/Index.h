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

class Database;
class Chunk;
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
    TreeNode *next_;
    TreeNode *prev_;
    int balance_;
    //Note::after this array of pointer to tuples are stored
    long long getTotalElements();
    TreeNode* locateNode(Database *db,TreeNode *iter, void *tuple, IndexInfo *indInfo,DbRetVal &rv);
    TreeNode *locateNodeFromFirstLevel(TreeNode *ftnode,IndexInfo *indInfo,void *tuple,int *nodepos);
    DbRetVal insertNodeIntoFirstLevel(Database * db, IndexInfo * indInfo, void* indexPtr, TreeNode * newNode,int nodepos);
    DbRetVal insert(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    DbRetVal insertRecordIntoNodeAndArrangeFirstLevel(Database * db, IndexInfo * indInfo, void* iptr, void * tuple, TreeNode * fstLevel,int nodepos);
    DbRetVal remove(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    DbRetVal update(Database *db, IndexInfo *info, void *indexPtr, void *tuple);
    void displayAll();
    void displayAll(int offset);
};

class BucketIter
{
    HashIndexNode *iter;
    HashIndexNode *head;
    bool isUnique;
    bool recordsOver;
    public:
    BucketIter(){iter = head = NULL;
                 isUnique=false; recordsOver = false;}
    void setHead(HashIndexNode *hd) { iter = head = hd; recordsOver=false;}
    BucketIter(HashIndexNode *head) { iter = head = head;
                 isUnique=false; recordsOver = false;}
    void setUnique() { isUnique = true; }
    bool getUnique() { return isUnique; }
    HashIndexNode* next();
    void reset() { iter = head; recordsOver=false;}
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
    static void destroy();
    virtual DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0;
    virtual DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0; 
    virtual DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag)=0;
};
class HashIndex : public Index
{
    //No members as it will be called by multiple threads 
    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    static unsigned int computeHashBucket(DataType type, void *key, int noOfBuckets, int length=0);
    static DbRetVal insertLogicalUndoLog(Database *sysdb, void *info);
    static DbRetVal deleteLogicalUndoLog(Database *sysdb, void *info);
};

class TreeIndex : public Index
{
    //No members as it will be called by multiple threads 
    DbRetVal removeElement(Database *db, TreeNode *iter, void *tuple, HashIndexInfo *info);
    void removeNode(Database *db,void *indexPtr,TreeNode *fltnode, TreeNode *node,int pos);
    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    static DbRetVal insertLogicalUndoLog(Database *sysdb, void *info);
    static DbRetVal deleteLogicalUndoLog(Database *sysdb, void *info);
    static DbRetVal getTreeNodeMutex(TreeNode*, int procSlot, bool isX=false);
    static DbRetVal upgradeTreeNodeMutex(TreeNode*, int procSlot);

};
class TreeIter
{
    TreeNode *iter;
    TreeNode *head;
    int fldOffset;
    DataType type;
    int length;
    ComparisionOp op;
    bool asc;
    void *searchKey;
    bool firstCall;
    int nodeOffset;
    bool recordsOver;
    void *fstLTnode;
    void* locateNode();
    void* locateElement();
    int procSlot;
    bool isUnique; 

    public:
    TreeIter(){ iter=head=NULL; searchKey=fstLTnode=NULL;isUnique = false;}
    TreeIter(TreeNode *hd,void *fTnode, int slot ) { fstLTnode = fTnode; iter = head = hd; firstCall = true; recordsOver=false; procSlot=slot; isUnique=false;}
    void set(TreeNode *hd,void *fTnode, int slot ) { fstLTnode = fTnode; iter = head = hd; firstCall = true; recordsOver=false; procSlot=slot; isUnique=false;}
    void setSearchKey(void *key, ComparisionOp cop, bool ascending = true)
    {
        searchKey = key; op = cop; asc =ascending;
    }
    void setUnique() { isUnique = true; }
    bool getUnique() { return isUnique; }
    void setFldOffset(int off) { fldOffset = off; }
    void setTypeLength(DataType t, int l) { type =t ; length =l; }
    void* prev();
    void* next();
    void nextNode();
    void* getFirstElement();
    void* getLastElement();
    void reset();// { iter = head; firstCall = true; recordsOver=false; }
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
    virtual ~IndexInfo() {}
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
    ~HashIndexInfo() { idxFldList.removeAll(); }
};
#endif

