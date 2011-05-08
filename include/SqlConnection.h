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
class SqlStatement;

struct CachedStmtNode{
    SqlStatement *sqlStmt;
    int stmtLength;
    char *sqlString;
    int hits;
    bool inUse;
    CachedStmtNode() { sqlStmt = NULL; sqlString=NULL; stmtLength=0; hits=0; inUse=0;}
    void display() {
        printf(" SQL=%s hits=%d inuse=%d\n", sqlString, hits, inUse);
    }
    
};
class DllExport SqlConnection : public AbsSqlConnection
{
    Connection conn;
    bool isConnOpen;
    public:
    static List connList;
    static bool isInit;
#if (defined MMDB && EMBED)
    static bool firstThread;
    static GlobalUniqueID UID;
#endif
    void initialize();
    List cachedStmts;
    SqlConnection(){ innerConn = NULL; isConnOpen = false; }
    ~SqlConnection();

    /** opens connection to the sql engine
    *   @param user username for authentication
    *   @param pass password for authentication
    *   @return DbRetVal
    */
    DbRetVal connect (char *user, char * pass);

    /** closes connection to the database and releases all the resources
    *   @return DbRetVal 
    */
    DbRetVal disconnect () { 
        flushCacheStmt();
        DbRetVal ret = conn.close(); 
        if (ret == OK) isConnOpen = false;
# if (defined MMDB && defined EMBED)
        if (Conf::config.useDurability() && connList.size()==1) UID.destroy();
# endif
        connList.remove(this);
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

    SqlStatement* findInCache(char *stmtStr);
    void flushCacheStmt();
    void addToCache(SqlStatement *stmt, char *stmtStr);
    void removeLeastUsed();
    void setStmtNotInUse(char *stmtStr);
    void displayStmtCache();
    void display() { displayStmtCache(); }


    friend class SqlFactory;
};

#endif
