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
    int rows =0;

    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(1234,?);");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    int rnd = 0;
    rv = con->beginTrans();
    stmt->setIntParam(1, 100);
    rv = stmt->execute(rows);
    stmt->setIntParam(1, 200);
    rv = stmt->execute(rows);
    if (rv != OK) { 
        printError(rv, "Insert failed with ret val %d", rv);
    }
    con->commit();
    stmt->free(); 

    strcpy(statement, "create index idx on t1 (f2) primary hash;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = stmt->execute(rows);
    if (rv != OK) {
        printError(rv, "create idx failed with ret val %d", rv);
    }
    stmt->free();

    strcpy(statement,"INSERT INTO t1 VALUES(1234,?);");
    rv = stmt->prepare(statement);
    stmt->setIntParam(1, 100);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = con->beginTrans();
    rv = stmt->execute(rows);
    if (rv != OK) {
        printError(rv, "insert failed with ret val %d", rv);
    }
    con->commit();
    stmt->free();

    strcpy(statement,"drop index idx;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = stmt->execute(rows);
    if (rv != OK) {
        printError(rv, "drop idx failed with ret val %d", rv);
    }
    stmt->free();

    strcpy(statement,"INSERT INTO t1 VALUES(1234,?);");
    rv = stmt->prepare(statement);
    stmt->setIntParam(1, 100);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = con->beginTrans();
    int val =0;
    rv = stmt->execute(rows);
    con->commit();
    stmt->free();

    con->disconnect();
    delete stmt; 
    delete con;
}
