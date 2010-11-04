//Should not allow field names more than 64 character
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;

    tabDef.addField("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklabc", typeInt, 0, NULL, true);
    rv=dbMgr->createTable("t1", tabDef);
    if(rv==OK) 
    { 
	printf("Allowing fieldname more than 64 character\n");
	printf("Test Failed\n");
	dbMgr->dropTable("t1");
	return 3;
    }
    printf("Test Passed\n");
    conn.close();
    return 0;
}

//Table is created  and allowing fieldnames with more than 64 characters

