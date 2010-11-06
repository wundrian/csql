/*   create table t1 with 10 fields,( f2 NOT NULL , f3 CHAR(20) DEFAULT 'LAKSHYA')
 *   insert 10 rows for 9 Fields except f3 Field into the table
 *   noofprojFields should return 5.
 *   getProjFldInfo() for all fields.
 *   select with 5 parameters withIwhere clause.(WHERE f1=100)
*/

#include "common.h"
int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;

    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    int rows=0;

    //  insert records
    if(strcmp(getenv("DSN"),"oracle")==0)
        strcpy(statement,"INSERT INTO t1(f1,f2,f4,f5,f6,f8,f9,f10)VALUES(?,?,?,?,?,?,?,?);");
    else if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"INSERT INTO t1(f1,f2,f4,f5,f6,f7,f8,f9,f10)VALUES(?,?,?,?,?,?,?,?,?)");
    else
        strcpy(statement,"INSERT INTO t1(f1,f2,f4,f5,f6,f7,f8,f9,f10)VALUES(?,?,?,?,?,?,?,?,?);");

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
    if(rv!=OK) { delete stmt; delete con; return 4; }

    int count=0;

    for(int i=0;i<2;i++) {
        f1var = f1var+i; 
        for(int j=0;j<5;j++) {	
            rv = con->beginTrans();
	        if(rv!=OK)break;
	        stmt->setIntParam(1,f1var);
            stmt->setShortParam(2,f2var);
            //stmt->setStringParam(3,f3var);
            stmt->setFloatParam(3,f4var);
            stmt->setFloatParam(4,f5var);
            stmt->setDateParam(5,f6var);
            if(strcmp(getenv("DSN"),"oracle")==0){
                stmt->setTimeStampParam(6,f8var);
                stmt->setIntParam(7,f9var);
                stmt->setLongLongParam(8,f10var);
            } else {
                stmt->setTimeParam(6,f7var);
                stmt->setTimeStampParam(7,f8var);
                stmt->setIntParam(8,f9var);
                stmt->setLongLongParam(9,f10var);
            } 
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

    strcpy(statement,"SELECT f8,f10,f2,f6,f3  FROM t1 WHERE f1=100;");
    if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"SELECT f8,f10,f2,f6,f3  FROM t1 WHERE f1=100");
    rv = stmt->prepare(statement);
    if(rv !=OK) { delete stmt; delete con; return 5; }
  
    int nop;
    nop = stmt->noOfProjFields();
    if(nop!=5)return 1;
    printf("Total number of projection fields in the select statement=%d\n",nop);
    char fldName[20];
    DataType type;
    size_t length;
    int offset;
    char defaultValueBuf[10];
    bool isNull;
    bool isDefault;
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
    while(stmt->fetch()!=NULL) {
        printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | f9=%d | f10=%lld  \n",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
        count++;
    }

    stmt->close();
    rv = con->commit();
    if(rv!=OK) { delete stmt; delete con; return 6; }

    printf("Total row fetched=%d\n",count);
    stmt->free();
    delete stmt;
    delete con;
    return 0;
}
