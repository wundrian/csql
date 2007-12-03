
#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0;
    ret = insertTuple(dbMgr, conn, "t1", 10);
    ret = insertTuple(dbMgr, conn, "t2", 10);
    conn.close();
    return ret;

}
