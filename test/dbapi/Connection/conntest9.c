//Create  transaction and abort it for one million times
//it should succeed

#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv=conn.open("praba","manager");
    if(rv!=OK)
    {
      return 1;
    }
   if(rv!=OK)
   {
     printf("unable to start transaction");
     return 2;
   }
   for(int i=0;i<1000000;i++)
   {
      rv=conn.startTransaction();
      if(rv!=OK) return 3;
      rv=conn.rollback();
      if(rv!=OK)
    {
      printf("Test script failed return value %d\n",rv);
      return 4;
    }
  }
 printf("test script passed return value %d\n",rv);
 return 0;
}

