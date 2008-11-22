//  Pass correct user name and password ,it should pass.

//  Author : Jitendra Lenkla

#include<SqlNwConnection.h>
#include<SqlFactory.h>
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = new SqlNwConnection();
   con->setInnerConnection(NULL);
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
