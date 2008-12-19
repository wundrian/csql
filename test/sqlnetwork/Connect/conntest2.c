/*  close the connection and call commit, it should fail

 *  Author : Jitendra Lenka
 */

#include<SqlNwConnection.h>
#include<SqlFactory.h>

int main()
{
   DbRetVal rv = OK;

   AbsSqlConnection *con = new SqlNwConnection();
   con->setInnerConnection(NULL);
   SqlNwConnection *conn = (SqlNwConnection *)con;
   conn->setHost("localhost", 5678);
   rv = con->connect("root","manager");
   if(rv!=OK)return 1;
   printf("Connection opened\n");
   rv = con->beginTrans();
   if(rv!=OK)return 2;
   rv = con->disconnect();
   if(rv !=OK)return 3;
   printf("Connection closed\n");
   rv = con->commit();
   if(rv==OK)
   {
       printf("Test script failed\n");
       return 4;
   }
   printf("After closing the connection, commit failed\n");
   printf("Test script pased\n");
   delete con;
   return 0;
}
   
   
   
