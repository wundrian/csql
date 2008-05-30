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
#include <list>
#include <SqlFactory.h>
#include <SqlOdbcConnection.h>
#include <SqlOdbcStatement.h>

void printUsage()
{
   printf("Usage: cacheverify [-U username] [-P passwd] -t tablename\n"
          "       [-p] [-f]\n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   printf("       tablename -> cached table name in csql from target db.\n");
   printf("       p -> verification at primary key field level\n");
   printf("       f -> verification at record level\n");
   printf("       ? -> help\n");
   return;
}

typedef struct PrimaryKeyField {
    int val;
    bool inCsql;
    bool inTrgtDb;
} PrimKeyFldVal;

using namespace std;
bool cmp(const PrimKeyFldVal *a, const PrimKeyFldVal *b)
{
    return a->val < b->val;
}

DbRetVal verifyCount(const char *tblName, long numTuples) 
{
    char statement[200];
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlAdapter);
    DbRetVal rv = con->connect("root", "manager");
    if (rv != OK) { delete con; return ErrSysInit; }
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(con);
    int count = 0;
    int rows = 0;
    sprintf(statement, "select count(*) from %s;", tblName);
    rv = con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv != OK) { 
        delete stmt; delete con;
        printError(rv, "Prepare failed\n"); 
        return rv; 
    }
    stmt->bindField(1, &count);
    rv  = stmt->execute(rows); 
    if(rv != OK) { 
        delete stmt; delete con; 
        printError(rv, "Execute failed\n"); 
        return rv; 
    }
    if (stmt->fetch()== NULL) { 
        delete stmt; delete con; 
        printError(ErrSysInternal, "Fetch failed\n"); 
        return ErrSysInternal; 
    }
    con->commit();
    printf("--------------------+-----------------+----------------------+\n");
    printf("       Data         |     In CSQL     |     In TargetDb      |\n");
    printf("--------------------+-----------------+----------------------+\n");
    printf(" Number of Tuples   |    %5d        |      %5d           |\n", numTuples, count);
    printf("--------------------+-----------------+----------------------+\n");
    delete stmt; delete con; 
    return OK;
}

DbRetVal verifyPrimKeyFldVal(const char *tblName)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager *) conn.getDatabaseManager();
    if (dbMgr == NULL) {
        conn.close();
        printError(ErrSysInit, "Auth failed");
        return ErrSysInit;
    }
    Table *table = dbMgr->openTable(tblName);
    if(table == NULL) {
        conn.close();
        printError(ErrNotExists, "Table \'%s\' does not exist", tblName);
        return ErrNotExists;
    }
    
    char statement[200];
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlAdapter);
    rv = con->connect("root", "manager");
    if (rv != OK) { delete con; return ErrSysInit; }
    AbsSqlStatement *stmt =  SqlFactory::createStatement(CSqlAdapter);
    stmt->setConnection(con);
    char fieldName[IDENTIFIER_LENGTH];
    fieldName[0] = '\0';
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) stmt;
    ostmt->getPrimaryKeyFieldName((char*)tblName, fieldName);
    if (fieldName[0] == '\0') {
        printError(ErrNotExists, "Primary key does not exist.");
        return ErrNotExists;
    }
    printf("Primary key field name is \'%s\'\n", fieldName);
    FieldInfo *fldInfo = new FieldInfo();
    table->getFieldInfo(fieldName, fldInfo);
    //if(! fldInfo->isPrimary) { printError(ErrBadArg, "\'%s\' is not a primary key field", fldName); return ErrBadArg; }
    int csqlVal = 0;
    List valListInCsql;
    table->bindFld(fieldName, &csqlVal);
    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if(rv != OK) { 
        delete stmt; delete con;
        printError(rv, "Execute failed\n"); 
        return rv; 
    }
    while(true) {
        void* tuple = table->fetch(rv);
        if (tuple == NULL) break;
        PrimKeyFldVal *pkFldVal = new PrimKeyFldVal(); 
        pkFldVal->val = csqlVal;  
        pkFldVal->inCsql = true; 
        pkFldVal->inTrgtDb = true;
        valListInCsql.append(pkFldVal);
    }    
    conn.commit();
    table->close();
    dbMgr->closeTable(table);
    int trgtDbVal = 0;
    int rows = 0;
    List valListInTrgtDb;
    sprintf(statement, "select f1 from %s;", tblName);
    rv = con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv != OK) { 
        delete stmt; delete con;
        printError(rv, "Prepare failed\n"); 
        return rv; 
    }
    stmt->bindField(1, &trgtDbVal);
    rv  = stmt->execute(rows);
    if(rv != OK) { 
        delete stmt; delete con;
        printError(rv, "Execute failed\n"); 
        return rv; 
    }
    while (stmt->fetch() != NULL) {
        PrimKeyFldVal *pkFldVal = new PrimKeyFldVal(); 
        pkFldVal->val = trgtDbVal; 
        pkFldVal->inCsql = true; 
        pkFldVal->inTrgtDb = true;
        valListInTrgtDb.append(pkFldVal);
    }
    con->commit();
    delete stmt; delete con;

    List diffInValList;
    ListIterator csqlValIter = valListInCsql.getIterator();
    ListIterator trgtDbValIter = valListInTrgtDb.getIterator();    
    PrimKeyFldVal *csqlelem, *trgtdbelem;
    while( (csqlelem = (PrimKeyFldVal *) csqlValIter.nextElement()) != NULL) {
        while ( (trgtdbelem = (PrimKeyFldVal *) trgtDbValIter.nextElement()) != NULL)   {
            if (csqlelem->val == trgtdbelem->val) { 
                trgtDbValIter.reset(); 
                break; 
            }
        }
        if (trgtdbelem == NULL) {    
            csqlelem->inTrgtDb = false;
            PrimKeyFldVal *elm = new PrimKeyFldVal();
            *elm = * csqlelem;
            diffInValList.append(elm);
            trgtDbValIter.reset();
        }
    }
    csqlValIter.reset();
    //trgtDbValIter.reset();
    while((trgtdbelem = (PrimKeyFldVal *)trgtDbValIter.nextElement()) != NULL) {
        while((csqlelem = (PrimKeyFldVal *)csqlValIter.nextElement()) != NULL) {
            if (trgtdbelem->val == csqlelem->val) { 
                csqlValIter.reset(); 
                break; 
            }
        }
        if (csqlelem == NULL) {    
            trgtdbelem->inCsql = false;
            PrimKeyFldVal *elm = new PrimKeyFldVal();
            *elm = *trgtdbelem;
            diffInValList.append(elm);
            csqlValIter.reset();
        }
    }
    list <PrimKeyFldVal *> li;
    ListIterator diffValIter = diffInValList.getIterator();
    if (diffInValList.size()) {
        PrimKeyFldVal *elem = NULL;
        while ((elem = (PrimKeyFldVal *) diffValIter.nextElement()) != NULL )  
            li.push_back(elem);

        list<PrimKeyFldVal *>::iterator it;
        li.sort(cmp);
        printf("-----------------+-------------------+-----------------------+\n");
        printf("%10s       |    not in csql    |    not in targetdb    |\n", fieldName);
        printf("-----------------+-------------------+-----------------------+\n");  
        for (it = li.begin(); it != li.end(); it++) {
            if ((*it)->inCsql == false) 
                printf("    %6d       |         X         |                       |\n", (*it)->val);
            else if ((*it)->inTrgtDb == false)
                printf("    %6d       |                   |           X           |\n", (*it)->val);
        }
        printf("-----------------+-------------------+-----------------------+\n");
    }
    else printf("The data in both the servers is consistent\n");
    li.clear();
    PrimKeyFldVal *elem;   
    while((elem = (PrimKeyFldVal *)trgtDbValIter.nextElement()) != NULL)
        delete elem;
    while((elem = (PrimKeyFldVal *)csqlValIter.nextElement()) != NULL) 
        delete elem;
    while ((elem = (PrimKeyFldVal *) diffValIter.nextElement()) != NULL )  
        delete elem;
    diffInValList.reset();
    valListInTrgtDb.reset();
    valListInCsql.reset();
    return OK;
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char tableName[IDENTIFIER_LENGTH];
    tableName[0] = '\0';
    while ((c = getopt(argc, argv, "U:P:t:pf?")) != EOF) 
    {
        switch (c)
        {
            case 'U' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'P' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tableName, argv[optind - 1]); 
                         if (opt==10) opt = 2; 
                         break; 
                       }
            case 'p' : { opt = 3; break; } //verify at primary key level
            case 'f' : { opt = 4; break; } //verify at record level
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 

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
    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager *) conn.getDatabaseManager();
    if (dbMgr == NULL) { 
        conn.close();
        printError(ErrSysInit, "Auth failed"); 
        return ErrSysInit; 
    }
    Table *table = dbMgr->openTable(tableName);
    if(table == NULL) {
        conn.close(); 
        printError(ErrNotExists, "Table \'%s\' does not exist", tableName); 
        return ErrNotExists; 
    }

    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        dbMgr->closeTable(table);
        conn.close();
        printError(ErrSysInit, "cachetable.conf file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    int mode;
    bool filePresent = false;
    while(!feof(fp)) {
        fscanf(fp, "%d:%s\n", &mode, tablename);
        if (mode ==2 )  //just replicated table and not cached
            continue;
        if (strcmp(tableName, tablename) == 0) {
            filePresent = true;
            break;
        }
    }
    fclose(fp);
    long numTuples = table->numTuples();
    dbMgr->closeTable(table);
    conn.close();
    
    if (filePresent == false) { printError(ErrNotCached, "The table \'%s\' is not cached", tableName);
        return ErrNotCached;
    }

    if (opt == 2) { 
    rv = verifyCount(tableName, numTuples); 
    if (rv != OK) return 1;
    }
 
    if (opt == 3) { 
    rv = verifyPrimKeyFldVal(tableName); 
    if (rv != OK) return 2;
    }
    return 0;
}
