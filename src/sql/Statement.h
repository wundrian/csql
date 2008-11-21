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

class Statement
{
    protected:
    ParsedData *parsedData;
    DatabaseManager *dbMgr;

    public:
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
    virtual DbRetVal setBinaryParam(int paramNo, void *value)=0;

    virtual DbRetVal resolve()=0;
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
    virtual DbRetVal setBinaryParam(int paramNo, void *value)=0;

    virtual DbRetVal resolve()=0;
    virtual void* getParamValuePtr( int pos )=0;
    virtual ~DmlStatement(){}
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
	DbRetVal setBinaryParam(int paramNo, void *value);
    void* getParamValuePtr( int );
    DbRetVal resolve();
    InsStatement();
    ~InsStatement();
};

class SelStatement : public DmlStatement
{
    private:
    DbRetVal resolveStar();
    DbRetVal setBindFieldAndValues();
    DbRetVal resolveForCondition();

    public:
    FieldValue **bindFields;
    char **bindFieldValues;
    int totalFields;


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
    DbRetVal setBinaryParam(int paramNo, void *value);

    DbRetVal close();
    DbRetVal resolve();
    SelStatement();
    ~SelStatement();

    DbRetVal openTables();
    DbRetVal replaceStarWithFirstFldName(FieldName *name);
    DbRetVal resolveGroupFld(AggTableImpl *impl);

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
    DbRetVal setBinaryParam(int paramNo, void *value);
    void* getParamValuePtr(int);
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);


    DbRetVal resolve();
    UpdStatement();
    ~UpdStatement();

    int totalAssignParams;
    DbRetVal resolveForAssignment();
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
    DbRetVal setBinaryParam(int paramNo, void *value);

    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);
    void* getParamValuePtr(int);
    DbRetVal resolve();
    DelStatement();
    ~DelStatement();

    DbRetVal resolveForCondition(); //TODO::put this is Statement class, duplicated from SelStatement.

};

class DdlStatement : public Statement
{
    public:
    DbRetVal execute(int &rowsAffected)=0; 
    //TODO: i think rowsAffected is not part of ddl - gopal said its design decision
    DbRetVal resolve()=0;

    DbRetVal setParam(int paramNo, void *value) { }
    DbRetVal setShortParam(int paramNo, short value) { }
    DbRetVal setIntParam(int paramNo, int value) { }
    DbRetVal setLongParam(int paramNo, long value) { }
    DbRetVal setLongLongParam(int paramNo, long long value) { }
    DbRetVal setByteIntParam(int paramNo, ByteInt value) { }
    DbRetVal setFloatParam(int paramNo, float value) { }
    DbRetVal setDoubleParam(int paramNo, double value) { }
    DbRetVal setStringParam(int paramNo, char *value) { }
    DbRetVal setDateParam(int paramNo, Date value) { }
    DbRetVal setTimeParam(int paramNo, Time value) { }
    DbRetVal setTimeStampParam(int paramNo, TimeStamp value) { }
    DbRetVal setBinaryParam(int paramNo, void *value) { }
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
class DropIdxStatement : public DdlStatement
{
    public:
    DbRetVal execute(int &rowsAffected);
    DbRetVal resolve() {return OK; }

    DropIdxStatement(){}
    ~DropIdxStatement(){}
};

class StatementFactory
{
    public:
    static Statement* getStatement(ParsedData *pData );
};
#endif
