#include<SqlFactory.h>
#include<SqlNwConnection.h>
#include<SqlNwStatement.h>

AbsSqlConnection *createConnection()
{
#ifdef NET
    AbsSqlConnection *con = new SqlNwConnection();
    con->setInnerConnection(NULL);
    SqlNwConnection *conn = (SqlNwConnection *)con;
    conn->setHost("localhost", 5678);
#else
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
#endif
    return con;
}

AbsSqlStatement *createStatement()
{
#ifdef NET
    AbsSqlStatement *stmt = new SqlNwStatement();
    stmt->setInnerStatement(NULL);
#else
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
#endif
    return stmt;
}
