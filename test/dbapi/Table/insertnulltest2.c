#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeInt, 0, NULL, false, true); //NOT NULL
    tabDef.addField("f3", typeString, 20);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return 3; }
    printf("Table created\n");

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
    int icount =0;
    for (int i = 0 ; i < 5 ; i++)
    {
        conn.startTransaction();
        id1= i;
        if (i%2 == 0) table->markFldNull(2);
        if (i%2 == 0) table->markFldNull(3);
        rv = table->insertTuple();
        if (rv != OK) break;
        if (i%2 == 0) table->clearFldNull(2);
        if (i%2 == 0) table->clearFldNull(3);
        icount++;
        conn.commit();

    }
    printf("Tuples inserted in 1/txn is %d\n", icount);
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
    }
    table->bindFld("f2", &id2);
    void *tuple = NULL; 
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        if (table->isFldNull(1)) printf("Column 1 is null\n");
        if (table->isFldNull(2)) printf("Column 2 is null\n");
        if (table->isFldNull(3)) printf("Column 3 is null\n");
        printf("Binded Tuple value is %d %d %s \n", id1, id2, name);

    }
    table->close();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
