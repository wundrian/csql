#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;
    os::setenv("CSQL_CONFIG_FILE", "./noexistcsql.conf");
    rv = conn.open("root", "manager");
    if (rv == OK) return 1;
    return 0;
}
