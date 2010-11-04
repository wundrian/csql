// Test Case: DB Full test with table and two index(hash and tree)
// Create table 
// Insert 4000 records
// Note:Each page can hold 4 records.
// For 100 iterations, delete and insert 4000 records 
// Result:In all 100 iterations operations should succeed

#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt, 0, NULL, true);
    tabDef.addField("f3", typeString, 2000);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return 3; }
    printf("Table created\n");

    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    idxInfo->list.remove("f1");
    idxInfo->list.append("f2");
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx2", idxInfo);
    delete idxInfo;

    Table *table = dbMgr->openTable("t1");
    if (table == NULL) 
    { 
        printf("Unable to open table\n"); 
        dbMgr->dropTable("t1");
        conn.close();
        return -1; 
    }
    int id1 = 0, id2 = 5;
    char name[20] = "PRAVEEN";
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table->bindFld("f3", name);
    int i=0;
    for (i = 0 ; i < 4000 ; i++)
    {
        conn.startTransaction();
        id1= i;
        id2= i;
        rv = table->insertTuple();
        if (rv != OK) break;
        conn.commit();
    }
    printf("%d records inserted\n", i);
    //sleep(10);
    for (int k=0; k <100; k++) {
      table->setCondition(NULL);
      rv = table->execute();
      if (rv != OK) {
        printf("table execute failed rv:%d\n", rv);
        dbMgr->closeTable(table);
        conn.close();
        return 1;
      }
      void *tuple = NULL;
      conn.startTransaction();
      for (i = 0 ; i < 4000 ; i++)
      {
        tuple = table->fetchNoBind();
        if (tuple == NULL) { printf("No more records\n"); break; }
        rv = table->deleteTuple();
        if (rv != OK) { printf("Delete tuple failed\n"); break;}
        if (i%50 == 0) { conn.commit(); conn.startTransaction(); }
      }
      conn.commit();
      table->closeScan();
      printf("Iteration:%d \n %d records deleted\n", k, i);
      i=0;
      conn.startTransaction();
      for (i = 0 ; i < 4000 ; i++)
      {
        id1= i;
        id2= i;
        rv = table->insertTuple();
        if (rv != OK) break;
        if (i%50 == 0) { conn.commit(); conn.startTransaction(); }
      }
      conn.commit();
      printf("%d records inserted\n", i);
    }

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
