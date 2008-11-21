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
    char tabFieldName[IDENTIFIER_LENGTH*2];
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
    bool availableLeft;

    JoinType jType;
    ListIterator rsIter;
    bool isNestedLoop;
    bool rightExhausted;
    DbRetVal copyValuesToBindBuffer(void *tuple);
    JoinCondition jCondition;
    Predicate *pred;

    public:
    JoinTableImpl();
    virtual ~JoinTableImpl();

    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info);

    void setTable(Table *left, Table *right)
    { leftTableHdl = left; rightTableHdl = right; }

    void closeScan();
    void setJoinType(JoinType type) { jType = type; }
    //binding
    DbRetVal bindFld(const char *name, void *val);
    DbRetVal setJoinCondition(const char *fldname1, ComparisionOp op,  
                              const char *fldname2);

     void setCondition(Condition *p)
     { if (p) pred = p->getPredicate(); else pred = NULL;}

    void markFldNull(const char *name){}
    void markFldNull(int colpos){}
    bool isFldNull(const char *name){return false;}
    bool isFldNull(int colpos){return false;}
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
    void resetNullinfo(){ }
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
    List getFieldNameList();
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
    void *getBindFldAddr(const char *name);

};


#endif
