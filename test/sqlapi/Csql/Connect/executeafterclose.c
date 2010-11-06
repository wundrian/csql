/*
   close the connection and call execute,it should fail.
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

    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20)); ");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { 
	con->disconnect();
	delete stmt; 
	delete con; 
	return 2; 
    }
    printf("prepared successfully\n");

    rv = con->disconnect();
    if(rv!=OK) {
	delete con;
	return 3;
    }
    printf("Disconnect successfully\n");

    rv = stmt->execute(rows);
    if(rv == OK) {
        printf("Test script failed \n");
        delete stmt; return 4;
    }
    printf("Execute failed after closing Connection\n");
    stmt->free();
    printf("Test script passed\n");
    delete stmt; delete con;
    return 0;
}
