/*
  Pass correct username and incorrect password, it should fail.
  Pass incorrect user name, it should fail.
  Pass correct username and correct password, Connection should be established.
*/

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
//Incorrect Password 
    rv = con->connect("root","manager123");
    if(rv==OK) {
        printf("Test script failed with error%d\n",rv);
        con->disconnect();
        delete con;
        return 1;
    }
    printf("Connection is not opened due to Incorrect password\n");
//Incorrect user name 
    rv = con->connect("root123","manager");
    if(rv==OK) {
        printf("Test script failed with error%d\n",rv);
        con->disconnect();
        delete con;
        return 2;
    }
    printf("Connection is not opened due to Incorrect Username\n");
//Correct user name and correct password
    rv = con->connect("root","manager");
    if(rv!=OK) {
        printf("Test script failed with error%d\n",rv);
        delete con;
        return 3;
    }
    printf("Connection is opened with correct Username and password\n");

    con->disconnect();
    delete con;
    return 0;
}
