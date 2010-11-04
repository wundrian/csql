#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("wrongusername", "manager");
    if (rv == OK)
    {
       conn.close();
       return 1;
    }
    printf("wrong username test passed Return value %d \n", rv);
    rv = conn.open("root", "wrongpasswd");
    if (rv == OK)
    {
       conn.close();
       return 2;
    }
    printf("wrong password test passed Return value %d \n", rv);
    conn.close(); 
    return 0;
}
