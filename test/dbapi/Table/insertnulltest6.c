#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);//NOT NULL
    tabDef.addField("f2", typeInt, 0, NULL, false);
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
    int id1=0, id2 = 5;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    conn.startTransaction();
  	rv = table->markFldNull(1);
    if (rv != OK) {
        printf("test passed\n");
        dbMgr->dropTable("t1");
        printf("table dropped\n");
        conn.close();
        return 0;
    }
    rv = table->insertTuple();
	if(rv==OK)
	{
    	    printf("Error\n");
       	    dbMgr->dropTable("t1");
	    conn.close();
            return -1;
	}
        table->clearFldNull(1);
        conn.commit();
   
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
      printf("Binded Tuple value is %d %d \n", id1, id2);

    }
    table->close();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
