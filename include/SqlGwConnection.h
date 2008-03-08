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
#ifndef SQLGWCONNECTION_H
#define SQLGWCONNECTION_H
#include<CSql.h>
#include<AbsSqlConnection.h>
#include<SqlFactory.h>

/**
* @class SqlGwConnection
*
*/
class SqlGwConnection : public AbsSqlConnection
{
    Connection dummyConn;
    AbsSqlConnection *adapter;
    bool isCSqlConnected;
    bool isAdapterConnected;
    char username[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];

    public:
    SqlGwConnection(){innerConn = NULL; }

    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel);

    friend class SqlFactory;

    void setAdapter(AbsSqlConnection *conn) { adapter =  conn; }
    AbsSqlConnection* getAdapterConnection() { return adapter; }

    DbRetVal connectCSqlIfNotConnected();
    DbRetVal connectAdapterIfNotConnected();
    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }
};

#endif
