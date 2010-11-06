/*
  close the connection and call commit, it should fail
  close the connection and call rollback, it should fail.
*/

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK) {
	delete con;
	return 1;
    }
    printf("Connection opened\n");

    rv = con->beginTrans();
    if(rv!=OK) {
	con->disconnect();
	delete con;
	return 2;
    }
 
   rv = con->disconnect();
    if(rv !=OK) {
	delete con;
	return 3;
    }
    printf("Connection closed\n");

    rv = con->commit();
    if(rv==OK) {
        printf("Test script failed\n");
	delete con;
        return 4;
    }
    printf("Commit Failed After closing connection,\n");

    rv = con->rollback();
    if(rv==OK) {
        printf("Test script failed\n");
	delete con;
        return 4;
    }
    printf("Rollback Failed After closing connection,\n");

    printf("Test script pased\n");
    delete con;
    return 0;
}
