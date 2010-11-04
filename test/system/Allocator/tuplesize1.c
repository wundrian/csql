/**********************************************************
* Test Case
* create table t1 with int
* create index if specified
* check  table information for tuple size 
*/
#include <CSql.h>
#include <TableImpl.h>
#include <DatabaseManagerImpl.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0, rc =0;

    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 1; }
    printf("Table created\n");

    TableImpl *table = (TableImpl*) dbMgr->openTable("t1");
    table->printInfo();
    dbMgr->closeTable((Table*)table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
