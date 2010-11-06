#include <SqlFactory.h>

int main(int argc, char **argv)
{
    DbRetVal rv = OK;
    struct timeval timeout;
    struct timeval timeStamp;
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement, "CREATE TABLE t1 (f1 int, f2 int, f3 char(20), primary key (f2));");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("AFTER CREATE TABLE operation\n");
    con->display();

    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(1234,?,'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER INSERT PREPARE operation\n");
    con->display();
    int rnd = 0;
    int i = 0;
    if (1) {
        i++;
        rv = con->beginTrans();
        //stmt->setIntParam(1, rnd);
        stmt->setIntParam(1, i);
        rv = stmt->execute(rows);
        if (rv == ErrUnique) {
            printf("Unique Key Violation Error\n"); 
            con->rollback(); 
        } else if (rv != OK) { 
            printError(rv, "Insert failed with ret val %d", rv);
            con->rollback(); 
        }
        else con->commit();
    }
    printf("AFTER INSERT EXECUTE operation\n");
    con->display();
    stmt->free(); 
    printf("AFTER STMT FREE operation\n");
    con->display();

    printf("AFTER DROP TABLE\n");
    strcpy(statement, "DROP TABLE t1");
    rv = stmt->prepare(statement);
    if (rv != OK) {con->disconnect();delete stmt; delete con; return -1; }
    stmt->execute(rows);
    con->display();

    con->disconnect();
    printf("AFTER disconnect\n");
    con->display();
    delete stmt; 
    delete con;
}
