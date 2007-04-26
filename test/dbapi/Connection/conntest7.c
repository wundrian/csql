//Create One million transaction without committing it or aborting it
//It should return error after sometime

#include<CSql.h>
int main()
{
  Connection conn;
  DbRetVal rv=conn.open("praba","manager");
  if(rv!=OK)
  {
    return 1;
  }
  for(int i=0;i<1000000;i++)
  {
    rv=conn.startTransaction();
    if(rv!=OK)
    {
      printf("Test script passed return value %d\n",rv);
      return 0;
    }
  }
 printf("test script failed return value %d\n",rv);
 return 2;
}
