//  Pass correct user name and password ,it should pass.

//  Author : Jitendra Lenkla

#include<AbsSqlStatement.h>i
#include<SqlFactory.h>
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = SqlFactory::createConnection(CSqlAdapter);
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
