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
  **************************************************************************/
#include<CSql.h>
int main()
{
    //connect to the database first
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }

    //get dbmgr to create table and index
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}

    //create table with two fields, f1 integer and f2 string
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeString, 20);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");

    //Creating hash index on field f1 of table t1
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");

    //open the table handle for doing DML operations
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id = 0;
    char name[20] = "THIRU";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    char names[10][20]={"Ganga", "Gopal", "Chaitra", "Aruna", "Vinayak", "Shekar",
                        "Pramod", "Rakesh", "Murthy", "Amit" };
                       
    //insert 10 tuples into the table t1 
    for(i = 0; i< 10; i++)
    {
        conn.startTransaction();
        id= i;
        strcpy(name, names[i]);
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
        conn.commit();
    }
    char msgBuf[1024];
    sprintf(msgBuf,"Total rows inserted %d \n",icount);
    os::write(1,msgBuf,strlen(msgBuf));

    //set the condition f1 >=5
    Condition p1;
    int val1 = 5;
    p1.setTerm("f1", OpGreaterThanEquals, &val1);
    table->setCondition(&p1);
    icount=0;
    printf("Selection f1 >= 5 starts on table t1\n");
    conn.startTransaction();
    table->execute();
    printf("Tuple values:\n");
    while(true)
    {    
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) { break; }
        printf("    f1=%d f2=%s\n", id, name);
        icount++;
    }
    table->closeScan();
    conn.commit();
    sprintf(msgBuf,"Total Rows selected: %d \n", icount);
    os::write(1,msgBuf,strlen(msgBuf));

    //unset the condtion set as we need to delete all rows
    table->setCondition(NULL);
    conn.startTransaction();
    table->execute();
    icount = 0;
    while(true)
    {
        tuple = (char*)table->fetch();
        if (tuple == NULL)  { break;}
        table->deleteTuple();
        icount++;
    }
    conn.commit();
    table->closeScan();
    printf("Total Deleted Rows %d\n", icount);

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    printf("Table dropped\n");
    conn.close();
    return 0;
}
