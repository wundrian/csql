
#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0;
    if ( createTable(dbMgr, "t1") != 0 ) { ret = 3; }
    if ( createTable(dbMgr, "t2") != 0 ) { ret = 3; }
    if ( createIndex(dbMgr, "t1", "f1", "t1idx1") != 0 ) { ret= 3; }
    if ( createIndex(dbMgr, "t1", "f2", "t1idx2") != 0 ) { ret = 3; }
    if ( createIndex(dbMgr, "t2", "f1", "t2idx1") != 0 ) { ret = 3; }

    conn.close();
    return ret;

}
