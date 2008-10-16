//addfield f1 int, addField f2 char(10), addField f3 int. 
//Check the getTupleSize() return value. It should be 20 
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    TableDef tabDef;
    
    tabDef.addField("f1", typeInt, 0, NULL, true);
    tabDef.addField("f2", typeString,10);
    tabDef.addField("f3", typeInt);
        
    dbMgr->createTable("t1", tabDef);
    printf("Table created\n");
    size_t sizeofTuple = os::align(tabDef.getTupleSize());
    printf("Size of 1 tuple is %d\n",sizeofTuple);
  
    dbMgr->dropTable("t1");
    conn.close();
    return 0;
}


