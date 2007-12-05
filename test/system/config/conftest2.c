//print values of the config file
#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;
    char *root = os::getenv("PWD");
    char conf[512];
    char *s = root + (strlen(root) - 9);
    if (strcmp(s, "csql/test") == 0)
        sprintf(conf,  "%s/system/config/csql.conf", root);
    else
        sprintf(conf,  "%s/csql.conf", root);
    os::setenv("CSQL_CONFIG_FILE", conf);
    char *val = os::getenv("CSQL_CONFIG_FILE");
    printf("CSQL_CONFIG_FILE= %s\n", val);
    rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    Conf::config.print();
    conn.close();
    return 0;
}
