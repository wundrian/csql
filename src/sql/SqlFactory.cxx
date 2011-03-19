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
  ***************************************************************************/
#include <SqlFactory.h>
#ifndef CSQL_CLIENT_LIB
#include <SqlStatement.h>
#include <SqlConnection.h>
#include <SqlLogConnection.h>
#include <SqlLogStatement.h>
#include <SqlOdbcConnection.h>
#include <SqlOdbcStatement.h>
#include <SqlGwStatement.h>
#endif
#include <SqlNwConnection.h>
#include <SqlNwStatement.h>
#ifndef CSQL_CLIENT_LIB
Config Conf::config;
#endif

AbsSqlConnection* SqlFactory::createConnection(SqlApiImplType implFlag)
{
    DbRetVal rv=OK;
    AbsSqlConnection *conn = NULL ;
    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    bool isSqlLogNeeded = false;
#if !(defined MMDB && defined EMBED)
    isSqlLogNeeded = Conf::config.useDurability() ||
                     (Conf::config.useCache() && 
                      (Conf::config.getCacheMode()==ASYNC_MODE || 
                        Conf::config.getCacheMode() == OFFLINE_MODE));
#else
    isSqlLogNeeded = Conf::config.useDurability();
#endif
    switch(implFlag)
    {
#ifndef CSQL_CLIENT_LIB
        case CSql:
            if (!isSqlLogNeeded) conn = new SqlConnection();
            else {
               AbsSqlConnection *sqlCon = new SqlConnection();
#if (defined MMDB && defined EMBED)
    ((SqlConnection *)sqlCon)->UID.create();
#endif
               conn = new SqlLogConnection();
               SqlLogConnection *logCon = (SqlLogConnection *)conn;
               logCon->setNoMsgLog(true);
               conn->setInnerConnection(sqlCon);
            }
            break;
#endif
        case CSqlNetwork:
            {
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetwork);
            sqlNwCon->setInnerConnection(NULL);
            conn = sqlNwCon;
            break;
            }
#ifndef CSQL_CLIENT_LIB
        case CSqlDirect:
            conn = new SqlConnection();
            break;
        case CSqlLog:
            {
            //generates sql logs
            AbsSqlConnection *sqlCon = new SqlConnection();
            conn = new SqlLogConnection();
            conn->setInnerConnection(sqlCon);
            break;
            }
#endif
#ifndef MMDB
#ifndef CSQL_CLIENT_LIB
        case CSqlAdapter:
            {
            conn = new SqlOdbcConnection();
            conn->setInnerConnection(NULL);
            break;
            }
        case CSqlGateway:
            {
            SqlLogConnection *sqllogconn=NULL;
            AbsSqlConnection *sqlCon = new SqlConnection();
            SqlGwConnection *gwconn = new SqlGwConnection();
            if (isSqlLogNeeded) {
                sqllogconn = new SqlLogConnection();
                sqllogconn->setInnerConnection(sqlCon);
                bool isNoMsgLog = Conf::config.useDurability() &&
                                  !(Conf::config.useCache() && 
                                    Conf::config.getCacheMode()==ASYNC_MODE);
                if (isNoMsgLog) sqllogconn->setNoMsgLog(true);
                gwconn->setInnerConnection(sqllogconn);
            } else gwconn->setInnerConnection(sqlCon);
            
            //createAdapters for MultiDSN
            rv=gwconn->createAdapters(gwconn);
            if(rv != OK){
                delete sqlCon;
                delete gwconn;
                if(isSqlLogNeeded) delete sqllogconn;
                return NULL;
            }
            conn = gwconn;
            break;
            }
#endif
        case CSqlNetworkAdapter:
            {
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetworkAdapter);
            sqlNwCon->setInnerConnection(NULL);
            conn = sqlNwCon;
            break;
            }
        case CSqlNetworkGateway:
            {
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetworkGateway);
            sqlNwCon->setInnerConnection(NULL);
            conn = sqlNwCon;
            break;
            }
#endif
        default:
            printf("Todo");
            break;
    }
    return conn;
}

AbsSqlStatement* SqlFactory::createStatement(SqlApiImplType implFlag)
{
    AbsSqlStatement *stmt = NULL;
    bool isSqlLogNeeded = false;
#if !(defined MMDB && defined EMBED)
    isSqlLogNeeded = Conf::config.useDurability() ||
                     (Conf::config.useCache() && 
                      (Conf::config.getCacheMode()==ASYNC_MODE || 
                        Conf::config.getCacheMode() == OFFLINE_MODE));
#else
    isSqlLogNeeded = Conf::config.useDurability();
#endif
    switch(implFlag)
    {
#ifndef CSQL_CLIENT_LIB
	case CSql:
            if (!isSqlLogNeeded) stmt = new SqlStatement();
            else {
               AbsSqlStatement *sqlStmt = new SqlStatement();
               stmt = new SqlLogStatement();
               stmt->setInnerStatement(sqlStmt);
            }
            break;
#endif
        case CSqlNetwork:
            {
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlNwStmt->setInnerStatement(NULL);
            stmt = sqlNwStmt;
            break;
            }
#ifndef CSQL_CLIENT_LIB

        case CSqlDirect:
            stmt = new SqlStatement();
            break;
        case CSqlLog:
            {
            //generates sql logs
            AbsSqlStatement *sqlStmt = new SqlStatement();
            stmt = new SqlLogStatement();
            stmt->setInnerStatement(sqlStmt);
            break;
            }
#endif
#ifndef MMDB
#ifndef CSQL_CLIENT_LIB

		case CSqlAdapter:
            {
            stmt = new SqlOdbcStatement();
            stmt->setInnerStatement(NULL);
            break;
            }
        case CSqlGateway:
            {
            SqlGwStatement *gwstmt = new SqlGwStatement();
            AbsSqlStatement *sqlstmt = new SqlStatement();

            if (isSqlLogNeeded) {
                AbsSqlStatement *sqllogstmt = new SqlLogStatement();
                sqllogstmt->setInnerStatement(sqlstmt);
                gwstmt->setInnerStatement(sqllogstmt);
            } else gwstmt->setInnerStatement(sqlstmt);
            AbsSqlStatement *adapterstmt = new SqlOdbcStatement();
            gwstmt->setAdapter(adapterstmt);
            stmt = gwstmt;
            break;
            }
#endif
		case CSqlNetworkAdapter:
            {
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlNwStmt->setInnerStatement(NULL);
            stmt=sqlNwStmt;
            break;
            }
        case CSqlNetworkGateway:
            {
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlNwStmt->setInnerStatement(NULL);
            stmt = sqlNwStmt;
            break;
            }
#endif
        default:
            printf("Todo");
            break;
    }
    return stmt;
}
