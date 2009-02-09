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
#include <SqlStatement.h>
#include <SqlConnection.h>
#include <SqlLogConnection.h>
#include <SqlLogStatement.h>
#include <SqlOdbcConnection.h>
#include <SqlOdbcStatement.h>
#include <SqlGwStatement.h>
#include <SqlNwConnection.h>
#include <SqlNwStatement.h>

AbsSqlConnection* SqlFactory::createConnection(SqlApiImplType implFlag,
                                char *hostName, int port)
{
    AbsSqlConnection *conn = NULL ;
    switch(implFlag)
    {
        case CSql:
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
        case CSqlAdapter:
            {
            conn = new SqlOdbcConnection();
            conn->setInnerConnection(NULL);
            break;
            }
        case CSqlGateway:
            {
            AbsSqlConnection *sqlCon = new SqlConnection();
            AbsSqlConnection *sqllogconn = new SqlLogConnection();
            sqllogconn->setInnerConnection(sqlCon);
            AbsSqlConnection *adapterCon = new SqlOdbcConnection();
            SqlGwConnection *gwconn = new SqlGwConnection();
            gwconn->setInnerConnection(sqllogconn);
            gwconn->setAdapter(adapterCon);
            conn = gwconn;
            break;
            }
        case CSqlNetwork:
            {
            if (hostName == NULL) return NULL;
            AbsSqlConnection *sqlCon = new SqlConnection();
            AbsSqlConnection *sqlLogCon = new SqlLogConnection();
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetwork);
            sqlLogCon->setInnerConnection(sqlCon);
            sqlNwCon->setInnerConnection(sqlLogCon);
            conn = sqlNwCon;
            sqlNwCon->setHost(hostName, port);
            break;
            }
        case CSqlNetworkAdapter:
            {
            if (hostName == NULL) return NULL;
            AbsSqlConnection *adapterCon = new SqlOdbcConnection();
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetworkAdapter);
            adapterCon->setInnerConnection(NULL);
            sqlNwCon->setInnerConnection(adapterCon);
            sqlNwCon->setHost(hostName, port);
            break;
            }
        case CSqlNetworkGateway:
            {
            if (hostName == NULL) return NULL;
            AbsSqlConnection *sqlCon = new SqlConnection();
            AbsSqlConnection *sqlLogCon = new SqlLogConnection();
            AbsSqlConnection *adapterCon = new SqlOdbcConnection();
            SqlGwConnection *sqlGwCon = new SqlGwConnection();
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetworkGateway);
            sqlLogCon->setInnerConnection(sqlCon);
            sqlGwCon->setInnerConnection(sqlLogCon);
            sqlGwCon->setAdapter(adapterCon);
            sqlNwCon->setInnerConnection(sqlGwCon);
            conn = sqlNwCon;
            sqlNwCon->setHost(hostName, port);
            break;
            }
            
        default:
            printf("Todo");
            break;
    }
    return conn;
}
AbsSqlStatement* SqlFactory::createStatement(SqlApiImplType implFlag)
{
    AbsSqlStatement *stmt = NULL;
    switch(implFlag)
    {
        case CSql:
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
        case CSqlAdapter:
            {
            stmt = new SqlOdbcStatement();
            stmt->setInnerStatement(NULL);
            break;
            }
        case CSqlGateway:
            {
            AbsSqlStatement *sqlstmt = new SqlStatement();
            AbsSqlStatement *sqllogstmt = new SqlLogStatement();
            sqllogstmt->setInnerStatement(sqlstmt);
            AbsSqlStatement *adapterstmt = new SqlOdbcStatement();
            SqlGwStatement *gwstmt = new SqlGwStatement();
            gwstmt->setInnerStatement(sqllogstmt);
            gwstmt->setAdapter(adapterstmt);
            stmt = gwstmt;
            break;
            }
        case CSqlNetwork:
            {
            AbsSqlStatement *sqlStmt = new SqlStatement();
            AbsSqlStatement *sqlLogStmt = new SqlLogStatement();
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlLogStmt->setInnerStatement(sqlStmt);
            sqlNwStmt->setInnerStatement(sqlLogStmt);
            stmt = sqlNwStmt;
            break;
            }
        case CSqlNetworkAdapter:
            {
            AbsSqlStatement *adapterStmt = new SqlOdbcStatement();
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            adapterStmt->setInnerStatement(NULL);
            sqlNwStmt->setInnerStatement(adapterStmt);
            break;
            }
        case CSqlNetworkGateway:
            {
            AbsSqlStatement *sqlStmt = new SqlStatement();
            AbsSqlStatement *sqlLogStmt = new SqlLogStatement();
            AbsSqlStatement *adapterStmt = new SqlOdbcStatement();
            SqlGwStatement *sqlGwStmt = new SqlGwStatement();
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlLogStmt->setInnerStatement(sqlStmt);
            sqlGwStmt->setInnerStatement(sqlLogStmt);
            sqlGwStmt->setAdapter(adapterStmt);
            sqlNwStmt->setInnerStatement(sqlGwStmt);
            stmt = sqlNwStmt;
            break;
            }

        default:
            printf("Todo");
            break;
    }
    return stmt;
}
