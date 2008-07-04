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
    
    strcpy(statement,"select * from t1;");
    int rows=0;
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    sleep(15);
    rv  = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    con->commit();
    stmt->free();
    printf("csql down: select from t1(cached table) success\n");
    
    strcpy(statement,"select * from t2;");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: select from t2(not cached mysql table) failed\n"); delete stmt; delete con; return 4; }
    printf("csql down: select from t2(not cached mysql table) success\n");
    con->commit();
    stmt->free();

    strcpy(statement,"select * from t3;");
    con->beginTrans();
    rv = stmt->prepare(statement);
    if(rv!=OK) { printf("csql down: select from t3(not cached csql table) failed\n"); delete stmt; delete con; return 5; }
    rv  = stmt->execute(rows);
    if(rv!=OK) { printf("csql down: select from t3(not cached csql table) failed\n"); delete stmt; delete con; return 6; }
    printf("csql down: select from t3(not cached csql table) success\n");
    con->commit();
    
    stmt->free();
    delete stmt;
    delete con;
    return 0;
}


