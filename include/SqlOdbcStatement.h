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
#ifndef SQLODBCSTATEMENT_H
#define SQLODBCSTATEMENT_H
#include <AbsSqlStatement.h>
#include <SqlOdbcConnection.h>
#include <SqlFactory.h>
#include <CSql.h>
class SqlOdbcStatement: public AbsSqlStatement
{
    public:
    SqlOdbcStatement() 
    { 
        innerStmt = NULL; 
        con = NULL;  
        tdbname = mysql;
        isSelStmt = false; 
        len=NULL; 
        paramlen=NULL; 
        isPrepared = false; 
        strcpy(errState,"00000");
        rowStatus = NULL;
        nRecords = 0;
    }

    void setConnection(AbsSqlConnection *conn)
    {
        if (innerStmt) innerStmt->setConnection(conn->getInnerConnection());
        con = conn;
    }

    DbRetVal executeDirect(char *stmt);    
    DbRetVal prepare(char *stmt);
    DbRetVal prepareForResultSet(char *stmt);

    DbRetVal execute(int &rowsAffect);
    DbRetVal executeForResultSet();
    DbRetVal bindParam(int pos, void*);

    DbRetVal bindField(int pos, void* val);
    DbRetVal rsBindField(int pos, void* val);

    void* fetch();
    void* fetch(DbRetVal &rv);
    DbRetVal fetchScroll(void *nrows);
    void setResultSetInfo(int nrecs);
    void* fetchAndPrint(bool SQL);
    void* next();
    DbRetVal close();
    int noOfProjFields();

    void* getFieldValuePtr( int pos );
    void* getFieldValuePtr( char *name );

    DbRetVal free();

    int noOfParamFields();

    DbRetVal getProjFldInfo(int projPos, FieldInfo *&info);

    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);

    void setShortParam(int paramPos, short value);
    void setIntParam(int paramPos, int value);
    void setLongParam(int paramPos, long value);
    void setLongLongParam(int paramPos, long long value);
    void setByteIntParam(int paramPos, ByteInt value);
    void setFloatParam(int paramPos, float value);
    void setDoubleParam(int paramPos, double value);
    void setStringParam(int paramPos, char *value);
    void setDateParam(int paramPos, Date value);
    void setTimeParam(int paramPos, Time value);
    void setTimeStampParam(int paramPos, TimeStamp value);
    void setBinaryParam(int paramPos, void *value, int length);
	bool isSelect();
    void getPrimaryKeyFieldName(char *tablename, char *pkfieldname);
    void setNullInfo(AbsSqlStatement *stmt);
//    void setNullInfo(Table *stmt);
    bool isFldNull(int pos);
    bool isFldNull(char *name);
    bool checkStmtType(char *stmtstr);
    void setNull(int pos);
    int getFldPos(char *name){ return 0;} 
    List getAllTableNames(DbRetVal &ret){ List dummy; return dummy;}
    List getAllUserNames(DbRetVal &ret){ List dummy; return dummy;}
    bool isTableExists(char *tblname);
    int getNoOfPagesForTable(char *tbl){ return 0;}
    DbRetVal loadRecords(char *tbl, void *buf){ return ErrBadCall;}
    ResultSetPlan getResultSetPlan(){ return Normal;}
    char *getTableName(){ return "";}
    StatementType getStmtType() { return UnknownStatement; }
    void setErrorState(SQLHSTMT hStmt);
    DbRetVal resolveForBindField(SQLHSTMT hstmt);
    DbRetVal resolveForResultSetBindField(SQLHSTMT hstmt);
    void getProjFieldType(int *data);
    TDBInfo getTdbInfo() { return tdbname; }
    long long getLastInsertedVal(DbRetVal &rv) { rv = ErrBadCall; return 0;} 
    //TODO
    
    SQLUSMALLINT *rowStatus;
    private:
    char errState[STATE_LENGTH];
    TDBInfo tdbname;
    bool isSelStmt;
    bool isPrepared;
    List paramList;
    List bindList;
    SQLHSTMT hstmt;
    SQLINTEGER *len;
    SQLINTEGER *paramlen;
    int totalFld;
    bool isProcedureCallStmt; 
    //For result set retrieval
    int nRecords;
    friend class SqlFactory;
};

#endif
