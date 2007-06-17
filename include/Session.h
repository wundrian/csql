/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
#ifndef SESSION_H
#define SESSION_H
#include<DatabaseManager.h>
#include<UserManager.h>
#include<ErrorType.h>
class Session;

enum IsolationLevel
{
    READ_UNCOMMITTED = 1,
    READ_COMMITTED = 2,
    READ_REPEATABLE = 3
};

/**
* @class Connection
*
* @brief Represents a database connection.
* All database operations shall be done within the context of the connection. <br>
* Application should first create object of this class for accessing the database.<br/>
* Each connection has only one active transaction at any given point of time, all <br/>
* operations which happen using this connection object will be done as part of that <br/>
* transaction.<br/>
* <br/>
* Functionality: <br/>
*     1.Connection Management (connect and disconnect) <br/>
*     2.Transaction Management (start, commit, abort) <br/>
*     3.Provides getter methods for database manager and user manager <br/>
* <br/>
* TODO: <br/>
* 1.Isolation Level support needs to be added. Currently it supports REPEATABLE READ <br/>
*   isolation level as the default. It will soon support READ COMMITTED and <br/>
*   READ UNCOMMITTED isolation levels<br/>
* 2.AutoCommit mode<br/>
* <br/>
*  Note: <br/>
*  SERIALIZABLE isolation level is not supported.
* @author Prabakaran Thirumalai
*/

class Connection
{
    Session *session;
    public:
    Connection() { session = NULL; }
    ~Connection(); 

    /** opens connection to the database
    *   @param username username for authentication
    *   @param password password for authentication
    *   @return DbRetVal
    */
    DbRetVal open(const char*username, const char*password);


    /** closes connection to the database and releases all the resources
    *   @return DbRetVal 
    */
    DbRetVal close();

    /** gets the database manager object.
    *   @return DatabaseManager 
    */
    DatabaseManager* getDatabaseManager();

    /** gets the user manager object.
    *   @return UserManager 
    */
    UserManager* getUserManager();

    /** Starts a transaction.
    *   The previous transaction should be either committed or rollback <br/> 
    *   before startTransaction is called. <br/>
    *   Application are required to start transaction before they attempt any <br>
    *   database operation.
    *   @return DbRetVal
    */
    DbRetVal startTransaction(IsolationLevel level = READ_COMMITTED);

    /** Commits active transaction. 
    *   It makes all the changes made in the current transaction permanent and <br/>
    *   it also releases the locks held by the current transaction.<br/>
    *   After a transaction commits, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    DbRetVal commit();

    /** Aborts the active transaction. 
    *   undo all the changes made in the current transaction and it also <br/>
    *   releases the locks held by the current transaction.<br/>
    *   After a transaction rollback, application is required to start another <br/>
    *   transaction for further database operations.
    *   @return DbRetVal 
    */
    DbRetVal rollback();
};


class Session
{
    public:
    virtual DbRetVal open(const char*username, const char*password)=0;
    virtual DbRetVal close()=0;

    virtual DatabaseManager* getDatabaseManager()=0;
    virtual UserManager* getUserManager()=0;

    virtual DbRetVal startTransaction(IsolationLevel level)=0;
    virtual DbRetVal commit()=0;
    virtual DbRetVal rollback()=0;
    //TODO:: virtual int setAutoCommit(bool flag)=0;
    //TODO::support for save points
    virtual ~Session() { }

};



#endif
