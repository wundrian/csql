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
#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include<CSql.h>
#include<AbsSqlConnection.h>
#include<SqlFactory.h>

class SqlConnection : public AbsSqlConnection
{
    Connection conn;
    bool isConnOpen;
    public:
    SqlConnection(){innerConn = NULL; isConnOpen = false; }

    /** opens connection to the sql engine
    *   @param user username for authentication
    *   @param pass password for authentication
    *   @return DbRetVal
    */
    DbRetVal connect (char *user, char * pass) {
        DbRetVal ret = conn.open(user, pass);
        if (ret == OK) isConnOpen = true;
        return ret;
    }

    /** closes connection to the database and releases all the resources
    *   @return DbRetVal 
    */
    DbRetVal disconnect () { 
        DbRetVal ret = conn.close(); 
        if (ret == OK) isConnOpen = false;
        return ret;
    }

    /** Commits active transaction. 
    *   It makes all the changes made in the current transaction permanent and <br/>
    *   it also releases the locks held by the current transaction.<br/>
    *   After a transaction commits, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    DbRetVal commit() { return conn.commit(); }

    /** Aborts the active transaction. 
    *   undo all the changes made in the current transaction and it also <br/>
    *   releases the locks held by the current transaction.<br/>
    *   After a transaction rollback, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    DbRetVal rollback() { return conn.rollback(); }

    /** Starts a transaction.
    *   The previous transaction should be either committed or rollback <br/> 
    *   before beginTrans is called. <br/>
    *   Applications are required to start transaction before they attempt any <br>
    *   database operation.
    *   @param isoLevel isolation level. Default is read committed.
    *   @return DbRetVal
    */
    DbRetVal beginTrans (IsolationLevel isoLevel = READ_COMMITTED, 
                         TransSyncMode mode = OSYNC) 
        { return conn.startTransaction(isoLevel); }

    Connection& getConnObject(){  return conn; }
    bool isConnectionOpen() { if (isConnOpen) return true; return false; };
    DbRetVal getExclusiveLock(){ return conn.getExclusiveLock(); }

    friend class SqlFactory;
};

#endif
