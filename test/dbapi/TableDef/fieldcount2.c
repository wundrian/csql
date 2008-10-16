//100 times addField f1 and dropField f1. getFieldCount() should return 0 
//and table creation should fail saying no fields in tabledef
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
    for (int i=0;i<100;i++)
    {
	tabDef.addField("f1", typeInt);
	tabDef.dropField("f1");
    }
    int fieldcount=tabDef.getFieldCount();
    printf("Number of Fields = %d\n",fieldcount);
    rv=dbMgr->createTable("t1", tabDef);
    if(rv==OK) 
    { 
	printf("Table created without Fields\n"); 
	printf("Test failed\n");
	dbMgr->dropTable("t1");
	return 3;
    }
    
    dbMgr->dropTable("t1"); 
    conn.close();
    return 0;
}

