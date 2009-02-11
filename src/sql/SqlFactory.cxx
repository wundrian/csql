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

AbsSqlConnection* SqlFactory::createConnection(SqlApiImplType implFlag)
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
            SqlNwConnection *sqlNwCon = new SqlNwConnection(CSqlNetwork);
            sqlNwCon->setInnerConnection(NULL);
            conn = sqlNwCon;
            break;
            }
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
            SqlNwStatement *sqlNwStmt = new SqlNwStatement();
            sqlNwStmt->setInnerStatement(NULL);
            stmt = sqlNwStmt;
            break;
            }
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

        default:
            printf("Todo");
            break;
    }
    return stmt;
}
