#include<CSql.h>
int main()
{
    Connection conn;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr != NULL) { printf("Database found without opening Connection\n"); printf("Test failed\n");return 1;}
    printf("Test passed\n");
    conn.close();
    return 0;
}
