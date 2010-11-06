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
    strcpy(statement,"INSERT INTO t1 VALUES(1234,100);");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    int rnd = 0;
    rv = con->beginTrans();
    con->commit();
    con->disconnect();
    delete con;
}
