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
#include <SqlFactory.h>
#include <SqlStatement.h>
#include <SqlOdbcConnection.h>
#include <SqlOdbcStatement.h>

AbsSqlConnection *conn=NULL;
AbsSqlStatement *stmt=NULL;
DataType pkFldType = typeUnknown;
int pkFldLen = 0;
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
    bool inCsql;
    bool inTrgtDb;
    char val[1];
} PrimKeyFldVal;

typedef struct FldVal {
    void *value;
    DataType type;
    int length;
    int pos;
}FldVal;

typedef struct Rec {
    List csqlFldValList;
    List tdbFldValList;
    char val[1];
}Record;

int cmpIntPkFldVal (const void *pkfv1, const void *pkfv2)
{
    PrimKeyFldVal *p1 = (PrimKeyFldVal *)pkfv1;
    PrimKeyFldVal *p2 = (PrimKeyFldVal *)pkfv2;
    bool result = false;
    result=AllDataType::compareVal(&p1->val,&p2->val,OpLessThan,pkFldType);
    if (result) return -1; 
    else return 1;
}

int cmpStringPkFldVal (const void *pkfv1, const void *pkfv2)
{
    PrimKeyFldVal *p1 = (PrimKeyFldVal *)pkfv1;
    PrimKeyFldVal *p2 = (PrimKeyFldVal *)pkfv2;
    char *val1 = (char *) &p1->val;
    char *val2 = (char *) &p2->val;
    if (strcmp(val1, val2) < 0) return -1;
    else return 1;
}

int cmpIntRecord (const void *pkfv1, const void *pkfv2)
{
    Record *p1 = (Record *)pkfv1;
    Record *p2 = (Record *)pkfv2;
    if (AllDataType::compareVal(&p1->val, &p2->val, OpLessThan, pkFldType))
        return -1;
    else return 1;
}

int cmpStringRecord (const void *pkfv1, const void *pkfv2)
{
    Record *p1 = (Record *)pkfv1;
    Record *p2 = (Record *)pkfv2;
    char *val1 = (char *) &p1->val;
    char *val2 = (char *) &p2->val;
    if (strcmp(val1, val2) < 0) return -1;
    else return 1;
}

DbRetVal verifyCount(const char *tblName, long numTuples)
{
    char statement[200];
    AbsSqlConnection *adConn = SqlFactory::createConnection(CSqlAdapter);
    DbRetVal rv = adConn->connect(I_USER,I_PASS);
    if (rv != OK) { delete adConn; return ErrSysInit; }
    AbsSqlStatement *adStmt = SqlFactory::createStatement(CSqlAdapter);
    adStmt->setConnection(adConn);
    long long count1=0;
    int rows = 0;
    sprintf(statement, "select count(*) from %s;", tblName);
    rv = adConn->beginTrans();
    rv = adStmt->prepare(statement);
    if(rv != OK) {
        delete adStmt; delete adConn;
        printError(rv, "Prepare failed");
        return rv;
    }
    SqlOdbcConnection *adcon= (SqlOdbcConnection *)adConn;
    adStmt->bindField(1, &count1);
    rv  = adStmt->execute(rows);
    if(rv != OK) {
        delete adStmt; delete adConn;
        printError(rv, "Execute failed");
        return rv;
    }
    if (adStmt->fetch()== NULL) {
        delete adStmt; delete adConn;
        printError(ErrSysInternal, "Fetch failed");
        return ErrSysInternal;
    }
    adConn->commit();
    adStmt->free();
    printf("\nNumber of Records:\n");
    printf("-------------------+-------------------+-------------------+\n");
    printf("  Data             |  In CSQL          |  In TargetDB      |\n");
    printf("-------------------+-------------------+-------------------+\n");
    printf("  No. Of Records   |  %-6ld           |  %-6ld          |\n", numTuples, count1);
    printf("-------------------+-------------------+-------------------+\n");
    delete adStmt; delete adConn;
    return OK;
}

DbRetVal verifyMismatchingRecords(const char *tblName, int option)
{
    char csqlstatement[256];
    char tdbstatement[256];
    AbsSqlConnection *trgtDbCon = SqlFactory::createConnection(CSqlAdapter);
    DbRetVal rv = trgtDbCon->connect(I_USER,I_PASS);
    if (rv != OK) {
        delete trgtDbCon; return ErrSysInit;
    }
    AbsSqlStatement *trgtDbStmt =  SqlFactory::createStatement(CSqlAdapter);
    trgtDbStmt->setConnection(trgtDbCon);

    char fieldName[IDENTIFIER_LENGTH];
    fieldName[0] = '\0';
    SqlOdbcStatement *ostmt = (SqlOdbcStatement*) trgtDbStmt;
    ostmt->getPrimaryKeyFieldName((char*)tblName, fieldName);
    if (fieldName[0] == '\0') {
        delete trgtDbStmt; delete trgtDbCon;
        printError(ErrSysInternal, "Primary key does not exist on table %s", tblName);
        return ErrNotExists;
    }
    printf("\nPrimary key field name is \'%s\'\n", fieldName);
    int rows = 0;

    //will work for single field primary keys
    //composite need to be worked out
    FieldInfo *fInfo = new FieldInfo();
    ((SqlStatement *)stmt)->getFieldInfo(tblName, fieldName, fInfo);
    pkFldType = fInfo->type;
    if (pkFldType == typeString) pkFldLen = os::align(fInfo->length + 1);
    else pkFldLen = fInfo->length;
    void *pkval = AllDataType::alloc(pkFldType, pkFldLen);
    memset(pkval, 0, pkFldLen);
    //List for primary key field values present in csql server
    List valListInCsql;
    List valListInTrgtDb;
    List sameInBothDb;
    List missingList;

    sprintf(csqlstatement, "select %s from %s;", fieldName, tblName);
    sprintf(tdbstatement, "select %s from %s where %s=?;", fieldName, tblName, fieldName);
    rv = stmt->prepare(csqlstatement);
    if (rv != OK) {
        delete trgtDbStmt; delete trgtDbCon;
        printError(rv, "Prepare failed");
        return rv;
    }
    rv = trgtDbStmt->prepare(tdbstatement);
    if (rv != OK) {
        delete trgtDbStmt; delete trgtDbCon;
        printError(rv, "Prepare failed");
        return rv;
    }
    stmt->bindField(1, pkval);
    trgtDbStmt->bindField(1, pkval);
    rv = conn->beginTrans();
    if (rv != OK) {
        stmt->free();
        delete trgtDbStmt; delete trgtDbCon;
        printError(rv, "BeginTrans failed");
        return rv;
    }
    rv = stmt->execute(rows);
    if(rv != OK) {
        stmt->free();
        delete trgtDbStmt; delete trgtDbCon;
        printError(ErrSysInternal, "Execute failed");
        return rv;
    }
    rv = trgtDbCon->beginTrans();
    int pkFldValSize = sizeof(PrimKeyFldVal) - 1 + pkFldLen;
    while(stmt->fetch(rv) != NULL && rv == OK) {
        PrimKeyFldVal *pkFldVal = (PrimKeyFldVal *) malloc (pkFldValSize);
        memset(pkFldVal, 0, pkFldValSize);
        AllDataType::copyVal(&pkFldVal->val, pkval, pkFldType, pkFldLen);
        pkFldVal->inCsql = true;
        pkFldVal->inTrgtDb = true;
        SqlStatement::setParamValues(trgtDbStmt,1, pkFldType,pkFldLen,pkval);
        trgtDbStmt->execute(rows);
        if (trgtDbStmt->fetch(rv) != NULL) {
            sameInBothDb.append(pkFldVal);  
        } else {
            pkFldVal->inTrgtDb = false; 
            missingList.append(pkFldVal);
        }
        trgtDbStmt->close();
    }
    trgtDbCon->commit();
    stmt->close();
    conn->commit();
    stmt->free();
    trgtDbStmt->free();
     
    // List for primary key field values present in target DB
    sprintf(tdbstatement, "select %s from %s;", fieldName, tblName);
    sprintf(csqlstatement, "select %s from %s where %s=?;", fieldName, tblName, fieldName);
    rv = trgtDbCon->beginTrans();
    rv = trgtDbStmt->prepare(tdbstatement);
    if(rv != OK) {
        delete trgtDbStmt; delete trgtDbCon;
        printError(rv, "Prepare failed");
        return rv;
    }
    stmt->prepare(csqlstatement);
    stmt->bindField(1, pkval);
    trgtDbStmt->bindField(1, pkval);
    rv  = trgtDbStmt->execute(rows);
    if(rv != OK) {
        delete trgtDbStmt; delete trgtDbCon;
        printError(rv, "Execute failed\n");
        return rv;
    }
    conn->beginTrans();
    while (trgtDbStmt->fetch() != NULL) {
        PrimKeyFldVal *pkFldVal = (PrimKeyFldVal *) malloc (pkFldValSize);
        memset(pkFldVal, 0, pkFldValSize);
        AllDataType::copyVal(&pkFldVal->val, pkval, pkFldType, pkFldLen);
        pkFldVal->inCsql = true;
        pkFldVal->inTrgtDb = true;
        SqlStatement::setParamValues(stmt, 1, pkFldType, pkFldLen, pkval);
        stmt->execute(rows);
        if (stmt->fetch(rv) == NULL && rv ==OK) {
            pkFldVal->inCsql = false;
            missingList.append(pkFldVal);
        }
    }
    stmt->close();
    trgtDbStmt->close();
    conn->commit();
    trgtDbCon->commit();
    stmt->free();
    trgtDbStmt->free();
/*    
    PrimKeyFldVal *pkArr = NULL;
    ListIterator missIter = missingList.getIterator();
    int nEitherDb = missingList.size();
    if (nEitherDb) {
        pkArr = (PrimKeyFldVal *) malloc(nEitherDb * pkFldValSize);
        int i = 0;
        char *ptr = (char *)pkArr;
        while (missIter.hasElement()) {
            PrimKeyFldVal *elm = (PrimKeyFldVal *)missIter.nextElement();
            memcpy(ptr, elm, pkFldValSize);
            ptr += pkFldValSize; 
        }
        if (pkFldType == typeByteInt || pkFldType == typeShort ||
                       pkFldType == typeInt || pkFldType == typeLong || 
                                                     pkFldType == typeLongLong) 
            qsort (pkArr, nEitherDb, pkFldValSize, cmpIntPkFldVal);
        else if (pkFldType == typeString) 
            qsort (pkArr, nEitherDb, pkFldValSize, cmpStringPkFldVal);
    }
*/
    // Sorting the primary key field values present in either of the databases
    bool missingRecords = false;
    printf("\nMissing Records: Marked by \'X\'\n");
        printf("-------------------+-------------------+-------------------+\n");
        printf("  Primary Key      |  In CSQL          |  In Target DB     |\n");
        printf("-------------------+-------------------+-------------------+\n");
/*    if (missingList.size()) {
        char *ptr = (char *) pkArr;
        missingRecords = true;
        for (int i = 0; i < nEitherDb; i++) {
            PrimKeyFldVal *pkFldVal = (PrimKeyFldVal *) ptr;
            printf("  ");
            int nChrs = AllDataType::printVal(&pkFldVal->val, pkFldType, 
                                                                     pkFldLen);
            nChrs = 17 - nChrs;
            while (nChrs-- != 0) printf(" ");
            if (pkFldVal->inCsql == false) { 
                printf("|  X                |                   |\n");
            }
            else if (pkFldVal->inTrgtDb == false) {
                printf("|                   |  X                |\n");
            }
            ptr += pkFldValSize;
        }
        printf("-------------------+-------------------+-------------------+\n");
    }
    else {
        printf("  No missing Records in either of the databases            |\n");
        printf("-------------------+-------------------+-------------------+\n");
    }
*/
    






    ListIterator missIter = missingList.getIterator();
    if (missingList.size()) {
        missingRecords = true;
        while (missIter.hasElement()) {
            PrimKeyFldVal *pkFldVal = (PrimKeyFldVal *) missIter.nextElement();
            printf("  ");
            int nChrs = AllDataType::printVal(&pkFldVal->val, pkFldType, 
                                                                     pkFldLen);
            nChrs = 17 - nChrs;
            while (nChrs-- != 0) printf(" ");
            if (pkFldVal->inCsql == false) { 
                printf("|  X                |                   |\n");
            }
            else if (pkFldVal->inTrgtDb == false) {
                printf("|                   |  X                |\n");
            }
        }
        printf("-------------------+-------------------+-------------------+\n");
    }
    else {
        printf("  No missing Records in either of the databases            |\n");
        printf("-------------------+-------------------+-------------------+\n");
    }

    // Need to clean up the mess that is no more required 
    //free (pkArr);
    missIter.reset();
    PrimKeyFldVal *pkFldVal = NULL;
    while ((pkFldVal = (PrimKeyFldVal *) missIter.nextElement()) != NULL)
        free (pkFldVal);
    missingList.reset();
    
    if (option == 4) {
        //statement to fetch the values from the database
        sprintf(csqlstatement, "select * from %s where %s = ?;", tblName, fieldName);
        rv = stmt->prepare(csqlstatement);
        rv = trgtDbStmt->prepare(csqlstatement);
        if(rv != OK) {
            delete trgtDbStmt; delete trgtDbCon;
            printError(rv, "Prepare failed");
            return rv;
        }

        // need to bind each field with buffer which is list of field values
        SqlStatement *sqlStmt = (SqlStatement *) stmt;
        List fldNameList = sqlStmt->getFieldNameList(tblName);
        ListIterator iter = fldNameList.getIterator();
        Identifier *fname = NULL;
        FieldInfo *fldInfo = new FieldInfo();
        List cfieldValueList;
        List tfieldValueList;

        // List to hold all the records that are present in both the databases
        List recordList;
        int paramPos = 1;
        while (iter.hasElement()) {
            fname = (Identifier *) iter.nextElement();
            if (NULL == fname) {
                delete trgtDbStmt; delete trgtDbCon;
                delete fldInfo;
                printError(ErrSysFatal, "Fatal:Field Name list has NULL");
                return ErrSysFatal;
            }
            rv = sqlStmt->getFieldInfo(tblName, fname->name, fldInfo);
            if (ErrNotFound == rv) {
                delete trgtDbStmt; delete trgtDbCon;
                delete fldInfo;
                printError(ErrSysInternal, "Field %s does not exist in table", fname->name);
                return ErrSyntaxError;
            }
            FldVal *cfldVal = new FldVal();
            FldVal *tfldVal = new FldVal();
            cfldVal->type = fldInfo->type;
            tfldVal->type = fldInfo->type;
            if(cfldVal->type == typeString) 
                cfldVal->length = os::align(fldInfo->length + 1);
            else cfldVal->length = fldInfo->length;
            cfldVal->value = AllDataType::alloc(fldInfo->type, cfldVal->length);
            tfldVal->value = AllDataType::alloc(fldInfo->type, cfldVal->length);
            memset(cfldVal->value, 0, cfldVal->length);
            memset(tfldVal->value, 0, cfldVal->length);
            cfieldValueList.append(cfldVal);
            tfieldValueList.append(tfldVal);
            stmt->bindField(paramPos, cfldVal->value);
            trgtDbStmt->bindField(paramPos, tfldVal->value);
            paramPos++;
        }
        delete fldInfo;
        iter.reset();
        while ((fname=(Identifier *)iter.nextElement())!= NULL) delete fname;
        fldNameList.reset();

        // WHERE parameter should be binded with the primary key field value of the list that is present in both the databases
        int recSize = 2 * sizeof(List) + pkFldLen; 
        ListIterator sameValIter = sameInBothDb.getIterator();
        PrimKeyFldVal *sameElem = NULL;
        while((sameElem = (PrimKeyFldVal *)sameValIter.nextElement()) != NULL) {
            conn->beginTrans();
            trgtDbCon->beginTrans();
            SqlStatement::setParamValues(stmt, 1, pkFldType, pkFldLen, 
                                                                sameElem->val);
            SqlStatement::setParamValues(trgtDbStmt, 1, pkFldType, pkFldLen, 
                                                                sameElem->val);
            rv  = stmt->execute(rows);
            rv  = trgtDbStmt->execute(rows);
            if(rv != OK) {
                delete trgtDbStmt; delete trgtDbCon;
                printError(rv, "Execute failed");
                return rv;
            }
            if (stmt->fetch() != NULL && trgtDbStmt->fetch() != NULL) {
                Record *rec = (Record *) malloc(recSize);
                memset(rec, 0, recSize);
                AllDataType::copyVal(&rec->val, &sameElem->val, 
                                                          pkFldType, pkFldLen);
                ListIterator cfldValIter = cfieldValueList.getIterator();
                ListIterator tfldValIter = tfieldValueList.getIterator();
                int pos = 1;
                while (cfldValIter.hasElement() && tfldValIter.hasElement()) {
                    FldVal *cfldVal = (FldVal *) cfldValIter.nextElement();
                    FldVal *tfldVal = (FldVal *) tfldValIter.nextElement();
                    if (AllDataType::compareVal(cfldVal->value, tfldVal->value, OpEquals, cfldVal->type, cfldVal->length) == false) {
                        FldVal *cfldValue = new FldVal();
                        FldVal *tfldValue = new FldVal();
                        cfldValue->type = cfldVal->type;
                        tfldValue->type = cfldVal->type;
                        cfldValue->length = cfldVal->length;
                        tfldValue->length = cfldVal->length;
                        cfldValue->value = AllDataType::alloc(cfldValue->type, cfldValue->length);
                        tfldValue->value = AllDataType::alloc(cfldValue->type, cfldValue->length);
                        cfldValue->pos = pos; tfldValue->pos = pos;
                        memset(cfldValue->value, 0, cfldValue->length);
                        memset(tfldValue->value, 0, cfldValue->length);
                        AllDataType::cachecopyVal(cfldValue->value, cfldVal->value, cfldVal->type, cfldVal->length);
                        AllDataType::cachecopyVal(tfldValue->value, tfldVal->value, cfldVal->type, cfldVal->length);
                        rec->csqlFldValList.append(cfldValue);
                        rec->tdbFldValList.append(tfldValue);
                    }
                    pos++;
                }
                if (rec->csqlFldValList.size()) recordList.append(rec);
            }
            stmt->close();
            trgtDbStmt->close();
            conn->commit();
            trgtDbCon->commit();
        }
        // stmt->free(); // dont free it just yet needed further up
        trgtDbStmt->free();
       
        // freeing the field value list that is present in both the databases  
        PrimKeyFldVal *pkFldVal = NULL;
        while ((pkFldVal = (PrimKeyFldVal *) sameValIter.nextElement()) != NULL)
            delete pkFldVal;
        sameInBothDb.reset();
/*        
        // sort the records based on Primary key that is present in both the databases
        int size = recordList.size();
        char *arr = (char *) malloc(size * recSize);
        memset(arr, 0, size * recSize);
        char *ptr = arr;
        int i = 0;
        ListIterator recIter = recordList.getIterator();
        while (recIter.hasElement()) {
            Record *rec = (Record *) recIter.nextElement();
            memcpy(ptr, rec, recSize);
            ptr += recSize;
        }
        if (pkFldType == typeByteInt || pkFldType == typeShort ||
                        pkFldType == typeInt || pkFldType == typeLong ||
                                                     pkFldType == typeLongLong)
            qsort(arr, size, recSize, cmpIntRecord);
        else if (pkFldType == typeString) 
            qsort(arr, size, recSize, cmpStringRecord);
*/

        int flag = 0;
        bool isConsistent = true;
        printf("\nInconsistent Records for the same key:\n");
        printf("-------------------+-------------------+-------------------+-------------------+\n");
        printf("  %-16s |  %-16s |  %-16s |  %-16s |\n", "Primary Key", "Field Name", "In CSQL", "In Trgt DB");
        printf("-------------------+-------------------+-------------------+-------------------+\n");
/*        ptr = arr;
        char *fldname = NULL;
        for (int i = 0; i < size; i++) {
            Record *recd = (Record *) ptr;
            ListIterator csqlIt = recd->csqlFldValList.getIterator();
            ListIterator trgtDbIt = recd->tdbFldValList.getIterator();
            flag = 0;
            while (csqlIt.hasElement() && trgtDbIt.hasElement()) {
                FldVal *csqlElem = (FldVal *) csqlIt.nextElement();
                FldVal *trgtDbElem = (FldVal *) trgtDbIt.nextElement();
                fldname = ((SqlStatement *) stmt)->getFieldName(csqlElem->pos);
                if (AllDataType::compareVal(csqlElem->value, trgtDbElem->value, OpEquals, csqlElem->type, csqlElem->length) == false) {
                    isConsistent = false;
                    if (! flag) {
                        printf("  ");
                        int cnt = AllDataType::printVal(&recd->val, 
                                                          pkFldType, pkFldLen);
                        cnt = 17 - cnt;
                        while (cnt-- != 0) printf(" ");
                        printf("|  %-16s |  ", fldname);
                        flag = 1;
                    }
                    else printf("                   |  %-16s |  ", fldname);
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
            ptr += recSize;
        }
*/
        ListIterator recIter = recordList.getIterator();
       
        char *fldname = NULL;
        if (recordList.size()) {
            isConsistent = false;
            while(recIter.hasElement()) {
                Record *recd = (Record *) recIter.nextElement();
                ListIterator csqlIt = recd->csqlFldValList.getIterator();
                ListIterator trgtDbIt = recd->tdbFldValList.getIterator();
                flag = 0;
                while (csqlIt.hasElement()) {
                    FldVal *csqlElem = (FldVal *) csqlIt.nextElement();
                    FldVal *trgtDbElem = (FldVal *) trgtDbIt.nextElement();
                    fldname = ((SqlStatement *) stmt)->getFieldName(csqlElem->pos);
                    if (! flag) {
                        printf("  ");
                        int cnt = AllDataType::printVal(&recd->val, 
                                                          pkFldType, pkFldLen);
                        cnt = 17 - cnt;
                        while (cnt-- != 0) printf(" ");
                        printf("|  %-16s |  ", fldname);
                        flag = 1;
                    }
                    else printf("                   |  %-16s |  ", fldname);
                    int cnt =  AllDataType::printVal(csqlElem->value, csqlElem->type, csqlElem->length);
                    cnt = 17 - cnt;
                    while (cnt-- != 0) printf(" ");
                    printf("|  ");
                    cnt = AllDataType::printVal(trgtDbElem->value, trgtDbElem->type, trgtDbElem->length);
                    cnt = 17 - cnt;
                    while (cnt-- != 0) printf(" ");
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
        stmt->free();
        //free(arr);
        Record *itm = NULL;
        while((itm = (Record *) recIter.nextElement()) != NULL) {
            ListIterator cit = (ListIterator) itm->csqlFldValList.getIterator();
            ListIterator tit = (ListIterator) itm->tdbFldValList.getIterator();
            FldVal *cfldVal = NULL; FldVal *tfldVal = NULL;
            while( (cfldVal = (FldVal *) cit.nextElement()) != NULL && 
                   (tfldVal = (FldVal *) tit.nextElement()) != NULL ) {
                free (cfldVal->value); free (tfldVal->value);
                delete cfldVal; delete tfldVal;
            }
            cit.reset(); tit.reset();
        }
        recordList.reset();
    }
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
        printError(ErrSysInternal, "Table name is not specified. Check usage with ?");
        return 1;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, I_USER);
        strcpy(password, I_PASS);
    }
   
    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(username, password);
    if (rv != OK) {
        printError(rv, "Authentication failed"); 
        delete conn;
        return 1;
    }
    stmt = SqlFactory::createStatement(CSqlDirect);
    stmt->setConnection(conn);
    bool found = false;
    List tableNameList = stmt->getAllTableNames(rv);
    ListIterator it = tableNameList.getIterator();
    while (it.hasElement()) {
        Identifier *elem = (Identifier *) it.nextElement();
        if (strcmp(elem->name, tableName) == 0) {
            found = true;
            break;
        }
    }
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        conn->disconnect();
        delete stmt; delete conn;
        printError(ErrSysInternal, "csqltable.conf file does not exist");
        return 2;
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];

    int mode;
    bool isCached = false;
    while(!feof(fp)) {
        fscanf(fp, "%d %s %s %s %s %s\n", &mode, tablename,fieldname,condition,field,dsnName);
        if (strcmp(tableName, tablename) == 0) {
            isCached = true;
            break;
        }
    }
    fclose(fp);
    long numTuples = 0;
    int rows;
    
    char statement[200];
    sprintf(statement, "select count(*) from %s;", tableName);
    rv = stmt->prepare(statement);
    if (rv != OK) {
        conn->disconnect();
        delete stmt; delete conn;
        return 3;
    }
    rv = conn->beginTrans();
    if (rv != OK) {
        conn->disconnect();
        delete stmt; delete conn;
        return 4;
    }
    stmt->bindField(1, &numTuples);
    stmt->execute(rows);
    if (rv != OK) {
        conn->disconnect();
        delete stmt; delete conn;
        return 5;
    }
    void *tuple = stmt->fetch(rv);
    stmt->close();
    conn->commit();
    stmt->free();
    
    if (isCached == false) { 
        conn->disconnect();
        printError(ErrSysInternal, "The table \'%s\' is not cached", tableName);
        delete stmt; delete conn; return 5;
    }

    if (opt == 2) { 
        rv = verifyCount(tableName, numTuples); 
        if (rv != OK) { 
            conn->disconnect(); delete stmt; delete conn; return 7; 
        }
    }
 
    if (opt == 3 || opt == 4) { 
        rv = verifyCount(tableName, numTuples); 
        if (rv != OK) { 
            conn->disconnect(); delete stmt; delete conn; return 8; 
        }
        rv = verifyMismatchingRecords(tableName, opt);
        if (rv != OK) { 
            conn->disconnect(); delete stmt; delete conn; return 9; 
        }
    }
    conn->disconnect(); delete stmt; delete conn;
    return 0;
}
