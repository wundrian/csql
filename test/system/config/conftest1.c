#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;
    os::setenv("CSQL_CONFIG_FILE", "./noexistcsql.conf");
    rv = conn.open("praba", "manager");
    if (rv == OK) return 1;
    return 0;
}