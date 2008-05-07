/*  create table T1 with 10 fields.
 *  insert some records into it.
 *  noOfParamFields() should return zero.
 *  getParamFldInfo() for all fields and print the field info.
 *  select * from T1;
 
 *  Author : Jitendra Lenka.
 */

#include<SqlStatement.h>
#include<CSql.h>
#include<Info.h>
int main()
{
  DbRetVal rv = OK;
  SqlConnection *con= new SqlConnection();
  rv = con->connect("root","manager");
  if(rv!=OK)return 1;

  SqlStatement *stmt = new SqlStatement();
  stmt->setSqlConnection(con);
  char statement[200];
  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 INT,F10 BIGINT);");
  
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
     return 1;
   }

   stmt->free();
   printf("Table created\n");

   // insert into table

   strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?);");
   
   int f1var = 0;
   short int f2var = 1;
   char f3var[20]="jitendra";
   float f4var = 5.5;
   float f5var = 10.50;
   Date f6var;
   f6var.set(2008,01,21);
   
   Time f7var;
   f7var.set(12,29,30);     
   
   TimeStamp f8var;
   f8var.setDate(2008,01,21);
   f8var.setTime(12,29,30);

   int f9var = 20;
   long long f10var = 12000;

   rv = stmt->prepare(statement);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 1;
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
    printf("Total rows inserted %d\n",count);
    
    
    int nop;
    nop = stmt->noOfParamFields();
    printf("Total parameter in the statement=%d\n",nop);
    
    FieldInfo * field = new FieldInfo();
    

    char fldName[20];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[10];
    bool isNull;
    bool isDefault;

    rv = stmt->getParamFldInfo(1,field);
    if(rv !=OK)return -1;    
    printf("fldname of field is %s\n", field->fldName);
    printf("data type of the field=%d\n",field->type);
    printf("length of the field=%d\n",field->length);
    printf("offset=%d\n",field->offset); 
    printf("default value=%s\n",field->defaultValueBuf);
    printf("null field=%d\n",field->isNull);
    printf("default value is set for the field=%d\n",field->isDefault);

   stmt->free();
    
    //**********************************************************

    // SELECT * FROM T1;

    strcpy(statement,"SELECT * FROM T1;");
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
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);

    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL)
    {
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
    

    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
      delete stmt;
      delete con;
      return 8;
    }
    rv = stmt->execute(rows);
    if(rv!=OK)
     {
      delete stmt;
      delete con;
      return 9;
    }
    stmt->free();
    printf("Table dropped\n");
    
    delete stmt;
    delete con;
    return 0;
} 	 	      
