#include<AbsSqlStatement.h>
#include<SqlFactory.h>
#include<NanoTimer.h>
#define ITERATIONS 10000
int main()
{
    DbRetVal rv = OK; 
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlGateway);
    rv = con->connect("root", "manager");
    if (rv != OK) return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlGateway);
    stmt->setConnection(con);
    char statement[1024];
    int id1 =10;
    int newVal = 1000;
    int count =0, rows=0;
    /*
    strcpy(statement, "INSERT INTO t1 (f1, f2) VALUES (?, ?);");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       rv = con->beginTrans();
       if (rv != OK) break;
       id1 =  i;
       stmt->setIntParam(1, id1);
       stmt->setIntParam(2, id1);
       rv = stmt->execute(rows);
       if (rv != OK) break;
       rv =  con->commit();
       if (rv != OK) break;
       count++;
    }
    stmt->free();
    */

    /*strcpy(statement, "UPDATE t1 set f2=? where f1=?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(2, i);
       stmt->setIntParam(1, newVal);
       rv = stmt->execute(rows);
       if (rv != OK && rows !=1) break;
       rv = con->commit();
       if (rv != OK) break;
       count++;
    }
    stmt->free();
    */

    strcpy(statement, "DELETE FROM t1 where f1=?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->bindField(1, &id1);
    count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(1, i+100000);
       rv = stmt->execute(rows);
       if (rv != OK && rows != 1) break;
       rv = con->commit();
       if (rv != OK) break;
       count++;
    }
    stmt->free();

    delete stmt;
    delete con;
    return 0; 
}
