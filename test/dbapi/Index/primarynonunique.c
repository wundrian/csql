#include<CSql.h>
//creating index with primary attribute set but unique unset
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
    idxInfo->isUnique = false;
    idxInfo->isPrimary = true;
    rv = dbMgr->createIndex("indx1", idxInfo);
    int ret = 0;
    if (rv == OK) ret =1;
    delete idxInfo;
    dbMgr->dropTable("t1");
    conn.close();
    return ret;
}
