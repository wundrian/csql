#include<CSql.h>
DbRetVal createIndex(DatabaseManager *dbMgr, char *fldname, char *indname) 
{
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append(fldname);
    idxInfo->indType = hashIndex;
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    DbRetVal rv = dbMgr->createIndex(indname, idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return rv; }
    printf("Index created for %s\n", fldname);
    delete idxInfo;
    return OK;
}
DbRetVal createTable(DatabaseManager *dbMgr)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt, 0, NULL, true);
    tabDef.addField("f3", typeInt);
    tabDef.addField("f4", typeInt);
    tabDef.addField("f5", typeInt);
    DbRetVal rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return rv; }
    printf("Table created\n");
    return OK;
}
int insertTuple(DatabaseManager *dbMgr, Connection &conn)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }
    int id1 = 0;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id1);
    table->bindFld("f3", &id1);
    table->bindFld("f4", &id1);
    table->bindFld("f5", &id1);
    int icount =0;
    DbRetVal rv = OK;
    rv = conn.startTransaction();
    if (rv != OK) { dbMgr->closeTable(table); return 1; }
    for (int i = 0 ; i < 10 ; i++)
    {
        id1= i;
        rv = table->insertTuple();
        if (rv != OK) break;
        icount++;

    }
    conn.commit();
    printf("Total Tuples inserted is %d\n", icount);
    dbMgr->closeTable(table);
    return icount;
}
DbRetVal execAndPrint(Table *table)
{
    table->execute();
    void *tuple;
    while ((tuple = (char*) table->fetch())) {
        char *t = (char*) tuple;
        printf("tuple value is %d %d %d %d %d\n", *(int*)t, *(int*)(t+4), 
                               *(int*)(t+8),*(int*)(t+12),*(int*)(t+16));
    }
    table->closeScan();
    return OK;
}
