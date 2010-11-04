#include<SqlFactory.h>
#include<SqlNwConnection.h>
#include<SqlNwStatement.h>
#include<AbsSqlStatement.h>
#include<Info.h>

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
    AbsSqlConnection *con = SqlFactory::createConnection(CSqlAdapter);
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
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
#endif
    return stmt;
}
