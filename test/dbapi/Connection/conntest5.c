//commit a transaction  without starting it and it should fail

#include<CSql.h>
int main()
{
   Connection conn;
   DbRetVal rv=conn.open("praba","manager");
   if(rv!=OK) return 1;
   rv=conn.commit();
   if(rv==OK)
   {
      printf("test script failed");
      return 2;
   }
   printf("Test script passed return value %d\n",rv);
   return 0;
} 
