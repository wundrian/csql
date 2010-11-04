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
    tabDef.addField("f3", typeInt, 0, NULL, false);
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
    int id1=0, id2 = 5, id3=10;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table->bindFld("f3", &id3);
    int icount=0;
    for(int i=0;i<6;i++)
    {
        conn.startTransaction();
	id1=i;
  	if(i%2==0) 
	{
	    if(i!=0)
        table->markFldNull(2);
    }    
        else table->markFldNull(3);
        rv = table->insertTuple();
	if(rv!=OK) break;
        if(i%2==0) table->clearFldNull(2);
	else table->clearFldNull(3);
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
    void *tuple = NULL; 
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        if (table->isFldNull(1))
	{ 
	    printf("Column 1 is null\n");
	    dbMgr->closeTable(table);
	    dbMgr->dropTable("t1");
	    conn.close();
	    return -1;
	}
        if (table->isFldNull(2)) printf("Column 2 is null\n");
        if (table->isFldNull(3)) printf("Column 3 is null\n");
        printf("Binded Tuple value is %d %d %d\n", id1, id2, id3);
    }
    rv=table->closeScan();

    Condition p1;
    int val1=4;
    p1.setTerm("f1", OpLessThan, &val1);
    table->setCondition(&p1);
    conn.startTransaction();
    rv=table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
       return 5;
    }
    while(true)
    {
        tuple = (char*)table->fetch();
	if (tuple == NULL) { break; } 
       	rv = table->markFldNull("f1");
        if (rv == ErrNullViolation) {
            printf("NULL Violation\n");
            continue;
        }
        rv=table->updateTuple();
	if(rv==OK) 
	{
	    table->clearFldNull("f1");
	    break;
	}
        table->clearFldNull("f1");
    }
    conn.commit();
    table->closeScan();

    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
       return 4;
    }
    printf("Scan after updation\n");
    printf("********************\n");
    printf("f1 | f2\t| f3\n");
    printf("--------------------------\n");

    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
	if (table->isFldNull(1))
        { 
            printf("Column 1 is null\n");
            dbMgr->closeTable(table);
            dbMgr->dropTable("t1");
            conn.close();
            return -1;
        }
        if (table->isFldNull(2)) printf("Column 2 is null\n");
        if (table->isFldNull(3)) printf("Column 3 is null\n");
        printf("%d  | %d\t| %d\n", id1, id2, id3);
    }
    table->closeScan();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
