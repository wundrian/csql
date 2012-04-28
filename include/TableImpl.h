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
#include<AggTableImpl.h>//for AggType
#ifndef SCANTYPE
enum ScanType
{
    fullTableScan = 0,
    hashIndexScan,
    treeIndexScan,
    unknownScan
};
#define SCANTYPE
#endif

static char ScanTypeNames[][10] =
{
    "TableScan", "HashScan", "TreeScan", "Invalid"
};

class Predicate;

class TupleIterator
{
    Predicate *pred_;
    ScanType scanType_;
    ChunkIterator *cIter;
    BucketIter *bIter;
    TreeIter *tIter;
    IndexInfo *info;
    char *keyBuffer;
    char *keyPtr;
    ComparisionOp op;
    void *chunkPtr_;
    int procSlot;
    bool isBetween;
    bool isPointLook;
    bool shouldNullCheck; 
    bool isClosed;
    TupleIterator() { }
    public:
    TupleIterator(Predicate *p, ScanType t, IndexInfo *i, void *cptr, int pslot,bool between , bool isPtLook,bool nullflag)
    { bIter = new BucketIter(); 
      cIter = new ChunkIterator();; 
      tIter = new TreeIter(); 
      keyBuffer = NULL;
      pred_ = p ; scanType_ = t; info = i; chunkPtr_ = cptr; 
      isClosed =true;
      procSlot =pslot; isBetween=between; isPointLook=isPtLook; shouldNullCheck=nullflag;
    }
    DbRetVal setPlan();
    
    ~TupleIterator() 
	{ 
        if (bIter) { delete bIter; bIter = NULL; }
        if (cIter) { delete cIter; cIter = NULL; }
        if (tIter) { delete tIter; tIter = NULL; }
        if (keyBuffer) { ::free(keyBuffer); keyBuffer = NULL; }
    }
    bool isIterClosed() { return isClosed; }
    bool isBetInvolved(){ return isBetween;}
    void setBetInvolved(bool between){ isBetween=between;}
    bool isPointLookInvolved(){return isPointLook;}
    DbRetVal open();
    void* next();
    void* prev();//used only for tree iter during deleteTuple
    void reset();
    DbRetVal close();
};
class DllExport TableImpl:public Table
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
    void* vcChunkPtr_;
    void *curTuple_; //holds the current tuple ptr. moved during fetch() calls

    Predicate *pred_;
    List predList;
    ScanType scanType_;
    //ChunkIterator *iter;
    //BucketIter *bIter;

    TupleIterator *iter;

    bool loadFlag;
    char aliasName[IDENTIFIER_LENGTH];

    public:
    FieldList fldList_;
    List bindList_;
    void **bindListArray_;
    int numBindFlds_;
    int numIndexes_;
    int numFkRelation_;
    char** indexPtr_; // array of index ptrs to the catalog table for the indexes of this table.
    IndexInfo **idxInfo;
    int useIndex_;//offet in the above array indexPtr_ for scan
    bool isPlanCreated;
    bool isPointLook;
    bool isBetween;
    Database *db_;
    Database *sysDB_;
    void *ptrToAuto;
    long long tempAutoVal;
    //Either one of the below is populated based on the no of fields and 
    //is used for tuple insertions
    bool isIntUsedForNULL;
    int iNullInfo;
    char *cNullInfo;
    int iNotNullInfo;
    char *cNotNullInfo;
    //Table *fkTbl;
    List tblList;
    List tblFkList;
    bool isFkTbl;
    bool isPkTbl; 
    bool shouldNullSearch;
    private:

    //copy Values from binded buffer to tuple pointed by arg
    DbRetVal copyValuesFromBindBuffer(void *tuple, bool isInsert=true);
    DbRetVal copyValuesToBindBuffer(void *tuple);
    void setNullBit(int fldpos);
    void clearNullBit(int fldpos);
    DbRetVal insertIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal updateIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal deleteIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    bool isFKTable(){return isFkTbl;};
    DbRetVal createPlan();
    Chunk* getSystemTableChunk(CatalogTableID id)
    {
        return sysDB_->getSystemDatabaseChunk(id);
    }
    DbRetVal trySharedLock(void *curTuple, Transaction **trans);
    DbRetVal tryExclusiveLock(void *curTuple, Transaction **trans);
    DbRetVal getCheckpointMutex();


    public:
    TableImpl() { db_ = NULL; chunkPtr_ = NULL; vcChunkPtr_=NULL; iter = NULL;
        idxInfo = NULL; indexPtr_ = NULL; scanType_ = unknownScan; 
        pred_ = NULL; useIndex_ = -1; numFlds_ = 0; bindListArray_ = NULL;
        iNullInfo = 0; cNullInfo = NULL; isIntUsedForNULL = true; 
        iNotNullInfo = 0; cNotNullInfo = NULL; curTuple_ = NULL;
        isPlanCreated = false; loadFlag = false;isFkTbl=false;isPkTbl=false;numFkRelation_=0; shouldNullSearch = false;}
    ~TableImpl();

    void setDB(Database *db) { db_ = db; }
    Database* getDB() { return db_;}
    void setSystemDB(Database *db) { sysDB_ = db; }
    void setLockManager(LockManager *lmgr) { lMgr_ = lmgr; }
    void setTrans(Transaction **t) { trans = t; }
    inline void setCurTuple(void *tuple){ curTuple_=tuple; }
    DataType getFieldType(const char *name)
        { return fldList_.getFieldType(name);   }
    int getFieldOffset(const char *name)
        { return fldList_.getFieldOffset(name); }
    size_t getFieldLength(const char *name)
        { return fldList_.getFieldLength(name); }
    int getNumFields() { return numFlds_; }
    void fillFieldInfo(int pos, void* val)
        { return fldList_.fillFieldInfo(pos,val); }
    
    long long getLastInsertedVal(DbRetVal &rv);
    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
    { 
        char tblName[IDENTIFIER_LENGTH];
        char fldName[IDENTIFIER_LENGTH];
        getTableNameAlone((char*)fieldName, tblName);
        getFieldNameAlone((char*)fieldName, fldName);
        if (0 == strcmp(tblName, "") || 0 ==strcmp(tblName, getName()) ||
            0 == strcmp(tblName, getAliasName()))
            return fldList_.getFieldInfo(fldName, info); 
        else
            return ErrNotExists;
    }
    DbRetVal getQualifiedName(const char *fldname, char *qualName);

    List getFieldNameList();

    // search predicate
     void setCondition(Condition *p); 
     //{ isPlanCreated = false; if (p) pred_ = p->getPredicate(); else pred_ = NULL;}

    //binding
    DbRetVal bindFld(const char *name, void *val, bool isNullExpl=false);
    void *getBindFldAddr(const char *name);
    int getFldPos(char *name);
    DbRetVal markFldNull(const char *name);
    DbRetVal markFldNull(int colpos);
    bool isFldNull(const char *name);
    bool isFldNull(int colpos);

    void clearFldNull(const char *name);
    void clearFldNull(int colpos);
    void resetNullinfo();
    DbRetVal insertTuple();
    DbRetVal updateTuple();

    DbRetVal deleteTuple();
    int deleteWhere();
    int truncate();

    DbRetVal execute();
    bool isPkTableHasRecord(char *name,TableImpl *fkTbl,bool isInsert);
    bool isFkTableHasRecord(char *name,TableImpl *fkTbl);
    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal fetchAgg(const char *fldName, AggType aType, void *buf, bool &noRec);

    DbRetVal close();
    DbRetVal closeScan();


    long spaceUsed();
    long numTuples();
    int pagesUsed();
    void printInfo();
    void printPlan(int space);

    DbRetVal lock(bool shared);
    DbRetVal unlock();
    DbRetVal takeTableMutex();
    DbRetVal releaseTableMutex();
   
    DbRetVal setUndoLogging(bool flag) { loadFlag = flag; return OK;}

    void printSQLIndexString(FILE *fp, int fd);
    void printSQLForeignString();
    DbRetVal optimize();
    bool isTableInvolved(char *tblName);
    bool pushPredicate(Predicate *pred);
    void setPredicate(Predicate *pred);
    ScanType getScanType() { return scanType_; }
    bool hasIndex(char *fldName);
    IndexType getIndexType(char *fldName, int* pos);
    void addPredicate(char *fName, ComparisionOp op, void *buf);
    DbRetVal compact();
    DbRetVal compactIndexNode( void *indexPtr);
    char* getName() { return tblName_; }
    int getId() { return tblID_; }
    char* getAliasName() { return aliasName; }
    void setAliasName(char *name);
    void setTableInfo(char *name, int tblid, size_t  length,
                       int numFld, int numIdx, void *chunk, void *vcchunk);
    void setLoading(bool flag) { loadFlag = flag; }
    friend class DatabaseManagerImpl;
};


#endif
