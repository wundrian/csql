/*   call execute without calling prepare. it should fail.
     
 *   Author : Jitendra Lenka
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");
    int rows=0;
    rv  = stmt->execute(rows);
    if(rv!=OK) { 
        delete stmt; delete con; 
        printf("Execute failed without call prepare\n");
        return 0;
    }
    printf("Test script failed\n");
    stmt->free(); delete stmt; delete con;
    return 1;
}
