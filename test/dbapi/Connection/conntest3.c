//Open connection twice using the same object without closing the connection inbetween.
// Is should fail.

#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv1 = conn.open("root", "manager");
    if (rv1!= OK)
    {
       printf("Unable to open the database");
       return 1;
    }

    DbRetVal rv2 = conn.open("root", "manager");
    if(rv2==OK)
    {
      printf("Test failed");
      return 2;
    }

    printf("Opening connection twice w/o closing inbetween passed return value %d \n",rv1); 
    return 0;
} 
