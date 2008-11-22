/*  connect ,disconnect and again connect ,it should pass. 

 *  AUTHOR : Jitendra Lenka
 */

#include<SqlNwConnection.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv =OK;
  AbsSqlConnection *con = new SqlNwConnection();
  con->setInnerConnection(NULL);

  rv = con->connect("root","manager");
  if(rv!=OK)return 1;
  printf("Connection opened\n");
  rv = con->disconnect();
  if (rv != OK) { printf("disconnect failed\n"); return 2; }
  rv = con->connect("root","manager");
  if(rv !=OK)
  {
    printf("Test script failed \n");
    return 3;
  }
  printf("Connection opened\n");
  printf("Test script passed\n");
  delete con;
  return 0;
}
  
    
