/*  create table 't1' with two fields f1 int, f2 int.
 *  use spaceused() to know the size of the table,
 *  here the table size will be 16 bytes.
 *  
 *  AUTHOR : Jitendra Lenka
 */ 

#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root","manager");
    if(rv!=OK)return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if(dbMgr == NULL)
    {
       printf("Auth failed\n");
       return 2;
    }

    TableDef tabDef;
    tabDef.addField("f1",typeInt,0,NULL,true);
    tabDef.addField("f2",typeInt);
    
    rv = dbMgr->createTable("t1",tabDef);
    if(rv!=OK)
    {
      printf("Table created failed\n");
      conn.close();
      return 0;
    }

    
    Table *table = dbMgr->openTable("t1");
    long spaceused;
    spaceused = table->spaceUsed();
    printf("Total space used=%ld\n",spaceused);

   dbMgr->closeTable(table);
   dbMgr->dropTable("t1");
   conn.close();
   return 0;
}  	
