#include <SqlStatement.h>
#include<NanoTimer.h>
int main()
{
    DbRetVal rv = OK; 
    SqlConnection *con = new SqlConnection();
    con->connect("praba", "manager");
    SqlStatement *stmt = new SqlStatement();
    stmt->setConnection(con);
    char statement[1024];
    strcpy(statement, "DELETE FROM t1 WHERE f1 >97");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return 1; }
    int id1 =100, id2 = 100;
    int icount=0;
    void *tuple;
    NanoTimer timer;
        timer.start();
    con->beginTrans();
    stmt->execute(rows);
    printf(" Rows returned %d\n", rows);
    /*while(true)
    {
        tuple = (char*)stmt->fetch() ;
        if (tuple == NULL) { break; }
        printf("f1=%d f2=%d\n", id1, id2);
        icount++;
    }*/
    con->commit();
        timer.stop();

    printf("Select %d %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());


    stmt->free();
    delete stmt;
    delete con;
    return 0; 
}
