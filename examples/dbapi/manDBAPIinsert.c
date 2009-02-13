// DBAPI Demo:	insert and read 
//

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
   
   	//Define the table
    TableDef tabDef;
    tabDef.addField("empId", typeInt, 0, NULL, true);
    tabDef.addField("name", typeString, 20);
    tabDef.addField("salary", typeFloat);

	// create table
    rv = dbMgr->createTable("EMP", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return 3; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "EMP");
    idxInfo->list.append("empId");
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return ErrUnknown; }

	// open table
    Table *table = dbMgr->openTable("EMP");
    if (table == NULL) 
    { 
        printf("Unable to open table\n"); 
        dbMgr->dropTable("EMP");
        conn.close();
        return -1; 
    }

	// allocate fields to bind
    int id1 = 0;
    char *setNames[10] = {"Praba", "Kishor", "Jiten", "Gopal", "Aruna",							  "Ravi", "Kiran" , "Sanjay", "Rajesh", "Arun" };
	float sal=0.0; 
	char name[20];
    int icount =0, i = 0;

	// bind the allocated fields 
    table->bindFld("empId", &id1);
    table->bindFld("name", name);
    table->bindFld("salary", &sal);

	// start transaction
    conn.startTransaction();
    for (i = 0 ; i < 10; i++)
    {
		// set values to insert into table
        id1 = 1001 + i;
		sal = 1000.00 * (i + 1); 
		strcpy(name, setNames[i]); 

		// insert tuple
        rv = table->insertTuple();
        if (rv != OK) break;
    }
	// commit transaction
    conn.commit();
    printf("%d Tuples inserted\n", i);
	
	// start transaction
	conn.startTransaction();

	// set condition to select all the tuples 
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("EMP");
       conn.close();
    }
	printf("\ninserted values are as follows\n");
	printf("EmpId | name\t| salary\n");
	printf("--------------------------\n");
	i = 0;
	while(true)
    {
		// fetch each tuple satisfying the condition
        char * tuple = (char*)table->fetch();
        if (tuple == NULL) {break;}
        printf("%d  | %s\t| %6.2f\n", id1, name, sal);
        i++;
    }
	// commit the transaction
	conn.commit();
    
	//close the condition
	table->closeScan();
    
	// close the table using the table handle
	dbMgr->closeTable(table);

	//close the connection
    conn.close();
    return 0;
}
