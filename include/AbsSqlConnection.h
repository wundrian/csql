/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/
#ifndef ABSSQLCONNECTION_H
#define ABSSQLCONNECTION_H
#include<os.h>
#include<ErrorType.h>
#include<Session.h>
#include<Util.h>
class Connection; 
class CachedTable{
    public:
    char tableName[IDENTIFIER_LENGTH];
    CachedTable() { tableName[0] = '\0'; }
};

enum TransSyncMode {
    OSYNC=1,
    ASYNC=2,
    OASYNC=3
};

enum TableSyncMode {
    TABLE_OSYNC=1,
    TABLE_ASYNC=2
};
/**
* @class AbsSqlConnection
*
* \brief Represents a database connection to sql engine.
*
* It represents the database connection to the sql engine.\n
* All database operations shall be done within the context of the connection.\n 
* Application should first create object of this class to accessing the database\n
* through SQL Engine.
* Each connection has only one active transaction at any given point of time, all \n
* operations which happen using this connection object will be done as part of that \n
* transaction.\n
* \n
*  Note: \n
*  SERIALIZABLE isolation level is not supported. \n
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

    /** closes connection to the sql engine and releases all the resources
    *   @return DbRetVal 
    */
    virtual DbRetVal disconnect () = 0;

    /** Commits active transaction. \n
    *   It makes all the changes made in the current transaction permanent and \n
    *   it also releases the locks held by the current transaction.\n
    *   After a transaction commits, application is required to start another \n
    *   transaction for further database operations.\n
    *   @return DbRetVal 
    */
    virtual DbRetVal commit() = 0;

    /** Aborts the active transaction.\n 
    *   undo all the changes made in the current transaction and it also \n
    *   releases the locks held by the current transaction.\n
    *   After a transaction rollback, application is required to start another \n
    *   transaction for further database operations.\n
    *   @return DbRetVal 
    */
    virtual DbRetVal rollback() = 0;

    /** Starts a new transaction.\n
    *   The previous transaction should be either committed or rollback \n
    *   before beginTrans is called. \n
    *   Applications are required to start transaction before they attempt any \n
    *   database operation.\n
    *   @param isoLevel isolation level. Default is read committed.
    *   @return DbRetVal
    */
    virtual DbRetVal beginTrans (IsolationLevel isoLevel = READ_COMMITTED,
                                 TransSyncMode mode = OSYNC) = 0;
    virtual ~AbsSqlConnection()
    {
        if (innerConn) { delete innerConn; innerConn = NULL; }
    }
    virtual void display()
    {
        if (innerConn)  innerConn->display();
    }
};

#endif
