#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;

    os::setenv("CSQL_CONFIG_FILE", "/tmp/csql1.conf");


    rv = conn.open("praba", "manager");
    if (rv == OK) return 1;

    rv = conn.close();
    if (rv != OK) return 2;
    return 0;
}
