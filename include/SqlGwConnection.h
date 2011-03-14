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
#include<AbsSqlConnection.h>
#include<SqlFactory.h>
#include<Network.h>

//List Contains MultiDsn Elements
struct MultiDSN
{
   char dsn[IDENTIFIER_LENGTH];
   AbsSqlConnection *adapter;
   struct MultiDSN *next;
   bool isConnected;
   bool toCommit;
};

enum GwHandler
{
    NoHandler =0,
    CSqlHandler = 1,
    AdapterHandler =2,
    CSqlAndAdapterHandler =3
};

class DllExport SqlGwConnection : public AbsSqlConnection
{
    Connection dummyConn;
    AbsSqlConnection *adapter;
   // struct MultiDSN *multiAdapter;
    bool isCSqlConnected;
    bool isAdapterConnected;
    char username[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];

    public:
    static List cacheList;
    //Head of MultiDsn List
    struct MultiDSN *multi_adapter_head;
    int noOfCon;
    GwHandler txnHdlr;
    TransSyncMode mode;
    SqlGwConnection(){innerConn = NULL; mode = OSYNC; multi_adapter_head = NULL; noOfCon = 0; }
    ~SqlGwConnection();
    
    bool isTableCached(char *name);
    void setTxnHandler(GwHandler hdlr) { txnHdlr = hdlr; }
    GwHandler getTxnHandler() { return txnHdlr; }

    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel, TransSyncMode mode = OSYNC);

    friend class SqlFactory;
    bool isCsqlConnected(){ return isCSqlConnected;} 
    bool isAdptConnected(){ return isAdapterConnected;} 
    DbRetVal createAdapters(SqlGwConnection *gateway);
    void setAdapter(AbsSqlConnection *conn, char *dsn);
    AbsSqlConnection* getAdapterConnection(char *dsn);

    DbRetVal connectCSqlIfNotConnected();
    DbRetVal connectAdapterIfNotConnected();
    DbRetVal populateCachedTableList();
    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }
};

#endif
