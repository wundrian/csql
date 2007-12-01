//Testing OR operator with all comparision operator on int data type.
//Five tuples are inserted and then selected by setting predicates
//with OR operator

#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    if ( createTable(dbMgr) != 0 ) { conn.close(); return 3; }
#ifdef WITHF1INDEX
    if (createIndex(dbMgr, "f1", "idx1") != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif

#ifdef WITHF2INDEX
    if (createIndex(dbMgr, "f2", "idx2" ) != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif

    int inscount =  insertTuple(dbMgr, conn);
    //check the inscount and return error

    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }


    Condition p1,p2,p3,p4,p5;
    int val1 = 2, val2 = 3, val3 = 4;
    p1.setTerm("f1", OpEquals, &val3);
    p2.setTerm("f2", OpGreaterThan, &val2);
    p3.setTerm("f2", OpEquals, &val3);
    p4.setTerm("f1", OpLessThan, &val3);
    p5.setTerm("f1", OpGreaterThan, &val1);


    Condition cond1;
    cond1.setTerm(p1.getPredicate(), OpOr, p2.getPredicate());
    table->setCondition(&cond1);
    printf("Predicate: f1 ==4 OR f2 >3 \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond2;
    cond2.setTerm(p1.getPredicate(), OpOr, p3.getPredicate());
    table->setCondition(&cond2);
    printf("Predicate: f1 ==4 OR f2 ==4 \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond3;
    cond3.setTerm(p4.getPredicate(), OpOr, p5.getPredicate());
    table->setCondition(&cond3);
    printf("Predicate: f1 <4 OR f2 >2 \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();


    Condition cond4;
    cond4.setTerm(p4.getPredicate(), OpOr, p2.getPredicate());
    table->setCondition(&cond4);
    printf("Predicate: f1 <4 OR f2 >3 \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;

}

