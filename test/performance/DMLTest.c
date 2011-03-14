#include<CSql.h>
#include<NanoTimer.h>
#include<TableImpl.h>
#define ITERATIONS 100
//#define LOAD 1000000
//Note: Set following parameters in csql.conf for this test
//MAX_SYS_DB_SIZE=10485760
//MAX_DB_SIZE=335544320
//you may have to set the kernel.shmmaxc kernel paremeter(login as root) using 
//$sysctl -w kernel.shmmaxc=1000000000
#define LOAD 0
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
    tabDef.addField("f1", typeInt, 0, NULL, true );
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    if (LOAD >0 )
       idxInfo->bucketSize = 100007;
    else
       idxInfo->bucketSize = 10007;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id = 0;
    char name[196] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    if (LOAD > 0) {
      TableImpl *impl = (TableImpl*)table;
      impl->setUndoLogging(false);
      strcpy(name, "PRABAKARAN0123456750590");
      rv = conn.startTransaction();
      if (rv != OK) exit(1);
      for(i = 0; i< LOAD; i++)
      {
        id= i;
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
        if (i % 100 == 0 ) { rv = conn.commit(); 
                             if (rv != OK) exit(1);
                             rv = conn.startTransaction(); 
                             if (rv != OK) exit(1);
                           }
        if (i %50000 == 0) printf("%d rows inserted\n", i);
      }
      conn.commit();
      impl->setUndoLogging(true);
      printf("Loaded %d records\n", icount);
    }
   
      //TableImpl *impl = (TableImpl*)table;
      //impl->setUndoLogging(false);
    i = 0; 
    NanoTimer timer;
    icount =0;
    for(i = LOAD; i< LOAD+ITERATIONS; i++)
    {
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit(1);
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        if (ret != 0) break;
    //    printf("%d\n ", i);
        icount++;
        conn.commit();
        timer.stop();
    }
   printf("%d rows inserted %lld %lld %lld\n",icount, timer.minc(), timer.maxc(), timer.avg());

    int offset1= os::align(sizeof(int));
    Condition p1;
    int val1 = 0;
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    icount=0;
   

    timer.reset();
    for(i = LOAD; i< LOAD+ITERATIONS; i++)
    {    
        timer.start();
        rv =conn.startTransaction();
        if (rv != OK) exit(1);
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->closeScan();break;}
  //      printf(" %d tuple value is %d %s \n", i, *((int*)tuple), tuple+offset1);
        table->closeScan();
        icount++;
        conn.commit();
        timer.stop();
    }
    printf("%d rows selected %lld %lld %lld\n", icount, timer.minc(), timer.maxc(), timer.avg());
    timer.reset();

    for(i = LOAD; i< LOAD+ITERATIONS; i++)
    {
        timer.start();
        rv  = conn.startTransaction();
        if (rv != OK) exit (1);
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->closeScan();break;}
        strcpy(name, "PRABAKARAN0950576543210");
        table->updateTuple();
        table->closeScan();
        conn.commit();
        timer.stop();
    }
    printf("%d rows updated %lld %lld %lld\n", i- LOAD, timer.minc(), timer.maxc(), timer.avg());


    icount=0;
    for(i = LOAD; i< LOAD+ITERATIONS; i++)
    {
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit (1);
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("No record for %d\n", i);table->closeScan();break;}
        table->deleteTuple();
        icount++;
        table->closeScan();
        conn.commit();
        timer.stop();
    }
    printf("%d rows deleted %lld %lld %lld\n", icount, timer.minc(), timer.maxc(), timer.avg());


    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    printf("Table dropped\n");

    conn.close();
    return 0;
}
