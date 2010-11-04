
#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0;
    ret = deleteTuple(dbMgr, conn, "t1", 1);
    conn.close();
    return ret;

}
