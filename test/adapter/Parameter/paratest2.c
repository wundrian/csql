/*  create table T1 with 10 fields.
 *  insert some records into it.
 *  select * from T1 with where clause;
*/

#include "common.h"
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con= createConnection();
  rv = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = createStatement();
  stmt->setConnection(con);
  char statement[200];
  if(strcmp(getenv("DSN"),"oracle")==0)
      strcpy(statement,"CREATE TABLE t1(f1 number(9),f2 number(4),f3 CHAR(30),f4 FLOAT,f5 FLOAT,f6 DATE,f8 TIMESTAMP,f9 number(9),f10 number(18));");
   else if(strcmp(getenv("DSN"),"psql")==0)
      strcpy(statement,"CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 FLOAT4,f5 FLOAT4,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT);");
   else if(strcmp(getenv("DSN"),"sybase")==0)
      strcpy(statement,"CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 REAL,f5 REAL,f6 DATE,f7 TIME,f8 DATETIME,f9 INT,f10 BIGINT);");
   else if(strcmp(getenv("DSN"),"db2")==0)
      strcpy(statement,"CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 REAL,f5 REAL,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT)");
   else
      strcpy(statement,"CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 FLOAT,f5 FLOAT,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT);");
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 1;
   }

   rv = stmt->execute(rows);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 2;
   }
   con->commit();
   stmt->free();
   printf("Table created\n");

   // insert into table
   if(strcmp(getenv("DSN"),"oracle")==0){
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?);");
   }
   else if(strcmp(getenv("DSN"),"db2")==0){
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?,?)");
   }
   else{
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?,?);");
   }
   
   int f1var = 100;
   short int f2var = 10;
   char f3var[35]="jitendra";
   float f4var = 5.5;
   float f5var = 10.50;
   Date f6var;
   f6var.set(2007,01,21);
   
   Time f7var;
   f7var.set(12,29,30);     
   
   TimeStamp f8var;
   f8var.setDate(2007,01,21);
   f8var.setTime(12,29,30);

   int f9var = 20;
   long long f10var = 12000;

   rv = stmt->prepare(statement);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 3;
   }
   if(strcmp(getenv("DSN"),"psql")==0){
   con->rollback();
   }


   int count=0;
   
   for(int i=0;i<10;i++) 
   {	
	rv  = con->beginTrans();
	if(rv!=OK) break;
	f1var++;
        stmt->setIntParam(1,f1var);
        stmt->setShortParam(2,f2var);
        stmt->setStringParam(3,f3var);
        stmt->setFloatParam(4,f4var);
        stmt->setFloatParam(5,f5var);
        stmt->setDateParam(6,f6var);
        if(strcmp(getenv("DSN"),"oracle")==0){
            stmt->setTimeStampParam(7,f8var);
            stmt->setIntParam(8,f9var);
            stmt->setLongLongParam(9,f10var);
        }else{
            stmt->setTimeParam(7,f7var);
            stmt->setTimeStampParam(8,f8var);
            stmt->setIntParam(9,f9var);
            stmt->setLongLongParam(10,f10var);
        }
        rv = stmt->execute(rows);
        if(rv!=OK)break;
    	rv = con->commit();
	if(rv!=OK)break;
        count++;
    }
    printf("Total rows inserted %d\n",count);
    
    
        stmt->free();
    
    //**********************************************************

    // SELECT * FROM T1;
    if(strcmp(getenv("DSN"),"oracle")==0)
        strcpy(statement,"SELECT * FROM t1 WHERE F1=? AND F2=? AND F3=? AND F4=? AND F5=? AND F6=? AND F8=? AND F9=? AND F10=?;");
   else if(strcmp(getenv("DSN"),"sybase")==0)
        strcpy(statement,"SELECT * FROM t1 WHERE f1=? AND f2=? AND f3=? AND f4=? AND f5=? AND f6=? AND f7=? AND f8=? AND f9=? AND f10=?;");
   else if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"SELECT * FROM t1 WHERE f1=? AND f2=? AND f3=? AND f4=? AND f5=? AND f6=? AND f7=? AND f8=? AND f9=? AND f10=?");
   else
        strcpy(statement,"SELECT * FROM t1 WHERE F1=? AND F2=? AND F3=? AND F4=? AND F5=? AND F6=? AND F7=? AND F8=? AND F9=? AND F10=?;");
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
        delete stmt;
        delete con;
	return 4;
    }

    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,&f5var);
    stmt->bindField(6,&f6var);
    if(strcmp(getenv("DSN"),"oracle")==0){
        stmt->bindField(7,&f8var);
        stmt->bindField(8,&f9var);
        stmt->bindField(9,&f10var);

    }else{
        stmt->bindField(7,&f7var);
        stmt->bindField(8,&f8var);
        stmt->bindField(9,&f9var);
        stmt->bindField(10,&f10var);
   }

    int f1var1=100;
    short int f2var1=10;
    char f3var1[35]="jitendra";
    float f4var1=5.5;
    float f5var1=10.50;
    Date f6var1;
    f6var1.set(2007,01,21);

    Time f7var1;
    f7var1.set(12,29,30);

    TimeStamp f8var1;
    f8var1.setDate(2007,01,21);
    f8var1.setTime(12,29,30);

    int f9var1=20;
    long long f10var1=12000; 
    count=0;
    for(int i=0;i<10;i++)
    {
        rv  = con->beginTrans();
	if(rv!=OK)break;

        f1var1++;      
        stmt->setIntParam(1,f1var1);
        stmt->setShortParam(2,f2var1);
        stmt->setStringParam(3,f3var1);
        stmt->setFloatParam(4,f4var1);
        stmt->setFloatParam(5,f5var1);
        stmt->setDateParam(6,f6var1);
        if(strcmp(getenv("DSN"),"oracle")==0){
            stmt->setTimeStampParam(7,f8var1);
            stmt->setIntParam(8,f9var1);
            stmt->setLongLongParam(9,f10var1);
        }else{
            stmt->setTimeParam(7,f7var1);
            stmt->setTimeStampParam(8,f8var1);
            stmt->setIntParam(9,f9var1);
            stmt->setLongLongParam(10,f10var1);
        }


        stmt->execute(rows);
	
        while(stmt->fetch()!=NULL)
        {
            if(strcmp(getenv("DSN"),"oracle")==0)
                printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
            else
                printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
       
            count++;
        }
        stmt->close();
        rv = con->commit();
        if(rv!=OK)return 5;
    }
     stmt->free();
     
     printf("%d Tuples fetched\n",count);
     strcpy(statement,"DROP TABLE t1;");
     if(strcmp(getenv("DSN"),"db2")==0){
         strcpy(statement,"DROP TABLE t1");
     }
     rv = stmt->prepare(statement);
     if(rv!=OK){delete stmt; delete con; return -1;}

     rv = stmt->execute(rows);
     if(rv!=OK){delete stmt;delete con;return -1;}
     stmt->free();
     con->commit();
     printf("Table dropped\n");

     delete stmt;
     delete con;
     return 0;
}   		 
