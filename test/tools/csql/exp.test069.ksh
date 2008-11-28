echo set autocommit on;
AUTOCOMMIT Mode is set to ON
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100,200,300);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	10	20	30	
	100	200	300	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	10	20	30	
	100	200	300	
	
Statement Executed
