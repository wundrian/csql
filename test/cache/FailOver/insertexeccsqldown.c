#include<AbsSqlStatement.h>
#include<SqlFactory.h>
#include<Info.h>
int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = SqlFactory :: createConnection(CSqlGateway);
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = SqlFactory :: createStatement(CSqlGateway);
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"insert into t1 values(11, 33, 4234, 'mohan', 34.34, 345.543, '1999/02/23', '11:22:33', '1999/02/23 11:22:33');");
    int rows=0;
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    sleep (15);
    con->commit();
    stmt->free();
    printf("csql down: insert into t1(cached table) success\n");
    
    strcpy(statement,"insert into t2 values(11, 33, 4234, 'mohan', 34.34, 345.543, '1999/02/23', '11:22:33', '1999/02/23 11:22:33');");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: insert into t2(not cached mysql table) failed\n"); delete stmt; delete con; return 4; }
    printf("csql down: insert into t2(not cached mysql table) success\n");
    con->commit();
    
    strcpy(statement,"insert into t3 values(11, 33, 4234, 'mohan', 34.34, 345.543, '1999/02/23', '11:22:33', '1999/02/23 11:22:33');");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: insert into t3(not cached csql table) failed\n"); delete stmt; delete con; return 6; }
    printf("csql down: insert into t3(not cached csql table) success\n");
    con->commit();
    
    stmt->free();
    
    delete stmt;
    delete con;
    return 0;
}


