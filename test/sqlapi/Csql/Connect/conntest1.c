/*  connect ,disconnect and again connect ,it should pass. 
*/
#include "common.h"

int main()
{
    DbRetVal rv =OK;
    AbsSqlConnection *con = createConnection();
// Connection 1st time
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    printf("Connection Opened\n");
    rv = con->disconnect();
    if(rv!=OK)return 2;
    printf("Connection Closed\n");
//  Connecting 2nd time 
    con = createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK) {
        printf("Test script failed \n");
        return 3;
    }
    printf("Connection Opened\n");
    con->disconnect();
    printf("Connection closed\n");
    printf("Test script passed\n");
    delete con;
    return 0;
}
