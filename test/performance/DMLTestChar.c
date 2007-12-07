#include<CSql.h>
#include<NanoTimer.h>
#define ITERATIONS 100
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
    tabDef.addField("f1", typeString, 50, NULL, true);
    tabDef.addField("f2", typeString, 950);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return -1; }
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return -1; }
    int id = 0;
    char f1[50] = "PRABAKARAN";
    char f2[950] = "Static Data is stored here";
    table->bindFld("f1", f1);
    table->bindFld("f2", f2);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    NanoTimer timer;
    for(i = 0; i< ITERATIONS; i++)
    {
        sprintf(f1, "PRABAKARAN%d", i);
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit(1);
        //printf("%d\n ", i);
        ret = table->insertTuple();
        if (ret != 0) break;
        icount++;
        conn.commit();
        timer.stop();
    }
   char msgBuf[1024];
   sprintf(msgBuf,"Total rows inserted %d %lld %lld %lld\n",icount, timer.min(), timer.max(), timer.avg());
   os::write(1,msgBuf,strlen(msgBuf));

    int offset= os::align(50);
    Condition p1;
    char val1[50];
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(&p1);
    icount=0;
    timer.reset();
    for(i = 0; i< ITERATIONS; i++)
    {    
        sprintf(val1, "PRABAKARAN%d", i);
        timer.start();
        rv =conn.startTransaction();
        if (rv != OK) exit(1);
        table->execute();
        tuple = (char*)table->fetch();
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        //printf("Select f1 = %s, f2=%s\n", tuple, tuple + offset);
        table->close();
        icount++;
        conn.commit();
        timer.stop();
    }
    sprintf(msgBuf,"%d rows selected %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());
    os::write(1,msgBuf,strlen(msgBuf));
    timer.reset();
    for(i = 0; i< ITERATIONS; i++)
    {
        sprintf(val1, "PRABAKARAN%d", i);
        timer.start();
        rv  = conn.startTransaction();
        if (rv != OK) exit (1);
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        strcpy(f2, "PRABAKARAN0950576543210");
        table->updateTuple();
        table->close();
        conn.commit();
        timer.stop();
    }
    sprintf(msgBuf,"%d rows updated %lld %lld %lld\n", i, timer.min(), timer.max(), timer.avg());
    os::write(1,msgBuf,strlen(msgBuf));
    icount=0;
    for(i = 0; i< ITERATIONS; i++)
    {
        sprintf(val1, "PRABAKARAN%d", i);
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit (1);
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        //printf("Before delete f1 = %s, f2=%s\n", tuple, tuple + offset);
        table->deleteTuple();
        icount++;
        table->close();
        conn.commit();
        timer.stop();
    }
    printf("%d rows deleted %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());
    int count =0;
    timer.reset();
    for(i = 0; i< ITERATIONS; i++)
    {
        sprintf(val1, "PRABAKARAN%d", i);
        rv = conn.startTransaction();
        if (rv != OK) exit (1);
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        //printf("tuple value is %d %s \n", *((int*)tuple), tuple+offset);
        count++;
        table->close();
        conn.commit();
    }
    printf("Total rows selected %d\n", count);


    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
