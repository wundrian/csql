/* 
  closing the connection twice with single connect.
  second close should fail because of connection is already closed. 
*/

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK) {
	delete con;
	return 1;
    }
    printf("Connection Opened\n");
//Closing Connection.
    rv = con->disconnect();
    if(rv !=OK) {
        delete con;
        return 2;
    }
    printf("Connection Closed\n");
//Closing Connection without connect.
    rv = con->disconnect();
    if(rv ==OK) {
        delete con;
        printf("Test script Failed\n");
        return 3;
    }
    printf("Closing Connection without connect failed");
    delete con;
    printf("Test Script Passed\n");
    return 0;
}   
