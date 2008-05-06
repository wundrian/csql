// create table EMP(EID INT,ENAME CHAR(20),SALARY  FLOAT)
//  insert ten rows  and EID should starts from 1001.
//   seletct all rows from the table.


#include<SqlFactory.h>

int main()
{
    DbRetVal rv = OK;
    
	AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    
	rv = con->connect("root", "manager");
    if(rv != OK) return 1;

    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    stmt->setConnection(con);
    char statement[200];

    strcpy(statement, "CREATE TABLE EMP(EID INT,ENAME CHAR(20),SALARY FLOAT);");
    
	int rows = 0;
    
	rv = stmt->prepare(statement);
    if(rv != OK) { delete stmt; delete con; return 2; }
    
	rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 3; }
                                                                                    stmt->free();
    printf("Table Created\n");

    strcpy(statement,"INSERT INTO EMP VALUES(?,?,?);");

    int eid = 1000;
    char ename[20] = "fasd";
    char ename1[10][20]={"praba",	"kishor",	"jitu",	"biswa",	"suman",
						 "arin", 	"arabi", "sanjit","sanjay",	"rajesh" };
    float salary = 0;
    int count = 0;

    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    
	rv = con->beginTrans();
    for(int i = 0; i < 10; i++) {
		eid++;
        salary = salary + 1000;
        strcpy(ename, ename1[i]);
		stmt->setIntParam(1, eid);
        stmt->setStringParam(2, ename);
		stmt->setFloatParam(3, salary);
		rv = stmt->execute(rows); if(rv != OK) break; 
		count++;
    }
	con->commit(); 
    stmt->free();

    printf("Total rows Inserted = %d\n", count);
    
	//fetching the rows from EMP Table
    strcpy(statement, "SELECT * FROM EMP;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
	
	stmt->bindField(1, &eid);
    stmt->bindField(2, ename);
    stmt->bindField(3, &salary);
    count=0;

    rv = con->beginTrans(); if(rv != OK) return 6;
	stmt->execute(rows);
    printf("\ninserted values are as follows\n");
    printf("EmpId | name\t| salary\n");
    printf("--------------------------\n");
	while (stmt->fetch() != NULL)  
		printf("%d  | %s\t| %6.2f\n", eid, ename, salary);
    rv = con->commit();
    if(rv != OK) { delete stmt; delete con; return 7; }
    stmt->close();
    stmt->free();
	delete stmt;
    delete con;
    return 0;
}
 
