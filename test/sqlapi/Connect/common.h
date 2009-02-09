#include<SqlFactory.h>
#include<SqlNwConnection.h>
#include<SqlNwStatement.h>

AbsSqlConnection *createConnection()
{
#ifdef NET
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlNetwork, "localhost", 5678);
#else
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
#endif
    return con;
}

AbsSqlStatement *createStatement()
{
#ifdef NET
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlNetwork);
#else
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
#endif
    return stmt;
}
