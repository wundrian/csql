/*  connect ,disconnect and again connect ,it should pass. 

 *  AUTHOR : Jitendra Lenka
 */


#include<AbsSqlStatement.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv =OK;
  AbsSqlConnection *con = SqlFactory :: createConnection(CSqlAdapter); 
  rv = con->connect("root","manager");
  if(rv!=OK)return 1;
  printf("Connection opened\n");
  delete con;

   con = SqlFactory::createConnection(CSqlAdapter);
   rv = con->connect("root","manager");
   if(rv !=OK)
   {
    printf("Test script failed \n");
    return 2;
   }
  printf("Connection closed\n");
  printf("Test script passed\n");
  delete con;
  return 0;
}
  
    
