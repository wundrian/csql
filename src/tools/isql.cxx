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
#include <Statement.h>
#include <SqlStatement.h>
#define SQL_STMT_LEN 1024
enum STMT_TYPE
{
    SELECT =0,
    DDL ,
    OTHER
};
STMT_TYPE stmtType = SELECT;
FILE *fp;
SqlConnection *conn;
SqlStatement *stmt;
bool getInput(bool);
void printUsage()
{
   printf("Usage: csql [-u username] [-p passwd] [-s sqlfile] \n");
   printf("       username -> username to connect to database\n");
   printf("       password -> password to connect to database\n");
   printf("       sqlfile -> filename containing sql statements\n");
   return;
  
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char filename[512];
    filename [0] ='\0';
    int c = 0, opt=0;
    while ((c = getopt(argc, argv, "u:p:s:?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : strcpy(username , argv[optind - 1]); break;
            case 'p' : strcpy(password , argv[optind - 1]); break;
            case 's' : strcpy(filename , argv[optind - 1]); break;
            case '?' : { opt = 1; break; } //print help 
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
    bool fileFlag = false;
    if (filename [0] !='\0')
    {
        printf("Entering here\n");
        fp = fopen(filename,"r");
        if (fp == NULL)
        {
            printf("Unable to open the file %s\n", filename);
            return 1;
        }
        fileFlag = true;
    }
    
    DbRetVal rv = OK;
    conn = new SqlConnection();
    rv = conn->connect(username,password);
    if (rv != OK) return 1;
    stmt = new SqlStatement();
    stmt->setConnection(conn);
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
    delete stmt;
    delete conn;
    return 0;
}
bool handleTransaction(char *st)
{
    while (isspace (*st)|| *st == '(' ) st++; // Skip white spaces
    if (strncasecmp (st, "COMMIT", 6) == 0 ||
        strncasecmp (st, "commit", 6) == 0 )
    {
        conn->commit();
        conn->beginTrans();
        return true;
    }
    else if (strncasecmp (st, "ROLLBACK", 8) == 0|| 
        strncasecmp (st, "rollback", 8) == 0)
    {
        conn->rollback();
        conn->beginTrans();
        return true;
    }
    return false;
}
bool handleEchoAndComment(char *st)
{
    while (isspace (*st)|| *st == '(' ) st++; // Skip white spaces
    if (strncasecmp (st, "ECHO", 4) == 0 ||
        strncasecmp (st, "echo", 4) == 0 )
    {
        printf("%s\n", st);
        return true;
    }else if (strncmp(st, "--", 2) == 0)
    {
        return true;
    }
    return false;
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
    char    c;
    int    ln;

    ln=1;
    printf("CSQL>");
    while( (c=(char ) getchar()) != EOF && c != ';')
    {
        *buf++ = c;
        if(c=='\n')
            //printf("%1d>",ln++);
            ln++;
    }
    *buf++ = ';';
    *buf = '\0';
    return c;
}
char getQueryFromFile(char *buf)
{
    char    c;
    while( (c=(char ) fgetc(fp)) != EOF && c != ';')
    {
        *buf++ = c;
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
        printf("Statement Executed: Rows Affected = %d\n", rows);
    }
    else if (stmtType == DDL)
    {
        printf("Statement Executed\n");
    }
    else
    {
        FieldInfo *info = new FieldInfo();
        printf("---------------------------------------------------------\n");
        printf("\t");
        for (int i = 0 ; i < stmt->noOfProjFields() ; i++)
        {
            stmt->getProjFldInfo(i, info);
            printf("%s\t", info->fldName);
        }
        printf("\n---------------------------------------------------------\n");
        delete info;
        void *tuple = NULL;
        while(true)
        {
            printf("\t");
            tuple = (char*)stmt->fetchAndPrint();
            printf("\n");
            if (tuple == NULL) { break; }
        }
        stmt->close();
    }
    stmt->free();
    return true;

}
