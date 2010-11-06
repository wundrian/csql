#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) {
       conn.close();
       return 1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    rv = dbMgr->checkPoint();
    printf("Checkpoint returned %d\n", rv);
    conn.close(); 
    return 0;
}
