//addField f1, dropField f1 and then addField f1 with notnull flag set, 
//table creation should succeed and it should make the f1 field notnull
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;

    tabDef.addField("f1", typeInt);
    tabDef.dropField("f1");
    tabDef.addField("f1", typeInt, 0, NULL, true);
    rv=dbMgr->createTable("t1", tabDef);
    if(rv!=OK) 
    { 
	printf("Table creation failed\n");
	printf("Test Failed\n");
	dbMgr->dropTable("t1");
	return 3;
    }
    printf("Table created\n");

    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        dbMgr->dropTable("t1");
        conn.close();
        return -1;
    }
//    int id;
//    table->bindFld("f1",&id);
    
    conn.startTransaction();
    rv=table->insertTuple();
    if(rv==OK)
    {
	printf("NULL value inserted in NOTNULL field\n");
	printf("Test Failed\n");
        conn.commit();
	dbMgr->closeTable(table);
	dbMgr->dropTable("t1");
	return 4;
    }
    conn.commit();
    printf("NULL value can not be stored\n");
    printf("Test passed\n");
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");  
    conn.close();
    return 0;
}



