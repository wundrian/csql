//abort a transaction without starting it
//it should fail

#include<CSql.h>
int main()
{
   Connection conn;
   DbRetVal rv=conn.open("root","manager");
   if(rv!=OK) return 1;
   rv=conn.rollback();
   if(rv!=OK)
   {
      printf("Test script failed");
      return 2;
   }
   printf("Test script passed return value %d\n",rv);
   return 0;
}

