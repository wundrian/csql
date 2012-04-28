/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef STATEMENT_H
#define STATEMENT_H
#include "Parser.h"
#include "CacheTableLoader.h"
class Statement
{
protected:
    ParsedData *parsedData;
    DatabaseManager *dbMgr;
    char userName[IDENTIFIER_LENGTH];
    UserManager *usrMgr;

public:
    /**
     * Set UserManager instance (called from upper layer SqlStatement)
     * @param mgr the connection's UserManager instance. You are not responsible for managing this pointer!
     * @param user Name of the currently logged in user.
     */
    void setUserManager(UserManager *mgr, const char *user)
    { 
        usrMgr = mgr;
        strncpy(userName, user, IDENTIFIER_LENGTH);
    }
    void setParsedData(ParsedData *pData) {  parsedData = pData; }
    void setDbMgr(DatabaseManager *dbmgr) { dbMgr = dbmgr; }


    virtual int noOfParamFields() { return  0; }
    virtual DbRetVal execute(int &rowsAffected)=0;
    virtual DbRetVal setParam(int paramNo, void *value)=0;

    virtual DbRetVal setShortParam(int paramNo, short value)=0;
    virtual DbRetVal setIntParam(int paramNo, int value)=0;
    virtual DbRetVal setLongParam(int paramNo, long value)=0;
    virtual DbRetVal setLongLongParam(int paramNo, long long value)=0;
    virtual DbRetVal setByteIntParam(int paramNo, ByteInt value)=0;
    virtual DbRetVal setFloatParam(int paramNo, float value)=0;
    virtual DbRetVal setDoubleParam(int paramNo, double value)=0;
    virtual DbRetVal setStringParam(int paramNo, char *value)=0;
    virtual DbRetVal setDateParam(int paramNo, Date value)=0;
    virtual DbRetVal setTimeParam(int paramNo, Time value)=0;
    virtual DbRetVal setTimeStampParam(int paramNo, TimeStamp value)=0;
    virtual DbRetVal setBinaryParam(int paramNo, void *value, int length)=0;
    virtual DbRetVal getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info) = 0;
    virtual List getFieldNameList(const char *tblName, DbRetVal &rv)=0;
    virtual DbRetVal resolve()=0;
    virtual bool isFldNull(int pos)=0;
    virtual bool isFldNull(char *name)=0;
    virtual int getFldPos(char *name)=0;
    virtual DbRetVal setNull(int pos)=0;
    virtual ResultSetPlan getResultSetPlan()=0;
    virtual long long getLastInsertedVal(DbRetVal &rv)=0;
    virtual ~Statement(){}
};

class DmlStatement : public Statement
{
    protected:
    Table *table;

    void **params;
    //used to store FieldValue* for insert or ConditionValue* for other stmts

    char **paramValues;
    int totalParams;

    public:
    int noOfParamFields() { return totalParams; }
    virtual DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info) =0;

    virtual DbRetVal execute(int &rowsAffected)=0;
    virtual DbRetVal setParam(int paramNo, void *value)=0;

    virtual DbRetVal setShortParam(int paramNo, short value)=0;
    virtual DbRetVal setIntParam(int paramNo, int value)=0;
    virtual DbRetVal setLongParam(int paramNo, long value)=0;
    virtual DbRetVal setLongLongParam(int paramNo, long long value)=0;
    virtual DbRetVal setByteIntParam(int paramNo, ByteInt value)=0;
    virtual DbRetVal setFloatParam(int paramNo, float value)=0;
    virtual DbRetVal setDoubleParam(int paramNo, double value)=0;
    virtual DbRetVal setStringParam(int paramNo, char *value)=0;
    virtual DbRetVal setDateParam(int paramNo, Date value)=0;
    virtual DbRetVal setTimeParam(int paramNo, Time value)=0;
    virtual DbRetVal setTimeStampParam(int paramNo, TimeStamp value)=0;
    virtual DbRetVal setBinaryParam(int paramNo, void *value, int length)=0;
    virtual bool isFldNull(int pos)=0;
    virtual bool isFldNull(char *fldName)=0;
    virtual DbRetVal setNull(int pos)=0;
    virtual DbRetVal resolve()=0;
    virtual void* getParamValuePtr( int pos )=0;
    virtual int getFldPos(char *name)=0;
    virtual ~DmlStatement(){}
    virtual ResultSetPlan getResultSetPlan()=0;
    virtual long long getLastInsertedVal(DbRetVal &rv)=0;
    void setLoading(bool flag) { table->setLoading(flag); }
    DbRetVal getFieldInfo(const char *tblName, const char *fldName, 
                                                             FieldInfo *&info);
    List getFieldNameList(const char *tblName, DbRetVal &rv);
};

class InsStatement : public DmlStatement
{
    public:
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);

    DbRetVal execute(int &rowsAffected);
    DbRetVal setParam(int paramNo, void *value);

    DbRetVal setShortParam(int paramNo, short value);
    DbRetVal setIntParam(int paramNo, int value);
    DbRetVal setLongParam(int paramNo, long value);
    DbRetVal setLongLongParam(int paramNo, long long value);
    DbRetVal setByteIntParam(int paramNo, ByteInt value);
    DbRetVal setFloatParam(int paramNo, float value);
    DbRetVal setDoubleParam(int paramNo, double value);
    DbRetVal setStringParam(int paramNo, char *value);
    DbRetVal setDateParam(int paramNo, Date value);
    DbRetVal setTimeParam(int paramNo, Time value);
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value);
	DbRetVal setBinaryParam(int paramNo, void *value, int length);
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){return table->isFldNull(fldName);}
    void* getParamValuePtr( int );
    int getFldPos(char *name);
    DbRetVal setNull(int pos);
    long long getLastInsertedVal(DbRetVal &rv);
    DbRetVal resolve();
    ResultSetPlan getResultSetPlan(){return Normal;}
    InsStatement();
    ~InsStatement();
};

class SelStatement : public DmlStatement
{
    private:
    DbRetVal resolveStar();
    DbRetVal setBindFieldAndValues();
    DbRetVal resolveForCondition();
    DbRetVal resolveDistinct();

    public:
    FieldValue **bindFields;
    char **bindFieldValues;
    int totalFields;

    bool isPointReturned;
    bool handleAggWithTbl;
    bool isRecLimitReached;
    bool isOffsetReached;
    int numRecords;
    bool isExplain;
    bool isJoin;

    DbRetVal execute(int &rowsAffected);
    DbRetVal setParam(int paramNo, void *value);

    DbRetVal setShortParam(int paramNo, short value);
    DbRetVal setIntParam(int paramNo, int value);
    DbRetVal setLongParam(int paramNo, long value);
    DbRetVal setLongLongParam(int paramNo, long long value);
    DbRetVal setByteIntParam(int paramNo, ByteInt value);
    DbRetVal setFloatParam(int paramNo, float value);
    DbRetVal setDoubleParam(int paramNo, double value);
    DbRetVal setStringParam(int paramNo, char *value);
    DbRetVal setDateParam(int paramNo, Date value);
    DbRetVal setTimeParam(int paramNo, Time value);
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value);
    DbRetVal setBinaryParam(int paramNo, void *value, int length);
    
    DbRetVal replaceStarWithFirstFldName(FieldName *name);
    DbRetVal resolveGroupFld(AggTableImpl *impl, bool &isGrpFld);
    DbRetVal resolveOrderByFld();
    bool isInProjectionList(char *name, AggType aType);
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){ return table->isFldNull(fldName); }
    int getFldPos(char *name);
    DbRetVal setNull(int pos){ return ErrBadCall;}
    DbRetVal close();
    DbRetVal resolve();
    long long getLastInsertedVal(DbRetVal &rv){rv = ErrBadCall;return 0;}
 
    void* handleSingleTableAggWithoutGroup();
    bool isGroupFld(char *fName);
    bool isJoinStmt() { return isJoin; }

    SelStatement();
    ~SelStatement();

    bool isTableAlreadyPresent(char* tblName, char* aliasName);
    DbRetVal openTables();
//    DbRetVal resolveGroupFld(AggTableImpl *impl);

    DbRetVal setBindField(int pos, void* value);

    int noOfProjFields();
    DbRetVal getProjFldInfo (int projpos, FieldInfo *&fInfo);
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    
    void *getParamValuePtr( int );
    DataType getFieldType( int );
    int getFieldLength( int );
    char* getFieldName( int );

    void *fetch();
    void *fetch(DbRetVal &rv);
    void *fetchAndPrint(bool SQL);
    void *next();
    void *getFieldValuePtr( int );
    void *getFieldValuePtr( char *name );
    void getProjFieldType(int *data);
    ResultSetPlan getResultSetPlan(){ return Normal; }
};

class UpdStatement : public DmlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal setParam(int paramNo, void *value);

    DbRetVal setShortParam(int paramNo, short value);
    DbRetVal setIntParam(int paramNo, int value);
    DbRetVal setLongParam(int paramNo, long value);
    DbRetVal setLongLongParam(int paramNo, long long value);
    DbRetVal setByteIntParam(int paramNo, ByteInt value);
    DbRetVal setFloatParam(int paramNo, float value);
    DbRetVal setDoubleParam(int paramNo, double value);
    DbRetVal setStringParam(int paramNo, char *value);
    DbRetVal setDateParam(int paramNo, Date value);
    DbRetVal setTimeParam(int paramNo, Time value);
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value);
    DbRetVal setBinaryParam(int paramNo, void *value, int length);
    void* getParamValuePtr(int);
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){return table->isFldNull(fldName);}
    int getFldPos(char *name);
    DbRetVal setNull(int pos);
    DbRetVal resolve();
    long long getLastInsertedVal(DbRetVal &rv){ rv=ErrBadCall; return 0;}
    UpdStatement();
    ~UpdStatement();
    ResultSetPlan getResultSetPlan() {return Normal;}
    int totalAssignParams;
    DbRetVal resolveForAssignment();
    ResultSetPlan plan;
};

class DelStatement : public DmlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal setParam(int paramNo, void *value);

    DbRetVal setShortParam(int paramNo, short value);
    DbRetVal setIntParam(int paramNo, int value);
    DbRetVal setLongParam(int paramNo, long value);
    DbRetVal setLongLongParam(int paramNo, long long value);
    DbRetVal setByteIntParam(int paramNo, ByteInt value);
    DbRetVal setFloatParam(int paramNo, float value);
    DbRetVal setDoubleParam(int paramNo, double value);
    DbRetVal setStringParam(int paramNo, char *value);
    DbRetVal setDateParam(int paramNo, Date value);
    DbRetVal setTimeParam(int paramNo, Time value);
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value);
    DbRetVal setBinaryParam(int paramNo, void *value, int length);
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){return table->isFldNull(fldName);}
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    void* getParamValuePtr(int);
    DbRetVal setNull(int pos){ return ErrBadCall;}
    DbRetVal resolve();
    long long getLastInsertedVal(DbRetVal &rv){ rv = ErrBadCall;return 0;}
    DelStatement();
    ~DelStatement();
    int getFldPos(char *name);
    DbRetVal resolveForCondition(); //TODO::put this is Statement class, duplicated from SelStatement.
    ResultSetPlan getResultSetPlan(){return Normal;}
};

class MetadataStatement : public DmlStatement
{
    public:
    FieldValue **bindFields;
    char **bindFieldValues;
    int totalFields;
    ListIterator  dataListIter;

    int numRecords;
    bool isPlanFreed;
    bool isSecondFetch;
    ResultSetPlan plan;
    DbRetVal execute(int &rowsAffected);
    DbRetVal setParam(int paramNo, void *value){return OK;};

    DbRetVal setShortParam(int paramNo, short value){ return OK;};
    DbRetVal setIntParam(int paramNo, int value){ return OK;};
    DbRetVal setLongParam(int paramNo, long value){ return OK;};
    DbRetVal setLongLongParam(int paramNo, long long value){ return OK;};
    DbRetVal setByteIntParam(int paramNo, ByteInt value){ return OK;};
    DbRetVal setFloatParam(int paramNo, float value){ return OK;};
    DbRetVal setDoubleParam(int paramNo, double value){ return OK;};
    DbRetVal setStringParam(int paramNo, char *value){ return OK;};
    DbRetVal setDateParam(int paramNo, Date value){ return OK;};
    DbRetVal setTimeParam(int paramNo, Time value){ return OK;};
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value){ return OK;};
    DbRetVal setBinaryParam(int paramNo, void *value, int length){ return OK;};

    DbRetVal replaceStarWithFirstFldName(FieldName *name){ return OK;};
    DbRetVal resolveGroupFld(AggTableImpl *impl){ return OK;};
    DbRetVal resolveOrderByFld(){ return OK;};
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){
        if(plan != Normal) return false;
        return table->isFldNull(fldName); }
    int getFldPos(char *name);
    DbRetVal setNull(int pos){ return ErrBadCall;}
    DbRetVal close();
    DbRetVal resolve();

    MetadataStatement();
    ~MetadataStatement();
    long long getLastInsertedVal(DbRetVal &rv){rv=ErrBadCall; return 0;}
    void *getParamValuePtr( int ){ return NULL;}
    DbRetVal openTables();
    DbRetVal setBindField(int pos, void* value);
    int noOfProjFields();
    DbRetVal getProjFldInfo (int projpos, FieldInfo *&fInfo);
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    DataType getFieldType( int );
    int getFieldLength( int );
    char* getFieldName( int );
    
    void *fetch();
    void *fetch(DbRetVal &rv);
    void *fetchAndPrint(bool SQL);
    void *next();
    void *getFieldValuePtr( int );
    void *getFieldValuePtr( char *name );
    void getProjFieldType(int *data);
    void *fetchMetaData();
    void freeMetadata();
    ResultSetPlan getResultSetPlan(){return plan;}
    ListIterator getExportKeyIterator();
    ListIterator getImportKeyIterator();
    ListIterator getDataTypeInfoIterator();
};
class CopyTblStatement : public DmlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    DbRetVal setParam(int paramNo, void *value);
    DbRetVal setShortParam(int paramNo, short value);
    DbRetVal setIntParam(int paramNo, int value);
    DbRetVal setLongParam(int paramNo, long value);
    DbRetVal setLongLongParam(int paramNo, long long value);
    DbRetVal setByteIntParam(int paramNo, ByteInt value);
    DbRetVal setFloatParam(int paramNo, float value);
    DbRetVal setDoubleParam(int paramNo, double value);
    DbRetVal setStringParam(int paramNo, char *value);
    DbRetVal setDateParam(int paramNo, Date value);
    DbRetVal setTimeParam(int paramNo, Time value);
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value);
    DbRetVal setBinaryParam(int paramNo, void *value, int length);
    bool isFldNull(int pos){return table->isFldNull(pos);}
    bool isFldNull(char *fldName){return table->isFldNull(fldName);}
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    void* getParamValuePtr(int);
    DbRetVal setNull(int pos){ return ErrBadCall;}
    int getFldPos(char *name);
    ResultSetPlan getResultSetPlan(){return Normal;}
    DbRetVal resolveForInsert();
    DbRetVal resolveForCreate();
    long long getLastInsertedVal(DbRetVal &rv){ rv = ErrBadCall; return 0;}
    CopyTblStatement();
    ~CopyTblStatement();
    private:
    void **bindFieldValues;
    int totalFields;
    Statement *innerSelStmt;
    char tblName[IDENTIFIER_LENGTH];
};



class DdlStatement : public Statement
{
    public:
    DbRetVal execute(int &rowsAffected)=0; 
    //TODO: i think rowsAffected is not part of ddl - gopal said its design decision
    DbRetVal resolve()=0;

    DbRetVal setParam(int paramNo, void *value) { return ErrBadCall; }
    DbRetVal setShortParam(int paramNo, short value) { return ErrBadCall; }
    DbRetVal setIntParam(int paramNo, int value) { return ErrBadCall; }
    DbRetVal setLongParam(int paramNo, long value) { return ErrBadCall; }
    DbRetVal setLongLongParam(int paramNo, long long value) { return ErrBadCall; }
    DbRetVal setByteIntParam(int paramNo, ByteInt value) { return ErrBadCall; }
    DbRetVal setFloatParam(int paramNo, float value) { return ErrBadCall; }
    DbRetVal setDoubleParam(int paramNo, double value) { return ErrBadCall; }
    DbRetVal setStringParam(int paramNo, char *value) { return ErrBadCall; }
    DbRetVal setDateParam(int paramNo, Date value) { return ErrBadCall; }
    DbRetVal setTimeParam(int paramNo, Time value) { return ErrBadCall; }
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value) {  return ErrBadCall;}
    DbRetVal setBinaryParam(int paramNo, void *value, int length) {  return ErrBadCall;}
    DbRetVal getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info){return ErrBadCall; }
    List getFieldNameList(const char *tblName, DbRetVal &rv) {
        List dummylist; rv = ErrBadCall; return dummylist;
    }
    bool isFldNull(int pos){  return false;}
    bool isFldNull(char *fldName ){ return false;}
    int getFldPos(char *name){ return -1;}
    long long getLastInsertedVal(DbRetVal &rv){ rv = ErrBadCall; return 0;}
    DbRetVal setNull(int pos){ return ErrBadCall;}
    ResultSetPlan getResultSetPlan(){ ResultSetPlan dummy; return dummy;}
};

class CreateTblStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    DbRetVal checkForDot(char *name);
    CreateTblStatement();
    ~CreateTblStatement();
   
    private:
    char tblName[IDENTIFIER_LENGTH];  
    TableDef tblDef; 
};

class CreateIdxStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve(){return OK; }

    CreateIdxStatement();
    ~CreateIdxStatement();

};

class DropTblStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve(){return OK; }

    DropTblStatement(){}
    ~DropTblStatement(){}
};
class TruncateTblStatement : public DdlStatement
{
    Table *table;
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();

    TruncateTblStatement(){}
    ~TruncateTblStatement(){}
};


class CacheTblStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    CacheTableLoader cacheLoader;
    CacheTblStatement(){}

};

class UserTblStatement : public DdlStatement
{
    public:
    
    UserNodeType uType;
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    
    UserTblStatement(){ }
};
class AlterTblStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve(); 
    DbRetVal resolveForModifyColumn();
    DbRetVal resolveForAddDropColumn();
    DbRetVal executeForAddDropColumn(int &rowsAffected);
    DbRetVal executeForModifyColumn(int &rowsAffected){}
    DbRetVal createIndex(const char *oldName,const char *newName);
    AlterTblStatement();
    ~AlterTblStatement();
    AlterTableType altType;    
    void **bindFieldValues;
    int totalFields;
    int noOfOldTabFld;
    Table *table;
    TableDef tblDef;
};


class DropIdxStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve() {return OK; }
    DropIdxStatement(){}
    ~DropIdxStatement(){}
};
class CompactTblStatement : public DdlStatement
{
    Table *table;
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    CompactTblStatement(){ table=NULL;}
    ~CompactTblStatement(){}
};

class DclStatementImpl : public Statement
{
public:
    DclStatementImpl() {};
    ~DclStatementImpl() {};
    
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve();
    
    /* must implement complete interface */
    DbRetVal setParam(int paramNo, void *value) { return ErrBadCall; }
    DbRetVal setShortParam(int paramNo, short value) { return ErrBadCall; }
    DbRetVal setIntParam(int paramNo, int value) { return ErrBadCall; }
    DbRetVal setLongParam(int paramNo, long value) { return ErrBadCall; }
    DbRetVal setLongLongParam(int paramNo, long long value) { return ErrBadCall; }
    DbRetVal setByteIntParam(int paramNo, ByteInt value) { return ErrBadCall; }
    DbRetVal setFloatParam(int paramNo, float value) { return ErrBadCall; }
    DbRetVal setDoubleParam(int paramNo, double value) { return ErrBadCall; }
    DbRetVal setStringParam(int paramNo, char *value) { return ErrBadCall; }
    DbRetVal setDateParam(int paramNo, Date value) { return ErrBadCall; }
    DbRetVal setTimeParam(int paramNo, Time value) { return ErrBadCall; }
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value) {  return ErrBadCall;}
    DbRetVal setBinaryParam(int paramNo, void *value, int length) {  return ErrBadCall;}
    DbRetVal getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info){return ErrBadCall; }
    List getFieldNameList(const char *tblName, DbRetVal &rv) {
        List dummylist; rv = ErrBadCall; return dummylist;
    }
    bool isFldNull(int pos){  return false;}
    bool isFldNull(char *fldName ){ return false;}
    int getFldPos(char *name){ return -1;}
    long long getLastInsertedVal(DbRetVal &rv){ rv = ErrBadCall; return 0;}
    DbRetVal setNull(int pos){ return ErrBadCall;}
    ResultSetPlan getResultSetPlan(){ ResultSetPlan dummy; return dummy;}
    
private:
    int mapConditionValueList(List values, FieldConditionValMap &result);
    TableImpl *table;
};

class StatementFactory
{
    public:
    static Statement* getStatement(ParsedData *pData );
};
#endif
