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
    strcpy(statement,"insert into t1 values(100,'KKK');");
    int rows=0;
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    sleep (2);
    con->commit();
    stmt->free();
    printf("csql down: insert into t1(cached table) success\n");
    
    strcpy(statement,"insert into t2 values(100,'KKK');");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: insert into t2(not cached mysql table) failed\n"); delete stmt; delete con; return 4; }
    printf("csql down: insert into t2(not cached mysql table) success\n");
    con->commit();
    
    strcpy(statement,"insert into t3 values(100,'KKK');");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: insert into t3(not cached csql table) failed\n"); stmt->free(); delete stmt;con->disconnect(); delete con; return 6; }
    printf("csql down: insert into t3(not cached csql table) success\n");
    con->commit();
    
    stmt->free();
    con->disconnect();
    delete stmt;
    delete con;
    return 0;
}


