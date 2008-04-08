// DBAPI Demo:	delete and read 

#include<CSql.h>
int main()
{
	// Connect to the database
	Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;

	// get database manager
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
	// open table
    Table *table = dbMgr->openTable("EMP");
    if (table == NULL) 
    { 
        printf("Unable to open table\n"); 
        dbMgr->dropTable("EMP");
        conn.close();
        return 3; 
    }

	// allocate fields to bind
    int id1 = 0;
	float sal=0.0; 
	char name[20];
    int icount =0, i = 0;

	// bind the allocated fields 
    table->bindFld("empId", &id1);
    table->bindFld("name", name);
    table->bindFld("salary", &sal);

    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("EMP");
       conn.close();
       return 4;
    }
    printf("Scan before deletion\n");
    printf("********************\n");
    printf("EmpId | name\t| salary\n");
    printf("--------------------------\n");

    void *fld2ptr, *tuple;
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("%d  | %s\t| %6.2f\n", id1, name, sal);
    }
    conn.commit();
    rv=table->close();

    Condition p1;
    int val1 = 1005;
    p1.setTerm("empId",OpGreaterThan, &val1);
    table->setCondition(&p1);
    conn.startTransaction();
    rv=table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("EMP");
       conn.close();
       return 5;
    }

    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) { break; }
        table->deleteTuple();
    }
    conn.commit();
    table->close();

    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("EMP");
       conn.close();
       return 4;
    }
    printf("Scan after deletion\n");
    printf("********************\n");
    printf("EmpId | name\t| salary\n");
    printf("--------------------------\n");

    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("%d  | %s\t| %6.2f\n", id1, name, sal);
    }
    conn.commit();
    rv=table->close();
    dbMgr->closeTable(table);
	dbMgr->dropTable("EMP");
    conn.close();
    return 0;
}
