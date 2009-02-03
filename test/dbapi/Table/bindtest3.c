/*  create table with two fields f1(not null) and f2
 *  f1 field in not binded
 *  when fetching count variable should be zero. 

*  Author : Jitendra Lenka 
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
	  printf("Table creation failed\n");
          return 3;
        }
        printf("Table created\n");

	Table *table = dbMgr->openTable("t1");
	if(table == NULL)
	{
	   printf("Unable to open table\n");
	   dbMgr->dropTable("t1");
	   conn.close();
	   return -1;
	}

	int id1=0;
	table->bindFld("f2",&id1);          
	int count=0;
        for(int i=0;i<5;i++)
	{
	   conn.startTransaction();
	   id1=i;
	   rv = table->insertTuple();
	   if(rv!=OK)break;
           count++;
           conn.commit();
 	}

	printf("Total row inserted=%d\n",count);

        void *tuple, *fld;
        count=0;
        table->setCondition(NULL);
        rv = table->execute();
        if(rv!=OK)
	{
	  dbMgr->closeTable(table);
	  dbMgr->dropTable("t1");
          conn.close();
        }
        while(1)
	{
	   tuple = (char*)table->fetch();
	   if(tuple == NULL){break;}
	   fld = (char*)tuple + os::align(sizeof(int));
	   printf("Tuple value is %d %d\n",*((int*)tuple),*((int*)fld));
        }
        table->closeScan();
        dbMgr->closeTable(table);
	dbMgr->dropTable("t1");
	conn.close();
	return 0;
}
