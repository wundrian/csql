
#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0;
    conn.startTransaction();
    ret = insertTuple(dbMgr, conn, "t1", 1);
    conn.commit();
    conn.close();
    return ret;

}
