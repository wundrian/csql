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
#include<os.h>
#include <SqlOdbcConnection.h>
#include <CSql.h>
#include<TableConfig.h>
#include <dlfcn.h>
bool SqlOdbcConnection::symbolsLoaded= false;
struct SQLFuncPtrs SqlOdbcConnection::ODBCFuncPtrs;

DbRetVal SqlOdbcConnection::loadSymbols()
{
#ifdef x86_64
    void *handle =  RTLD_DEFAULT;
#else
    void *handle =  (void*) -1l;
#endif
    ODBCFuncPtrs.SQLAllocHandlePtr = (SQLRETURN (*)(SQLSMALLINT,SQLHANDLE,SQLHANDLE*))dlsym(handle, "SQLAllocHandle");
    if (!ODBCFuncPtrs.SQLAllocHandlePtr){

        if (handle == RTLD_DEFAULT) handle = (void*) -1l; else handle = RTLD_DEFAULT;
        ODBCFuncPtrs.SQLAllocHandlePtr = (SQLRETURN (*)(SQLSMALLINT,SQLHANDLE,SQLHANDLE*))dlsym(handle, "SQLAllocHandle");
        if (!ODBCFuncPtrs.SQLAllocHandlePtr) {
           printError(ErrSysInternal, "Symbol lookup failed\n");
           return ErrSysInternal;
        }
    }
    ODBCFuncPtrs.SQLSetEnvAttrPtr = (SQLRETURN (*)(SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER ))dlsym(handle, "SQLSetEnvAttr");
    if (!ODBCFuncPtrs.SQLSetEnvAttrPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLDriverConnectPtr = (SQLRETURN (*)(SQLHDBC, SQLHWND, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLUSMALLINT ))dlsym(handle, "SQLDriverConnect");
    if (!ODBCFuncPtrs.SQLDriverConnectPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLGetDiagRecPtr = (SQLRETURN (*)(SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLCHAR*, SQLINTEGER*, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*))dlsym(handle, "SQLGetDiagRec");
    if (!ODBCFuncPtrs.SQLGetDiagRecPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLSetConnectAttrPtr = (SQLRETURN (*)(SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER ))dlsym(handle, "SQLSetConnectAttr");
    if (!ODBCFuncPtrs.SQLSetConnectAttrPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLProcedureColumnsPtr = (SQLRETURN (*)(SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT))dlsym(handle, "SQLProcedureColumns");
    if (!ODBCFuncPtrs.SQLProcedureColumnsPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLFreeHandlePtr = (SQLRETURN (*)(SQLSMALLINT,SQLHANDLE))dlsym(handle, "SQLFreeHandle");
    if (!ODBCFuncPtrs.SQLFreeHandlePtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLTransactPtr = (SQLRETURN (*)(SQLHENV, SQLHDBC, SQLUSMALLINT ))dlsym(handle, "SQLTransact");
    if (!ODBCFuncPtrs.SQLTransactPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLExecDirectPtr = (SQLRETURN (*)(SQLHSTMT, SQLCHAR*, SQLINTEGER ))dlsym(handle, "SQLExecDirect");
    if (!ODBCFuncPtrs.SQLExecDirectPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLPreparePtr = (SQLRETURN (*)(SQLHSTMT, SQLCHAR*, SQLINTEGER ))dlsym(handle, "SQLPrepare");
    if (!ODBCFuncPtrs.SQLPreparePtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLNumResultColsPtr = (SQLRETURN (*)(SQLHSTMT, SQLSMALLINT* ))dlsym(handle, "SQLNumResultCols");
    if (!ODBCFuncPtrs.SQLNumResultColsPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLDescribeColPtr = (SQLRETURN (*)(SQLHSTMT, SQLUSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLSMALLINT*, SQLULEN*,SQLSMALLINT*, SQLSMALLINT* ))dlsym(handle, "SQLDescribeCol");
    if (!ODBCFuncPtrs.SQLDescribeColPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }
    
    ODBCFuncPtrs.SQLBindColPtr = (SQLRETURN (*)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN* ))dlsym(handle, "SQLBindCol");
    if (!ODBCFuncPtrs.SQLBindColPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLNumParamsPtr = (SQLRETURN (*)(SQLHSTMT, SQLSMALLINT* ))dlsym(handle, "SQLNumParams");
    if (!ODBCFuncPtrs.SQLNumParamsPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLDescribeParamPtr = (SQLRETURN (*)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT*, SQLULEN*, SQLSMALLINT*, SQLSMALLINT* ))dlsym(handle, "SQLDescribeParam");
    if (!ODBCFuncPtrs.SQLDescribeParamPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLBindParameterPtr = (SQLRETURN (*)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLULEN, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN* ))dlsym(handle, "SQLBindParameter");
    if (!ODBCFuncPtrs.SQLBindParameterPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLExecutePtr = (SQLRETURN (*)(SQLHSTMT ))dlsym(handle, "SQLExecute");
    if (!ODBCFuncPtrs.SQLExecutePtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLRowCountPtr = (SQLRETURN (*)(SQLHSTMT, SQLLEN* ))dlsym(handle, "SQLRowCount");
    if (!ODBCFuncPtrs.SQLRowCountPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLFetchPtr = (SQLRETURN (*)(SQLHSTMT ))dlsym(handle, "SQLFetch");
    if (!ODBCFuncPtrs.SQLFetchPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLCloseCursorPtr = (SQLRETURN (*)(SQLHSTMT ))dlsym(handle, "SQLCloseCursor");
    if (!ODBCFuncPtrs.SQLCloseCursorPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLPrimaryKeysPtr = (SQLRETURN (*)(SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT ))dlsym(handle, "SQLPrimaryKeys");
    if (!ODBCFuncPtrs.SQLPrimaryKeysPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLGetDataPtr = (SQLRETURN (*)(SQLHSTMT,SQLUSMALLINT,SQLSMALLINT,SQLPOINTER, SQLLEN,SQLLEN* ))dlsym(handle, "SQLGetData");
    if (!ODBCFuncPtrs.SQLGetDataPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    ODBCFuncPtrs.SQLDisconnectPtr = (SQLRETURN (*)(SQLHDBC))dlsym(handle, "SQLDisconnect");
    if (!ODBCFuncPtrs.SQLDisconnectPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }
     ODBCFuncPtrs.SQLTablesPtr =(SQLRETURN (*)(SQLHSTMT ,SQLCHAR *, SQLSMALLINT , SQLCHAR * , SQLSMALLINT, SQLCHAR *,  SQLSMALLINT, SQLCHAR*,SQLSMALLINT))dlsym(handle,"SQLTables");
    if (!ODBCFuncPtrs.SQLTablesPtr){
        printError(ErrSysInternal, "Symbol lookup failed\n");
        return ErrSysInternal;
    }

    symbolsLoaded=true;
    return OK;
}
DbRetVal SqlOdbcConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    char tdbname[IDENTIFIER_LENGTH];
    char *dsnAda;
    //Get the appropriate DSN
    dsnAda=getDsn();    
    
    if(strcmp(dsnAda,"")==0) 
        rv=TableConf::config.getDsnAndTdb(Conf::config.getDSN(),dsn,tdbname);
    else
        rv=TableConf::config.getDsnAndTdb(dsnAda,dsn,tdbname);
    
    if(rv!=OK){
        printError(rv,"Add Entry To csqlds.conf");
        return rv;
    }
    setTrDbName(tdbname);
    int retVal =0;
    if (!symbolsLoaded) {
        loadSymbols();
    }
    if (!symbolsLoaded) {
        printError(ErrSysFatal, "Unable to load symbols. check LD_LIBRARY_PATH");
        return ErrSysFatal; 
    }
    retVal = (*ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_ENV, 
                                            SQL_NULL_HANDLE, &envHdl);
    if (retVal) 
    {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }

   (*ODBCFuncPtrs.SQLSetEnvAttrPtr)(envHdl, SQL_ATTR_ODBC_VERSION, 
                                        (void *) SQL_OV_ODBC3, 0);
    
    retVal = (*ODBCFuncPtrs.SQLAllocHandlePtr) (SQL_HANDLE_DBC, 
                                                    envHdl, &dbHdl);
    if (retVal) 
    {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    retVal = (*ODBCFuncPtrs.SQLDriverConnectPtr)(dbHdl, NULL, (SQLCHAR*)dsn,
             SQL_NTS,outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);

    if (!SQL_SUCCEEDED(retVal)) {
        printError(ErrSysInit, "Failed to connect to target database using dsn=%s\n", dsn);

    SQLINTEGER   i = 0;
    SQLINTEGER   native;
    SQLCHAR      state[ 7 ];
    SQLCHAR      text[256];
    SQLSMALLINT  len;
    SQLRETURN    ret;

    fprintf(stderr,
            "\n"
            "The driver reported the following diagnostics whilst running "
            "\n\n");

    do
    {
        ret = (*ODBCFuncPtrs.SQLGetDiagRecPtr)(SQL_HANDLE_DBC, dbHdl, ++i, 
                                   state, &native, text, sizeof(text), &len );

        if (SQL_SUCCEEDED(ret))
            printf("%s:%ld:%ld:%s\n", state, i, native, text);
    }
    while( ret == SQL_SUCCESS );
 rv = ErrNoConnection;
 rv = OK; //masking the error:tmp
    }
    //printError(ErrSysInit, "Connecting with dsn=%s\n", dsn);
    (*ODBCFuncPtrs.SQLSetConnectAttrPtr)(dbHdl, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, 0);
    return rv;
    
}

DbRetVal SqlOdbcConnection::disconnect()
{
    DbRetVal rv = OK;
    (*ODBCFuncPtrs.SQLDisconnectPtr)(dbHdl); 
    (*ODBCFuncPtrs.SQLFreeHandlePtr) (SQL_HANDLE_DBC, dbHdl);
    (*ODBCFuncPtrs.SQLFreeHandlePtr) (SQL_HANDLE_ENV, envHdl);
    return rv;
}
void SqlOdbcConnection::setTrDbName(char *name)
{
    if(strcmp(name, "mysql")==0)
        tdbName=mysql;
    else if(strcmp(name, "postgres")==0)
        tdbName = postgres;
    return;
}
DbRetVal SqlOdbcConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode mode)
{
    if (prevIsoLevel == isoLevel) return OK;
    DbRetVal rv = OK;
    int retVal =0;
    SQLPOINTER iso;
    
    switch(isoLevel)
    {
        case READ_UNCOMMITTED:
            iso = (SQLPOINTER)SQL_TXN_READ_UNCOMMITTED;
            break;
        case READ_COMMITTED:
            iso = (SQLPOINTER)SQL_TXN_READ_COMMITTED;
            break;
        case READ_REPEATABLE:
            iso = (SQLPOINTER)SQL_TXN_REPEATABLE_READ;
            break;
        default:
            iso = (SQLPOINTER)SQL_TXN_READ_COMMITTED;
            break;
    } 

    retVal = (*ODBCFuncPtrs.SQLTransactPtr)(envHdl, dbHdl, SQL_ROLLBACK);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    retVal = (*ODBCFuncPtrs.SQLSetConnectAttrPtr)(dbHdl, SQL_ATTR_TXN_ISOLATION, iso, 0);    
    if (!SQL_SUCCEEDED(retVal)) return ErrSysInit;
    prevIsoLevel = isoLevel;
    //retVal = (*ODBCFuncPtrs.SQLTransactPtr)(envHdl, dbHdl, SQL_ROLLBACK);
    //if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
DbRetVal SqlOdbcConnection::commit()
{
    DbRetVal rv = OK;
    int retVal=0;
    retVal = (*ODBCFuncPtrs.SQLTransactPtr)(envHdl, dbHdl, SQL_COMMIT);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
DbRetVal SqlOdbcConnection::rollback()
{
    DbRetVal rv = OK;
    int retVal =0;
    retVal = (*ODBCFuncPtrs.SQLTransactPtr)(envHdl, dbHdl, SQL_ROLLBACK);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
void SqlOdbcConnection::setErrorState( SQLHDBC dbc)
{
    SQLINTEGER   i = 0;
    SQLINTEGER   native;
    SQLCHAR      state[ 7 ];
    SQLCHAR      text[256];
    SQLSMALLINT  len;
    SQLRETURN    ret;
    ret = (*ODBCFuncPtrs.SQLGetDiagRecPtr)(SQL_HANDLE_DBC, dbc, ++i,
                                   state, &native, text, sizeof(text), &len );

    if (SQL_SUCCEEDED(ret)){
         printf("%s:%ld:%ld:%s\n", state, i, native, text);
         strcpy(errState,(char*)state);
    }
}
