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
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info) 
    { 
        //TODO
    }

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


    virtual DbRetVal resolve()=0;
    virtual ~DmlStatement(){}
};

class InsStatement : public DmlStatement
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


    DbRetVal resolve();
    SelStatement();
    ~SelStatement();


    DbRetVal setBindField(int pos, void* value);

    int noOfProjFields();
    DbRetVal getProjFldInfo (int projpos, FieldInfo *&fInfo);

    void *fetch();
    void *fetchAndPrint();

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


    DbRetVal resolve();
    DelStatement();
    ~DelStatement();

    DbRetVal resolveForCondition(); //TODO::put this is Statement class, duplicated from SelStatement.

};

//Introduce one more class DdlStatement and derive createTbl from that.
class CreateTblStatement : public Statement
{
    public:
    DbRetVal execute(int &rowsAffected); //TODO: i think rowsAffected is not part of ddl - gopal said its design decision
    DbRetVal resolve();

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

    CreateTblStatement();
    ~CreateTblStatement();
   
    private:
    char tblName[IDENTIFIER_LENGTH];  
    TableDef tblDef; 
};

class StatementFactory
{
    public:
    static Statement* getStatement(ParsedData *pData );
};
#endif
