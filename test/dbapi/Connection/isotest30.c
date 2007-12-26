#include "common.h"
//READ_REPEATABLE isolation testing 
//           T1                 T2
//        -------------------------
//         Read
//	        		Update
//         Read
// T1 should fail to get read lock
void* runTest1(void *p);
void* runTest2(void *p);
int selectDone =0, updateDone=0, select2Done=0;
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
    int *retval = new int();
    *retval = 0;
    rv = select(dbMgr, 100, true);
    if (rv != OK) { printf("Test Failed:first thread read failed \n"); *retval = 1; }
    selectDone = 1;
    while (updateDone !=1) ::sleep(1);
    rv = select(dbMgr, 100, true, true);
    if (rv != OK) { printf("Test Failed:first thread read failed %d \n", rv); *retval = 1; }
    select2Done=1;
    conn.commit();
    rv  = conn.close();
    pthread_exit(retval);
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
    while (selectDone !=1) ::sleep(1);
    int *retval = new int();
    *retval = 0;
    rv = update(dbMgr, 100, true);
    if (rv == OK) { printf("Test Failed:second thread updated\n"); *retval = 1; }
    updateDone = 1;
    while(select2Done !=1) ::sleep(1);
    conn.commit();
    conn.close();
    pthread_exit(retval);
}

