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
        default:
            printf("Todo");
            break;
    }
    return stmt;
}
