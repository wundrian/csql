//Testing OR with OR operator with all comparision operator on int data type.
//Five tuples are inserted and then selected by setting predicates

#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    if ( createTable(dbMgr) != 0 ) { conn.close(); return 3; }
    int inscount =  insertTuple(dbMgr, conn);
    //check the inscount and return error

    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }


    Condition p1,p2,p3,p4,p5;
    int val1 = 2, val2 = 3, val3 = 5;
    p1.setTerm("f1", OpEquals, &val2);
    p2.setTerm("f2", OpGreaterThan, &val1);
    p3.setTerm("f3", OpNotEquals, &val3);
    p4.setTerm("f4", OpLessThan, &val3);
    p5.setTerm("f5", OpGreaterThanEquals, &val2);


    Condition cond1, cond1a, cond1b, cond1c;
    cond1.setTerm(p1.getPredicate(), OpOr, p2.getPredicate());
    cond1a.setTerm(cond1.getPredicate(), OpOr, p3.getPredicate());
    cond1b.setTerm(cond1a.getPredicate(), OpOr, p4.getPredicate());
    cond1c.setTerm(cond1b.getPredicate(), OpOr, p5.getPredicate());
    table->setCondition(&cond1c);
    printf("Predicate: (f1 ==3 OR  f2 > 2 OR f3 !=5 OR f4 <5 OR f5 >=3 ) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond2, cond2a, cond2b;
    cond2.setTerm(p1.getPredicate(), OpOr, p2.getPredicate());
    cond2a.setTerm(p3.getPredicate(), OpOr, p4.getPredicate());
    cond2b.setTerm(cond2.getPredicate(), OpOr, cond2a.getPredicate());
    table->setCondition(&cond2b);
    printf("Predicate: (f1 ==3 OR  f2 > 2) OR (f3 !=5 OR f4 <5) ) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;

}

