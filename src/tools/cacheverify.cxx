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
   printf("Usage: cacheverify [-U username] [-P passwd] -t tablename [-p] [-f]\n");
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


typedef struct FldVal {
    void *value;
    DataType type;
    int length;
}FldVal;

typedef struct Rec {
    int val;
    List fldValList;
}Record;

using namespace std;

// functions to sort the list for STL list
bool cmp(const PrimKeyFldVal *a, const PrimKeyFldVal *b)
{
    return a->val < b->val;
}

bool cmpRec(const Record *a, const Record *b)
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
        printf("Prepare failed\n"); 
        return rv; 
    }
    stmt->bindField(1, &count);
    rv  = stmt->execute(rows); 
    if(rv != OK) { 
        delete stmt; delete con; 
        printf("Execute failed\n"); 
        return rv; 
    }
    if (stmt->fetch()== NULL) { 
        delete stmt; delete con; 
        printf("Fetch failed\n"); 
        return ErrSysInternal; 
    }
    con->commit();
    stmt->free();
    printf("\nNumber of Records:\n");
    printf("-------------------+-------------------+-------------------+\n");
    printf("  Data             |  In CSQL          |  In TargetDB      |\n");
    printf("-------------------+-------------------+-------------------+\n");
    printf("  No. Of Records   |  %-6ld           |  %-6d           |\n", numTuples, count);
    printf("-------------------+-------------------+-------------------+\n");
    delete stmt; delete con; 
    return OK;
}

DbRetVal verifyMismatchingRecords(const char *tblName, int option)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager *) conn.getDatabaseManager();
    if (dbMgr == NULL) {
        conn.close();
        printf("Auth failed\n");
        return ErrSysInit;
    }
    Table *table = dbMgr->openTable(tblName);
    if(table == NULL) {
        conn.close();
        printf("Table \'%s\' does not exist", tblName);
        return ErrNotExists;
    }
    
    char statement[200];
    AbsSqlConnection *trgtDbCon = SqlFactory::createConnection(CSqlAdapter);
    rv = trgtDbCon->connect("root", "manager");
    if (rv != OK) { 
        dbMgr->closeTable(table); conn.close();
        delete trgtDbCon; return ErrSysInit; 
    }
    AbsSqlStatement *trgtDbStmt =  SqlFactory::createStatement(CSqlAdapter);
    trgtDbStmt->setConnection(trgtDbCon);
 
    char fieldName[IDENTIFIER_LENGTH];
    fieldName[0] = '\0';
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) trgtDbStmt;
    ostmt->getPrimaryKeyFieldName((char*)tblName, fieldName);
    if (fieldName[0] == '\0') {
        dbMgr->closeTable(table); conn.close();
        delete trgtDbStmt; delete trgtDbCon;  
        printf("Primary key does not exist on table %s\n", tblName);
        return ErrNotExists;
    }
    printf("\nPrimary key field name is \'%s\'\n", fieldName);
    //FieldInfo *fldInfo = new FieldInfo();
    //table->getFieldInfo(fieldName, fldInfo);
    //if(! fldInfo->isPrimary) { printError(ErrBadArg, "\'%s\' is not a primary key field", fldName); return ErrBadArg; }
    int csqlVal = 0;

    //List for primary key field values present in csql server
    List valListInCsql;
    table->bindFld(fieldName, &csqlVal);
    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if(rv != OK) { 
        dbMgr->closeTable(table); conn.close();
        delete trgtDbStmt; delete trgtDbCon;
        printf("Execute failed\n"); 
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
    table->close();
    conn.commit();
    int trgtDbVal = 0;
    int rows = 0;

    // List for primary key field values present in target DB
    List valListInTrgtDb;
    sprintf(statement, "select %s from %s;", fieldName, tblName);
    rv = trgtDbCon->beginTrans();
    rv = trgtDbStmt->prepare(statement);
    if(rv != OK) { 
        dbMgr->closeTable(table); conn.close();
        delete trgtDbStmt; delete trgtDbCon;
        printf("Prepare failed\n"); 
        return rv; 
    }
    trgtDbStmt->bindField(1, &trgtDbVal);
    rv  = trgtDbStmt->execute(rows);
    if(rv != OK) { 
        dbMgr->closeTable(table); conn.close();
        delete trgtDbStmt; delete trgtDbCon;
        printf("Execute failed\n"); 
        return rv; 
    }
    while (trgtDbStmt->fetch() != NULL) {
        PrimKeyFldVal *pkFldVal = new PrimKeyFldVal(); 
        pkFldVal->val = trgtDbVal; 
        pkFldVal->inCsql = true; 
        pkFldVal->inTrgtDb = true;
        valListInTrgtDb.append(pkFldVal);
    }
    trgtDbCon->commit();
    trgtDbStmt->free();

    // List for primary key field values present in either of the databases
    List diffInValList;

    // List for primary key field values present in both the databases
    List sameInBothDbList;
    ListIterator csqlValIter = valListInCsql.getIterator();
    ListIterator trgtDbValIter = valListInTrgtDb.getIterator();    
    PrimKeyFldVal *csqlelem, *trgtdbelem;
    while( (csqlelem = (PrimKeyFldVal *) csqlValIter.nextElement()) != NULL) {
        while ( (trgtdbelem = (PrimKeyFldVal *) trgtDbValIter.nextElement()) != NULL)   {
            if (csqlelem->val == trgtdbelem->val) { 
                PrimKeyFldVal *elm = new PrimKeyFldVal();
                *elm = *csqlelem;
                sameInBothDbList.append(elm);
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
    
    // Sorting the primary key field values present in either of the databases
    list <PrimKeyFldVal *> li;
    ListIterator diffValIter = diffInValList.getIterator();
    bool missingRecords = false;
    printf("\nMissing Records: Marked by \'X\'\n");
        printf("-------------------+-------------------+-------------------+\n");
        printf("  Primary Key      |  In CSQL          |  In Target DB     |\n");
        printf("-------------------+-------------------+-------------------+\n");  
    if (diffInValList.size()) {
        missingRecords = true;
        PrimKeyFldVal *elem = NULL;
        while ((elem = (PrimKeyFldVal *) diffValIter.nextElement()) != NULL )  
            li.push_back(elem);

        list<PrimKeyFldVal *>::iterator it;
        li.sort(cmp);
        for (it = li.begin(); it != li.end(); it++) {
            if ((*it)->inCsql == false) 
                printf("  %-6d           |  X                |                   |\n", (*it)->val);
            else if ((*it)->inTrgtDb == false)
                printf("  %-6d           |                   |  X                |\n", (*it)->val);
        }
        printf("-------------------+-------------------+-------------------+\n");  
    }
    else {
        printf("  No missing Records in either of the databases            |\n");
        printf("-------------------+-------------------+-------------------+\n");  
    }

    // Need to clean up the mess that is no more required 
    PrimKeyFldVal *pkFldVal = NULL;
    while ((pkFldVal = (PrimKeyFldVal *) csqlValIter.nextElement()) != NULL)
        delete pkFldVal;
    valListInCsql.reset();
    while ((pkFldVal = (PrimKeyFldVal *) trgtDbValIter.nextElement()) != NULL)
        delete pkFldVal;
    valListInTrgtDb.reset();
    while ((pkFldVal = (PrimKeyFldVal *) diffValIter.nextElement()) != NULL)
        delete pkFldVal;
    diffInValList.reset();

 
    if (option == 4) {
        AbsSqlConnection *csqlCon = SqlFactory::createConnection(CSql);
        rv = csqlCon->connect("root", "manager");
        if (rv != OK) { 
            dbMgr->closeTable(table); conn.close();
            delete trgtDbStmt; delete trgtDbCon;
            delete csqlCon; return ErrSysInit; 
        }
        AbsSqlStatement *csqlStmt =  SqlFactory::createStatement(CSql);
        csqlStmt->setConnection(csqlCon);

        //statement to fetch the values from the database
        sprintf(statement, "select * from %s where %s = ?;", tblName, fieldName);
        rv = csqlStmt->prepare(statement);
        if(rv != OK) {
            dbMgr->closeTable(table); conn.close();
            delete trgtDbStmt; delete trgtDbCon;
            delete csqlStmt; delete csqlCon;
            printf("Prepare failed\n");
            return rv;
        }
   
        // need to bind each field with buffer which is list of field values
        List fldNameList = table->getFieldNameList();
        ListIterator iter = fldNameList.getIterator();
        Identifier *fname = NULL;
        FieldInfo *fldInfo = new FieldInfo();
        List fieldValueList;

        // List to hold all the records that are present in both the databases
        List csqlRecordList;
        int paramPos = 1;
        while (iter.hasElement()) {
            fname = (Identifier *) iter.nextElement();
            if (NULL == fname) {
                dbMgr->closeTable(table); conn.close();
                delete trgtDbStmt; delete trgtDbCon;
                delete csqlStmt; delete csqlCon;
                table = NULL;
                delete fldInfo;
                printf("Should never happen. Field Name list has NULL\n");
                return ErrSysFatal;
            }
            rv = table->getFieldInfo(fname->name, fldInfo);
            if (ErrNotFound == rv) {
                dbMgr->closeTable(table); conn.close();
                delete trgtDbStmt; delete trgtDbCon;
                delete csqlStmt; delete csqlCon;
                table = NULL;
                delete fldInfo;
                printf("Field %s does not exist in table\n",
                                                                 fname->name);
                return ErrSyntaxError;
            }
            FldVal *fldVal = new FldVal();
            fldVal->type = fldInfo->type;
            fldVal->length = fldInfo->length;
            fldVal->value = AllDataType::alloc(fldInfo->type, fldInfo->length);
            fieldValueList.append(fldVal);
            csqlStmt->bindField(paramPos++, fldVal->value);
        }
        delete fldInfo;
        
        // WHERE parameter should be binded with the primary key field value of the list that is present in both the databases
        ListIterator sameValIter = sameInBothDbList.getIterator();
        PrimKeyFldVal *sameElem = NULL;
        while((sameElem = (PrimKeyFldVal *)sameValIter.nextElement()) != NULL) {
            csqlCon->beginTrans();
            csqlStmt->setIntParam(1, sameElem->val);
            rv  = csqlStmt->execute(rows);
            if(rv != OK) {
                dbMgr->closeTable(table); conn.close();
                delete trgtDbStmt; delete trgtDbCon;
                delete csqlStmt; delete csqlCon;
                printf("Execute failed\n");
                return rv;
            }
            while (csqlStmt->fetch() != NULL) {
                Record *rec = new Record();
                rec->val = sameElem->val;
                ListIterator fldValIter = fieldValueList.getIterator();
                while (fldValIter.hasElement()) {
                    FldVal *fldVal = (FldVal *) fldValIter.nextElement();
                    FldVal *fldValue = new FldVal();
                    fldValue->type = fldVal->type;
                    fldValue->length = fldVal->length;
                    fldValue->value = AllDataType::alloc(fldValue->type, fldValue->length);
                    AllDataType::copyVal(fldValue->value, fldVal->value, fldVal->type, fldVal->length);
                    rec->fldValList.append(fldValue);
                }
                csqlRecordList.append(rec);
            }    
            csqlStmt->close();
            csqlCon->commit();
        }
        csqlStmt->free();   

        //statement to fetch the values from the database
        sprintf(statement, "select * from %s where %s = ?;", tblName, fieldName);
        rv = trgtDbStmt->prepare(statement);
        if(rv != OK) {
            dbMgr->closeTable(table); conn.close();
            delete csqlStmt; delete csqlCon;
            delete trgtDbStmt; delete trgtDbCon;
            printf("Prepare failed\n");
            return rv;
        }
        
        // need to bind each field with buffer which is list of field values
        ListIterator fldValIter = fieldValueList.getIterator();
        fldValIter.reset();
        List trgtDbRecordList;
        paramPos = 1;
        while (fldValIter.hasElement()) {
            FldVal *fldVal = (FldVal *) fldValIter.nextElement();
            trgtDbStmt->bindField(paramPos++, fldVal->value);
        }
    
        // WHERE parameter should be binded
        sameValIter.reset();
        while((sameElem = (PrimKeyFldVal *)sameValIter.nextElement()) != NULL) {
            trgtDbCon->beginTrans();
            trgtDbStmt->setIntParam(1, sameElem->val);
            rv  = trgtDbStmt->execute(rows);
            if(rv != OK) {
                dbMgr->closeTable(table); conn.close();
                delete csqlStmt; delete csqlCon;
                delete trgtDbStmt; delete trgtDbCon;
                printf("Execute failed\n");
                return rv;
            }
            while (trgtDbStmt->fetch() != NULL) {
                Record *rec = new Record();
                rec->val = sameElem->val;
                fldValIter.reset();
                while (fldValIter.hasElement()) {
                    FldVal *fldVal = (FldVal *) fldValIter.nextElement();
                    FldVal *fldValue = new FldVal();
                    fldValue->type = fldVal->type;
                    fldValue->length = fldVal->length;
                    fldValue->value = AllDataType::alloc(fldValue->type, fldValue->length);
                    AllDataType::copyVal(fldValue->value, fldVal->value, fldVal->type, fldVal->length);
                    rec->fldValList.append(fldValue);
                }
                trgtDbRecordList.append(rec);
            }        
            trgtDbStmt->close();
            trgtDbCon->commit();
        }
        trgtDbStmt->free();

        // freeing the fieldValue buffer list which is not required any more
        FldVal *fldVal = NULL;
        while ((fldVal =(FldVal *) fldValIter.nextElement()) != NULL) {
            free(fldVal->value);
            delete fldVal;
        }
        fieldValueList.reset();
        
        // freeing the field value list that is present in both the databases  
        PrimKeyFldVal *pkFldVal = NULL;
        while ((pkFldVal = (PrimKeyFldVal *) sameValIter.nextElement()) != NULL)
            delete pkFldVal;
        sameInBothDbList.reset();
    
        // sort the records based on Primary key that is present in both the databases
        list <Record *> csqlRecList;
        ListIterator csqlRecListIter = csqlRecordList.getIterator();
        Record *elem;
        while ((elem = (Record *) csqlRecListIter.nextElement()) != NULL )
            csqlRecList.push_back(elem);
        csqlRecList.sort(cmpRec);

        list <Record *> trgtDbRecList;
        ListIterator trgtDbRecListIter = trgtDbRecordList.getIterator();
        while ((elem = (Record *) trgtDbRecListIter.nextElement()) != NULL )
            trgtDbRecList.push_back(elem);
        trgtDbRecList.sort(cmpRec);
    
        int flag = 0;
        bool isConsistent = true;
        list<Record *>::iterator itCsql;
        list<Record *>::iterator itTrgtDb;
        iter.reset();
        printf("\nInconsistent Records for the same key:\n");
        printf("-------------------+-------------------+-------------------+-------------------+\n");
        printf("  %-16s |  %-16s |  %-16s |  %-16s |\n", "Primary Key", "Field Name", "In CSQL", "In Trgt DB");    
        printf("-------------------+-------------------+-------------------+-------------------+\n");
        for (itCsql = csqlRecList.begin(), itTrgtDb = trgtDbRecList.begin(); 
             itCsql != csqlRecList.end() && itTrgtDb != trgtDbRecList.end();
                 itCsql++, itTrgtDb++) {
            ListIterator csqlIt = (ListIterator)((*itCsql)->fldValList).getIterator();    
            ListIterator trgtDbIt = (ListIterator)((*itTrgtDb)->fldValList).getIterator();    
            iter.reset();
            flag = 0;
            while (csqlIt.hasElement() && trgtDbIt.hasElement()) {
                FldVal *csqlElem = (FldVal *) csqlIt.nextElement();
                FldVal *trgtDbElem = (FldVal *) trgtDbIt.nextElement();
                fname = (Identifier *) iter.nextElement();
                if (AllDataType::compareVal(csqlElem->value, trgtDbElem->value, OpEquals, csqlElem->type, csqlElem->length) == false) {
                    isConsistent = false;
                    if (! flag) { 
                        printf("  %-16d |  %-16s |  ", (*itCsql)->val, fname); 
                        flag = 1;
                    }
                    else printf("                   |  %-16s |  ", fname);
                    int cnt =  AllDataType::printVal(csqlElem->value, csqlElem->type, csqlElem->length);
                    cnt = 17 - cnt;
                    while (cnt-- != 0) 
                        printf(" ");
                    printf("|  ");
                    cnt = AllDataType::printVal(trgtDbElem->value, trgtDbElem->type, trgtDbElem->length);
                    cnt = 17 - cnt;
                    while (cnt-- != 0) 
                        printf(" ");
                    printf("|\n");
                }  
            }
        }
        if (isConsistent == true && missingRecords == false) 
            printf("                  The data is consistent in both the databases                 |\n");
        else if (isConsistent == true && missingRecords == true) 
            printf("           The data is consistent for the records with the same key            |\n");
        printf("-------------------+-------------------+-------------------+-------------------+\n");

        // clean up all the mess before leaving
        csqlRecList.clear();
        trgtDbRecList.clear();
       
        iter.reset();
        while ((fname = (Identifier *) iter.nextElement()) != NULL)
            delete fname;
        fldNameList.reset();     

        Record *item = NULL;
        while((item = (Record *) csqlRecListIter.nextElement()) != NULL) {
            ListIterator it = (ListIterator) item->fldValList.getIterator();
            FldVal *fldVal = NULL;
            while((fldVal = (FldVal *) it.nextElement()) != NULL) {
                free (fldVal->value);
                delete fldVal;
            }
            it.reset();
        }
        csqlRecordList.reset();
        
        while((item = (Record *) trgtDbRecListIter.nextElement()) != NULL) {
            ListIterator it = (ListIterator) item->fldValList.getIterator();
            FldVal *fldVal = NULL;
            while((fldVal = (FldVal *) it.nextElement()) != NULL) {
                free (fldVal->value);
                delete fldVal;
            }
            it.reset();
        } 
        trgtDbRecordList.reset();
        delete csqlStmt; delete csqlCon;
    } 

    dbMgr->closeTable(table);
    conn.close();
    delete trgtDbStmt; delete trgtDbCon;
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
    bool tableNameSpecified = false;

    while ((c = getopt(argc, argv, "U:P:t:pf?")) != EOF) 
    {
        switch (c)
        {
            case 'U' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'P' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tableName, argv[optind - 1]); 
                         if (opt==10) opt = 2; 
                         tableNameSpecified = true;
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
    
    if (!tableNameSpecified) {
        printf("Table name is not specified. Check usage with ?\n");
        return 1;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, "root");
        strcpy(password, "manager");
    }
   
    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) {
        printf("Authentication failed\n"); 
        return 1;
    }
 
    DatabaseManager *dbMgr = (DatabaseManager *) conn.getDatabaseManager();
    if (dbMgr == NULL) { 
        conn.close();
        printf("could not connect to the database\n"); 
        return 2; 
    }


    Table *table = dbMgr->openTable(tableName);
    if(table == NULL) {
        conn.close(); 
        printf("Table \'%s\' does not exist\n", tableName); 
        return 3; 
    }

    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        dbMgr->closeTable(table);
        conn.close();
        printf("cachetable.conf file does not exist\n");
        return 4;
    }
    char tablename[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int mode;
    bool filePresent = false;
    while(!feof(fp)) {
        fscanf(fp, "%d:%s %s %s\n", &mode, tablename,condition,field);
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
    
    if (filePresent == false) { printf("The table \'%s\' is not cached\n", tableName);
        return 5;
    }

    if (opt == 2) { 
        rv = verifyCount(tableName, numTuples); 
        if (rv != OK) return 6;
    }
 
    if (opt == 3 || opt == 4) { 
        rv = verifyCount(tableName, numTuples); 
        if (rv != OK) return 7;
        rv = verifyMismatchingRecords(tableName, opt);
        if (rv != OK) return 8;
    }
    return 0;
}
