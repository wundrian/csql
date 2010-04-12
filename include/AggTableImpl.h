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
#ifndef AGGTABLE_IMPL_H
#define AGGTABLE_IMPL_H
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
#include<HeapAllocator.h>
#ifndef AGGTYPE
enum AggType
{
    AGG_MIN = 1,
    AGG_MAX,
    AGG_SUM,
    AGG_AVG,
    AGG_COUNT,
    AGG_UNKNOWN
};

#define AGGTYPE
#endif
#include<TableImpl.h>
class AggFldDef
{
    public:
    char fldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *bindBuf;
    void *appBuf;
    AggType aType;
    bool alreadyBinded;
    bool isNullable;
    AggFldDef()
    {
        strcpy(fldName, "");
        type=typeUnknown;
        length=0;
        bindBuf=NULL;
        appBuf=NULL;
        aType=AGG_UNKNOWN;
        alreadyBinded=false;
        isNullable=false;
    }
};

class AggTableImpl:public Table
{
    private:
    char tblName_[IDENTIFIER_LENGTH];
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List fldList;
    List fldGroupList;
    Table *tableHdl;
    List aggNodes; //change this list to some other data structure
    ListIterator aggNodeIter;
    HashMap aggNodeMap; //for faster lookup
    Predicate *havingPred;
    int grpNullInfo;
    long long prjNullInfo;
    int aggNodeSize;
    int groupSize;
    char *grpFldBuffer;

    bool optGrpIntNoNull;
    void *grpBindBuf;

    DbRetVal copyValuesToBindBuffer(void *tuple);
    public:
    AggTableImpl();
    virtual ~AggTableImpl();
    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return tableHdl->getFieldInfo(fieldName, info); }
    void* insertOrGetAggNode();
    void setTable(Table *impl){ tableHdl = impl;}
    Table* getTableHdl(){ return tableHdl; }
    DbRetVal closeScan();
    void *getBindFldAddr(const char *name);
    DbRetVal bindFld(const char *name, void *val, bool dummy=false);
    DbRetVal bindFld(const char *name, AggType aggType, void *val);
    DbRetVal setGroup(const char *name, void *val);
    bool isFldPresentInGrp(char *fname);
    int computeGrpNodeSize();
    void* getGroupValueBuffer();
    int getAggOffset(char *fname, AggType aggType);
    DbRetVal copyValuesFromGrpBindBuf(char *grpFldBuf, char *fldName);
    void setCondition(Condition *p){ havingPred = p->getPredicate();}
    DbRetVal markFldNull(const char *name){ return OK;}
    inline DbRetVal markFldNull(int colpos){
        SETBIT(grpNullInfo, colpos-1);
        return OK;
    }
    bool isFldNull(const char *name);
    inline bool isFldNull(int colpos) {
       if (colpos <= 32) { if (BITSET(prjNullInfo, colpos-1)) return true; }
       else if (BITSET(*(int *)((char *)&prjNullInfo + 4), colpos-1)) 
           return true;
       return false;
    }
    void clearFldNull(const char *name){}
    inline void clearFldNull(int colpos){
       if (colpos <= 32) CLEARBIT(prjNullInfo, colpos-1);
       else CLEARBIT(*(int *)((char*)&prjNullInfo + 4), colpos-1);
    }
    DbRetVal compact(){ return OK;}
    int getFldPos(char *name){ return 0;}
    void resetNullinfo(){}
    DbRetVal insertTuple() { return ErrBadCall; }
    DbRetVal updateTuple() { return ErrBadCall; }
    DbRetVal deleteTuple() { return ErrBadCall; }
    int deleteWhere() { return ErrBadCall; }
    int truncate() { return ErrBadCall; }
    long spaceUsed() { return 0; }
    int pagesUsed() { return 0; }
    DbRetVal lock(bool shared) { return ErrBadCall; }
    DbRetVal unlock(){ return ErrBadCall; }
    DbRetVal setUndoLogging(bool flag) { return ErrBadCall; }
    void printSQLIndexString(FILE *fp, int fd){ };
    void printSQLForeignString(){}
    char* getName() { return tableHdl->getName(); }
    char* getAliasName(){ return tableHdl->getAliasName();}    
    List getFieldNameList(){ List list; return list;}
    DbRetVal execute();
    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal close();
    long numTuples();
    void printInfo();
    bool pushPredicate(Predicate *pred)
        { printf("Wrong call\n"); return false; }
    void setPredicate(Predicate *pred) 
        { printf("Wrong call\n"); }
    bool isTableInvolved(char *tableName)
        { printf("Wrong call\n"); return false; }
    void printPlan(int space);
    DbRetVal optimize();
    bool isFKTable(){return false;}
    ScanType getScanType(){ return unknownScan;}
    bool hasIndex(char *fName){ return false;}
    AggType getAggType(const char *aggName, char *fldName);
};

#endif
