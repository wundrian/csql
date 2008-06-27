/*   create table T1 with 10 fields,( F2 NOT NULL , F3 CHAR(20) DEFAULT 'LAKSHYA')
 *   
 *   insert 10 rows for 9 Fields except F3 Field into the table
 *   noofprojFields should return 5.
 *   getProjFldInfo() for all fields.
 *   select with 5 parameters withIwhere clause.(WHERE F1=100)

 *   Author : Jitendra Lenka
 */

#include<AbsSqlStatement.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = SqlFactory :: createConnection(CSqlAdapter);
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = SqlFactory ::createStatement(CSqlAdapter);
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT NOT NULL,F3 CHAR(30) DEFAULT 'LAKSHYA',F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 INT,F10 BIGINT);");

  int rows=0;
  rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 2;
 }

 rv  = stmt->execute(rows);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 3;
 }
 stmt->free();
 printf("'T1' Table created\n");

 //  insert records

 strcpy(statement,"INSERT INTO T1(F1,F2,F4,F5,F6,F7,F8,F9,F10)VALUES(?,?,?,?,?,?,?,?,?);");

 int f1var = 99;
 short int f2var = 1;
// char f3var[20] = "prabakaran";
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
 if(rv!=OK)
 {
   delete stmt;
   delete con;
   return 4;
 }

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
	//stmt->setStringParam(3,f3var);
	stmt->setFloatParam(3,f4var);
	stmt->setFloatParam(4,f5var);
	stmt->setDateParam(5,f6var);
	stmt->setTimeParam(6,f7var);
	stmt->setTimeStampParam(7,f8var);
	stmt->setIntParam(8,f9var);
	stmt->setLongLongParam(9,f10var);

	rv = stmt->execute(rows);
	if(rv!=OK)break;
	rv = con->commit();
	if(rv!=OK)break;
	count++;
     }
    
  }
  printf("%d Rows Inserted\n",count);
  stmt->free();

//*******************************************

  strcpy(statement,"SELECT F8,F10,F2,F6,F3  FROM T1 WHERE F1=100;");
  rv = stmt->prepare(statement);
  
   int nop;
   nop = stmt->noOfProjFields();
   if(nop!=5)return 1;
   printf("Total number of projection fields in the select statement=%d\n",nop);

   // getParamFldInfo() 
    FieldInfo *field = new FieldInfo();
    
    char fldName[20];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[10];
    bool isNull;
    bool isDefault;

  if(rv !=OK)
  {
     delete stmt;
     delete con;
     return 5;
  }

  char f3var[32]="jitu";
  
  stmt->bindField(1,&f8var);
  stmt->bindField(2,&f10var);
  stmt->bindField(3,&f2var);
  stmt->bindField(4,&f6var);
  stmt->bindField(5,f3var);
  
  
  count = 0;
  rv = con->beginTrans();
  if(rv!=OK)return 6;
  stmt->execute(rows);
  while(stmt->fetch()!=NULL)
  {
     
        printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);

       count++;
  }

  stmt->close();
  rv = con->commit();
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 6;
  }

  printf("Total row fetched=%d\n",count);
  
  stmt->free();

 strcpy(statement,"DROP TABLE T1;");
 rv = stmt->prepare(statement);
 if(rv!=OK)
 {
   delete stmt;
   delete con;
   return 7;
 }
 rv = stmt->execute(rows);
 if(rv!=OK)
 {
   delete stmt;
   delete con;
   return 8;
 }
 stmt->free();
 printf("Table dropped\n");

 delete stmt;
 delete con;
 return 0;
}
 

 
