#include<CSql.h>
#include<NanoTimer.h>
#include<TableImpl.h>
//MAX_SYS_DB_SIZE=10485760
//MAX_DB_SIZE=335544320
//you may have to set the kernel.shmmax kernel paremeter(login as root) using 
//$sysctl -w kernel.shmmax=1000000000
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
    tabDef.addField("f2", typeString, 6);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    idxInfo->bucketSize = 100007;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id = 0;
    char name[6] = "PRABA";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    i = 0; 
    NanoTimer timer;
    icount =0;
    for(i = 0; i < 20; i++)
    {
        timer.start();
        for (int j =0; j < 100000; j++)
        {
            rv = conn.startTransaction();
            if (rv != OK) exit(1);
            id= i*100000+j;
            strcpy(name, "KARAN");
            ret = table->insertTuple();
            if (ret != 0) break;
            icount++;
            conn.commit();
        }
        timer.stop();
        printf("Insert: %d %lld\n", icount, timer.last());
    }
   printf("%d rows inserted %lld %lld %lld\n",icount, timer.min(), timer.max(), timer.avg());

    int offset1= os::align(sizeof(int));
    Condition p1;
    int val1 = 0;
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    icount=0;
   

    timer.reset();
    for(i = 0; i< 20; i++)
    {    
        timer.start();
        for (int j=0 ; j <100000; j++)
        {
            rv =conn.startTransaction();
            if (rv != OK) exit(1);
            val1 = i *100000 + j;
            table->execute();
            tuple = (char*)table->fetch() ;
            if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
    //    printf(" %d tuple value is %d %s \n", i, *((int*)tuple), tuple+offset1);
            table->close();
            icount++;
            conn.commit();
        }
        timer.stop();
        printf("Select: %d %lld\n", icount, timer.last());
    }
    printf("%d rows selected %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());
    timer.reset();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    printf("Table dropped\n");


    conn.close();
    return 0;
}
