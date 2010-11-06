/* 
 Connect and dissconnect 5000 times. it should pass. 
*/
#include "common.h"

int main()
{
    DbRetVal rv =OK;
    AbsSqlConnection *con = createConnection();
// Connection 1st time
    int i;
    for(i=1; i<=5000; i++)
    {
	rv = con->connect("root","manager");
	if(rv!=OK)return 1;
	rv = con->disconnect();
	if(rv!=OK)return 2;
	if(i%500==0)printf("Connected and Closed %d times\n",i); 
    }
    printf("Test script passed\n");
    delete con;
    return 0;
}
