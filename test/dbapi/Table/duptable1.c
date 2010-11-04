#include<CSql.h>
//create two table with same name
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    tabDef.addField("f3", typeString, 20);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return 3; }
    printf("Table created\n");
    int ret =0;
    rv = dbMgr->createTable("t1", tabDef);
    if (rv == OK) ret =1;
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}
