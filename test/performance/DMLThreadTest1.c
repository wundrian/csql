/*  create 't1' table with two fields f11 int, f12 char,
 *  create 3 threads and each one insert 1000 records in the table.
 *
 *  AUTHOR : Jitendra Lenka
 */ 
#include<CSql.h>
#define THREADS 3 

void *runInsTest(void *p);
void runSelTest(void *p);
int main()
{
   Connection conn;
   DbRetVal rv = conn.open("root","manager");
   if(rv!=OK)
   {
      printf("Error during connection %d\n",rv);
      return -1;
   }

   DatabaseManager *dbMgr = conn.getDatabaseManager();
   if(dbMgr ==NULL)
   {
      printf("Auth failed\n");
      return -2;
   }
   TableDef tabDef;
   tabDef.addField("f11",typeInt,0,NULL,true);
   tabDef.addField("f12",typeString,1020);
   
   rv = dbMgr->createTable("t1",tabDef);
   if(rv!=OK)
   {
     printf("Table creation failed\n");
     return -3;
   }

   // thread creation
   pthread_t thr[THREADS];
   int message[THREADS];
   int status;
   for(int i=0;i<THREADS;i++)
   {
	message[i]=i;
        pthread_create(&thr[i],NULL,&runInsTest,(void*)&message[i]);
   }
   for(int i=0;i<THREADS;i++)
   {
      pthread_join(thr[i],(void**)&status);
   }
   
   dbMgr->dropTable("t1");
   conn.close();
   return 0;
}

void* runInsTest(void *message)
{
	Connection conn;
        DbRetVal rv = conn.open("root","manager");
	if(rv!=OK)
	{
	  printf("Error during connection %d \n",rv);
	  return NULL;
        }
	DatabaseManager *dbMgr = conn.getDatabaseManager();
	if(dbMgr ==NULL)
	{
	  printf("Auth failed\n");
	  return NULL;
	}
	Table *table = dbMgr->openTable("t1");
	if(table == NULL)
	{
	  printf("Unable to open table\n");
	  return NULL;
	}

	int id=0;
	char name[1020] = "LAKSHYA";
	table->bindFld("f11",&id);
	table->bindFld("f12",name);

	char *tuple;
	int ret;
	int i;
	int count = 0;
	int val = *(int*)message;
	for(i=val*1000; i<(val*1000)+1000;i++)
	{
	   rv = conn.startTransaction();
	   //if(rv!=OK)return 1;
	   id = i;
           strcpy(name,"LAKSHYA SOLUTIONS");
	   ret = table->insertTuple();
           if(ret !=0)break;

           count++;
	   conn.commit();
	   
         }

	printf("Thread :%d Inserted :%d records.\n",val,count);
	dbMgr->closeTable(table);
	rv = conn.close();
	return NULL;
  }  
