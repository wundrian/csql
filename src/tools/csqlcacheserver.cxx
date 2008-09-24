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
#include <AbsSqlConnection.h>
#include <AbsSqlStatement.h>
#include <SqlOdbcStatement.h>
#include <SqlFactory.h>
#include <CSql.h>

int insert(Table *table, int pkid);
int remove(Table *table, int pkid);
int getRecordsFromTargetDb(int mode);

int srvStop =0;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
}

void printUsage()
{
   printf("Usage: csqlcacheserver \n");
   printf("Description: Start the csql caching server.\n");
   return;
}
AbsSqlConnection *targetconn;
Connection conn;
int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "?")) != EOF) 
    {
        switch (c)
        {
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 

        }
    }//while options

    if (opt == 10) {
        printUsage();
        return 0;
    }

    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);

    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    targetconn = SqlFactory::createConnection(CSqlAdapter);
    rv = targetconn->connect("root", "manager");
    if (rv != OK) return 1;
    if (!Conf::config.useCache())
    {
        printf("Cache is set to OFF in csql.conf file\n");
        return 1;
    } 
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    /*rv = stmt->prepare("create table csql_log_int(tablename char(64), pkid int, operation int, id int not null unique auto_increment)engine='innodb';");
    targetconn->beginTrans();
    int rows=0;
    stmt->execute(rows);
    targetconn->commit();
    stmt->free();
    delete stmt;*/

    printf("Cache server started\n");
    int ret = 0;
    struct timeval timeout, tval;
    timeout.tv_sec = Conf::config.getCacheWaitSecs();
    timeout.tv_usec = 0;
    
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        ret = os::select(0, NULL, 0, 0, &tval);
        printf("Checking for cache updates\n");
        ret = getRecordsFromTargetDb(1);       
        if (ret !=0) srvStop = 1;
        //ret = getRecordsFromTargetDb(2);       
        if (ret !=0) srvStop = 1;
    }
    printf("Cache Server Exiting\n");
    conn.close();
    targetconn->disconnect();
    return 0;
}
int getRecordsFromTargetDb(int mode)
{
    int pkid;
    char tablename[64];
    int op, id,caId;
    int rows =0;
    DbRetVal rv = OK;
    char StmtStr[1024];
    caId =Conf::config.getCacheID();
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    AbsSqlStatement *delstmt = SqlFactory::createStatement(CSqlAdapter);
    delstmt->setConnection(targetconn);
    if (mode == 1 ) {
        //rv = delstmt->prepare("DELETE from csql_log_int where id=?;");
      	sprintf(StmtStr, "SELECT * FROM csql_log_int where cacheid = %d;", caId);
        rv = stmt->prepare(StmtStr);
        if (rv != OK) {printf("Stmt prepare failed\n"); return 1; }
    }
    else {
        rv = stmt->prepare("SELECT * FROM csql_log_char;");
        if (rv != OK) {printf("Stmt prepare failed\n"); return 1; }
        //rv = delstmt->prepare("DELETE from csql_log_char where id=?;");
    }
    if (rv != OK) {printf("Stmt prepare failed\n"); return 1; }
    stmt->bindField(1, tablename);
    stmt->bindField(2, &pkid);
    stmt->bindField(3, &op);
    stmt->bindField(4, &caId);
    stmt->bindField(5, &id);

    DatabaseManager *dbMgr = conn.getDatabaseManager();
    while(true) {
      rv = targetconn->beginTrans();
      rv = stmt->execute(rows);
      if (rv != OK) 
      {
          printError(ErrSysInit, "Unable to execute stmt in target db");
          targetconn->rollback();
          stmt->free();
          delstmt->free();
          delete stmt;
          delete delstmt;
          return 1;
      }
      if (stmt->fetch() != NULL) {
          printf("Row value is %s %d %d %d\n", tablename, pkid, op,caId);
	 
            	Table *table = dbMgr->openTable(tablename);
          	int ret = 0;
          	if (table == NULL)
          	{
              		printError(ErrSysInit, "Table %s not exist in csql", tablename);
              		targetconn->rollback();
            		stmt->free();
              		delstmt->free();
              		delete stmt;
              		delete delstmt;
              		break;
          	}
          	if (op == 2)//DELETE
          	{
              		ret = remove(table,pkid);
          	}
          	else //INSERT
          	{
              		ret = insert(table, pkid);
          	}
          	dbMgr->closeTable(table);
          	rv = targetconn->commit();
          	rv = targetconn->beginTrans();
          //Remove record from csql_log_XXX table
          	sprintf(StmtStr, "DELETE from csql_log_int where id=%d ;", id);
          	rv = delstmt->prepare(StmtStr);
          	if (rv != OK) {printf("FAILED\n"); return 1; }
         	// delstmt->setIntParam(1, id);
          	rv = delstmt->execute(rows);
          	if (rv != OK) 
          	{
              		printf("log record not deleted from the target db %d\n", rv);
              		targetconn->rollback();
              		stmt->free();
              		delstmt->free();
              		delete stmt;
              		delete delstmt;
          	}
          	delstmt->free();
         
          	rv = targetconn->commit();
	
     }
     else {
         stmt->close();
         break;
     }
     stmt->close();
   }
   stmt->free();
   delstmt->free();
   delete stmt;
   delete delstmt;
   return 0;
}
int insert(Table *table, int pkid)
{
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    char pkfieldname[128];
    ostmt->getPrimaryKeyFieldName(table->getName(), pkfieldname);
    char sbuf[1024];
    sprintf(sbuf, "SELECT * FROM %s where %s = %d;", table->getName(), pkfieldname, pkid);
    //TODO::get the primary key field name from the table interface. need to implement it
    DbRetVal rv = stmt->prepare(sbuf);
    if (rv != OK) return 1;

    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf; int fieldsize=0;
    void *buf[128];//TODO:resticts to support only 128 fields in table
    Identifier *elem = NULL;
    while (fNameIter.hasElement()) {
        elem = (Identifier*) fNameIter.nextElement();
        table->getFieldInfo((const char*)elem->name, info);
        valBuf = AllDataType::alloc(info->type, info->length);
        buf[fcount] = valBuf;
        table->bindFld(elem->name, valBuf);
        stmt->bindField(fcount++, valBuf);
        
    }
    delete info;
    int rows=0;
    int retValue = stmt->execute(rows);
    if (retValue && rows != 1) {printError(ErrSysInit, "Unable to execute statement at target db\n"); return ErrSysInit; }
    conn.startTransaction();
    if (stmt->fetch() != NULL) {
        table->insertTuple();
        //Note:insert may fail if the record is inserted from this cache
    }
    for (int i=1; i < fcount; i++) {
        free(buf[i]);
    }
    stmt->free();
    delete stmt;
    conn.commit();      
    return 0;
}
int remove(Table *table, int pkid)
{
    DbRetVal rv = OK;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(targetconn);
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    char pkfieldname[128];
    ostmt->getPrimaryKeyFieldName(table->getName(), pkfieldname);
    delete stmt;
    Condition p1;
    p1.setTerm(pkfieldname, OpEquals, &pkid);
    table->setCondition(&p1);
    rv = conn.startTransaction();
    if (rv != OK) return 1;
    rv = table->execute();
    if (rv != OK)  
    {
        table->setCondition(NULL); 
        conn.rollback();
        return 1;
    }
    if (table->fetch() != NULL)
        rv = table->deleteTuple();
        //Note:Delete may fail if the record is deleted from this cache
    table->setCondition(NULL);
    rv = conn.commit();
    if (rv != OK) return 1;
    return 0;
}

