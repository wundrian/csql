#include<CSql.h>
#define DEFAULT
#include "common.h"
//test with default value for isUnique of IndexInitInfo
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    if ( createTable(dbMgr) != 0 ) { conn.close(); return 3; }
    if ( createIndex(dbMgr, false) != 0 ) { dbMgr->dropTable("t1");conn.close(); return 4;
 }
    int inscount =  insertTupleWithSameValue(dbMgr, conn);
    if (inscount != 10 ) { dbMgr->dropTable("t1"); conn.close(); return 5; }
    dbMgr->dropTable("t1");
    conn.close();
    return 0;

}
