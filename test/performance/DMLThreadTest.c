#include<CSql.h>
#include<NanoTimer.h>
#define THREADS 2
void* runTest(void *p);
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created %d %lu\n", os::getpid(), os::getthrid());

    pthread_t thr[THREADS];
    int message[THREADS];
    int status;
    for (int i=0; i <THREADS; i++) {
        message[i] = i;
        pthread_create (&thr[i], NULL,
                  &runTest, (void *) &message[i]);
                  //&runTest, NULL);
    }
    printf("All threads started\n");
    for (int i=0; i <THREADS; i++) {
        pthread_join(thr[i], (void**)&status);
    }
    //dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
void* runTest(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return NULL;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return NULL; }
    int id = 0;
    char name[196] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    NanoTimer timer;
    int val = *(int*)message;
    // int val = 0;
    //printf("PRABA::val in this thread %d is %d\n", val, os::getthrid());
    printf("PRABA::val in this thread %d is %lu\n", val, ::pthread_self());
    if (val == 0) sleep(1);
    for(i = val * 10; i< (val *10) +10; i++)
    {
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit(1);
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
        printf("%d %lu \n ", i, os::getthrid());
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
        conn.commit();
        timer.stop();
    }
   char msgBuf[1024];
   sprintf(msgBuf,"Total rows inserted %d %lld %lld %lld\n",icount, timer.min(), timer.max(), timer.avg());
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table); 
    rv  = conn.close();
    printf("connc closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    return NULL;
}