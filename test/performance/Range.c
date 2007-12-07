#include<CSql.h>
#include<NanoTimer.h>
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
    printf("Table created\n");
    //HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    //strcpy(idxInfo->tableName, "t1");
    //idxInfo->list.append("f1");
    //idxInfo->indType = hashIndex;
    //rv = dbMgr->createIndex("indx1", idxInfo);
    //if (rv != OK) { printf("Index creation failed\n"); return -1; }
    //printf("Index created\n");
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
    NanoTimer timer;
    for(i = 0; i< 1000; i++)
    {
        timer.start();
        rv = conn.startTransaction();
        if (rv != OK) exit(1);
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
    p1.setTerm("f1", OpGreaterThan, &val1);
    table->setCondition(&p1);
    icount=0;
    timer.reset();
    val1 = 899;
    for(i = 0; i< 100; i++)
    {    
        int cnt = 0;
        timer.start();
        rv =conn.startTransaction();
        if (rv != OK) exit(1);
        table->execute();
        while ((tuple = (char*)table->fetch()) != NULL) {
            //printf("tuple value is %d %s \n", *((int*)tuple), tuple+offset1);
            cnt++;
        }
        if (cnt != 100) printf("Error in fetching %d\n", cnt);
        icount++;
        conn.commit();
        table->close();
        timer.stop();
    }
    sprintf(msgBuf,"%d rows selected %lld %lld %lld\n", icount, timer.min(), timer.max(), timer.avg());
    os::write(1,msgBuf,strlen(msgBuf));
    timer.reset();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
