//Update a tuple in a transation and commit it.
// Next scan should display the update tuple.

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
    if (table == NULL) { printf("Unable to open table\n"); return 3; }
    int id;
    char name[20]="PRABA";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    int icount = 0;
    int i;

    conn.startTransaction();
    for (i=0;i<10;i++)
    {
      id=i;
      rv=table->insertTuple();
      if(rv!=OK)
      {
         printf("Insertion failed at %d th tuple",i);
         dbMgr->closeTable(table);
         dbMgr->dropTable("t1");
         conn.close();
         return 4;
      }
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
    printf("Scan before Deletion\n"); 
    printf("********************\n");
    void *fld2ptr, *tuple;
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("Binded Tuple value is %d %s \n", id, name);

    }
    conn.commit();
    rv=table->close();
    if(rv!=OK){ printf("Error in closing the table\n"); return 3;}
 
    Condition p1;
    int val1 = 5;
    p1.setTerm("f1",OpEquals, &val1);
    table->setCondition(&p1);
    conn.startTransaction();
    rv=table->execute();
    if (rv != OK)
    {
       dbMgr->closeTable(table);
       dbMgr->dropTable("t1");
       conn.close();
       return 4;   
    }

//    char *tuple; 
    //printf("Scan After:\n");
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) { break; }
        //strcpy(name,"Kanchana");
        table->deleteTuple();
    }
   conn.commit();
   table->close(); 


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
    printf("Scan After Deletion\n");
    printf("********************\n");
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("Binded Tuple value is %d %s \n", id, name);

    }
    conn.commit();

    //unset the condtion set as we need to delete all rows
    table->setCondition(NULL);
    table->close();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    printf("Test script passed ");
    return 0;
}
