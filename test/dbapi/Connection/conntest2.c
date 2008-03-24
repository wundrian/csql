// Make sure the server is not running

#include<CSql.h>

int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
	if (rv == OK) {
		printf("The server must be running. Stop the server and rerun the test\n");
		printf("Test failed\n");
		return 1;
	}
    if (rv != OK) {
	    printf("The test passed, return value %d\n", rv);
		return 0;
	}
}
