#include<CSql.h>
//bind twice the same field. 
//the later should have the effect
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
    int id1 = 1, id2 = 5, id3 = 8;
    int ret =0;
    char name[20] = "PRAVEEN";
    rv = table->bindFld("f1", &id1);
    if (rv != OK) ret = 1;
    rv  = table->bindFld("f2", &id2);
    if (rv != OK) ret = 2;
    rv  = table->bindFld("f2", &id3);
    if (rv != OK) ret = 3;
    conn.startTransaction();
    rv = table->insertTuple();
    conn.commit();
    conn.startTransaction();
    table->execute();
    char *tuple = (char*)table->fetch();
    int value = *(int*)((char*)tuple + 4);
    if (value !=8) ret = 5;
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}
