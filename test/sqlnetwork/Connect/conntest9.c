//  Pass correct username and  incorrect  password ,it should fail.

//  Author : Jitendra Lenkla

#include<SqlNwConnection.h>
#include<SqlFactory.h>
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = new SqlNwConnection();
   rv = con->connect("root","manager123");
   if(rv==OK)
   {
     printf("Test script failed with error%d\n",rv);
     return 1;
   }
   printf("Connection is not opened dueto Incorrect password\n");
   printf("Test script passed\n");
   delete con;
   return 0;
}
