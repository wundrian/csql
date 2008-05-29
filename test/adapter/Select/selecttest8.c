/*   prepare,execute,free,prepare, second prepare should pass.

 *   Author : Jitendra Lenka
 */

#include<AbsSqlStatement.h>
#include<SqlFactory.h>
//#include<Info.h>
int main()
{
	DbRetVal rv = OK;
  	AbsSqlConnection *con = SqlFactory :: createConnection(CSqlAdapter);
  	rv  = con->connect("root","manager");
  	if(rv!=OK)return 1;

  	AbsSqlStatement *stmt = SqlFactory :: createStatement(CSqlAdapter);
  	stmt->setConnection(con);
  	char statement[200];

  	strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20));");
       	int rows=0;
  	
	rv = stmt->prepare(statement);
  	if(rv!=OK)
  	{
    		delete stmt;
    		delete con;
    		return 1;
 	}
 	printf("Prepare the Statement\n");
 	rv  = stmt->execute(rows);
  	if(rv!=OK)
  	{
    		delete stmt;
    		delete con;
    		return 2;
 	}
 	printf("Execute the Statement\n");
 
 	stmt->free();
 	printf("free all the resources\n");
 
 	//again prepare
 	strcpy(statement,"DROP TABLE T1;");
 	rv = stmt->prepare(statement);
 	if(rv!=OK)
 	{
   		printf("Test script failed\n");
   		delete stmt;
   		delete con;
   		return 3;
 	}
 	printf("Again prepare passed\n");
 
        //Drop the table
        strcpy(statement,"DROP TABLE T1;");
        rv = stmt->prepare(statement);
        rv = stmt->execute(rows); 
  	if(rv==OK)printf("Table dropped successfully\n");
    stmt->free();
        delete stmt;
 	delete con;
	 return 0;
} 

   

  
