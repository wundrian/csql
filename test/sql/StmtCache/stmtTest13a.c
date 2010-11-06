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

    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(1234,?,'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER INSERT PREPARE operation\n");
    int rnd = 0;
    int i = 0;
    if (1) {
        i++;
        rv = con->beginTrans();
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
    stmt->free(); 

    printf("rename TABLE\n");
    strcpy(statement, "rename TABLE t1 to t2");
    rv = stmt->prepare(statement);
    if (rv != OK) {con->disconnect();delete stmt; delete con; return -1; }
    rv = con->beginTrans();
    stmt->execute(rows);
    con->commit();
    con->display();

    strcpy(statement,"INSERT INTO t2 VALUES(1234,?,'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER INSERT PREPARE operation\n");
    i = 1000;
    if (1) {
        i++;
        rv = con->beginTrans();
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
    stmt->free(); 
    system("csqldump");
    strcpy(statement, "drop TABLE t2");
    rv = stmt->prepare(statement);
    if (rv != OK) {con->disconnect();delete stmt; delete con; return -1; }
    stmt->execute(rows);
    stmt->free();

    con->disconnect();
    delete stmt; 
    delete con;
}
