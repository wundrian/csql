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
    char *tuple;
    int ret;
    int i;
    int icount =0;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }

    //get dbmgr to create table and index
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
/*
    //create table with two fields, f1 integer and f2 string
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    rv = dbMgr->createTable("t2", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
*/
    //open the table handle for doing DML operations
    Table *table = dbMgr->openTable("t1");
    Table *table1 = dbMgr->openTable("t2");
/*
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id1 = 0, id2=0;
    table->bindFld("f1", &id1);
    table1->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table1->bindFld("f2", &id2);
                       
    //insert 10 tuples into the table t1 
    for(i = 0; i< 5; i++)
    {
        conn.startTransaction();
        id1= i;  id2 = i %3; 
        ret = table->insertTuple();
        if (ret != 0) break;
        ret = table1->insertTuple();
        if (ret != 0) break;
        icount++;
        conn.commit();
    }
    char msgBuf[1024];
    sprintf(msgBuf,"Total rows inserted %d \n",icount);
    os::write(1,msgBuf,strlen(msgBuf));
    dbMgr->closeTable(table);
    dbMgr->closeTable(table1);

    table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    table1 = dbMgr->openTable("t2");
    if (table1 == NULL) { printf("Unable to open table\n"); return -1; }
*/

    JoinTableImpl joinTable;
    joinTable.setTable(table, table1);
    int out1, out2, out3;
    joinTable.bindFld("t1.f1", &out1);
    joinTable.bindFld("t1.f2", &out2);
    joinTable.bindFld("t2.f1", &out3);

    //joinTable.setJoinCondition("t1.f1", OpEquals, "t2.f1");

    conn.startTransaction();
    joinTable.execute();
    printf("Tuple values:\n");
    int cnt=0;
    while(true)
    {    
        tuple = (char*)joinTable.fetch() ;
        if (tuple == NULL) { break; }
        printf("Tuple %d: %d %d %d\n", cnt++, out1, out2, out3);
        icount++;
    }
    joinTable.closeScan();
    conn.commit();
    joinTable.close();
    
    dbMgr->closeTable(table);
    dbMgr->closeTable(table1);
 //   dbMgr->dropTable("t1");
    printf("Table dropped\n");
    conn.close();
    return 0;
}
