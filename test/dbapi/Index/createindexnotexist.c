#include<CSql.h>
//creating index with non existing field
//It should fail
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("notexist");
    idxInfo->indType = hashIndex;
#ifdef TREEINDEX
    idxInfo->indType = treeIndex;
#endif
    int ret =0;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv == OK) ret =1;
    delete idxInfo;
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}
