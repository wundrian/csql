//#include <NanoTimer.h>
//TestCase: It creates 5 threads and all threads insert ITERATION records simultanesouly.
//after insertion, it checks whether 50000 records are there in the table
//after that, 5 threads select 10K records each simultanesouly.
//verify that 10K records are selected in each thread.
//The test is repeated with no index, hash index and tree index
#include<CSql.h>
#define THREADS 5
#define ITERATION 25000
void* runInsTest(void *p);
void* runSelTest(void *p);
void* runDelTest(void *p);
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
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeString, 12);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isPrimary = true;
    idxInfo->isUnique = true;
#ifdef HASH
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
#endif
#ifdef TREE
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
#endif
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

#ifdef HASH
    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);
    int icount=0;
    for(int i = 0; i< THREADS * ITERATION; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        valTerm = i+1;
        rv = table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL)  break;
        icount++;
        table->closeScan();
        conn.commit();
        //if (i%ITERATION == 0) printf("%d\n", i);
    }
    printf("Index Tuples found: %d\n", icount);
#endif



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
    char name[20] = "PRABAKARAN";
    //table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    int val = *(int*)message;
    int retrycnt=0;
    for(i = val * ITERATION; i< (val *ITERATION) +ITERATION; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        id= i;
        strcpy(name, "KARAN123");
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
        //if (icount %ITERATION ==0) printf("%d\n", i);
    }
   char msgBuf[1024];
   sprintf(msgBuf,"Insert: Thread %lu %d: Total rows :%d\n",os::getthrid(), val, icount);
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
    int val = *(int*)message;

    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);

    for(i = val * ITERATION; i< (val *ITERATION) +ITERATION; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        valTerm = i;
        if (valTerm ==0) valTerm=1;
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

   char msgBuf[1024];
   sprintf(msgBuf,"Select: Thread %lu %d: Total rows :%d\n",os::getthrid(), val, icount);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table);
   rv  = conn.close();
   return NULL;
}
void* runDelTest(void *message)
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
    char name[20] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int i;
    int ret;
    int retrycnt=0;
    int icount =0;
    int val = *(int*)message;

    Condition p1;
    int valTerm = 0;
    p1.setTerm("f1", OpEquals, &valTerm);
    table->setCondition(&p1);

    for(i = val * ITERATION; i< (val *ITERATION) +ITERATION; i++)
    {
        rv = conn.startTransaction();
        if (rv != OK) while (rv !=OK) rv = conn.startTransaction();
        id= i;
        valTerm = i;
        rv = table->execute();
        if (rv != OK) {
            printf("Execute returned %d\n", rv);
            os::usleep(500);
            int retry=5;
            while (rv == ErrLockTimeOut) {
                if (retry == 0) { printf("DELETE:execute failed\n"); break;}
                printf("retrying execute\n");
                rv = table->execute();
                retry--;
            }
        }
        tuple = (char*)table->fetch() ;
        if (tuple == NULL)  { printf("DELETE:fetch failed\n");break;}
        ret = table->deleteTuple();
        retrycnt=0;
        while (ret == ErrLockTimeOut)
        {
           table->closeScan();
            rv = conn.rollback();
            if (rv != OK)  {
                while (rv == ErrLockTimeOut)
                {
                    printf("retrying abort\n");
                    rv = conn.rollback();
                }
            }
            if (retrycnt == 10) { ret = 1; break;}
            rv = conn.startTransaction();
            if (rv != OK) {
                while (rv == ErrLockTimeOut)
                {
                    printf("retrying startTransaction\n");
                    rv = conn.startTransaction();
                }
            }
            rv = table->execute();
            if (rv != OK) {
                printf("Execute returned %d\n", rv);
                os::usleep(500);
                int retry=5;
                while (rv == ErrLockTimeOut) {
                   if (retry == 0) { printf("DELETE:execute failed\n"); break;}
                   printf("retrying execute\n");
                   rv = table->execute();
                   retry--;
                }
            }
            tuple = (char*)table->fetch() ;
            if (tuple == NULL)  { printf("DELETE:fetch failed\n");break;}
            ret = table->deleteTuple();
            retrycnt++;
        }
        if (ret != 0) { printf("RETURNING EARLY: %d with i:%d\n", ret, i); break;}
        table->closeScan();
        rv = conn.commit();
        if (rv != OK) {
            printf("COMMIT returned %d for record %d\n", rv, i);
            if (rv != ErrLockTimeOut)
            {
                printf("RETURNING EARLY: with i:%d\n", i);
                break;
            }

            os::usleep(500);
            while (rv == ErrLockTimeOut) {
                printf("retrying commit\n");
                rv = conn.commit();
            }
        }
        icount++;
    }
   char msgBuf[1024];
   sprintf(msgBuf,"Delete: Thread %lu %d: Total rows :%d\n",os::getthrid(), val, icount);
   os::write(1,msgBuf,strlen(msgBuf));
   dbMgr->closeTable(table);
   rv  = conn.close();
   return NULL;
}


