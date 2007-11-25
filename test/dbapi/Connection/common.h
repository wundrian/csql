#include<CSql.h>
DbRetVal createTable(DatabaseManager *dbMgr)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeString, 196);
    DbRetVal rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return ErrUnknown; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return ErrUnknown; }
    return OK;
}
DbRetVal insert(DatabaseManager *dbMgr, int val, bool isSleep)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return ErrUnknown; }
    int id = val ;
    char name[196] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    ret = table->insertTuple();
    if (ret != 0)  return ErrLockTimeOut;
    if (isSleep) ::sleep(2);
    dbMgr->closeTable(table);
    return OK;
}
