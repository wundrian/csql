//print values of the config file
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;
    rv = conn.open("praba", "manager");
    if (rv == OK) return 1;
    return 0;
}
