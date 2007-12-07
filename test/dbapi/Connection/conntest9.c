#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <CSql.h>
void* print_message_function (void *ptr);
int flag=0;
int main (int argc, char **argv)
{
  Connection conn;
  DbRetVal rv = conn.open("root","manager");
  printf ("Main open Returned %d\n", rv);
  pthread_t thread1, thread2;
  int message1 =1; 
  int message2 =2; 
  int status;

  pthread_create (&thread1, NULL,
		  &print_message_function, (void *) &message1);
  pthread_create (&thread2, NULL,
		  &print_message_function, (void *) &message2);

  pthread_join(thread1, (void **)&status);
  pthread_join(thread2, (void **)&status);


  DatabaseManager *dbMgr = conn.getDatabaseManager();
  if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
  dbMgr->dropTable("T1");
  dbMgr->dropTable("T2");

  rv = conn.close();
  printf ("Main Returned %d\n", rv);
  exit (0);
}


void* print_message_function(void *ptr)
{
    //if (flag == 0) {flag =1; sleep(2); }
    char tblname[20];
    sprintf(tblname, "T%d", *(int*)ptr );
    Connection conn;
    DbRetVal rv=conn.open("root","manager");
    printf("Thread Return value of open %d %d\n", rv, getpid());
    if(rv!=OK)
    {
      return NULL;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}


    TableDef tabDef;
    tabDef.addField("f1", typeInt);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable(tblname, tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return NULL; }
    printf("Table created\n");

    rv = conn.close();
    printf("Thread Return value of close %d %d\n", rv, getpid());
}
