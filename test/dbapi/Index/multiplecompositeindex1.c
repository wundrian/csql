// create table t1(f1 int,f2 int,f3 int)
// create composite index cmpidx on t1(f1,f2,f3)
// create composite index cmpidx1 on t1(f1,f2)
// create composite index cmpidx2 on t1(f2,f3);

#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root","manager");
    if(rv!=OK) 
    { 
	printf("Connection Failed with return value %d\n",rv); 
	return 1;
    }
    DatabaseManager *dbmgr=conn.getDatabaseManager();
    if(dbmgr==NULL) { printf("Authentication Failed\n"); return 2;}
    TableDef tabDef;
    tabDef.addField("f1",typeInt,0,NULL,true);
    tabDef.addField("f2",typeInt);
    tabDef.addField("f3",typeInt);
    rv=dbmgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
 
    HashIndexInitInfo *idx1 = new HashIndexInitInfo();
    strcpy(idx1->tableName, "t1");
    idx1->list.append("f1");
    idx1->list.append("f2");
    idx1->list.append("f3");
    idx1->indType = hashIndex;
    rv = dbmgr->createIndex("cmpidx", idx1);
    if(rv != OK) { printf("Composite Index creation Failed\n"); return 4; }
    printf("Composite Index 'cmpidx' created on t1(f1,f2,f3)\n");
    delete idx1;
    
    HashIndexInitInfo *idx2 = new HashIndexInitInfo();
    strcpy(idx2->tableName, "t1");
    idx2->list.append("f1");
    idx2->list.append("f2");
    idx2->indType = hashIndex;
    rv = dbmgr->createIndex("cmpidx1", idx2);
    if(rv != OK) { printf("Composite Index creation Failed\n"); return 5; }
    printf("Composite Index 'cmpidx1' created on t1(f1,f2)\n");
    delete idx2;
    
    HashIndexInitInfo *idx3 = new HashIndexInitInfo();
    strcpy(idx3->tableName, "t1");
    idx3->list.append("f2");
    idx3->list.append("f3");
    idx3->indType = hashIndex;
    rv = dbmgr->createIndex("cmpidx2", idx3);
    if(rv != OK) { printf("Composite Index creation Failed\n"); return 5; }
    printf("Composite Index 'cmpidx2' created on t1(f2,f3)\n");
    delete idx3;
     
    HashIndexInitInfo *idx4 = new HashIndexInitInfo();
    strcpy(idx4->tableName, "t1");
    idx4->list.append("f1");
    idx4->list.append("f3");
    idx4->indType = hashIndex;
    rv = dbmgr->createIndex("cmpidx3", idx4);
    if(rv != OK) { printf("Composite Index creation Failed\n"); return 5; }
    printf("Composite Index 'cmpidx3' created on t1(f1,f3)\n");
    delete idx4;
    dbmgr->dropTable("t1");
    conn.close();
    return 0;
}

    

    
    
    

