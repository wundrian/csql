//create table t1(f1 int,f2 int)
//create index idx1 on t1(f1)
//create index idx2 on t1(f2)
//insert null records for f2 and check whether the system is stable after that.

#include<CSql.h>
#include"common.h"
int main()
{
    Connection conn;
    DbRetVal rv=conn.open("root","manager");
    if(rv != OK) return 1;
    DatabaseManager *dbmgr=conn.getDatabaseManager();
    if(dbmgr == NULL) { printf("Authentication Failed\n"); return 2; }
    
    if( creatTable(dbmgr) !=0 ) { conn.close(); return 3; }
    if( createIndex(dbmgr) != 0 ) { dbmgr->dropTable("t1"); conn.close(); return 4; }
    int flag = insertTuplef2NUL(dbmgr,conn);
    if( flag != 0 ) { dbmgr->dropTable("t1"); conn.close(); return 5; }
    dbmgr->dropTable("t1");
    conn.close();
    return 0;
}
