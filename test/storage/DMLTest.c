#include<CSql.h>
#include<NanoTimer.h>
int main()
{

    Connection conn;
    conn.open("praba", "manager");

    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 0;}
    TableDef tabDef;
    tabDef.addField("f1", typeInt, 0, NULL, true, true);
    tabDef.addField("f2", typeString, 196);
    dbMgr->createTable("t1", tabDef);
    printf("Table created\n");
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = hashIndex;
    dbMgr->createIndex("indx1", idxInfo);
    printf("Index created\n");
    Table *table = dbMgr->openTable("t1");

    int id = 0;
    char name[196] = "PRABAKARAN";
    table->bindFld("f1", &id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    int icount =0;
    NanoTimer timer;
    for(i = 0; i< 100; i++)
    {
        timer.start();
        conn.startTransaction();
        id= i;
        strcpy(name, "PRABAKARAN0123456750590");
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

    int offset1= os::align(sizeof(int));
    Condition p1;
    int val1 = 0;
    p1.setTerm("f1", OpEquals, &val1);
    table->setCondition(p1);
    icount=0;
    timer.reset();
    for(i = 0; i< 100; i++)
    {    
        timer.start();
        conn.startTransaction();
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        //printf("tuple value is %d %s \n", *((int*)tuple), tuple+offset1);
        table->close();
        icount++;
        conn.commit();
        timer.stop();
    }
    sprintf(msgBuf,"%d rows selected %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());
    os::write(1,msgBuf,strlen(msgBuf));
    timer.reset();
    for(i = 0; i< 100; i++)
    {
        timer.start();
        conn.startTransaction();
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        strcpy(name, "PRABAKARAN0950576543210");
        table->updateTuple();
        table->close();
        conn.commit();
        timer.stop();
    }
    sprintf(msgBuf,"%d rows updated %lld %lld %lld\n", i, timer.min(), timer.max(), timer.avg());
    os::write(1,msgBuf,strlen(msgBuf));
    icount=0;
    for(i = 0; i< 100; i++)
    {
        timer.start();
        conn.startTransaction();
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        table->deleteTuple();
        icount++;
        table->close();
        conn.commit();
        timer.stop();
    }
    printf("%d rows deleted %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());

    int count =0;
    timer.reset();
    for(i = 0; i< 100; i++)
    {    
        conn.startTransaction();
        val1 = i;
        table->execute();
        tuple = (char*)table->fetch() ;
        if (tuple == NULL) {printf("loop break in %d\n", i);table->close();break;}
        //printf("tuple value is %d %s \n", *((int*)tuple), tuple+offset1);
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
