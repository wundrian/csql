echo create table t1(f1 int,f2 char(10));
Statement Executed
echo insert into t1 values(1,'x');
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,'y');
Statement Executed: Rows Affected = 1
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo update t1 set f2='k' where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	x	
	2	k	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	x	
	2	y	
	
echo insert into t1 values(3,'k');
Statement Executed: Rows Affected = 1
echo insert into t1 values(4,'p');
Statement Executed: Rows Affected = 1
echo commit;
echo insert into t1 values(5,'t');
Statement Executed: Rows Affected = 1
echo rollback;
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	x	
	2	y	
	3	k	
	4	p	
	
Statement Executed
