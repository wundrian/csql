//TestCase: We need to start new server to test this.
//the default db size set is not enough to test this
#include<CSql.h>
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
    
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return ErrUnknown; }
    delete idxInfo; 
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) 
    { 
        printf("Unable to open table\n"); 
        dbMgr->dropTable("t1");
        conn.close();
        return 2; 
    }
    int id1 = 0, id2 = 5;
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    int icount =0;
    for (int i = 0 ; i < 10000 ; i++)
    {
        conn.startTransaction();
        for (int j = 0 ; j < 100 ; j++) {
            id1= icount++;
            rv = table->insertTuple();
            if (rv != OK) break;
        }
        if (rv != OK) break;
        conn.commit();
    }
    printf("Tuples inserted %d\n", icount);
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
    }
    void *fld2ptr, *fld3ptr, *tuple;
    icount = 0; 
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        icount++;
    }
    table->closeScan();
    dbMgr->closeTable(table);
    conn.close();
    if (icount != 1000000) return 3;
    return 0;
}
