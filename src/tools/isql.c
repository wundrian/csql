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
#include <SqlStatement.h>
#define SQL_STMT_LEN 1024
SqlConnection *conn;
SqlStatement *stmt;
bool getInputFromUser();
int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char filename[512];
    filename [0] ='\0';
    int c = 0;
    while ((c = getopt(argc, argv, "u:p:s")) != EOF) 
    {
        switch (c)
        {
            case 'u' : strcpy(username , argv[optind - 1]); break;
            case 'p' : strcpy(password , argv[optind - 1]); break;
            case 's' : strcpy(filename , argv[optind ]); break;
            default: printf("Wrong args\n"); exit(1);

        }
    }//while options
    printf("%s %s %s", username, password, filename);
    if (username[0] == '\0' )
    {
        strcpy(username, "praba");
        strcpy(password, "manager");
    }
    
    DbRetVal rv = OK;
    conn = new SqlConnection();
    conn->connect("praba", "manager");
    stmt = new SqlStatement();
    stmt->setConnection(conn);
    conn->beginTrans();

    while (getInputFromUser() == true) continue;

    //TODO::conn should provide method telling status of the transaction.
    //if running, then abort it
    conn->rollback();
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
bool isSelectStmt(char *st)
{
    if (strncasecmp (st, "SELECT", 6) == 0) return true; 
    return false;
}

char getQuery(char *buf)
{
    char    c;
    int    ln;

    ln=1;
    printf("CSQL>");
    while( (c=(char ) getchar()) != EOF && c != ';')
    {
        *buf++ = c;
        if(c=='\n')
            printf("%1d>",ln++);
    }
    *buf++ = ';';
    *buf = '\0';
    if(c==EOF)
        return c;

    //while( (c=getchar()) != EOF && c != '\n');

    return c;
}

bool getInputFromUser()
{
    char buf [SQL_STMT_LEN + 1];

    char eof = getQuery(buf);
    printf("PRABA== %s\n", buf);
    if (eof == EOF || strncasecmp (buf, "quit", 4) == 0)
        return false;
    if (handleTransaction(buf)) return true;

    bool isSelect = false;
    if (isSelectStmt(buf)) isSelect = true;

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
        return true; 
    }
    if (! isSelect)
    {
        printf("Statement Executed: Rows Affected = %d\n", rows);
    }
    else
    {
        printf("Currently not supported\n");
    }
    stmt->free();
    return true;

}
