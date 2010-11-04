#include "common.h"
//READ_REPEATABLE isolation testing 
// T1 and T2 both doing select for same tuple

void* runTest1(void *p);
void* runTest2(void *p);
int *p1RetVal = NULL;
int *p2RetVal = NULL;
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return 1; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    int ret = createTable(dbMgr);
    if (ret != 0) { return 1; }

    rv = conn.startTransaction();
    if (rv != OK) {printf ("Unable to start trans\n"); return 1; }
    rv = insert(dbMgr, 100, false);
    if (rv != OK) { printf("Unable to insert\n"); return 2; }
    conn.commit();
    printf("Tuple inserted\n");

    pthread_t thr[2];
    int *status1, *status2;
    pthread_create (&thr[0], NULL, &runTest1,  NULL);
    pthread_create (&thr[1], NULL, &runTest2,  NULL);
    printf("All threads started\n");

    pthread_join(thr[0], (void**)&status1);
    pthread_join(thr[1], (void**)&status2);
    ret = 0;
    if (*status1 != 0 || *status2 != 0) ret = 1;
    dbMgr->dropTable("t1");
    conn.close();
    if (p1RetVal) { delete p1RetVal; p1RetVal = NULL; }
    if (p2RetVal) { delete p2RetVal; p2RetVal = NULL; }
    return ret;
}
void* runTest1(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
    rv = conn.startTransaction(READ_REPEATABLE);
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    p1RetVal = new int();
    *p1RetVal = 0;
    rv = select(dbMgr, 100, true);
    if (rv != OK) { printf("Test Failed:first thread failed to select\n"); *p1RetVal = 1; }

    conn.commit();
    rv  = conn.close();
    pthread_exit(p1RetVal);
}
void* runTest2(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
    rv = conn.startTransaction(READ_REPEATABLE);
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());

    p2RetVal = new int();
    *p2RetVal = 0;
    rv = select(dbMgr, 100, false);
    if (rv != OK) { printf("Test Failed:second thread failed to select\n"); *p2RetVal = 1; }
    conn.commit();
    conn.close();
    pthread_exit(p2RetVal);
}

