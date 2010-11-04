#include<CSql.h>

TimeStamp id;
char name[196] = "PRABAKARAN";
int select(Table *table, ComparisionOp op)
{
    printf("Operator test for %d\n", op);
    Condition p1;
    TimeStamp val1(1981, 12, 24, 12, 30, 30);
    p1.setTerm("f1", op, &val1);
    table->setCondition(&p1);
    table->execute();
    void *tuple;
    while ((tuple = (char*) table->fetch())) {
        printf("tuple value is ");
        AllDataType::printVal(&id, typeTimeStamp,0);
        printf(" %s \n", name);
    }
    table->closeScan();
    return 0;
}

int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return 1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    TableDef tabDef;
    tabDef.addField("f1", typeTimeStamp, 0, NULL, true);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
#ifdef WITHINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv == OK) { printf("Index creation passed\n"); return 1; }
    delete idxInfo;
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
#endif
#ifdef WITHTREEINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    delete idxInfo;
#endif

    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return 4; }
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    rv =conn.startTransaction();
    if (rv != OK) exit(5);
    for(i = 1; i< 10; i++) {
        id.setDate(1981, 12, 21+i );
        id.setTime(12, 30, 27 +i);
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        if (ret != 0) break;
        printf("Inserted ");
        AllDataType::printVal(&id, typeTimeStamp,0);
        printf(" %s \n", name);
    }
    conn.commit();

    conn.startTransaction();
    select(table, OpEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpNotEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpLessThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpLessThanEquals);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThanEquals);
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
