//Create transaction twice without committing it or aborting it on the same 
//object, It should fail

#include<CSql.h>
int main()
{
  Connection conn;
  DbRetVal rv=conn.open("root","manager");
  if(rv!=OK)
  {
    return 1;
  }
  rv=conn.startTransaction();
  rv=conn.startTransaction();
  if(rv!=OK)
  {
      printf("Test script passed return value %d\n",rv);
      return 0;
  }
 printf("test script failed return value %d\n",rv);
 return 2;
}
