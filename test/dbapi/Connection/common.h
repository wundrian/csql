#include<CSql.h>
DbRetVal createTable(DatabaseManager *dbMgr)
{
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeString, 196);
    DbRetVal rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return ErrUnknown; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
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
    printf("Inserted tuple : %d %s\n", val, name);
    if (isSleep) ::sleep(5);
    dbMgr->closeTable(table);
    return OK;
}
DbRetVal select(DatabaseManager *dbMgr, int val, bool isSleep, bool checkUpd=false)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return ErrUnknown; }
    int id = 0;
    char name[196];
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    Condition p1;
    int val1 = val; 
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    char *tuple;
    DbRetVal rv = table->execute();
    if (rv != OK)  { dbMgr->closeTable(table); return ErrUnknown; }
    tuple = (char*)table->fetch() ;
    if (tuple == NULL) {
        printf("Tuple not found\n"); 
        dbMgr->closeTable(table); 
        return ErrUnknown; 
    }
    printf("ThreadID: %lu Tuple %d %s\n", os::getthrid(), id, name);
    if (isSleep) ::sleep(5);
    dbMgr->closeTable(table);
    if ( checkUpd && strcmp(name, "KANCHANA") != 0) return ErrUnknown;
    return OK;
}
DbRetVal update(DatabaseManager *dbMgr, int val, bool isSleep, char *updname = NULL)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return ErrUnknown; }
    int id = 0;
    char name[196];
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    Condition p1;
    int val1 = val;  
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    char *tuple;
    DbRetVal rv = table->execute();
    if (rv != OK)  { dbMgr->closeTable(table); return ErrUnknown; }
    tuple = (char*)table->fetch() ;
    if (tuple == NULL) {dbMgr->closeTable(table); return ErrUnknown; }
    if (!updname) strcpy(name, "KANCHANA");
    else strcpy(name, updname);
    rv = table->updateTuple(); 
    if (rv != OK) { dbMgr->closeTable(table); return ErrUnknown; }
    printf("ThreadID: %lu Updated Tuple %d %s\n", os::getthrid(), id, name);

    if (isSleep) ::sleep(2);
    dbMgr->closeTable(table);
    return OK;
}
DbRetVal remove(DatabaseManager *dbMgr, int val, bool isSleep)
{
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return ErrUnknown; }
    int id = 0;
    char name[196];
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    Condition p1;
    int val1 = val;  
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    char *tuple;
    DbRetVal rv = table->execute();
    if (rv != OK)  { dbMgr->closeTable(table); return ErrUnknown; }
    tuple = (char*)table->fetch() ;
    if (tuple == NULL) {dbMgr->closeTable(table); return ErrUnknown; }
    rv = table->deleteTuple(); 
    if (rv != OK) { dbMgr->closeTable(table); return ErrUnknown; }
    printf("ThreadID: %lu Deleted Tuple %d %s\n", os::getthrid(), id, name);

    if (isSleep) ::sleep(2);
    dbMgr->closeTable(table);
    return OK;
}


