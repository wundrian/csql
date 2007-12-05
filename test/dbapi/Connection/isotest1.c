#include "common.h"
//READ_COMMITTED isolation testing
//T1 and T2 both inserting, T2 will fail saying unique key constraint

void* runTest1(void *p);
void* runTest2(void *p);
int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return 1; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    int ret = createTable(dbMgr);
    if (ret != 0) { return 1; }

    pthread_t thr[2];
    int *status1, *status2;
    pthread_create (&thr[0], NULL, &runTest1,  NULL);
    pthread_create (&thr[1], NULL, &runTest2,  NULL);
    printf("All threads started\n");

    pthread_join(thr[0], (void**)&status1);
    pthread_join(thr[1], (void**)&status2);
    dbMgr->dropTable("t1");
    conn.close();
    if (*status1 != 0 || *status2 != 0) return 1;
    return 0;
}
void* runTest1(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
#ifndef DEFAULT
    rv = conn.startTransaction(READ_COMMITTED);
#else
    rv = conn.startTransaction();
#endif
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    int *retval = new int();
    *retval = 0;

    rv = insert(dbMgr, 100, true);
    if (rv != OK) { printf("Test Failed:first thread failed to insert\n"); *retval = 1; }

    conn.commit();
    rv  = conn.close();
    printf("conn closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    pthread_exit(retval);
}
void* runTest2(void *message)
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return NULL;}
#ifndef DEFAULT
    rv = conn.startTransaction(READ_COMMITTED);
#else
    rv = conn.startTransaction();
#endif
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());

    int *retval = new int();
    *retval = 0;

    rv = insert(dbMgr, 100, false);
    if (rv == OK) { printf("Test Failed:second thread inserted\n"); *retval = 1; }

    conn.commit();
    rv  = conn.close();
    printf("conn closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    pthread_exit(retval);
}

