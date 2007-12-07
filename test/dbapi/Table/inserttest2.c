//Test Case:
//Insert 1 million tuples. There will not be enough db space.
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
    tabDef.addField("f3", typeString, 1016);
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
    char name[20] = "PRAVEEN";
    table->bindFld("f1", &id1);
    table->bindFld("f2", &id2);
    table->bindFld("f3", name);
    int icount =0;
    for (int i = 0 ; i < 1000 ; i++)
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
        fld2ptr = (char*)tuple + os::align(sizeof(int));
        fld3ptr = (char*)tuple + (2 * os::align(sizeof(int)));
        icount++;
        if (icount == 10000) printf("Binded Tuple value is %d %d %s \n", id1, id2, name);

    }
    table->close();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
