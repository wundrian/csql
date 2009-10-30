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
#ifndef ORDERTABLE_IMPL_H
#define ORDERTABLE_IMPL_H
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
#include<TableImpl.h>
#include<OrderByTree.h>

class OrderTableImpl:public Table
{
    private:
    char tblName_[IDENTIFIER_LENGTH];
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List fldProjList;
    List fldOrderByList;
    Table *tableHdl;
    List sortList; //change this list to some other data structure
    ListIterator sortIter;
    OrderByTree sortTree;
    long long nullValues;
    int orderBySize;
    int projSize;
    char *orderBuffer;
    void *orderBindBuf;
    bool isPlanCreated;

    DbRetVal copyValuesToBindBuffer(void *tuple);
    void setNullableForProj();
    public:
    OrderTableImpl();
    virtual ~OrderTableImpl();
    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return tableHdl->getFieldInfo(fieldName, info); }
    void setTable(Table *impl){ tableHdl = impl;}
    Table* getTableHdl(){ return tableHdl; }
    DbRetVal closeScan();
    void *getBindFldAddr(const char *name);
    DbRetVal bindFld(const char *name, void *val);
    void setProjList(List bindFldList) { fldProjList = bindFldList; }
    DbRetVal setOrderBy(const char *name, bool isDesc=false);
    DbRetVal setOrderByList(List orderList);
    void setDistinct() { sortTree.setDistinct(true); }
    OrderByType getOrderType();
    void checkAndSetSortAlgorithm();
    DbRetVal markFldNull(const char *name){ return ErrBadCall;}
    DbRetVal markFldNull(int colpos){ return ErrBadCall;}
    bool isFldNull(const char *name);
    bool isFldNull(int colpos);
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
    DbRetVal compact(){ return ErrBadCall;}
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
    char* getAliasName(){return tableHdl->getAliasName(); }
    List getFieldNameList(){ List dummyList; return dummyList;}
    DbRetVal execute();
    DbRetVal insert();
    DbRetVal insertDistinct();
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
    DbRetVal optimize()
        { printf("Wrong call\n"); return OK; }
    bool isFKTable(){return false;}
    ScanType getScanType(){ return unknownScan;}
    bool hasIndex(char *fName){ return false;}
    void setCondition(Condition *) {}
    int computeOrderBySize();
};

#endif
