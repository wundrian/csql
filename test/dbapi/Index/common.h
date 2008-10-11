#include<CSql.h>
int createIndex(DatabaseManager *dbMgr, bool unique)
{
    //Creating hash index on field f1 of table t1
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
#ifndef DEFAULT
    idxInfo->isUnique = unique;
#endif
    DbRetVal rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return 1; }
    printf("Index created\n");
    delete idxInfo;
    return 0;
}
int createTable(DatabaseManager *dbMgr)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    tabDef.addField("f3", typeString, 20);
    DbRetVal rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 1; }
    printf("Table created\n");
    return 0;
}
int insertTupleWithSameValue(DatabaseManager *dbMgr, Connection &conn)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }
    int id1 = 0, id2 = 5;
    char name[20] = "PRAVEEN";
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table->bindFld("f3", name);
    int icount =0;
    DbRetVal rv = OK;
    for (int i = 0 ; i < 10 ; i++)
    {
        conn.startTransaction();
        id1= 10;
        rv = table->insertTuple();
        if (rv != OK) break;
        icount++;
        conn.commit();

    }
    printf("Total Tuples inserted is %d\n", icount);
    dbMgr->closeTable(table);
    return icount;
}


int insertTuplef2NUL(DatabaseManager *dbMgr, Connection &conn)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }
    int id1 = 0, id2;
    int count=0;
    table->bindFld("f1", &id1);
    //table->bindFld("f2", &id2);
    DbRetVal rv = OK;
    for( int i=10;i<=20;i=i+10)
    {
        conn.startTransaction();
        id1= i;
        rv = table->insertTuple();
        if (rv != OK) { printf("Insertion failed "); break; }
        count++;
        conn.commit();
    }
    printf("Tuple inserted is %d \n",count);
    dbMgr->closeTable(table);
    return 0;
}

int creatTable(DatabaseManager *dbMgr)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    DbRetVal rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 1; }
    printf("Table created\n");
    return 0;
}
int createIndex(DatabaseManager *dbMgr)
{
    //Creating hash index on field f1 of table t1  
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;

    DbRetVal rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return 1; }
    printf("Index created for t1(f1)\n");

    //Creating hash index on field f2 of table t1 
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.remove("f1");
    idxInfo->list.append("f2");
    idxInfo->indType = hashIndex;

    rv = dbMgr->createIndex("indx2", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return 1; }
    printf("Index created for t1(f2)\n");

    delete idxInfo;
    return 0;
}
             
