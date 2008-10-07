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
#ifndef JOINTABLE_IMPL_H
#define JOINTABLE_IMPL_H
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
enum AggType
{
    AGG_MIN = 1,
    AGG_MAX,
    AGG_SUM,
    AGG_AVG,
    AGG_COUNT,
    AGG_UNKNOWN
};
class AggFldDef
{
    public:
    char fldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *bindBuf;
    void *appBuf;
    AggType atype;
    bool alreadyBinded;
    AggFldDef()
    {
        strcpy(fldName, "");
        type=typeUnknown;
        length=0;
        bindBuf=NULL;
        appBuf=NULL;
        atype=AGG_UNKNOWN;
        alreadyBinded=false;
    }
};

class AggTableImpl:public Table
{
    private:
    char tblName_[IDENTIFIER_LENGTH];
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List fldList;
    AggFldDef groupFld;
    Table *tableHdl;
    List aggNodes; //change this list to some other data structure
    ListIterator aggNodeIter;

    int aggNodeSize;
    DbRetVal copyValuesToBindBuffer(void *tuple);
    public:
    AggTableImpl();
    virtual ~AggTableImpl();
    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return ErrBadCall; }
    bool isGroupSet()
        {
        if (groupFld.type == typeUnknown) return false; else return true;
        }
    void* insertOrGet();
    void setTable(Table *impl){ tableHdl = impl;}
    Table* getTableHdl(){ return tableHdl; }
    void closeScan();
    void *getBindFldAddr(const char *name);
    DbRetVal bindFld(const char *name, void *val);
    DbRetVal bindFld(const char *name, AggType aggType, void *val);
    DbRetVal setGroup(const char *name, void *val);
    void setCondition(Condition *p){}
    void markFldNull(const char *name){}
    void markFldNull(int colpos){}
    bool isFldNull(const char *name){return false;}
    bool isFldNull(int colpos){return false;}
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
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
    void printSQLIndexString(){ };
    char* getName() { return tableHdl->getName(); }
    List getFieldNameList(){ List list; return list;}
    DbRetVal execute();
    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal close();
    long numTuples();
    void printInfo();
};






enum JoinType
{
    INNER_JOIN = 1,
    RIGHT_JOIN,
    LEFT_JOIN,
    FULL_JOIN,
    UNKNOWN_JOIN
};
class JoinProjFieldInfo
{
    public:
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *appBuf;
    void *bindBuf;
    JoinProjFieldInfo()
    {
        strcpy(tableName,""); strcpy(fieldName, "");
        type= typeUnknown; length =0; appBuf= NULL; bindBuf=NULL;
    }
};
class JoinCondition
{
    public:
    char tableName1[IDENTIFIER_LENGTH];
    char tableName2[IDENTIFIER_LENGTH];
    char fieldName1[IDENTIFIER_LENGTH];
    char fieldName2[IDENTIFIER_LENGTH];
    DataType type1;
    DataType type2;
    int length1;
    int length2;
    void *bindBuf1;
    void *bindBuf2;
    bool alreadyBinded1;
    bool alreadyBinded2;
    ComparisionOp op;
    JoinCondition()
    {
        strcpy(tableName1,""); strcpy(fieldName1, "");
        strcpy(tableName2,""); strcpy(fieldName2, "");
        type1= typeUnknown; length1 =0; bindBuf1=NULL;
        type2= typeUnknown; length2 =0; bindBuf2=NULL;
        alreadyBinded1=false; alreadyBinded2=false;
    }
    
};
class JoinTableImpl:public Table
{
    private:
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List projList;
    Table *leftTableHdl;
    Table *rightTableHdl;

    JoinType jType;
    ListIterator rsIter;
    bool isNestedLoop;
    bool rightExhausted;
    DbRetVal copyValuesToBindBuffer(void *tuple);
    JoinCondition jCondition;

    public:
    JoinTableImpl();
    virtual ~JoinTableImpl();

    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return ErrBadCall; }

    void setTable(Table *left, Table *right)
    { leftTableHdl = left; rightTableHdl = right; }

    void closeScan();
    void setJoinType(JoinType type) { jType = type; }
    //binding
    DbRetVal bindFld(const char *name, void *val);
    DbRetVal setJoinCondition(const char *fldname1, ComparisionOp op,  
                              const char *fldname2);
    void getFieldNameAlone(char*, char*);
    void getTableNameAlone(char*, char*);

    void setCondition(Condition *p){}
    void markFldNull(const char *name){}
    void markFldNull(int colpos){}
    bool isFldNull(const char *name){return false;}
    bool isFldNull(int colpos){return false;}
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
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
    void printSQLIndexString(){ };
    List getFieldNameList(){ List list; return list;}
    char* getName() { return NULL; }

    bool evaluate();
    DbRetVal execute();
    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal close();

    long numTuples();
    void printInfo();

};


#endif
