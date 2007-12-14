#include <SqlStatement.h>
#include<NanoTimer.h>
int main()
{
    DbRetVal rv = OK; 
    SqlConnection *con = new SqlConnection();
    con->connect("root", "manager");
    SqlStatement *stmt = new SqlStatement();
    stmt->setConnection(con);
    char statement[1024];
    //strcpy(statement, "UPDATE t1 SET f2 = 299 WHERE f1 >97");
    //strcpy(statement, "UPDATE t1 SET f1=290 WHERE f2 > ?");
    strcpy(statement, "UPDATE t1 SET f2 = 290 ");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return 1; }
    int id1 =160, id2 = 7;
    //stmt->bindParam(1, &id1);
    //stmt->bindParam(2, &id2);
    int icount=0;
    void *tuple;
    NanoTimer timer;
        timer.start();
    con->beginTrans();
    stmt->execute(rows);
    con->commit();
    timer.stop();

    printf("Update %d %lld %lld %lld\n", rows, timer.min(), timer.max(), timer.avg());

    stmt->free();
    delete stmt;
    delete con;
    return 0; 
}
