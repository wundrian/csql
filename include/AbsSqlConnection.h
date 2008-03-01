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
#ifndef ABSSQLCONNECTION_H
#define ABSSQLCONNECTION_H
#include<CSql.h>

/**
* @class AbsSqlConnection
*
* @brief Represents a database connection to sql engine.
* All database operations shall be done within the context of the connection. <br>
* Application should first create object of this class for accessing the database.<br/>
* Each connection has only one active transaction at any given point of time, all <br/>
* operations which happen using this connection object will be done as part of that <br/>
* transaction.<br/>
* <br/>
* Functionality: <br/>
*     1.Connection Management (connect and disconnect) <br/>
*     2.Transaction Management (start, commit, abort) <br/>
* <br/>
*  Note: <br/>
*  SERIALIZABLE isolation level is not supported.
* @author Prabakaran Thirumalai
*/
class AbsSqlConnection
{
    protected:
    AbsSqlConnection *innerConn;
    public:
    void setInnerConnection(AbsSqlConnection *conn) { innerConn = conn; }
    AbsSqlConnection* getInnerConnection() { return innerConn; }
    virtual Connection& getConnObject() =0;

    /** opens connection to the sql engine
    *   @param user username for authentication
    *   @param pass password for authentication
    *   @return DbRetVal
    */
    virtual DbRetVal connect (char *user, char * pass) =0;

    /** closes connection to the database and releases all the resources
    *   @return DbRetVal 
    */
    virtual DbRetVal disconnect () = 0;

    /** Commits active transaction. 
    *   It makes all the changes made in the current transaction permanent and <br/>
    *   it also releases the locks held by the current transaction.<br/>
    *   After a transaction commits, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    virtual DbRetVal commit() = 0;

    /** Aborts the active transaction. 
    *   undo all the changes made in the current transaction and it also <br/>
    *   releases the locks held by the current transaction.<br/>
    *   After a transaction rollback, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    virtual DbRetVal rollback() = 0;

    /** Starts a transaction.
    *   The previous transaction should be either committed or rollback <br/> 
    *   before beginTrans is called. <br/>
    *   Applications are required to start transaction before they attempt any <br>
    *   database operation.
    *   @param isoLevel isolation level. Default is read committed.
    *   @return DbRetVal
    */
    virtual DbRetVal beginTrans (IsolationLevel isoLevel = READ_COMMITTED) = 0;
    virtual ~AbsSqlConnection(){}

};

#endif
