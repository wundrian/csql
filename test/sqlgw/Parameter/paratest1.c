/*  create table t1 with 10 fields.
 *  insert some records into it.
 *  noOfParamFields() should return 10.
 *  getParamFldInfo() for all fields and print the field info.
 *  select * from t1;
 
 *  Author : Jitendra Lenka.
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
   int rows = 0;
   // insert into table
   int para=0;
   if(strcmp(getenv("DSN"),"oracle")==0){
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?);");
      para=8;
   }
   else if(strcmp(getenv("DSN"),"db2")==0){
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?,?)");
      para=9;
   }
   else{
      strcpy(statement,"INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?,?,?);");
      para=9;
   }
   int f1var = 100;
   short int f2var = 10;
   char f3var[32]="jitendra";
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
//******************************************************************************    
   if(strcmp(getenv("DSN"),"psql")==0){
   con->rollback();
   }
    int nop;
    nop = stmt->noOfParamFields();
    printf("noOfParamField Returns=%d\n",nop);


    //getParamFldInfo()
    FieldInfo *field = new FieldInfo();
    

    char fldName[20];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[10];
    bool isNull;
    bool isDefault;
    
    for(int i=0;i<nop;i++)
    {
         printf("\n***********************************************\n");
         printf("%d FIELD INFORMATION ::\n",i);;   
         rv = stmt->getParamFldInfo(i+1,field);
         if(rv!=OK)return 1;
         printf("Field Name :%s\n", field->fldName);
         printf("Data type of the field :%d\n",field->type);
         printf("length of the field :%d\n",field->length);
         printf("Offset :%d\n",field->offset);
         printf("Default value :%s\n",field->defaultValueBuf);
         printf("Null field :%d\n",field->isNull);
         printf("Default value :%d\n",field->isDefault);
         printf("***********************************************\n"); 
   }
   delete field;
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
    
    //**********************************************************

    // SELECT * FROM t1;

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
             printf("f1=%d | f2=%hd | f3=%s | f4=%f | f5=%f | DATE=%d-%d-%d | TIMESTAMP=%d-%d-%d %d:%d:%d | f9=%d | f10=%lld\n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var); 
        else
             printf("f1=%d | f2=%hd | f3=%s | f4=%f | f5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | f9=%d | f10=%lld\n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var); 
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
