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
#ifndef SQLODBCCONNECTION_H
#define SQLODBCCONNECTION_H
#include <CSql.h>
#include <AbsSqlConnection.h>
#include <SqlFactory.h>
#include <sql.h>
#include <sqlext.h>

#ifdef WINNT
typedef signed short int        SWORD;
#endif

struct SQLFuncPtrs{
    SQLRETURN (*SQLAllocHandlePtr)(SQLSMALLINT, SQLHANDLE, SQLHANDLE*);
    SQLRETURN (*SQLSetEnvAttrPtr)(SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER);
    SQLRETURN (*SQLDriverConnectPtr)(SQLHDBC, SQLHWND, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLUSMALLINT);
    SQLRETURN (*SQLGetDiagRecPtr)(SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLCHAR*, SQLINTEGER*, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*);
    SQLRETURN (*SQLSetConnectAttrPtr)(SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER);
    SQLRETURN (*SQLSetStmtAttrPtr)(SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER);
    SQLRETURN (*SQLFreeHandlePtr)(SQLSMALLINT, SQLHANDLE);
    SQLRETURN (*SQLTransactPtr)(SQLHENV, SQLHDBC, SQLUSMALLINT);

    SQLRETURN (*SQLExecDirectPtr)(SQLHSTMT, SQLCHAR*, SQLINTEGER);
    SQLRETURN (*SQLPreparePtr)(SQLHSTMT, SQLCHAR*, SQLINTEGER);
    SQLRETURN (*SQLNumResultColsPtr)(SQLHSTMT, SQLSMALLINT*);
    SQLRETURN (*SQLDescribeColPtr)(SQLHSTMT, SQLUSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLSMALLINT*, SQLULEN*,SQLSMALLINT*, SQLSMALLINT*);
    SQLRETURN (*SQLBindColPtr)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN*);
    SQLRETURN (*SQLNumParamsPtr)(SQLHSTMT, SQLSMALLINT*);
    SQLRETURN (*SQLDescribeParamPtr)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT*, SQLULEN*, SQLSMALLINT*, SQLSMALLINT*);
    SQLRETURN (*SQLBindParameterPtr)( SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLULEN, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN*);
    SQLRETURN (*SQLExecutePtr)(SQLHSTMT);
    SQLRETURN (*SQLRowCountPtr)(SQLHSTMT, SQLLEN*);
    SQLRETURN (*SQLFetchPtr)(SQLHSTMT);
    SQLRETURN (*SQLFetchScrollPtr)(SQLHSTMT, SQLSMALLINT, SQLLEN);
    SQLRETURN (*SQLCloseCursorPtr)(SQLHSTMT);
    SQLRETURN (*SQLPrimaryKeysPtr)( SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT);
    SQLRETURN (*SQLGetDataPtr)(SQLHSTMT,SQLUSMALLINT,SQLSMALLINT,SQLPOINTER, SQLLEN,SQLLEN*);
    SQLRETURN (*SQLDisconnectPtr)(SQLHDBC);    
    SQLRETURN (*SQLTablesPtr)(SQLHSTMT ,SQLCHAR *, SQLSMALLINT , SQLCHAR * , SQLSMALLINT, SQLCHAR *,  SQLSMALLINT, SQLCHAR*,SQLSMALLINT);
    SQLRETURN (*SQLProcedureColumnsPtr)(SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT,SQLCHAR *, SQLSMALLINT);
};

/**
* @class SqlOdbcConnection
*
*/
//class SqlOdbcSym {
//    public:
//};

class DllExport SqlOdbcConnection : public AbsSqlConnection
{
    Connection dummyConn;
    char errState[STATE_LENGTH];
    char dsName[IDENTIFIER_LENGTH];
    bool isConnOpen;
    TDBInfo tdbName;
    public:
    SQLHENV envHdl;
    SQLHDBC dbHdl;
    char dsString[IDENTIFIER_LENGTH];
    IsolationLevel prevIsoLevel;
    SqlOdbcConnection()
    { 
        strcpy(errState,"00000"); 
        innerConn = NULL; 
        tdbName = mysql; 
        prevIsoLevel = READ_COMMITTED; 
        dsName[0]='\0'; 
        isConnOpen = false; 
    }
    ~SqlOdbcConnection(){}
    
    void setDsName(char *dsname){ strcpy(dsName,dsname);}
    char *getDsName(){return dsName;}
    void setTrDbName(char *name);
    TDBInfo getTrDbName(){return tdbName;}
    static bool symbolsLoaded;
    static struct SQLFuncPtrs ODBCFuncPtrs;

    void setErrorState( SQLHDBC dbc);
    DbRetVal loadSymbols();

    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }
    bool isConnectionOpen() { if (isConnOpen) return true; return false; }
    
    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel, TransSyncMode mode);

    friend class SqlFactory;
};

#endif
