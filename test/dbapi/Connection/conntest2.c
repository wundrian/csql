#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK) return 1;

    //checking whether it returns already connected error 
    rv = conn.open("praba", "manager");
    if (rv == OK) return 2;

    rv = conn.close();
    if (rv != OK) return 3;

    //when not connected both are expected to return NULL
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    UserManager *uMgr  = conn.getUserManager();
    if (dbMgr != NULL || uMgr != NULL) return 5;
    return 0;
}
