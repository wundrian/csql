#include<SqlStatement.h>
#include<NanoTimer.h>
int main()
{
    DbRetVal rv = OK; 
    SqlConnection *con = new SqlConnection();
    con->connect("root", "manager");
    printf("Connected\n");
    SqlStatement *stmt = new SqlStatement();
    stmt->setConnection(con);
    char statement[1024];
    //strcpy(statement, "INSERT INTO t1 (f1, f2) VALUES (100, 200);");
    strcpy(statement, "INSERT INTO t1 (f1, f2) VALUES (?, ?);");
    //strcpy(statement, "INSERT INTO t1 VALUES (100, 200);");
    //strcpy(statement, "INSERT INTO t1 ");
    int rows =0;
    rv = stmt->prepare(statement);
    printf("Prepeared\n");
    int id1 =100, id2 = 100;
    if (rv != OK) {delete stmt; delete con; return -1; }
    NanoTimer timer;
    con->beginTrans();
    for (int i = 0 ;  i < 10 ; i++)
    {
    timer.start();
    id1 =  i; id2 = i;
    stmt->setIntParam(1, id1);
    stmt->setIntParam(2, id2);
    
    stmt->execute(rows);
    timer.stop();
    }
//{printf("Sleeping\n"); sleep(10);}
    con->commit();
    printf("Insert %lld %lld %lld\n", timer.min(), timer.max(), timer.avg());
    stmt->free();
    delete stmt;
    delete con;
    return 0; 
}
