//open connection
//close it and reopen the connection  using the same object
//It should pass

#include<CSql.h>
int main()
{
   Connection conn;
   DbRetVal rv=conn.open("root","manager");
   if(rv!=OK)
   {
     return 1;
   }
   rv=conn.close();
   if(rv!=OK)
   {
     return 2; 
   }
   rv=conn.open("root","manager");
   if(rv!=OK)
   {
     return 3;
   }
   printf("test 3 passed return value %d\n",rv);
   return 0;
}
