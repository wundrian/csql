/*  create table T1 with 2 fields.
 *  get Metadata by Describe <tblName>
 * 
 *  
 *  select * from T1;
 
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con =  createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    stmt->free();
    printf("Table T1 created\n");
    strcpy(statement,"DESCRIBE T1;");
    rv = stmt->prepare(statement);
    char colName[IDENTIFIER_LENGTH];
    int sqlType=0;
    int length=0;
    int isNull=0;
    stmt->bindField(4, colName);
    stmt->bindField(5, &sqlType);
    stmt->bindField(7, &length);
    stmt->bindField(11, &isNull);
    int i=0;
    rv = stmt->execute(rows);
    if (rv != OK) { printError(rv, "execute failed"); return rv; }
    while (stmt->fetch(rv) != NULL) {
       printf("cnt = %d\n", i++);
    }
    stmt->free();
    
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 9; }
    printf("Table dropped\n");
    stmt->free(); delete stmt; delete con;
    return 0;
} 	 	      
