//create table without fields. it should be failed
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
  
    rv=dbMgr->createTable("t1", tabDef);
    if(rv==OK) 
    { 
	printf("Table created without Fields\n"); 
	printf("Test failed\n");
	dbMgr->dropTable("t1");
	return 3;
    }
    
    printf("Test Passed\n"); 
    conn.close();
    return 0;
}

