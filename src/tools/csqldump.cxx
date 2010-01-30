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

SqlConnection *sqlconn;
SqlStatement *stmt;

bool isCached(char *tblName)
{
    if (!Conf::config.useCache()) return false;
    FILE *fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) { return OK; }
    char ctablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];

    int mode;
    bool isCached=false;
    while(!feof(fp)) {
        fscanf(fp, "%d %s %s %s %s %s %s %s\n", &mode, ctablename,fieldname,condition,field,dsnName);
        if (strcmp (ctablename, tblName) == 0) { isCached=true; break; }
    }
    fclose(fp);
    return isCached;
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char tblName[IDENTIFIER_LENGTH];
    char conditionVal[IDENTIFIER_LENGTH];
    int c = 0, opt = 0;
    int noOfStmts =100;
    bool exclusive = false;
    bool Iscondition=false;
    bool schema = false;
    char name[IDENTIFIER_LENGTH];
    while ((c = getopt(argc, argv, "u:p:n:T:c:XS?")) != EOF) {
        switch (c) {
            case 'u' : { strcpy(username, argv[optind - 1]); opt=1; break; }
            case 'p' : { strcpy(password, argv[optind - 1]); opt=1; break; }
            case 'n' : { noOfStmts = atoi(argv[optind - 1]); opt = 5; break; }
            case 'T' : { strcpy(tblName,  argv[optind - 1]); opt = 15; break; }
            case 'c' : {strcpy(conditionVal,argv[optind -1]); Iscondition=true;break;}
	    case 'X' : { exclusive = true; break; }
            case 'S' : { schema = true; break; }
            case '?' : { opt = 10; break; } //print help 
            default: opt=1; //list all the tables

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' ) {
        strcpy(username, I_USER);
        strcpy(password, I_PASS);
    }
    sqlconn = (SqlConnection*) SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = sqlconn->connect(username, password);
    if (rv != OK)  {
        printf("Unable to get connection to csql\n");
        delete sqlconn; delete stmt; return 1;
    }
    stmt = (SqlStatement*) SqlFactory::createStatement(CSqlDirect);
    stmt->setSqlConnection(sqlconn);
    if (exclusive) { stmt->setLoading(true); }
    
    if (opt == 0 || opt == 1) opt = 5;
    if (opt == 5) {
        os::signal(SIGCSQL1, SIG_IGN);
        DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) 
                                 sqlconn->getConnObject().getDatabaseManager();
        if (dbMgr == NULL) {  
            printf("Unable to retrive db manager\n"); 
            sqlconn->disconnect(); delete stmt; delete sqlconn; return 2; 
        }
        List tableList = dbMgr->getAllTableNames();
        ListIterator iter = tableList.getIterator();
        Identifier *elem = NULL;
        int count =0;
        while (iter.hasElement()) {
            elem = (Identifier*) iter.nextElement();
            //if (!exclusive && isCached(elem->name)) continue;
            printf("CREATE TABLE %s (", elem->name);
            Table *table = dbMgr->openTable(elem->name);
            if (NULL == table) {
                printError(ErrSysInternal, 
                                        "Unable to open table %s", elem->name);
                break;
            }
            FieldInfo *info = new FieldInfo();
            List fNameList = table->getFieldNameList();
            ListIterator fNameIter = fNameList.getIterator();
            count++;
            bool firstField=true;
            Identifier *elem1 = NULL;
            char fieldName[IDENTIFIER_LENGTH];
            while (fNameIter.hasElement()) {
                elem1 = (Identifier*) fNameIter.nextElement();
                Table::getFieldNameAlone(elem1->name, fieldName);
                rv = table->getFieldInfo(elem1->name, info);
                if (rv !=OK)  {
                    printf("unable to retrive info for table %s\n", 
                                                                  elem1->name);
                    sqlconn->disconnect(); delete stmt; delete sqlconn;
                    return 3;
                }
                if (firstField) {
                    printf("%s %s ", fieldName, 
                                        AllDataType::getSQLString(info->type));
                    firstField = false;
                } else
                    printf(", %s %s ", fieldName, 
                                        AllDataType::getSQLString(info->type));
                if (info->type == typeString || info->type == typeVarchar ||
                                                      info->type == typeBinary)
                     printf("(%d)",info->length);
                if (info->isNull) printf(" NOT NULL ");
                if (info->isDefault) 
                    printf(" DEFAULT '%s' ", info->defaultValueBuf);
                if (info->isAutoIncrement) printf(" AUTO_INCREMENT ");
            }
            fNameIter.reset();
            while (fNameIter.hasElement()) {
                elem1 = (Identifier*) fNameIter.nextElement();
                delete elem1;
            }
            fNameList.reset();
            if (table->isFKTable()){
                table->printSQLForeignString();
            }
            printf(");\n");
            table->printSQLIndexString();
            delete info;
            dbMgr->closeTable(table);
        }
        if (schema) { 
            sqlconn->disconnect(); 
            delete sqlconn; delete stmt; return 0; 
        }
        stmt->setSqlConnection(sqlconn);
        if (exclusive) {
            rv = sqlconn->getExclusiveLock();
            if (rv != OK) {
                printf("Unable to get exclusive lock\n");
                sqlconn->disconnect(); delete sqlconn; delete stmt; return 4;
            }
        }
        iter.reset();
        char sqlstring[1024]="";
        bool flag=false;
        while (iter.hasElement()) {
            elem = (Identifier*) iter.nextElement();
            //if (!exclusive && isCached(elem->name)) continue;
            if (!flag) { printf("SET AUTOCOMMIT OFF;\n"); flag=true; } 
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
            if (rows % noOfStmts !=0) { 
                sqlconn->commit(); 
                printf("COMMIT;\n"); 
            }
            stmt->close();
            stmt->free();
        }   
        iter.reset();
        while (iter.hasElement()) {
            elem = (Identifier*) iter.nextElement();
            delete elem;
        }
        tableList.reset();
    } 
    if (opt == 15) {
        os::signal(SIGCSQL1, SIG_IGN);
        DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) 
                                 sqlconn->getConnObject().getDatabaseManager();
        if (dbMgr == NULL) {
            printf("Unable to retrive db manager\n");
            sqlconn->disconnect(); delete stmt; delete sqlconn; return 5;
        }
        Table *table = dbMgr->openTable(tblName);
        if (table == NULL) {
            printf("csqldump: Table \'%s\' does not exist\n", tblName);
            sqlconn->disconnect(); delete sqlconn; delete stmt; return 6;
        }
        printf("CREATE TABLE %s (", tblName);
	    FieldInfo *info = new FieldInfo();
        List fNameList = table->getFieldNameList();
        ListIterator fNameIter = fNameList.getIterator();
        bool firstField=true;
        Identifier *elem = NULL;
        char fieldName[IDENTIFIER_LENGTH];
        while (fNameIter.hasElement()) {
            elem = (Identifier*) fNameIter.nextElement();
            Table::getFieldNameAlone(elem->name, fieldName);
            table->getFieldInfo((const char*)elem->name, info);
            if (firstField) {
                printf("%s %s ", fieldName, 
                                        AllDataType::getSQLString(info->type));
                firstField = false;
            }
            else
                printf(", %s %s ", fieldName, 
                                        AllDataType::getSQLString(info->type));
            if (info->type == typeString || info->type == typeVarchar ||
                                                      info->type == typeBinary)
                printf("(%d)",info->length);
            if (info->isNull) printf(" NOT NULL ");
            if (info->isDefault) 
                printf(" DEFAULT '%s' ", info->defaultValueBuf);
        }
        printf(");\n");
        table->printSQLIndexString();
        delete info;
        char sqlstring[1024];
	    bool flag=false;
        if (!flag) { printf("SET AUTOCOMMIT OFF;\n"); flag=true; } 
	    if(Iscondition)
            sprintf(sqlstring, "SELECT * FROM %s WHERE %s;", tblName,
                                                                 conditionVal);
        else sprintf(sqlstring, "SELECT * FROM %s;", tblName);
        sqlconn->beginTrans();
        rv = stmt->prepare(sqlstring);
	
        //***********************************************
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
    sqlconn->disconnect();
    delete sqlconn;
    delete stmt;
    return 0;
}
