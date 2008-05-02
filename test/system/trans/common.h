#include<CSql.h>
DbRetVal createIndex(DatabaseManager *dbMgr, char *tblname, char *fldname, char *indname) 
{
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, tblname);
    idxInfo->list.append(fldname);
    idxInfo->indType = hashIndex;
    idxInfo->isPrimary = true;
    idxInfo->isUnique = true;
    DbRetVal rv = dbMgr->createIndex(indname, idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return rv; }
    printf("Index created for %s\n", fldname);
    delete idxInfo;
    return OK;
}
DbRetVal createTable(DatabaseManager *dbMgr, char *tblname)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    DbRetVal rv = dbMgr->createTable(tblname, tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return rv; }
    printf("Table created\n");
    return OK;
}
DbRetVal dropTable(DatabaseManager *dbMgr, char *tblname)
{
    DbRetVal rv = dbMgr->dropTable(tblname);
    if (rv != OK) { printf("Table drop failed\n"); return rv; }
    printf("Table Dropped\n");
    return OK;
}
int insertTuple(DatabaseManager *dbMgr, Connection &conn, char *tblname, int count)
{
    Table *table = dbMgr->openTable(tblname);
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 1;
    }
    int id1 = 0;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id1);
    int icount =0;
    DbRetVal rv = OK;
    for (int i = 0 ; i < count ; i++)
    {
        id1= i;
        rv = table->insertTuple();
        if (rv != OK) break;
        icount++;

    }
    printf("Total Tuples inserted is %d\n", icount);
    dbMgr->closeTable(table);
    return icount;
}

int selectTuple(DatabaseManager *dbMgr, Connection &conn, char *tblname, int count)
{
    Table *table = dbMgr->openTable(tblname);
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 1;
    }
    DbRetVal rv = OK;

    Condition p1;
    int val1 = 0; 
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    int i =0;
    void *tuple;
    for (i = 0 ; i < count ; i++)
    {
        val1 = i;
        table->execute();
        if (rv != OK) break;
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) break;
        table->close();
    }
    printf("Total Tuples selected is %d\n", i);
    dbMgr->closeTable(table);
    return i;
}
int updateTuple(DatabaseManager *dbMgr, Connection &conn, char *tblname, int count)
{
    Table *table = dbMgr->openTable(tblname);
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 1;
    }
    DbRetVal rv = OK;

    int id1 = 0, id2 =0;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    Condition p1;
    int val1 = 0; 
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    int i =0;
    void *tuple;
    for (i = 0 ; i < count ; i++)
    {
        val1 = i;
        table->execute();
        if (rv != OK) break;
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) break;
        id2 = 1000 + i;
        rv = table->updateTuple();
        if (rv != OK) break;
        table->close();
    }
    printf("Total Tuples updated is %d\n", i);
    dbMgr->closeTable(table);
    return i;
}
int deleteTuple(DatabaseManager *dbMgr, Connection &conn, char *tblname, int count)
{
    Table *table = dbMgr->openTable(tblname);
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 1;
    }
    DbRetVal rv = OK;

    Condition p1;
    int val1 = 0; 
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    int i =0;
    void *tuple;
    for (i = 0 ; i < count ; i++)
    {
        val1 = i;
        table->execute();
        if (rv != OK) break;
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) break;
        rv = table->deleteTuple();
        if (rv != OK) break;
        table->close();
    }
    printf("Total Tuples deleted is %d\n", i);
    dbMgr->closeTable(table);
    return i;
}
