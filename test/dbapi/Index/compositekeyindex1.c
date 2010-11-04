#include<CSql.h>
//creating index with two fields
//It should be Passed
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
    tabDef.addField("f1", typeInt);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->list.append("f2");
    idxInfo->indType = hashIndex;
#ifdef TREEINDEX
    idxInfo->indType = treeIndex;
#endif
    rv = dbMgr->createIndex("indx1", idxInfo);
#ifdef TREEINDEX
    if(rv == OK) { printf("Composite Index creation Passed\n"); return 1; } 
    printf("Composite Index failed as expected\n");
#else
    if(rv != OK) { printf("Composite Index creation Failed\n"); return 1; } 
    printf("Composite Index created\n");
#endif
    delete idxInfo;
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
