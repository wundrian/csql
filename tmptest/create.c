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
#include<AggTableImpl.h>
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
    tabDef.addField("f2", typeInt);
    tabDef.addField("f3", typeInt);
    tabDef.addField("f4", typeInt);
    tabDef.addField("f5", typeInt);
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
    int id1 = 0, id2=0, id3=0, id4=0, id5=0;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table->bindFld("f3", &id3);
    table->bindFld("f4", &id4);
    table->bindFld("f5", &id5);
    char *tuple;
    int ret;
    int i;
    int icount =0;
                       
    //insert 10 tuples into the table t1 
    for(i = 0; i< 10; i++)
    {
        conn.startTransaction();
        id1= i;  id2 = i +100; id3 = i+ 1000; id4=i%2; id5=i%3;
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
        conn.commit();
    }
    char msgBuf[1024];
    sprintf(msgBuf,"Total rows inserted %d \n",icount);
    os::write(1,msgBuf,strlen(msgBuf));
    dbMgr->closeTable(table);
    table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }

    //set the condition f1 >=5
    Condition p1;
    int val1 = 2;
    p1.setTerm("f1", OpGreaterThanEquals, &val1);
    table->setCondition(&p1);
    icount=0;
    printf("Selection f1 >= 2 starts on table t1\n");
    AggTableImpl aggTable;
    int group1=0, sum1=0, max1=0, cnt1=0;
    aggTable.setTable(table);
    //aggTable.setGroup("f4", &group1);
    aggTable.bindFld("f1", AGG_AVG, &sum1);
    aggTable.bindFld("f2", AGG_MAX, &max1);
    aggTable.bindFld("f3", AGG_COUNT, &cnt1);

    conn.startTransaction();
    aggTable.execute();
    printf("Tuple values:\n");
    while(true)
    {    
        tuple = (char*)aggTable.fetch() ;
        if (tuple == NULL) { break; }
        printf("grpfld=%d sumfld=%d maxfld=%d cntfld=%d\n", group1, sum1,max1,cnt1);
      //  printf("grpfld=%d sumfld=%d \n", group1, sum1);
        icount++;
    }
    aggTable.closeScan();
    conn.commit();
    aggTable.close();
    
    dbMgr->closeTable(table);
 //   dbMgr->dropTable("t1");
    printf("Table dropped\n");
    conn.close();
    return 0;
}
