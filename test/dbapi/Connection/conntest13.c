//In a transaction mix insert, update and delete a tuple.
//All should take effect in a transaction

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
   char name[196] = "PRABAKARAN";
   table->bindFld("f1", &id);
   table->bindFld("f2", name);
   int i;
  // int icount =0;

   conn.startTransaction();
  
   //Inserts 10 tuples into the table
   for (i=0; i<10; i++)
   {
       id = i;
       rv = table->insertTuple();
       if (rv != OK)
       {
           printf("Insertion failed\n");
           dbMgr->dropTable("t1");
           conn.close();
           return 5;
       }
       //icount++;
   }
   printf("%d tuples are inserted into the dababase\n", i);

   //Updates the tuple having f1=5
   Condition p1;
   int val1 = 5;
   p1.setTerm("f1",OpEquals, &val1);
   table->setCondition(&p1);
   rv=table->execute();
   if (rv != OK)
   {
      dbMgr->closeTable(table);
      dbMgr->dropTable("t1");
      conn.close();
      return 4;   
   }
   void *tuple;
   while(true)
   {
       tuple = (char*)table->fetch() ;
       if (tuple == NULL) { break; }
       strcpy(name,"Kanchana");
       rv = table->updateTuple();
       if (rv != OK)
       {
          printf("Error during updation");
          dbMgr->closeTable(table);
          dbMgr->dropTable("t1");
          conn.close();
          return 5;   
       }
   }
   table->close();
   printf("Updated successfully\n");
   
  //Delets the tuple having f1=8 
   table->setCondition(NULL);
   val1 = 8;
   p1.setTerm("f1",OpEquals, &val1);
   table->setCondition(&p1);
   rv=table->execute();
   if (rv != OK)
   {
      dbMgr->closeTable(table);
      dbMgr->dropTable("t1");
      conn.close();
      return 4;   
   }

   while(true)
   {
       tuple = (char*)table->fetch() ;
       if (tuple == NULL) { break; }
       rv = table->deleteTuple();
       if (rv != OK)
       {
          printf("Error during deletion");
          dbMgr->closeTable(table);
          dbMgr->dropTable("t1");
          conn.close();
          return 6;   
       }
   }
   table->close();
   printf("Deleted successfully");

   conn.commit();

   conn.startTransaction();
   //Displays the database after the transaction 
   table->setCondition(NULL);
   table->execute();
   while(true)
   {
       tuple = (char*)table->fetch() ;
       if (tuple == NULL) {break;}
       printf("\nBinded Tuple value is %d %s", id, name);
   }
   conn.commit();

   table->close();
   dbMgr->closeTable(table);
   dbMgr->dropTable("t1");
   conn.close();
   return 0;
}
