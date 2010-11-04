//Should not allow duplicate field names in one table
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
    //int test=0;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    rv=(DbRetVal)tabDef.addField("f1", typeInt);
    if(rv==0) 
    {
	printf("Test failed with return value  %d\n",rv);
	return rv;
    } 
    printf("test passed\n");
    dbMgr->createTable("t1", tabDef);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}

//3298:3086821072:TableDef.cxx:40:Field f_1 already Exists
//Table created with field name f_1 only

