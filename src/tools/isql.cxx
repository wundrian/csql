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
#include <os.h>
#include<CSql.h>
#include <DatabaseManagerImpl.h>
#include <Statement.h>
#include <SqlFactory.h>
#include <SqlStatement.h>
#include <SqlNwConnection.h>
#include <SqlNwStatement.h>
#ifndef NO_READLINE_LIB
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include <NanoTimer.h>
#define SQL_STMT_LEN 8192
void printVariables();

enum STATEMENT_TYPE
{
    SELECT =0,
    EXPLAIN,
    DDL ,
    OTHER
};
STATEMENT_TYPE stmtType = SELECT;
FILE *fp;
AbsSqlConnection *conn;
AbsSqlStatement *stmt;
AbsSqlStatement *aconStmt; //stmt object when autocommit is on
List sqlStmtList;
SqlApiImplType type = CSqlUnknown;
bool gateway=false, silent=false;
bool autocommitmode = true;
bool isTimer = false;
bool network = false;
bool firstPrepare = true;
IsolationLevel isoLevel = READ_COMMITTED;
void printHelp();
bool getInput(bool);
void printUsage()
{
   printf("Usage: csql [ [-u username] [-p passwd] ] [ [-H hostname] [-P port] ]\n");
   printf("            [-s sqlfile] \n");
   printf("       username -> username to connect to database\n");
   printf("       password -> password to connect to database\n");
   printf("       hostname -> hostname to connect to database through network\n");
   printf("       port     -> port no\n");
   printf("       sqlfile  -> filename containing sql statements\n");
   return;
  
}
bool noUndolog=false;
bool exclusive=false;
int getConnType(int opt);

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char hostname[IDENTIFIER_LENGTH];
    hostname[0] = '\0';
    char port[8];
    port[0] ='\0'; 
    char filename[512];
    filename [0] ='\0';
    int c = 0, opt=0;
    int connOpt = 0;
    while ((c = getopt(argc, argv, "u:p:s:o:H:P:gXUS?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : strcpy(username , argv[optind - 1]); break;
            case 'p' : strcpy(password , argv[optind - 1]); break;
            case 's' : strcpy(filename , argv[optind - 1]); break;
            case 'o' : { connOpt = atoi(argv[optind - 1]); break; }
            case '?' : { opt = 1; break; } //print help 
            case 'S' : { silent = true; break; } //silent 
            case 'X' : { silent = true; exclusive = true; break; } //silent 
            case 'g' : { gateway = true; break; } //print help 
            case 'U' : { noUndolog = true; break; } //print help 
            case 'H' : { strcpy (hostname, argv[optind - 1]); 
                         network = true; break; }
            case 'P' : { strcpy (port,     argv[optind - 1]); 
                         network = true; break; }
            default: printf("Wrong args\n"); exit(1);

        }
    }//while options
    //printf("%s %s %s", username, password, filename);
    if (opt == 1)
    {
        printUsage();
        return 0;
    }
    if (username[0] == '\0' )
    {
        strcpy(username, I_USER);
        strcpy(password, I_PASS);
    }
    if (network) {
        if (hostname[0] == '\0') { printUsage(); return 0; }
        if (port[0] == '\0') { printUsage(); return 0; }
    }
    bool fileFlag = false;
    if (filename [0] !='\0')
    {
        fp = fopen(filename,"r");
        if (fp == NULL)
        {
            printf("Unable to open the file %s\n", filename);
            return 1;
        }
        fileFlag = true;
    }
    
    DbRetVal rv = OK;
    if (connOpt) {
        noUndolog =false;
        type = (SqlApiImplType) getConnType(connOpt);
        conn = SqlFactory::createConnection((SqlApiImplType)type);
        if(connOpt == 4 || connOpt == 5 || connOpt == 6) {
            SqlNwConnection *con = (SqlNwConnection *)conn;
            con->setHost("localhost", 5678);
        }
        else if (connOpt == 7) 
            conn = SqlFactory::createConnection((SqlApiImplType)type);
    } else {
        if (network) {
            if (gateway) type = CSqlNetworkGateway;
            else type = CSqlNetwork;
            conn = SqlFactory::createConnection(type);
            SqlNwConnection *con = (SqlNwConnection *)conn;
            con->setHost(hostname, atoi(port));
        }
        else {
            if (gateway) type = CSqlGateway;
            else {
                if (exclusive) type=CSqlDirect; else type = CSql;  
            }
            conn = SqlFactory::createConnection(type);
        }
    }
    rv = conn->connect(username,password);
    if (rv != OK) return 1;
    if (exclusive) {
        SqlConnection *sCon = (SqlConnection*) conn;
        rv = sCon->getExclusiveLock();
        if (rv != OK) {
            conn->disconnect();
            delete conn;
            return 1;
        }
    }
    aconStmt = SqlFactory::createStatement(type);
/*    if (exclusive) {
       SqlStatement *sqlStmt = (SqlStatement*)aconStmt;
       sqlStmt->setLoading(true);
    }*/
    aconStmt->setConnection(conn);
    //rv = conn->beginTrans(READ_COMMITTED, TSYNC);
    rv = conn->beginTrans();
    if (rv != OK) return 2;
    while (getInput(fileFlag) == true) continue;

    //TODO::conn should provide method telling status of the transaction.
    //if running, then abort it
    conn->rollback();
    if (filename [0] !='\0')
    {
       fclose(fp);
    }
    conn->disconnect();
    delete aconStmt;
    delete conn;
    return 0;
}
bool handleTransaction(char *st)
{
    while (isspace (*st)|| *st == '(' ) st++; // Skip white spaces
    if (strcasecmp (st, "COMMIT;") == 0 ||
        strcasecmp (st, "commit;") == 0 )
    {
        conn->commit();
        ListIterator it = sqlStmtList.getIterator();
        while(it.hasElement()) {
            stmt = (AbsSqlStatement *) it.nextElement();
            stmt->free();
            delete stmt;
        }
        sqlStmtList.reset();
        //conn->beginTrans(isoLevel, TSYNC);
        conn->beginTrans(isoLevel);
        return true;
    }
    else if (strcasecmp (st, "ROLLBACK;") == 0|| 
        strcasecmp (st, "rollback;") == 0)
    {
        conn->rollback();
        ListIterator it = sqlStmtList.getIterator();
        while(it.hasElement()) {
            stmt = (AbsSqlStatement *)it.nextElement();
            stmt->free();
            delete stmt;
        }
        sqlStmtList.reset();
        //conn->beginTrans(isoLevel, TSYNC);
        conn->beginTrans(isoLevel);
        return true;
    }
    else if (strcasecmp (st, "SET AUTOCOMMIT ON;") == 0)
    {
        autocommitmode = true;
        if (!silent) printf("AUTOCOMMIT Mode is set to ON\n");
        return true;
    }
    else if (strcasecmp (st, "SET AUTOCOMMIT OFF;") == 0)
    {
        autocommitmode = false;
        if (!silent) printf("AUTOCOMMIT Mode is set to OFF\n");
        return true;
    }
    else if (strcasecmp (st, "SET ISOLATION LEVEL UNCOMMITTED;") == 0)
    {
        isoLevel = READ_UNCOMMITTED;
        printf("Isolation Level is set to READ_UNCOMMITTED\n");
        return true;
    }
    else if (strcasecmp (st, "SET ISOLATION LEVEL COMMITTED;") == 0)
    {
        isoLevel = READ_COMMITTED;
        printf("Isolation Level is set to READ_COMMITTED\n");
        return true;
    }
    else if (strcasecmp (st, "SET ISOLATION LEVEL REPEATABLE;") == 0)
    {
        isoLevel = READ_REPEATABLE;
        printf("Isolation Level is set to READ_REPEATABLE\n");
        return true;
    }
    else if (strcasecmp(st, "SET TIMER ON;") == 0) 
    { isTimer=true; return true; }
    else if (strcasecmp(st, "SET TIMER OFF;") == 0) 
    {  isTimer=false; return true; }
    return false;
}
bool handleEchoAndComment(char *st)
{
    while (isspace (*st)|| *st == '(' ) st++; // Skip white spaces
    if (strncasecmp (st, "ECHO", 4) == 0)
    {
        printf("%s\n", st);
        return true;
    }else if (strncmp(st, "--", 2) == 0)
    {
        return true;
    }else if (strncasecmp(st, "help", 2) == 0)
    {
        printHelp();
        return true;
    }else if(strcasecmp(st,"show variables;")==0){
        
         printVariables();
         return true;
    }else if (strcasecmp(st, "show tables;") == 0) {
      DbRetVal rv = OK;
      List tableList = aconStmt->getAllTableNames(rv);
      ListIterator iter = tableList.getIterator();
      Identifier *elem = NULL;
      int ret =0;
      printf("=============TableNames===================\n");
      int count =0;
      while (iter.hasElement())
      {
          elem = (Identifier*) iter.nextElement();
          count++;
          printf("   %s \n", elem->name);
      }
      if (count ==0) printf("  No tables exist\n");
      printf("==========================================\n");
      return true;
    }else if( strcasecmp(st, "show users;" )==0){
      DbRetVal rv = OK;
      List userList = aconStmt->getAllUserNames(rv);
      ListIterator iter = userList.getIterator();
      Identifier *elem = NULL;
      int ret =0;
      printf("=============UserNames===================\n");
      while (iter.hasElement())
      {
          elem = (Identifier*) iter.nextElement();
          if(0==strcmp( elem->name ,I_USER))
              continue;
          printf("   %s \n", elem->name);
      }
      printf("=========================================\n");
      return true;
    }
    return false;
}
void printHelp()
{
    printf("CSQL Command List\n");
    printf("======================================================\n");
    printf("SHOW TABLES\n");
    printf("SET AUTOCOMMIT ON | OFF\n");
    printf("COMMIT | ROLLBACK\n");
    printf("SET ISOLATION LEVEL UNCOMMITTED | COMMITTED | REPEATABLE\n");
    printf("CREATE TABLE | INDEX ...\n");
    printf("DROP TABLE | INDEX ...\n");
    printf("INSERT ...\n");
    printf("UPDATE ...\n");
    printf("DELETE ...\n");
    printf("SELECT ...\n");
    printf("QUIT\n");
    printf("======================================================\n");
}
void printVariables()
{
  //SERVER Section Info.
  printf("=======================================================\n");
  printf("|             SERVER SECTION INFORMATION              |\n");
  printf("=======================================================\n");
  printf(" SITE_ID\t\t\t= %d\n",Conf::config.getSiteID());
  printf(" PAGE_SIZE\t\t\t= %d Byte\n",Conf::config.getPageSize());
  printf(" MAX_PROCS\t\t\t= %d\n",Conf::config.getMaxProcs());
  printf(" MAX_SYS_DB_SIZE\t\t= %d MB\n",(Conf::config.getMaxSysDbSize()/1048576));
  printf(" MAX_DB_SIZE\t\t\t= %d MB\n",(Conf::config.getMaxDbSize()/1048576));
  printf(" SYS_DB_KEY\t\t\t= %d\n",Conf::config.getSysDbKey());
  printf(" USER_DB_KEY\t\t\t= %d\n",Conf::config.getUserDbKey());
  printf(" LOG_LEVEL\t\t\t= %d\n",Conf::config.getLogLevel());
  printf(" MAP_ADDRESS\t\t\t= %ld\n",Conf::config.getMapAddress());

  if(Conf::config.useDurability())
     printf(" DURABILITY\t\t\t= True\n");
  else
     printf(" DURABILITY\t\t\t= False\n");

  if(Conf::config.useMmap())
     printf(" MMAP\t\t\t\t= True\n");
  else
     printf(" MMAP\t\t\t\t= False\n");

  printf(" DURABLE_MODE\t\t\t= %d\n",Conf::config.getDurableMode());
  printf(" DATABASE_FILE\t\t\t= %s\n",Conf::config.getDbFile());
  printf(" LOG_FILE_PATH\t\t\t= %s\n",Conf::config.getLogFile());
  printf(" STDERR_FILE\t\t\t= %s\n",Conf::config.getStderrFile());

  //Network Section Information
  printf("=======================================================\n");
  printf("|             NETWORK SECTION INFORMATION             |\n");
  printf("=======================================================\n");

  if(Conf::config.useCsqlSqlServer())
      printf(" CSQL_SQL_SERVER\t\t= True\n");
  else
      printf(" CSQL_SQL_SERVER\t\t= False\n");

  printf(" PORT\t\t\t\t= %d\n",Conf::config. getPort());
  printf(" NETWORK_RESPONSE_TIMEOUT\t= %d\n",Conf::config.getNetworkResponseTimeout());
  printf(" NETWORK_CONNECT_TIMEOUT\t= %d\n",Conf::config.getNetworkConnectTimeout());
  printf(" ID_SHM_KEY\t\t\t= %d\n",Conf::config.getShmIDKey());

  //Client section variables
  printf("=======================================================\n");
  printf("|             CLIENT SECTION INFORMATION              |\n");
  printf("=======================================================\n");
  printf(" MUTEX_TIMEOUT_SECS\t\t= %d\n",Conf::config.getMutexSecs());
  printf(" MUTEX_TIMEOUT_USECS\t\t= %d\n",Conf::config.getMutexUSecs());
  printf(" MUTEX_TIMEOUT_RETRIES\t\t= %d\n",Conf::config.getMutexRetries());
  printf(" LOCK_TIMEOUT_SECS\t\t= %d\n",Conf::config.getLockSecs());
  printf(" LOCK_TIMEOUT_USECS\t\t= %d\n",Conf::config.getLockUSecs());
  printf(" LOCK_TIMEOUT_RETRIES\t\t= %d\n",Conf::config.getLockRetries());

  //CACHE Section variables
  printf("=======================================================\n");
  printf("|             CACHE SECTION INFORMATION               |\n");
  printf("=======================================================\n");
  
  if(Conf::config.useCache())
  printf(" CACHE_TABLE\t\t\t= True\n");
  else
  printf(" CACHE_TABLE\t\t\t= False\n");
  
  printf(" DSN\t\t\t\t= %s\n",Conf::config.getDSN());
  
  if(Conf::config.useTwoWayCache()) 
      printf(" ENABLE_BIDIRECTIONAL_CACHE\t= True\n");
  else
      printf(" ENABLE_BIDIRECTIONAL_CACHE\t= False\n");

  printf(" CACHE_RECEIVER_WAIT_SECS\t= %d\n",Conf::config.getCacheWaitSecs());

  if(Conf::config.getCacheMode()==0)
      printf(" CACHE_MODE\t\t\t= SYNC\n");
  else if (Conf::config.getCacheMode()==1)
      printf(" CACHE_MODE\t\t\t= ASYNC\n");
  else
      printf(" CACHE_MODE\t\t\t= Unknown\n");

  printf(" DS_CONFIG_FILE\t\t\t= %s\n",Conf::config.getDsConfigFile());
  printf(" TABLE_CONFIG_FILE\t\t= %s\n",Conf::config.getTableConfigFile());
  printf(" MSG_KEY\t\t\t= %d\n",Conf::config.getMsgKey() );
  printf(" ASYNC_MSGMAX\t\t\t= %d\n",Conf::config.getAsyncMsgMax());
  printf(" MAX_QUEUE_LOGS\t\t\t= %d\n",Conf::config.getLogLevel());
  printf(" CONFL_RESOL_FILE\t\t= %s\n",Conf::config.getConflResoFile());
  printf(" \nNOTE: To modify above variables, You will be following 'csql.conf' file.\n\n");
}

void setStmtType(char *st)
{
   if (strncasecmp (st, "SELECT", 6) == 0)  {stmtType=SELECT; return; }
   else if (strncasecmp (st, "EXPLAIN", 6) == 0)  {stmtType=EXPLAIN; return; }
   else if (strncasecmp (st, "CREATE", 6) == 0) {stmtType=DDL; return; }
   else if (strncasecmp (st, "DROP", 4) == 0) { stmtType=DDL; return; }
   stmtType = OTHER;
   return ;
}

char getQueryFromStdIn(char *buf)
{
    char    c, *bufBegin=buf;
    int    ln, charCnt=0;
#ifdef NO_READLINE_LIB
    ln=1;
    printf("CSQL>");
    while( (c=(char ) getchar()) != EOF && c != ';')
    {
        *buf++ = c; charCnt++;
        if(c=='\n') //printf("%1d>",ln++);
            ln++;
	if( charCnt == SQL_STMT_LEN ) {
            printf("SQL Statement length is greater than %d. "
	    "Ignoring the statement.\n", SQL_STMT_LEN );
            *bufBegin++ =';';
            *bufBegin ='\0';
	    return 0;
	}
        //printf("=%d=\n", c);
    }
    *buf++ = ';';
    *buf = '\0';
#else 
    strcpy(buf, "");
    char *line = readline("CSQL>");
    if (line) {strcpy(buf, line); add_history(line); }
    else { free(line); return EOF; }
    free(line);
#endif
    return 0;
}
char getQueryFromFile(char *buf)
{
    char    c, *bufBegin=buf;
    int charCnt=0;
    while( (c=(char ) fgetc(fp)) != EOF && c != ';')
    {
        *buf++ = c; charCnt++; 
	if( charCnt == SQL_STMT_LEN ) {
            printf("SQL Statement length is greater than %d. "
	    "Ignoring the statement.\n", SQL_STMT_LEN );
            *bufBegin++ =';';
            *bufBegin ='\0';
	    return 0;
	}
    }
    *buf++ = ';';
    *buf = '\0';
    return c;
}

bool getInput(bool fromFile)
{
    char buffer [SQL_STMT_LEN + 1];

    char eof;
    if (fromFile == false)
        eof = getQueryFromStdIn(buffer);
    else
        eof = getQueryFromFile(buffer);
                     
    char *buf = buffer;
    while(*buf == ' ' || *buf == '\t' || *buf == '\n') buf++;
    if (eof == EOF || strncasecmp (buf, "quit", 4) == 0)
        return false;
    if (handleTransaction(buf)) return true;
    if (handleEchoAndComment(buf)) return true;
    if ( *buf == ';' ) return true; // Null statement.
    
    setStmtType(buf);
    NanoTimer timer;
    DbRetVal rv;
    if (autocommitmode) {
        if (!firstPrepare) aconStmt->free(); 
        rv  = aconStmt->prepare(buf);
        if (rv != OK) {
            printf("Statement prepare failed with error %d\n", rv); 
            return true; 
        }
        firstPrepare = false;
        stmt=aconStmt;
    }
    else {
        stmt = SqlFactory::createStatement(type);
        stmt->setConnection(conn);
        rv  = stmt->prepare(buf);
        if (rv != OK) {
            printf("Statement prepare failed with error %d\n", rv); 
            return true; 
        }
        sqlStmtList.append(stmt);
    }
    if (noUndolog || exclusive ){
       SqlStatement *sqlStmt = (SqlStatement*)stmt;
       sqlStmt->setLoading(true);
    }
    int rows =0;
    timer.start();
    rv = stmt->execute(rows);
    if (rv != OK) 
    {
        printf("Statement execute failed with error %d\n", rv);
        if (autocommitmode) {
            conn->rollback();
            aconStmt->free();
            firstPrepare = true; //set this so that it does not free again
            conn->beginTrans(isoLevel);
        }
        else {
            stmt->free();
            sqlStmtList.remove(stmt); 
            delete stmt; stmt = NULL;
        }
        return true; 
    }
    timer.stop();
    if (stmtType == EXPLAIN)
    {
        stmt->close();
    }
    else if (stmtType == OTHER && stmt->isSelect()) stmtType = SELECT;
    else if (stmtType == OTHER )
    {
        if (!silent) printf("Statement Executed: Rows Affected = %d\n", rows);
    }
    else if (stmtType == DDL)
    {
        if (!silent) printf("Statement Executed\n");
    }
    else
    {
        FieldInfo *info = new FieldInfo();
        printf("---------------------------------------------------------\n");
        printf("\t");
        for (int i = 0 ; i < stmt->noOfProjFields() ; i++)
        {
			stmt->getProjFldInfo(i+1, info);
            printf("%s\t", info->fldName);
        }
        printf("\n---------------------------------------------------------\n");
        delete info;
        void *tuple = NULL;
        timer.start();
        while(true)
        {
            printf("\t");
            tuple = (char*)stmt->fetchAndPrint(false);
            printf("\n");
            if (tuple == NULL) { break; }
        }
        stmt->close();
        timer.stop();
    }
    if (isTimer) printf("Time taken: %lld microsecs\n", timer.sum()/1000);
    if (autocommitmode)
    {
        conn->commit();
        //conn->beginTrans(isoLevel, TSYNC);
        stmt->free();
        firstPrepare = true; //set this so that it does not free again
        conn->beginTrans(isoLevel);
        return true;
    }
    return true;
}

int getConnType(int opt) 
{
    switch(opt) {
		case 1: { printf("Local CSql\n"); return (int) CSql; }
		case 2: { printf("Local Adapter\n"); return (int) CSqlAdapter; }
		case 3: { printf("Local Gateway\n"); return (int) CSqlGateway; }
		case 4: { printf("Network CSql\n");  return (int) CSqlNetwork; }
		case 5: { printf("Network Adapter\n"); return (int) CSqlNetworkAdapter;}
		case 6: { printf("Network Gateway\n"); return (int) CSqlNetworkGateway;}
		case 7: { printf("Log\n"); return (int) CSqlLog; }
		case 8: { printf("Log\n"); return (int) CSqlLog; }
    }
}
