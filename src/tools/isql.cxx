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
#include<CSql.h>
#include<DatabaseManagerImpl.h>
#include <Statement.h>
#include <SqlFactory.h>
#include <SqlStatement.h>
#include <SqlNwConnection.h>
#include <SqlNwStatement.h>
#define SQL_STMT_LEN 1024
enum STMT_TYPE
{
    SELECT =0,
    DDL ,
    OTHER
};
STMT_TYPE stmtType = SELECT;
FILE *fp;
AbsSqlConnection *conn;
AbsSqlStatement *stmt;
SqlApiImplType type = CSqlUnknown;
bool gateway=false, silent=false;
bool autocommitmode = true;
bool network = false;
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
    while ((c = getopt(argc, argv, "u:p:s:H:P:gS?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : strcpy(username , argv[optind - 1]); break;
            case 'p' : strcpy(password , argv[optind - 1]); break;
            case 's' : strcpy(filename , argv[optind - 1]); break;
            case '?' : { opt = 1; break; } //print help 
            case 'S' : { silent = true; break; } //silent 
            case 'g' : { gateway = true; break; } //print help 
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
        strcpy(username, "root");
        strcpy(password, "manager");
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
    if (network) {
        if (gateway) type = CSqlNetworkGateway;
        else type = CSqlNetwork;
        conn = SqlFactory::createConnection(type);
        SqlNwConnection *con = (SqlNwConnection *)conn;
        con->setHost(hostname, atoi(port));
    }
    else {
        if (gateway) type = CSqlGateway;
        else type = CSql;  
        conn = SqlFactory::createConnection(type);
    }
    rv = conn->connect(username,password);
    if (rv != OK) return 1;
    stmt = SqlFactory::createStatement(type);
    stmt->setInnerStatement(NULL);
    stmt->setConnection(conn);
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
    delete stmt;
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
        //conn->beginTrans(isoLevel, TSYNC);
        conn->beginTrans(isoLevel);
        return true;
    }
    else if (strcasecmp (st, "ROLLBACK;") == 0|| 
        strcasecmp (st, "rollback;") == 0)
    {
        conn->rollback();
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
    }else if (strcasecmp(st, "show tables;") == 0)
    {
      Connection conn;
      conn.open("root","manager");
      DatabaseManagerImpl *dbMgr =  (DatabaseManagerImpl*)conn.getDatabaseManager();
      if (dbMgr == NULL)
      {
          printf("Unable to connect to csql server\n");
          return true;
      }
      List tableList = dbMgr->getAllTableNames();
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
      printf("=========================================\n");
      conn.close();
      return true;
    }
    return false;
}
void printHelp()
{
    printf("CSQL Command List\n");
    printf("======================================================\n");
    printf("SHOW TABLES\n");
    printf("SET AUTOCOMMIT ON|OFF\n");
    printf("SET ISOLATION LEVEL UNCOMMITTED|COMMITTED|REPEATABLE\n");
    printf("CREATE TABLE|INDEX ...\n");
    printf("INSERT ...\n");
    printf("UPDATE ...\n");
    printf("DELETE ...\n");
    printf("SELECT ...\n");
    printf("======================================================\n");
}
void setStmtType(char *st)
{
   if (strncasecmp (st, "SELECT", 6) == 0)  {stmtType=SELECT; return; }
   else if (strncasecmp (st, "CREATE", 6) == 0) {stmtType=DDL; return; }
   else if (strncasecmp (st, "DROP", 4) == 0) { stmtType=DDL; return; }
   stmtType = OTHER;
   return ;
}

char getQueryFromStdIn(char *buf)
{
    char    c, *bufBegin=buf;
    int    ln, charCnt=0;

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
    }
    *buf++ = ';';
    *buf = '\0';
    return c;
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

    DbRetVal rv = stmt->prepare(buf);
    if (rv != OK) 
    {
        printf("Statement prepare failed with error %d\n", rv); 
        return true; 
    }
    int rows =0;
    rv = stmt->execute(rows);
    if (rv != OK) 
    {
        printf("Statement execute failed with error %d\n", rv);
        stmt->free();
        return true; 
    }
    if (stmtType == OTHER)
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
        while(true)
        {
            printf("\t");
            tuple = (char*)stmt->fetchAndPrint(false);
            printf("\n");
            if (tuple == NULL) { break; }
        }
        stmt->close();
    }
    stmt->free();
    if (autocommitmode)
    {
        conn->commit();
        //conn->beginTrans(isoLevel, TSYNC);
        conn->beginTrans(isoLevel);
        return true;
    }
    return true;
}
