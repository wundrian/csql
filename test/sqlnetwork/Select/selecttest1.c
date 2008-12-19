/*   create table T1 with 10 fields,
 *   insert 10 rows into the table ,
 *   noofprojFields shoul dreturn 10.
 *   call fetch and count the record.

 *   Author : Jitendra Lenka
 */

#include<SqlNwConnection.h>
#include<SqlNwStatement.h>
#include<SqlFactory.h>
#include<Info.h>
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = new SqlNwConnection();
  con->setInnerConnection(NULL);
  SqlNwConnection *conn = (SqlNwConnection *)con;
  conn->setHost("localhost", 5678);
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = new SqlNwStatement();
  stmt->setInnerStatement(NULL);
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 INT,F10 BIGINT);");

  int rows=0;
  rv = stmt->prepare(statement);
  if(rv!=OK) { delete stmt; delete con; return 2; }

 rv  = stmt->execute(rows);
  if(rv!=OK) { delete stmt; delete con; return 3; }
 printf("'T1'  table created\n");

 //  insert records

 strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?);");

 int f1var = 99;
 short int f2var = 1;
 char f3var[31] = "lakshya";
 float f4var = 5.5;
 float f5var = 10.50;
 Date f6var;
 f6var.set(2008,1,21);
 
 Time f7var;
 f7var.set(12,29,30);
 
 TimeStamp f8var;
 f8var.setDate(2008,1,21);
 f8var.setTime(12,29,30);

 int f9var = 20;
 long long f10var = 12000;

 rv = stmt->prepare(statement);
 if(rv!=OK) { delete stmt; delete con; return 4; }


 int count=0;

 for(int i=0;i<2;i++)
 {
   f1var = f1var+i; 
   for(int j=0;j<5;j++)
    {	
        rv = con->beginTrans();
	if(rv!=OK)break;
	
         	
        stmt->setIntParam(1,f1var);
	stmt->setShortParam(2,f2var);
	stmt->setStringParam(3,f3var);
	stmt->setFloatParam(4,f4var);
	stmt->setFloatParam(5,f5var);
	stmt->setDateParam(6,f6var);
	stmt->setTimeParam(7,f7var);
	stmt->setTimeStampParam(8,f8var);
	stmt->setIntParam(9,f9var);
	stmt->setLongLongParam(10,f10var);

	rv = stmt->execute(rows);
	if(rv!=OK)break;
	rv = con->commit();
	if(rv!=OK)break;
	count++;
    }
    
 }
  printf("%d Rows Inserted\n",count);

//*******************************************

  strcpy(statement,"SELECT * FROM T1 WHERE F1=100;");
  rv = stmt->prepare(statement);
  
   int nop;
   nop = stmt->noOfProjFields();
   printf("noOfProjFields returns=%d\n",nop);

   if(rv !=OK) { delete stmt; delete con; return 5; }

  stmt->bindField(1,&f1var);
  stmt->bindField(2,&f2var);
  stmt->bindField(3,f3var);
  stmt->bindField(4,&f4var);
  stmt->bindField(5,&f5var);
  stmt->bindField(6,&f6var);
  stmt->bindField(7,&f7var);
  stmt->bindField(8,&f8var);
  stmt->bindField(9,&f9var);
  stmt->bindField(10,&f10var);


  count = 0;
  rv = con->beginTrans();
  if(rv!=OK)return 6;
  stmt->execute(rows);
  printf("Fetching starts on table 'T1' :\n");
  while(stmt->fetch()!=NULL)
  {
      printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);

      count++;
  }

  stmt->close();
  rv = con->commit();
  if(rv!=OK) { delete stmt; delete con; return 7; }

  printf("%d Rows fetched\n",count);
  

 strcpy(statement,"DROP TABLE T1;");
 rv = stmt->prepare(statement);
 if(rv!=OK) { delete stmt; delete con; return 8; }
 rv = stmt->execute(rows);
 if(rv!=OK) { delete stmt; delete con; return 9; } 
 printf("'T1' table dropped\n");

 delete stmt;
 delete con;
 return 0;
}
 

 
