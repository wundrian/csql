//Insert a tuple in a transaction and commit it
//scan should display the tuple 

#include<CSql.h>
#include<NanoTimer.h>
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return 1;
    }


    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return 4; }
    int id = 0;
    char name[196] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    int i;
    int icount =0;
    
    conn.startTransaction();
      rv = table->insertTuple();
      if (rv != OK) 
      {
         printf("Insertion failed \n");
         return 5;
      }
    conn.commit();
     
    conn.startTransaction();
    table->setCondition(NULL);
    rv = table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
       return 6;
    }
    void *fld2ptr, *tuple;

    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("Binded Tuple value is %d %s \n", id, name);

    }
    conn.commit();
    table->close();
    dbMgr->dropTable("t1");
    printf("test passed successfully");                      
    return 0;
}
