#include<AbsSqlStatement.h>
#include<SqlFactory.h>
#include<NanoTimer.h>
#define ITERATIONS 100
int main()
{
    DbRetVal rv = OK; 
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    rv = con->connect("root", "manager");
    if (rv != OK) return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    stmt->setConnection(con);
    char statement[1024];
    strcpy(statement, "CREATE TABLE t1 (f1 int, f2 char(196));");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Table t1 created\n");

    strcpy(statement, "CREATE INDEX t1idx on t1 (f1);");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Index created on t1(f1) \n");

    strcpy(statement, "INSERT INTO t1 (f1, f2) VALUES (?, ?);");
    int id1 =10;
    char name[196];
    strcpy(name, "Rithish");
    NanoTimer timer;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    int count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       timer.start();
       rv = con->beginTrans();
       if (rv != OK) break;
       id1 =  i;
       stmt->setIntParam(1, id1);
       strcpy(name, "Gopika");
       stmt->setStringParam(2, name);
       rv = stmt->execute(rows);
       if (rv != OK) break;
       rv =  con->commit();
       if (rv != OK) break;
       timer.stop();
       count++;
    }
    printf("Total Rows Inserted %d %lld %lld %lld\n", count, timer.minc(), 
                                timer.maxc(), timer.avg());
    stmt->free();

    strcpy(statement, "SELECT * FROM t1 where f1 = ?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->bindField(1, &id1);
    stmt->bindField(2, name);
    timer.reset();
    count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       timer.start();
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(1, i);
       stmt->execute(rows);
       if (stmt->fetch() == NULL) { printf("unable to read record\n"); break; }
       stmt->close();
       rv = con->commit();
       if (rv != OK) break;
       timer.stop();
       count++;
    }
    stmt->free();
    printf("Total Rows Selected %d %lld %lld %lld\n", count, timer.minc(), 
                                timer.maxc(), timer.avg());
    
    strcpy(statement, "UPDATE t1 set f2=? where f1=?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->bindField(1, &id1);
    stmt->bindField(2, name);
    timer.reset();
    count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       timer.start();
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(2, i);
       stmt->setStringParam(1, "ChangedValue");
       rv = stmt->execute(rows);
       if (rv != OK && rows !=1) break;
       rv = con->commit();
       if (rv != OK) break;
       timer.stop();
       count++;
    }
    stmt->free();
    printf("Total Rows Updated %d %lld %lld %lld\n", count, timer.minc(), 
                                timer.maxc(), timer.avg());

    strcpy(statement, "DELETE FROM t1 where f1=?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->bindField(1, &id1);
    timer.reset();
    count =0;
    for (int i = 0 ;  i < ITERATIONS ; i++)
    {
       timer.start();
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(1, i);
       rv = stmt->execute(rows);
       if (rv != OK && rows != 1) break;
       rv = con->commit();
       if (rv != OK) break;
       timer.stop();
       count++;
    }
    stmt->free();
    printf("Total Rows Deleted %d %lld %lld %lld\n", count, timer.minc(), 
                                timer.maxc(), timer.avg());

    strcpy(statement, "DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Table dropped\n");


    delete stmt;
    delete con;
    return 0; 
}
