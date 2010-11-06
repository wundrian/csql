/*  create table T1 with 10 fields.
 *  insert some records into it.
 *  delete records from T1 with where clause
 *  select * from T1;
*/

#include "common.h"
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = createConnection();
  rv = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = createStatement();
  stmt->setConnection(con);
  char statement[200];
   int rows = 0;
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
 
   int f1var = 0;
   short int f2var = 1;
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
     return 4;
   }
   if(strcmp(getenv("DSN"),"psql")==0){
   con->rollback();
   }


   int count=0;
   
   for(int i=0;i<10;i++) 
   {	
	rv  = con->beginTrans();
	if(rv!=OK) break;
	f1var=i;
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
   //*********************************************************

   //  delete records from the T1
   if(strcmp(getenv("DSN"),"oracle")==0)
        strcpy(statement,"DELETE FROM t1 WHERE f10=? AND f9=? AND f8=? AND f6=? AND f5=? AND f4=? AND f3=? AND f2=? AND f1=?;");
   else if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"DELETE FROM t1 WHERE f10=? AND f9=? AND f8=? AND f7=? AND f6=? AND f5=? AND f4=? AND f3=? AND f2=? AND f1=?");
   else
        strcpy(statement,"DELETE FROM t1 WHERE f10=? AND f9=? AND f8=? AND f7=? AND f6=? AND f5=? AND f4=? AND f3=? AND f2=? AND f1=?;");
  
   rv = stmt->prepare(statement);
   if(rv!=OK){delete stmt;delete con;return -1;}
   if(strcmp(getenv("DSN"),"psql")==0){
   con->rollback();
   }


  /* stmt->bindField(1,&f10var);
   stmt->bindField(2,&f9var);
   stmt->bindField(3,&f8var);
   stmt->bindField(4,&f7var);
   stmt->bindField(5,&f6var);
   stmt->bindField(6,&f5var);
   stmt->bindField(7,&f4var);
   stmt->bindField(8,f3var);
   stmt->bindField(9,&f2var);
   stmt->bindField(10,&f1var);*/ 
    
   short int f2var1=1;
   char f3var1[20] ="jitendra";
   float f4var1 = 5.5;
   float f5var1 = 10.50;
   Date f6var1;
   f6var1.set(2007,1,21);

   Time f7var1;
   f7var1.set(12,29,30);
   
   TimeStamp f8var1;
   f8var1.setDate(2007,1,21);
   f8var1.setTime(12,29,30);

   int f9var1=20;
   long long f10var1=12000;
   count=0;

   for(int i=5;i<10;i++)
   {
      rv = con->beginTrans();
      if(rv!=OK)break;

      stmt->setLongLongParam(1,f10var1);
      stmt->setIntParam(2,f9var1);
      stmt->setTimeStampParam(3,f8var1);
      if(strcmp(getenv("DSN"),"oracle")==0){
          stmt->setDateParam(4,f6var1);
          stmt->setFloatParam(5,f5var1);
          stmt->setFloatParam(6,f4var1);
          stmt->setStringParam(7,f3var1);
          stmt->setShortParam(8,f2var1);
          stmt->setIntParam(9,i);
      }else{
          stmt->setTimeParam(4,f7var1);
          stmt->setDateParam(5,f6var1);
          stmt->setFloatParam(6,f5var1);
          stmt->setFloatParam(7,f4var1);
          stmt->setStringParam(8,f3var1);
          stmt->setShortParam(9,f2var1);
          stmt->setIntParam(10,i);

      }

      rv = stmt->execute(rows);
      if(rv!=OK)break;
      rv = con->commit();
      if(rv!=OK)break;
      count++;
   }
   stmt->free();
   printf("Total row deleted=%d\n",count); 	




   //**********************************************************

    // SELECT * FROM T1;
    strcpy(statement,"SELECT * FROM t1;");
    if(strcmp(getenv("DSN"),"db2")==0){
        strcpy(statement,"SELECT * FROM t1");
    }
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
      delete stmt;
      delete con;
      return 5;
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
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL)
    {
        if(strcmp(getenv("DSN"),"oracle")==0)   
            printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
        else
            printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);

       count++;
    }

    stmt->close();
    rv = con->commit();
    if(rv !=OK)
    {
      delete stmt;
      delete con;
      return 7;
    }

    printf("Total row fetched=%d\n",count);
    stmt->free();
    
    delete stmt;
    delete con;
    return 0;
} 	 	      
