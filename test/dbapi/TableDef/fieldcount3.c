//Create table with 1024 fields and call getFldCount() 
//and check return value is 1024
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int test;
    TableDef tabDef;
    char str[6]="f",field[6];
    for (int i=1;i<=1024;i++)
    {   
	sprintf(field,"%s%d",str,i);
        test=tabDef.addField(field, typeInt);
	if(test!=0)
	{
		printf("Field f%d could not be created",i);
		return test; 
	}
    }
    int fieldcount=tabDef.getFieldCount();
    printf("Number of Fields = %d\n",fieldcount);
    rv=dbMgr->createTable("t1", tabDef);
    if(rv!=OK) 
    { 
	printf("Table creation Failed\n"); 
	printf("Test failed\n");
	return 3;
    }
    printf("Table created \n");
    printf("Test passed\n");
    dbMgr->dropTable("t1"); 
    conn.close();
    return 0;
}

