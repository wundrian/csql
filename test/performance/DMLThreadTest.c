#include<CSql.h>
#include<NanoTimer.h>
#define THREADS 2
void* runInsTest(void *p);
void* runSelTest(void *p);
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
    tabDef.addField("f2", typeString, 1020);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }

    pthread_t thr[THREADS];
    int message[THREADS];
    int status;
    for (int i=0; i <THREADS; i++) {
        message[i] = i;
        pthread_create (&thr[i], NULL,
                  &runInsTest, (void *) &message[i]);
    }
    for (int i=0; i <THREADS; i++) {
        pthread_join(thr[i], (void**)&status);
    }
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    table->setCondition(NULL);
    rv = conn.startTransaction();
    if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
    table->execute();
    int count=0;
    void *tuple = NULL;
    while ((tuple = (char*) table->fetch())) {
         count++;
    }
    printf("Tuples found: %d\n", count);
    table->close();
    conn.commit();

    dbMgr->closeTable(table);

    for (int i=0; i <THREADS; i++) {
        message[i] = i;
        pthread_create (&thr[i], NULL,
                  &runSelTest, (void *) &message[i]);
    }
    for (int i=0; i <THREADS; i++) {
        pthread_join(thr[i], (void**)&status);
    }

    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}
void* runInsTest(void *message)
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
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return NULL; }
    int id = 0;
    char name[1020] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    NanoTimer timer;
    int val = *(int*)message;
    timer.start();
    for(i = val * 10000; i< (val *10000) +10000; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        while (ret == ErrLockTimeOut)  { ret = table->insertTuple(); }
        if (ret != 0) break;
        icount++;
        conn.commit();
        if (icount %10000 ==0) printf("%d\n", i);
    }
    timer.stop();
   char msgBuf[1024];
   sprintf(msgBuf,"Insert: Thread %d: Total rows :%d Time taken:%lld ms\n",val, icount, timer.avg()/1000/1000);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table); 
   rv  = conn.close();
   return NULL;
}
void* runSelTest(void *message)
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
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return NULL; }
    int id = 0;
    char name[1020] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int i;
    int icount =0;
    NanoTimer timer;
    int val = *(int*)message;

    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);

    timer.start();
    for(i = val * 10000; i< (val *10000) +10000; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        valTerm = i;
        rv = table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple != NULL) icount++;
        table->close();
        conn.commit();
    }

   timer.stop();
   char msgBuf[1024];
   sprintf(msgBuf,"Select: Thread %d: Total rows :%d Time taken:%lld ms\n",val, icount, timer.avg()/1000/1000);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table);
   rv  = conn.close();
   return NULL;
}

