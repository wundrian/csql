//create table with the name made up of special characters other than underscores.It should fail  
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;

    tabDef.addField("f1", typeInt, 0, NULL, true);
    rv=dbMgr->createTable("t-1",tabDef);
    if(rv==OK) 
    { 
	printf("Test Failed\n");
	rv=dbMgr->dropTable("t-1");
      	return 3;
    }
    printf("Test Passed\n"); 
    conn.close();
    return 0;
}

//Table creating with name made up of any special character

