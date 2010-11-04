//Create table with fieldname as "EMP" and "emp". it should succeed. 
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
    tabDef.addField("EMP", typeInt, 0, NULL, true);
    rv=(DbRetVal)tabDef.addField("emp", typeInt);
    if(rv!=0) 
    {
	printf("Test Failed with return value %d\n",rv);
	return rv;
    } 
    
    dbMgr->createTable("t1", tabDef);
    printf("Table created\n");
    printf("test Passed\n");
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}


