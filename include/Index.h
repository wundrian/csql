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
#define TRIE_SIZE 10
#define TRIE_MAX_LENGTH 64

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
class IndexNode
{
    public:
    void *ptrToKey_;
    void *ptrToTuple_;
    IndexNode *next_;
};

class TrieNode
{
    public:
    IndexNode *head_[TRIE_SIZE];
    TrieNode *next_[TRIE_SIZE];
};

class IndexInfo;

/**
* @class TreeNode
* @brief Represents node in tree index.
*	 It is actually a doubly linked list node which contains information such as minimum key value pointer, maximum key value pointer and total number of elements.
*
* TreeNode represents node in tree index and it is guarded by a mutex.
* Any modifications to tree node should be done only after acquiring 
* its associated mutex. At the end array of pointers to next level tree nodes(in case of intermediate node) / tuple is stored(in case of leaf nodes)
* <br/>
*
*/

class TreeNode
{
    public:
    Mutex mutex_; 	/**< Mutex guarding this node */
    void *min_;   	/**< Ptr to node having minimum value in this node */
    void *max_;         /**< Ptr to node having maximum value in this node */
    int noElements_;    /**< total number of elements in this node */
    TreeNode *next_;    /**< ptr to next tree node in same level */
    TreeNode *prev_;    /**< ptr to previous tree node in same level */
    int balance_;       /**< Reserved. Not currently used */
    //Note::after this array of pointer to tuples are stored

    long long getTotalElements();

    
    /**
    *  @brief insert node into the tree, by traversing and locating the right node
    *  
    *  Detailed description comes here
    *  Detailed desc continues here
    *  @param db  pointer to Database
    *  @param info pointer to tuple under search
    *  @param indexPtr  ptr to INDEX structure
    *  @param tuple pointer to tuple under search
    *  @return DbRetVal error code when function returns
    */
    DbRetVal insert(Database *db, IndexInfo *info, void *indexPtr, void *tuple);

    /**
    *  @brief remove node from the tree, by traversing and locating the right node
    *  
    *  @param db  pointer to Database
    *  @param info pointer to tuple under search
    *  @param indexPtr  ptr to INDEX structure
    *  @param tuple pointer to tuple to be removed
    *  @return DbRetVal error code when function returns
    */
    DbRetVal remove(Database *db, IndexInfo *info, void *indexPtr, void *tuple);

    /**
    *  @brief update node in the tree, by traversing and locating the right node
    *  
    *  @param db  pointer to Database
    *  @param info pointer to tuple under search
    *  @param indexPtr  ptr to INDEX structure
    *  @param tuple pointer to tuple to be updated
    *  @return DbRetVal error code when function returns
    */
    DbRetVal update(Database *db, IndexInfo *info, void *indexPtr, void *tuple);

    void displayAll();
    void displayAll(int offset);

    private:

    /**
    *  @brief locate node where tuple resides by traversing the tree nodes
    *  
    *  Detailed description comes here
    *  Detailed desc continues here
    *  @param db  pointer to Database
    *  @param iter  TreeNode pointer
    *  @param tuple pointer to tuple under search
    *  @param indInfo pointer to tuple under search
    *  @param rv OUT param which will contain error code when this function returns with any error
    *  @return TreeNode* pointer to TreeNode which contains the tuple under search
    */
    TreeNode* locateNode(Database *db,TreeNode *iter, void *tuple, IndexInfo *indInfo,DbRetVal &rv);
    TreeNode *locateNodeFromFirstLevel(TreeNode *ftnode,IndexInfo *indInfo,void *tuple,int *nodepos);
    DbRetVal insertRecordIntoNodeAndArrangeFirstLevel(Database * db, IndexInfo * indInfo, void* iptr, void * tuple, TreeNode * fstLevel,int nodepos);
    DbRetVal insertNodeIntoFirstLevel(Database * db, IndexInfo * indInfo, void* indexPtr, TreeNode * newNode,int nodepos);
    friend class TreeIndex;
};

class BucketIter
{
    IndexNode *iter;
    IndexNode *head;
    bool isUnique;
    bool recordsOver;
    public:
    BucketIter(){iter = head = NULL;
                 isUnique=false; recordsOver = false;}
    void setHead(IndexNode *hd) { iter = head = hd; recordsOver=false;}
    BucketIter(IndexNode *head) { iter = head = head;
                 isUnique=false; recordsOver = false;}
    void setUnique() { isUnique = true; }
    bool getUnique() { return isUnique; }
    IndexNode* next();
    void reset() { iter = head; recordsOver=false;}
    friend class BucketList;
};
class BucketList
{
    IndexNode *head;
    public:
    BucketList(){ head = NULL;}
    BucketList(IndexNode *h){ head = h; }
    void *getBucketListHead(){ return head;}
    DbRetVal insert(Chunk *chunk, Database *db, void *key, void *tuple);
    DbRetVal remove(Chunk *chunk, Database *db, void *key);
    void print();
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
class TrieIndex;
class Index
{
    // create (one) object for each indexing mechanisms here 
    // Also need to make changes to getIndex() and destroy() methods 
    // accordingly for new index machanism.
    static HashIndex *hIdx;
    static TreeIndex *tIdx;
    static TrieIndex *iIdx;
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
    bool checkForUniqueKey(IndexNode *head,HashIndexInfo *info, void *tuple);
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

class TrieIndex: public Index
{
    public:
    DbRetVal insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    DbRetVal update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *info, void *tuple, bool undoFlag);
    bool checkForUniqueKey(IndexNode *head, IndexInfo *info, void *tuple);
    static void computeHashValues(DataType type, void *key, char *in, int length=0);
    static DbRetVal insertLogicalUndoLog(Database *sysdb, void *info);
    static DbRetVal deleteLogicalUndoLog(Database *sysdb, void *info);
    static void displayAll(TrieNode *node, int level =1);
    static void printTrieNode(TrieNode *node, int level);
    private:
    DbRetVal addToValueList(Database*, void**, Chunk*, IndexInfo*, void*, void*);
    DbRetVal removeFromValueList(Database*, void**, Chunk*, void*, void*);

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
        tree = 3,
        trie = 4

};
class IndexInfo
{
    public:
    IndexType indType;
    int fldOffset;
    bool isUnique;
    DataType type;
    int compLength;
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
    void print() 
    {
        printf("HashIndexInfo indexPtr:%p noOfBuckets:%d buckets:%p \n",indexPtr, noOfBuckets, buckets);
    }
    ~HashIndexInfo() { idxFldList.removeAll(); }
};
#endif

