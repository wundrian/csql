#include<SqlFactory.h>
#include<SqlNwConnection.h>
#include<SqlNwStatement.h>

AbsSqlConnection *createConnection()
{
#ifdef NETWORK
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlNetwork);
    SqlNwConnection *conn = (SqlNwConnection *) con;
    conn->setHost("localhost", 5678);
#elif defined NETWORKADAPTER
	AbsSqlConnection *con = SqlFactory::createConnection(CSqlNetworkAdapter);
    SqlNwConnection *conn = (SqlNwConnection *) con;
    conn->setHost("localhost", 5678);
#elif defined NETWORKGATEWAY
	AbsSqlConnection *con = SqlFactory::createConnection(CSqlNetworkGateway);
    SqlNwConnection *conn = (SqlNwConnection *) con;
    conn->setHost("localhost", 5678);
#else
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
#endif
    return con;
}

AbsSqlStatement *createStatement()
{
#ifdef NETWORK
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlNetwork);
#elif defined NETWORKADAPTER
	AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlNetworkAdapter);
#elif defined NETWORKGATEWAY
	AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlNetworkGateway);
#else
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
#endif
    return stmt;
}

DbRetVal executeDdlQuery(AbsSqlConnection *conn, AbsSqlStatement *stmt, 
                                                                 char *stmtstr)
{
    DbRetVal rv = OK;
    rv = stmt->prepare(stmtstr);
    if (rv != OK) return rv;
    int rows = 0;
    rv = stmt->execute(rows);
    if (rv != OK) return rv;
    return OK;
}

DbRetVal insert(AbsSqlStatement *stmt, int val, bool isSleep)
{
    char statement[1024] = "insert into t1 values(?, 'PRABAKARAN');";
    DbRetVal rv = stmt->prepare(statement);
    if (rv != OK) return rv;
    stmt->setIntParam(1, val);
    int rows = 0;
    rv = stmt->execute(rows);
    if (rv != OK) { return ErrLockTimeOut; }
    printf("Inserted tuple : %d %s\n", val, "PRABAKARAN");
    if (isSleep) ::sleep(5);
    return OK;
}

DbRetVal select(AbsSqlStatement *stmt, int val, bool isSleep, bool checkUpd=false)
{
    char statement[1024] = "select * from t1 where f1 = ?;";
    int id = 0;
    char name[196];
    DbRetVal rv = stmt->prepare(statement);
    if (rv != OK) return rv;
    stmt->bindField(1, &id);
    stmt->bindField(2, name);
    stmt->setIntParam(1, val);
    int rows = 0;
    rv = stmt->execute(rows);
    if (rv != OK) return rv;
    void *tuple = stmt->fetch(rv);
    if (rv != OK) return rv;
    if (tuple == NULL) {
        printf("Tuple not found\n");
        return ErrNotFound;
    }
    printf("ThreadID: %lu Tuple %d %s\n", os::getthrid(), id, name);       
    if (isSleep) ::sleep(5);
    if ( checkUpd && strcmp(name, "KANCHANA") != 0)  return ErrUnknown;
    return OK;
}

DbRetVal update(AbsSqlStatement *stmt, int val, bool isSleep, char *updname = NULL)
{
    char statement[1024] = "update t1 set f2 = 'KANCHANA' where f1 = ?;";
    DbRetVal rv = stmt->prepare(statement);
    if (rv != OK) return rv;
    stmt->setIntParam(1, val);
    int rows = 0;
    rv = stmt->execute(rows);
    if (rv != OK) { return rv; }
    printf("ThreadID: %lu Updated Tuple %d %s\n", os::getthrid(), val, "KANCHANA");
    if (isSleep) ::sleep(2);
    return OK;
}

DbRetVal remove(AbsSqlStatement *stmt, int val, bool isSleep)
{
    char statement[1024] = "delete from t1 where f1 = ?;";
    DbRetVal rv = stmt->prepare(statement);
    if (rv != OK) return rv;
    stmt->setIntParam(1, val);
    int rows = 0;
    rv = stmt->execute(rows);
    if (rv != OK) { return rv; }
    printf("ThreadID: %lu Deleted Tuple %d %s\n", os::getthrid(), val, "PRABAKARAN");
    if (isSleep) ::sleep(2);
    return OK;
}

