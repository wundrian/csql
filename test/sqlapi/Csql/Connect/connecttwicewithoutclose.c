/* 
  connect twice without closing the connection,
  second conection should return "user already logged in".
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
    printf("Connection opened\n");
    rv = con->connect("root","manager");
    if(rv==OK) {
        printf("Testscript failed\n");
        con->disconnect();
        delete con;
        return 2;
    }
    printf("Test script passed\n");
    con->disconnect();
    delete con;
    return 0;
}   
