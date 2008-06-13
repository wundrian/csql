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
enum AggType
{
    AGG_MIN = 1,
    AGG_MAX,
    AGG_SUM,
    AGG_AVG,
    AGG_COUNT
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

    void* insertOrGet(); 
    void setTable(Table *impl){ tableHdl = impl;}
    void closeScan();

    //binding
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


#endif
