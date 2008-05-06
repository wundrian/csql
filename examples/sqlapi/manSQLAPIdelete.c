//  delete rows where eid > 1005.
#include<SqlFactory.h>

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = SqlFactory :: createConnection(CSql);
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = SqlFactory :: createStatement(CSql);
    stmt->setConnection(con);
    if(rv!=OK)return 2;
    char statement[200];
    int rows = 0;

//    deleteing tuples from EMP;

    int eid = 1000;
    char ename[20]="lakshya";
    float salary = 2000;

    strcpy(statement,"DELETE FROM EMP WHERE EID > 1005;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    
	rv = con->beginTrans();
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    printf("Rows Deleted successfully\n");
    rv = con->commit();
    if(rv!=OK) { delete stmt; delete con; return 6; }
    stmt->free();

    // fetching the rows from EMP Table
    strcpy(statement,"SELECT * FROM EMP;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 7; }

    stmt->bindField(1,&eid);
    stmt->bindField(2,ename);
    stmt->bindField(3,&salary);

	printf("EmpId | name\t| salary\n");
	printf("--------------------------\n");
	
	int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL)
        printf("%d  | %s\t| %6.2f\n", eid, ename, salary);
    rv = con->commit();
    if(rv!=OK) { delete stmt; delete con; return 7; }
    stmt->close();
    stmt->free();

    strcpy(statement,"DROP TABLE EMP;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 9; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 10; }
    stmt->free();
    printf("Table dropped\n");

    delete stmt;
    delete con;
    return 0;
}
