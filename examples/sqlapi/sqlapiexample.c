#include<SqlStatement.h>
int main()
{
    DbRetVal rv = OK; 
    SqlConnection *con = new SqlConnection();
    rv = con->connect("root", "manager");
    if (rv != OK) return 1;
    SqlStatement *stmt = new SqlStatement();
    stmt->setConnection(con);
    char statement[1024];
    strcpy(statement, "CREATE TABLE t1 (f1 int, f2 char(20), primary key (f1));");
    int rows =0;
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Table t1 created\n");

    strcpy(statement, "CREATE INDEX t1idx on t1 (f1);");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Index created on t1(f1) \n");

    strcpy(statement, "INSERT INTO t1 (f1, f2) VALUES (?, ?);");
    int id1 =10;
    char name[20];
    strcpy(name, "Rithish");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    int count =0;
    for (int i = 0 ;  i < 100 ; i++)
    {
       rv = con->beginTrans();
       if (rv != OK) break;
       id1 =  i;
       stmt->setIntParam(1, id1);
       sprintf(name, "Gopika_%d", id1);
       stmt->setStringParam(2, name);
       rv = stmt->execute(rows);
       if (rv != OK) break;
       rv =  con->commit();
       if (rv != OK) break;
       count++;
    }
    printf("Total Rows Inserted %d\n", count);
    stmt->free();

    strcpy(statement, "SELECT * FROM t1 where f1 = ?;");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->bindField(1, &id1);
    stmt->bindField(2, name);
    for (int i = 0 ;  i < 10 ; i++)
    {
       rv = con->beginTrans();
       if (rv != OK) break;
       stmt->setIntParam(1, i);
       stmt->execute(rows);
       while (stmt->fetch() != NULL) {
          printf("Row value is %d %s\n", id1, name);
       }
       stmt->close();
       rv = con->commit();
       if (rv != OK) break;
    }
    stmt->free();


    strcpy(statement, "DROP TABLE t1);");
    rv = stmt->prepare(statement);
    if (rv != OK) {delete stmt; delete con; return -1; }
    rv = stmt->execute(rows);
    if (rv != OK) {delete stmt; delete con; return -1; }
    stmt->free();
    printf("Table dropped\n");


    delete stmt;
    delete con;
    return 0; 
}
