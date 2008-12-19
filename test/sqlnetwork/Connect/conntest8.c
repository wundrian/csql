//  Pass incorrect user name and password ,it should fail.

//  Author : Jitendra Lenkla

#include<SqlNwConnection.h>
#include<SqlFactory.h>
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = new SqlNwConnection();
   con->setInnerConnection(NULL);
   SqlNwConnection *conn =(SqlNwConnection *)con;
   conn->setHost("localhost", 5678);
   rv = con->connect("root123","manager123");
   if(rv==OK)
   {
     printf("Test script failed with error%d\n",rv);
     return 1;
   }
   printf("Connection failed dueto incorrect user anme and password\n");
   printf("Test script passed\n");
   delete con;
   return 0;
}
