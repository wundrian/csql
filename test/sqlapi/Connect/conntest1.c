/*  connect ,disconnect and again connect ,it should fail.

 *  AUTHOR : Jitendra Lenka
 */


#include<AbsSqlStatement.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv =OK;
  AbsSqlConnection *con = SqlFactory :: createConnection(CSql); 
  rv = con->connect("root","manager");
  if(rv!=OK)return 1;
  printf("aConnection opened\n");
  delete con;

   con = SqlFactory::createConnection(CSql);
   rv = con->connect("root","manager");
   if(rv !=OK)
   {
    printf("Test script failed \n");
    return 2;
   }
  printf("Connection closed\n");
  printf("Test script passed\n");
  return 0;
}
  
    
