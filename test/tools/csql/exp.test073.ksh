echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100,200,300);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1000,2000,3000);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	10	20	30	
	100	200	300	
	1000	2000	3000	
	
echo update t1 set f2=0,f3=f1+f2+f3 where f1<=100 and f1 >1;
Statement Executed: Rows Affected = 2
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	10	0	60	
	100	0	600	
	1000	2000	3000	
	
Statement Executed
