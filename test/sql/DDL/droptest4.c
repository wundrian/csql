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
    AbsSqlStatement *dropstmt = SqlFactory::createStatement(CSql);
    dropstmt->setConnection(con);
    char statement[200];
    strcpy(statement, "CREATE TABLE t1 (f1 int, f2 int, f3 char(20), primary key (f1));");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();

    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(1234,5,'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }

    strcpy(statement, "DROP TABLE t1");
    rv = dropstmt->prepare(statement);
    if (rv != OK) {
        printf("DROP table failed\n");
        con->disconnect();delete stmt; delete con; return -1; 
    }
    dropstmt->execute(rows);
    dropstmt->free();

        rv = con->beginTrans();
        rv = stmt->execute(rows);
        if (rv != OK) { 
            printError(rv, "Insert failed with ret val %d", rv);
            con->rollback(); 
        }
        else con->commit();
    stmt->free(); 

    con->disconnect();
    delete stmt; 
    delete con;
}
