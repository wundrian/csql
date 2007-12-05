#include<CSql.h>
//bind non exisiting field
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
   
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeInt);
    tabDef.addField("f3", typeString, 20);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return 3; }
    printf("Table created\n");

    Table *table = dbMgr->openTable("t1");
    if (table == NULL) 
    { 
        printf("Unable to open table\n"); 
        dbMgr->dropTable("t1");
        conn.close();
        return -1; 
    }
    int id1 = 0, id2 = 5;
    int ret =0;
    char name[20] = "PRAVEEN";
    rv = table->bindFld("f1", &id1);
    if (rv != OK) ret = 1;
    rv  = table->bindFld("f5", &id2);
    if (rv == OK) ret = 1;
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}
