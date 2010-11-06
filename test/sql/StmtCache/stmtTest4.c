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
    strcpy(statement, "CREATE TABLE t1 (f1 int, f2 int, f3 char(20), primary key (f1));");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("AFTER CREATE TABLE operation\n");
    con->display();

    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(1234,5,'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER INSERT PREPARE operation\n");
    con->display();
    int rnd = 0;
        rv = con->beginTrans();
        rv = stmt->execute(rows);
        if (rv != OK) { 
            printError(rv, "Insert failed with ret val %d", rv);
            con->rollback(); 
        }
        else con->commit();
    printf("AFTER INSERT EXECUTE operation\n");
    con->display();
    stmt->free(); 
    printf("AFTER STMT FREE operation\n");
    con->display();

    strcpy(statement, "UPDATE t1 set f2=10 where f1=1234;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER UPDATE PREPARE operation\n");
    con->display();
    rv = con->beginTrans();
    rv = stmt->execute(rows);
    if (rv != OK) {
        printError(rv, "Update failed with ret val %d", rv);
        con->rollback();
    }
    else con->commit();
    stmt->free();
    printf("AFTER STMT FREE operation\n");
    con->display();

    strcpy(statement, "DELETE from t1 where f2=10;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER DELETE PREPARE operation\n");
    con->display();
    rv = con->beginTrans();
    rv = stmt->execute(rows);
    if (rv != OK) {
        printError(rv, "Delete failed with ret val %d", rv);
        con->rollback();
    }
    else con->commit();
    stmt->free();
    printf("AFTER STMT FREE operation\n");
    con->display();

    strcpy(statement, "SELECT f1 from t1 where f2=1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER SELECT PREPARE operation\n");
    con->display();
    rv = con->beginTrans();
    int val =0;
    stmt->bindField(1, &val);
    rv = stmt->execute(rows);
    while (stmt->fetch() != NULL)
    {
        printf("Tuple value %d\n", val);
    }
    con->commit();
    stmt->free();
    printf("AFTER STMT FREE operation\n");
    con->display();

    strcpy(statement, "DROP TABLE t1");
    rv = stmt->prepare(statement);
    if (rv != OK) {con->disconnect();delete stmt; delete con; return -1; }
    stmt->execute(rows);
    stmt->free();


    con->disconnect();
    printf("AFTER disconnect\n");
    con->display();
    delete stmt; 
    delete con;
}
