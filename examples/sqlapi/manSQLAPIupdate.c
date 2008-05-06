//  open table EMP
//  UPDATE WHERE EID = 1001, 1003, 1005
//   seletct all rows from the table.

#include<SqlFactory.h>
#include <AbsSqlStatement.h>


int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = SqlFactory :: createConnection(CSql);
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = SqlFactory :: createStatement(CSql);
    stmt->setConnection(con);
    char statement[200];

    int rows = 0;

    // UPDATE EMP WITH WHERE CLAUSE(EID<1006)
    strcpy(statement, "UPDATE EMP SET SALARY=?, ENAME=? WHERE EID=?;" );
    rv = stmt->prepare(statement);
    if(rv != OK) { delete stmt; delete con; return 3; }
    
	int eid = 1001;
    char ename[20];
    float salary;
    strcpy(ename, "Mani");	

	char *name[20] = { "Ravi", "Kiran",	"Ganesh", "Yogesh", "Vishnu" };

	int	i = 0;
	while(true) { 
		eid = 1001 + 2 * i;
		if (eid > 1005) break;
		strcpy(ename, name[i]);
		salary = 1111.00 * (1 + i);
   		rv = con->beginTrans();
		stmt->setFloatParam(1,salary);
		stmt->setStringParam(2,ename);
		stmt->setIntParam(3, eid);
   		if(rv != OK) { delete stmt; delete con; return 4; }
    	rv = stmt->execute(rows);
   		rv = con->commit();
   		if(rv != OK) { delete stmt; delete con; return 5; }
		i++;
	}
	stmt->free();
    
	//fetching the rows from EMP Table
    strcpy(statement, "SELECT * FROM EMP;");
    rv = stmt->prepare(statement);
    if(rv != OK) { delete stmt; delete con; return 6; }

    int count=0;

    stmt->bindField(1, &eid);
    stmt->bindField(2, ename);
    stmt->bindField(3, &salary);

    printf("updated values are as follows\n");
    printf("EmpId | name\t| salary\n");
    printf("--------------------------\n");

    rv = con->beginTrans();
    if(rv != OK) { delete stmt; delete con; return 6; }
    stmt->execute(rows);
    while(stmt->fetch() != NULL)  
		printf("%d  | %s\t| %6.2f\n", eid, ename, salary);	
    rv = con->commit();
    if(rv != OK) { delete stmt; delete con; return 7; }
    stmt->close();
    stmt->free();
    delete stmt;
    delete con;
    return 0;
}

