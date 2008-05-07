/*  close the connection and call commit, it should fail

 *  Author : Jitendra Lenka
 */


#include<SqlStatement.h>
#include<CSql.h>
int main()
{
   DbRetVal rv = OK;
   SqlConnection *con = new SqlConnection();
   rv = con->connect("root","manager");
   if(rv!=OK)return 1;
   printf("Connection opened\n");

    
   rv = con->beginTrans();
   if(rv!=OK)return 2;
   
   rv = con->disconnect();
   if(rv !=OK)return 3;printf("Connection closed\n");
   
   rv = con->commit();
   if(rv==OK)
   {
       printf("Test script failed\n");
       return 4;
   }
   printf("After closing the connection, commit failed\n");
   printf("Test script pased\n");
   return 0;
}
   
   
   
