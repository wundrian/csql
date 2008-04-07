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
#ifndef TABLE_IMPL_H
#define TABLE_IMPL_H
#include<os.h>
#include<DataType.h>
#include<Transaction.h>
#include<Database.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Info.h>
#include<Debug.h>
#include<DatabaseManagerImpl.h>
#include<Predicate.h>
enum ScanType
{
    fullTableScan = 0,
    hashIndexScan,
    treeIndexScan,
    unknownScan
};

class Predicate;

class TupleIterator
{
    Predicate *pred_;
    ScanType scanType_;
    ChunkIterator *cIter;
    BucketIter *bIter;
    IndexInfo *info;
    void *chunkPtr_;
    int procSlot;

    TupleIterator(){}
    public:
    TupleIterator(Predicate *p, ScanType t, IndexInfo *i, void *cptr, int pslot)
    { pred_ = p ; scanType_ = t; info = i; chunkPtr_ = cptr; procSlot =pslot;}
    DbRetVal open();
    void* next();
    DbRetVal close();

};
class TableImpl:public Table
{
    private:


    LockManager *lMgr_;
    Transaction **trans;
    //This is pointer to the pointer stored in the
    //Transaction manager.
    //If the transaction commits/aborts this pointer changes
    //and this will get that newly allocated transaction

    char tblName_[IDENTIFIER_LENGTH];
    int tblID_;
    size_t length_; //length of the tuple
    int numFlds_;
    void* chunkPtr_;
    void *curTuple_; //holds the current tuple ptr. moved during fetch() calls

    Predicate *pred_;
    ScanType scanType_;
    //ChunkIterator *iter;
    //BucketIter *bIter;

    TupleIterator *iter;

    bool undoFlag;

    public:
    FieldList fldList_;
    int numIndexes_;
    char** indexPtr_; // array of index ptrs to the catalog table for the indexes of this table.
    IndexInfo **idxInfo;
    int useIndex_;//offet in the above array indexPtr_ for scan
    bool isPlanCreated;

    Database *db_;
    Database *sysDB_;

    //Either one of the below is populated based on the no of fields and 
    //is used for tuple insertions
    bool isIntUsedForNULL;
    int iNullInfo;
    char *cNullInfo;
    int iNotNullInfo;
    char *cNotNullInfo;

    private:

    //copy Values from binded buffer to tuple pointed by arg
    DbRetVal copyValuesFromBindBuffer(void *tuple, bool isInsert=true);
    DbRetVal copyValuesToBindBuffer(void *tuple);
    void setNullBit(int fldpos);

    DbRetVal insertIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal updateIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal deleteIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);

    DbRetVal createPlan();
    Chunk* getSystemTableChunk(CatalogTableID id)
    {
        return sysDB_->getSystemDatabaseChunk(id);
    }

    public:
    TableImpl() { db_ = NULL; chunkPtr_ = NULL; iter = NULL;
        idxInfo = NULL; indexPtr_ = NULL; scanType_ = unknownScan; pred_ = NULL; useIndex_ = -1;
        iNullInfo = 0; cNullInfo = NULL; isIntUsedForNULL = true; 
        iNotNullInfo = 0; cNotNullInfo = NULL;
        isPlanCreated = false; undoFlag = true;}
    ~TableImpl();

    void setDB(Database *db) { db_ = db; }
    void setSystemDB(Database *db) { sysDB_ = db; }
    void setLockManager(LockManager *lmgr) { lMgr_ = lmgr; }
    void setTrans(Transaction **t) { trans = t; }

    DataType getFieldType(const char *name)
        { return fldList_.getFieldType(name);   }
    int getFieldOffset(const char *name)
        { return fldList_.getFieldOffset(name); }
    size_t getFieldLength(const char *name)
        { return fldList_.getFieldLength(name); }

    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return fldList_.getFieldInfo(fieldName, info); }

    List getFieldNameList();

    // search predicate
     void setCondition(Condition *p) 
     { isPlanCreated = false; if (p) pred_ = p->getPredicate(); else pred_ = NULL;}

    //binding
    DbRetVal bindFld(const char *name, void *val);

    void markFldNull(const char *name);
    void markFldNull(int colpos);
    bool isFldNull(const char *name);
    bool isFldNull(int colpos);


    void clearFldNull(const char *name);
    void clearFldNull(int colpos);


    DbRetVal insertTuple();
    DbRetVal updateTuple();

    DbRetVal deleteTuple();
    int deleteWhere();
    int truncate();

    DbRetVal execute();

    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);

    DbRetVal close();


    long spaceUsed();
    long numTuples();
    int pagesUsed();
    void printInfo();

    DbRetVal lock(bool shared);
    DbRetVal unlock();

    DbRetVal setUndoLogging(bool flag) { undoFlag = flag; }

    void printSQLIndexString();
    char* getName() { return tblName_; }
    void setTableInfo(char *name, int tblid, size_t  length,
                       int numFld, int numIdx, void *chunk);
    friend class DatabaseManagerImpl;
};


#endif
