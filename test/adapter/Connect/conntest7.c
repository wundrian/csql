//Connect with correct user name and password, it should pass.

#include"common.h"
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = createConnection();
   rv = con->connect("root","manager");
   if(rv!=OK)
   {
     printf("Test script failed with error%d\n",rv);
     return 1;
   }
   printf("Connection opened with correct user name and password\n");
   printf("Test script passed\n");
   delete con;
   return 0;
}
