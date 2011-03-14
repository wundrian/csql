/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef SESSION_H
#define SESSION_H
#include<os.h>
#include<ErrorType.h>
class DatabaseManager;
class UserManager;
class Session;
/**
* @enum IsolationLevel
* @brief Represents isolation level of the transaction.
*/
enum IsolationLevel
{
    READ_UNCOMMITTED = 1,
    READ_COMMITTED = 2,
    READ_REPEATABLE = 3,
    WRITE_OSYNC = 4 //this will work only from sqlapi
                    //for dbapi WRITE_OSYNC = READ_REPEATABLE
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
*     4.Isolation Level support. REPEATABLE READ, <br/>
*       READ COMMITTED and READ UNCOMMITTED isolation levels<br/>
* <br/>
*  Note: <br/>
*  SERIALIZABLE isolation level is not supported.
* 
*/

class DllExport Connection
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

    DbRetVal getExclusiveLock();
    char *getUserName();// { return session->getUserName(); }
};


class DllExport Session
{
    public:
    virtual DbRetVal open(const char*username, const char*password)=0;
    virtual DbRetVal close()=0;

    virtual DatabaseManager* getDatabaseManager()=0;
    virtual UserManager* getUserManager()=0;

    virtual DbRetVal startTransaction(IsolationLevel level)=0;
    virtual DbRetVal commit()=0;
    virtual DbRetVal rollback()=0;
    virtual DbRetVal getExclusiveLock()=0;
    virtual char * getUserName()=0;
    //TODO:: virtual int setAutoCommit(bool flag)=0;
    //TODO::support for save points
    virtual ~Session() { }

};



#endif
