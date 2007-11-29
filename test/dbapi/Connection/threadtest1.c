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
  DbRetVal rv = conn.open("praba","manager");
  if (rv != 0) return 1;
  pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int status1, status2;
  pthread_create (&thread1, NULL,
		  &print_message_function, (void *) message1);
  pthread_create (&thread2, NULL,
		  &print_message_function, (void *) message2);

  pthread_join(thread1, (void **)&status1);
  pthread_join(thread2, (void **)&status2);
  rv = conn.close();
  if (rv != 0) return 2;

  if( 1 == (status1 + status2) ) return 0;
  else return -1;
}


void* print_message_function(void *ptr)
{
    //if (flag == 0) {flag =1; sleep(2); }
    Connection conn;
    DbRetVal rv=conn.open("praba","manager");
    if(rv!=OK)
    {
       printf("Thread Return value of open %d %d\n", rv, getpid());
       return NULL;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); conn.close(); return NULL;}

    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeInt);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); conn.close(); return (void*) 1; }
    printf("Table created %d %lu\n", os::getpid(), os::getthrid());

    rv = conn.close();
    if (rv != OK) { printf("Thread Return value of close %d %d\n", rv, getpid()); } 
    return NULL;
}
