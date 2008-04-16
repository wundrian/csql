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
#include <SqlOdbcConnection.h>
#include <CSql.h>

DbRetVal SqlOdbcConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    char dsn[72];
    sprintf(dsn, "DSN=%s;", Conf::config.getDSN());
    int retVal =0;
    retVal = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &envHdl);
    if (retVal) 
    {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }
    SQLSetEnvAttr(envHdl, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    
    retVal = SQLAllocHandle (SQL_HANDLE_DBC, envHdl, &dbHdl);
    if (retVal) 
    {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    retVal = SQLDriverConnect(dbHdl, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(retVal)) {
        printError(ErrSysInit, "Failed to connect to target database using dsn=%s\n", dsn);
        rv = ErrNoConnection;
    }
    SQLSetConnectAttr(dbHdl, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, 0);
    return rv;
    
}
DbRetVal SqlOdbcConnection::disconnect()
{
    DbRetVal rv = OK;
    SQLDisconnect (dbHdl);
    SQLFreeHandle (SQL_HANDLE_DBC, dbHdl);
    SQLFreeHandle (SQL_HANDLE_ENV, envHdl);
    return rv;
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

    retVal = SQLSetConnectAttr(dbHdl, SQL_ATTR_TXN_ISOLATION, iso, 0);    
    if (!SQL_SUCCEEDED(retVal)) return ErrSysInit;
    prevIsoLevel = isoLevel;
    retVal = SQLTransact (envHdl, dbHdl, SQL_ROLLBACK);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
DbRetVal SqlOdbcConnection::commit()
{
    DbRetVal rv = OK;
    int retVal = SQLTransact (envHdl, dbHdl, SQL_COMMIT);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
DbRetVal SqlOdbcConnection::rollback()
{
    DbRetVal rv = OK;
    int retVal = SQLTransact (envHdl, dbHdl, SQL_ROLLBACK);
    if (!SQL_SUCCEEDED(retVal)) rv = ErrSysInit;
    return rv;
}
