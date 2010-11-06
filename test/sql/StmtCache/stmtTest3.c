#include <SqlFactory.h>

int main(int argc, char **argv)
{
    DbRetVal rv = OK;
    struct timeval timeout;
    struct timeval timeStamp;
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement, "UPDATE t1 set f2=? where f1=?;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER UPDATE PREPARE operation\n");
    con->display();
    int i = 1;
    int rows=0;
    rv = con->beginTrans();
    stmt->setIntParam(1, 100);
    stmt->setIntParam(2, i);
    rv = stmt->execute(rows);
    if (rv != OK) { 
        printError(rv, "Update failed with ret val %d", rv);
        con->rollback(); 
    }
    else con->commit();
    stmt->free(); 
    printf("AFTER STMT FREE operation\n");
    con->display();

    strcpy(statement, "DELETE from t1 where f2=?;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER DELETE PREPARE operation\n");
    con->display();
    rv = con->beginTrans();
    stmt->setIntParam(1, 100);
    rv = stmt->execute(rows);
    if (rv != OK) { 
        printError(rv, "Update failed with ret val %d", rv);
        con->rollback(); 
    }
    else con->commit();
    stmt->free(); 
    printf("AFTER STMT FREE operation\n");
    con->display();


    strcpy(statement, "SELECT f1 from t1 where f2=?;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    printf("AFTER SELECT PREPARE operation\n");
    con->display();
    rv = con->beginTrans();
    int val =0;
    stmt->bindField(1, &val);
    stmt->setIntParam(1, 1);
    rv = stmt->execute(rows);
    while (stmt->fetch()!= NULL)
    {
        printf("Tuple value %d\n", val);
    }
    con->commit();
    stmt->free();
    printf("AFTER STMT FREE operation\n");
    con->display();


    con->disconnect();
    printf("AFTER disconnect\n");
    con->display();
    delete stmt; 
    delete con;
}
