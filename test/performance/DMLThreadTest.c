#include<CSql.h>
#include<NanoTimer.h>
#define THREADS 5
void* runInsTest(void *p);
void* runSelTest(void *p);
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return -1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return -1;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    delete idxInfo;
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
    table->closeScan();
    conn.commit();


    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);
    int icount=0;
    for(int i = 0; i< 50000; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        valTerm = i;
        rv = table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL)  break;
        icount++;
        table->closeScan();
        conn.commit();
    }
    printf("Index Tuples found: %d\n", icount);



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
    DbRetVal rv = conn.open("root", "manager");
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
    char name[200] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    NanoTimer timer;
    int val = *(int*)message;
    int retrycnt=0;
    timer.start();
    for(i = val * 10000; i< (val *10000) +10000; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        retrycnt=0;
        while (ret == ErrLockTimeOut)  
        { 
            rv = conn.rollback();
            if (rv != OK)  {
                while (rv == ErrLockTimeOut) 
                {
                    printf("retrying abort\n");
                    rv = conn.rollback();
                }
            }
            if (retrycnt == 3) { ret = 1; break;}
            rv = conn.startTransaction();
            if (rv != OK) {
                while (rv == ErrLockTimeOut) 
                {
                    printf("retrying startTransaction\n");
                    rv = conn.startTransaction();
                }
            }
            ret = table->insertTuple(); 
            retrycnt++;
            //ret =1; break; //temp to analyse issue
        }
        if (ret != 0) { printf("RETURNING EARLY: %d with i:%d\n", ret, i); break;}
        icount++;
        rv = conn.commit();
        if (rv != OK) {
            printf("COMMIT returned %d\n", rv);
            os::usleep(500);
            while (rv == ErrLockTimeOut) { 
                printf("retrying commit\n");
                rv = conn.commit();
            }
        }
        //if (icount %10000 ==0) printf("%d\n", i);
    }
    timer.stop();
   char msgBuf[1024];
   sprintf(msgBuf,"Insert: Thread %lu %d: Total rows :%d Time taken:%lld ms\n",os::getthrid(), val, icount, timer.avg()/1000/1000);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table); 
   rv  = conn.close();
   return NULL;
}
void* runSelTest(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
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
        if (rv != OK) {
            printf("Execute returned %d\n", rv);
            os::usleep(500);
            int retry=5;
            while (rv == ErrLockTimeOut) { 
                if (retry == 0) break;
                printf("retrying execute\n");
                rv = table->execute();
                retry--;
            }
        }
        tuple = (char*)table->fetch() ;
        if (tuple == NULL)  break;
        icount++;
        table->closeScan();
        rv = conn.commit();
        if (rv != OK) {
            while (rv == ErrLockTimeOut) { 
                printf("retrying commit\n");
                rv = conn.commit();
            }
        }
    }

   timer.stop();
   char msgBuf[1024];
   sprintf(msgBuf,"Select: Thread %lu %d: Total rows :%d Time taken:%lld ms\n",os::getthrid(), val, icount, timer.avg()/1000/1000);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table);
   rv  = conn.close();
   return NULL;
}

