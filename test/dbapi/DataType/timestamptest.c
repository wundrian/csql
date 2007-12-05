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
    table->close();
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
    tabDef.addField("f1", typeTimeStamp, 0, NULL, true, true );
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
#ifdef WITHINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
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

    Condition p1;
    TimeStamp val1;
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    rv  = conn.startTransaction();
    if (rv != OK) exit (1);
    val1.setDate(1981, 12, 24);
    val1.setTime(12, 30, 30);
    table->execute();
    tuple = (char*)table->fetch() ;
    if (tuple != NULL) {
        strcpy(name, "My value is updated");
        table->updateTuple();
    }
    table->close();

    conn.commit();
    rv = conn.startTransaction();
        if (rv != OK) exit (1);
        val1.setDate(1981, 12, 28);
        val1.setTime(12, 30, 34);

        //val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple != NULL) {
            printf("deleting ");
            AllDataType::printVal(&id, typeTimeStamp,0);
            printf(" %s \n", name);
            table->deleteTuple();
        }
        table->close();
    conn.commit();

    table->setCondition(NULL);
    rv = conn.startTransaction();
    table->execute();
    while ((tuple = (char*) table->fetch())) {
        printf("after delete ");
        AllDataType::printVal(&id, typeTimeStamp,0);
        printf(" %s \n", name);
    }
    table->close();
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
