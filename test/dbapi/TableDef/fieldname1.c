//Create table with the field name made up of special characters other than
//underscore. it should not be allowed.  
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
    int i=0;
    rv=(DbRetVal)tabDef.addField("f-2", typeInt);
    if(rv==OK) i++; 
    rv=(DbRetVal)tabDef.addField("2f", typeInt);
    if(rv==OK) i++;
    rv=(DbRetVal)tabDef.addField("f2@", typeInt);
    if(rv==OK) i++;
    rv=(DbRetVal)tabDef.addField("_f2#", typeInt);
    if(rv==OK) i++; 
    rv=(DbRetVal)tabDef.addField("$f2", typeInt);
    if(rv==OK) i++; 
    rv=(DbRetVal)tabDef.addField("$@*#", typeInt);
    if(rv==OK) i++; 


    if(i){printf(" Test Failed \n"); return i;}
   
    rv=dbMgr->createTable("t1", tabDef);
    if(rv==OK) 
    { 
	printf("Allowing fieldnames made up of all special characters\n"); 
	printf("Test failed\n");
	dbMgr->dropTable("t1");
	return 3;
    }
    
    printf("Test Passed\n"); 
    conn.close();
    return 0;
}
//Table is created  and allowing field names with special characters other than underscores also
