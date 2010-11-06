/*   call execute without calling prepare. it should fail.
*/

#include "common.h"
int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"INSERT INTO t1 VALUES (1, 'jitendra');");
    if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"INSERT INTO t1 VALUES (1, 'jitendra')");
    int rows=0;
    rv  = stmt->execute(rows);
    if(rv!=OK) { 
        delete stmt; 
        delete con;         
        printf("Test script passed\n"); 
        return 0;
    }
    stmt->free();
    printf("Test script failed\n");
    delete stmt;
    delete con;
    return 1;
}
