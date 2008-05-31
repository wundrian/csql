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
#include <CSql.h>
#include <DatabaseManagerImpl.h>
#include <Database.h>
#include <TableImpl.h>
#include <SqlFactory.h>
#include <SqlStatement.h>
void printUsage()
{
   printf("Usage: csqldump [-u username] [-p passwd] [-n noOfStmtsPerCommit] [-T tableName]\n");
   printf("       n -> number of statements per commit\n");
   printf("            Default value is 100. If system db size is big, then it shall be increased.\n");
   printf("       T -> Will dump only the table specified with this option.\n");
   return;
  
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char tblName[IDENTIFIER_LENGTH];
    int c = 0, opt = 0;
    int noOfStmts =100;
    char name[IDENTIFIER_LENGTH];
    while ((c = getopt(argc, argv, "u:p:n:T:?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : { strcpy(username, argv[optind - 1]); opt=1; break; }
            case 'p' : { strcpy(password, argv[optind - 1]); opt=1; break; }
            case 'n' : { noOfStmts = atoi(argv[optind - 1]); opt = 5; break; }
            case 'T' : { strcpy(tblName,  argv[optind - 1]); opt = 15; break; }
            case '?' : { opt = 10; break; } //print help 
            default: opt=1; //list all the tables

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, "root");
        strcpy(password, "manager");
    }
    SqlConnection *sqlconn = (SqlConnection*) SqlFactory::createConnection(CSql);
    sqlconn->connect("root", "manager");
    SqlStatement *stmt = (SqlStatement*) SqlFactory::createStatement(CSql);
    stmt->setConnection(sqlconn);
    
    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return 1;
    DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    if (opt == 0 || opt == 1) opt = 5;
    if (opt == 5) {
        List tableList = dbMgr->getAllTableNames();
        ListIterator iter = tableList.getIterator();
        Identifier *elem = NULL;
        int count =0;
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            printf("CREATE TABLE %s (", elem->name);
            Table *table = dbMgr->openTable(elem->name);
	        FieldInfo *info = new FieldInfo();
            List fNameList = table->getFieldNameList();
            ListIterator fNameIter = fNameList.getIterator();
            count++;
            bool firstField=true;
            while (fNameIter.hasElement()) {
                 elem = (Identifier*) fNameIter.nextElement();
                 table->getFieldInfo((const char*)elem->name, info);
                 if (firstField) {
                     printf("%s %s ", elem->name, AllDataType::getSQLString(info->type));
                     firstField = false;
                 }
                 else
                     printf(", %s %s ", elem->name, AllDataType::getSQLString(info->type));
                 if (info->type == typeString) printf("(%d)",info->length -1);
                 if (info->isNull) printf(" NOT NULL ");
                 if (info->isDefault) printf(" DEFAULT '%s' ", info->defaultValueBuf);
            }
            printf(");\n");
            table->printSQLIndexString();
            delete info;
            dbMgr->closeTable(table);
       }
       iter.reset();
       char sqlstring[1024];
       bool flag=false;
       while (iter.hasElement()) {
           if (!flag) { printf("SET AUTOCOMMIT OFF;\n"); flag=true; } 
           elem = (Identifier*) iter.nextElement();
           sprintf(sqlstring, "SELECT * FROM %s;", elem->name);
           sqlconn->beginTrans();
           DbRetVal rv = stmt->prepare(sqlstring);
           int rows = 0;
           rv = stmt->execute(rows);
           void *tuple = NULL;
           rows = 0;
           while(true) {
               tuple = stmt->fetchAndPrint(true);
               if (tuple == NULL) break;
               rows++;
               if (rows % noOfStmts ==0) {
                   sqlconn->commit();
                   sqlconn->beginTrans();
                   printf("COMMIT;\n");
               }
           }
           if (rows % noOfStmts !=0) { sqlconn->commit(); printf("COMMIT;\n"); }
           stmt->close();
           stmt->free();
       }   
       conn.close();
       sqlconn->disconnect();
       delete sqlconn;
       delete stmt;
       return 0;
    } 
    if (opt == 15) {
        Table *table = dbMgr->openTable(tblName);
        if (table == NULL) {
            printf("csqldump: Table \'%s\' does not exist\n", tblName);
            conn.close();
            sqlconn->disconnect();
            delete sqlconn;
            delete stmt;
            return 3;
        }
        printf("CREATE TABLE %s (", tblName);
	    FieldInfo *info = new FieldInfo();
        List fNameList = table->getFieldNameList();
        ListIterator fNameIter = fNameList.getIterator();
        bool firstField=true;
        Identifier *elem = NULL;
        while (fNameIter.hasElement()) {
            elem = (Identifier*) fNameIter.nextElement();
            table->getFieldInfo((const char*)elem->name, info);
            if (firstField) {
                printf("%s %s ", elem->name, AllDataType::getSQLString(info->type));
                firstField = false;
            }
            else
                printf(", %s %s ", elem->name, AllDataType::getSQLString(info->type));
            if (info->type == typeString) printf("(%d)",info->length -1);
            if (info->isNull) printf(" NOT NULL ");
            if (info->isDefault) printf(" DEFAULT '%s' ", info->defaultValueBuf);
        }
        printf(");\n");
        table->printSQLIndexString();
        delete info;
        char sqlstring[1024];
        bool flag=false;
        if (!flag) { printf("SET AUTOCOMMIT OFF;\n"); flag=true; } 
        sprintf(sqlstring, "SELECT * FROM %s;", tblName);
        sqlconn->beginTrans();
        DbRetVal rv = stmt->prepare(sqlstring);
        int rows = 0;
        rv = stmt->execute(rows);
        void *tuple = NULL;
        rows = 0;
        while(true) {
            tuple = stmt->fetchAndPrint(true);
            if (tuple == NULL) break;
            rows++;
            if (rows % noOfStmts ==0) {
                sqlconn->commit();
                sqlconn->beginTrans();
                printf("COMMIT;\n");
            }
        }       
        if (rows % noOfStmts !=0) { sqlconn->commit(); printf("COMMIT;\n"); }
        stmt->close();
        stmt->free();
    }   
    conn.close();
    sqlconn->disconnect();
    delete sqlconn;
    delete stmt;
    
    return 0;
}
