/*  connect twice without closing the connection,
 *  second conection should return "user already logged in".

 *  Author : Jitendra lenka
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK)return 1;
    printf("Connection opened\n");
    rv = con->connect("root","manager");
    if(rv==OK) {
        printf("testscript failed\n");
        return 1;
    }
    printf("Test script passed\n");
    delete con;
    return 0;
}   
