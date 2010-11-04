#include<CSql.h>
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt, 0, NULL, true);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    idxInfo->indType = hashIndex;
#ifdef F1TREE
    idxInfo->indType = treeIndex;
#endif
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created for f1\n");
    printf("size of index field list %d\n", idxInfo->list.size());
    idxInfo->list.remove("f1");
    printf("size of index field list %d\n", idxInfo->list.size());
    idxInfo->list.append("f2");
    printf("size of index field list %d\n", idxInfo->list.size());
    idxInfo->indType = hashIndex;
#ifdef F2TREE
    idxInfo->indType = treeIndex;
#endif
    rv = dbMgr->createIndex("indx2", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created for f2\n");
    delete idxInfo;
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id1 = 0, id2=0;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    rv = conn.startTransaction();
    if (rv != OK) exit(1);
    for(i = 0; i< 10; i++)
    {
        id1= i;
        id2= i+100;
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
    }
    conn.commit();
    printf("Total tuples inserted: %d\n", icount);
    Condition p1, p2;
    int val1 = 0;
    p1.setTerm("f1", OpEquals, &val1);
    p2.setTerm("f2", OpEquals, &val1);
    table->setCondition(&p1);
    rv =conn.startTransaction();
    if (rv != OK) exit(1);
    for(i = 0; i< 10; i++)
    {    
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->closeScan();break;}
        printf("I:tuple value is %d %d \n", id1, id2);
        table->closeScan();
    }

    table->setCondition(&p2);
    for(i = 0; i< 10; i++)
    {    
        val1 = i+100;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->closeScan();break;}
        printf("II:tuple value is %d %d \n", id1, id2);
        table->closeScan();
    }
    conn.commit();

    rv = conn.startTransaction();
    if (rv != OK) exit (1);
    table->setCondition(&p1);
    val1 = 1;
    table->execute();
    tuple = (char*)table->fetch() ;
    if (tuple != NULL) {
        table->deleteTuple();
    }
    table->closeScan();
    printf("deleted record\n");


    table->setCondition(&p2);
    val1 = 102;
    table->execute();
    tuple = (char*)table->fetch() ;
    if (tuple != NULL) {
        table->deleteTuple();
    }
    table->closeScan();
    conn.commit();

    dbMgr->closeTable(table);
    table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    int count =0;
    rv = conn.startTransaction();
    table->setCondition(NULL);
    if (rv != OK) exit (1);
    table->execute();
    while((tuple = (char*)table->fetch())!= NULL) {
        printf("tuple value is %d %d \n", id1, id2);
        count++;
    }
    table->closeScan();
    conn.commit();
    printf("Total rows selected %d\n", count);
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
