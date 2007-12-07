//Delete a tuple in a transaction and abort it
//scan should not display the inserted tuple.

#include<CSql.h>
int main()
{
   Connection conn;
   DbRetVal rv = conn.open("root", "manager");
   if (rv != OK) { printf("Unable  to open database\n"); return 1;}
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
   char name[196] = "ARVIND KOTHI";
   table->bindFld("f1", &id);
   table->bindFld("f2", name);
   int i;
   for (i=0; i<10; i++)
   {
      id=i;
      conn.startTransaction();
      rv = table->insertTuple();
      if (rv != OK)
      {
           printf("Insertion failed at %d th tuple", i+1);
           dbMgr->closeTable(table);
           dbMgr->dropTable("t1");
           return 5;
      }
      conn.commit();
    }
    printf("%d tuples are inserted into the dababase\n", i);
 
    conn.startTransaction();
    Condition p;
    int val = 3;
    p.setTerm("f1", OpEquals, &val);
    table->setCondition(&p);
    table->execute();
    void *tuple;
    while(true)
    {
       tuple=(char*)table->fetch();
       if (tuple == NULL) break;
      // strcpy(name,"Kanchana");
       rv = table->deleteTuple(); 
       if (rv != OK)
       {
           printf("Deletion failed ");
           dbMgr->closeTable(table);
           dbMgr->dropTable("t1");
           return 6;
       }
     //  printf("Updated tuple value is %d %s",id,name);
    }
    table->close();
    conn.rollback();
    table->setCondition(NULL);
    table->execute();
    while(true)
    {
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {break;}
        printf("\nBinded Tuple value is %d %s", id, name);
    }

    table->close();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}

 
