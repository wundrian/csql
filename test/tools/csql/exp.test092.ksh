echo create table t1(f1 int,f2 int auto_increment);
Statement Executed
echo insert into t1 values(12,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 (f1)values(12);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,232);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	1	
	12	2	
	12	232	
	
echo create table t2(f1 int,f2 int auto_increment);
Statement Executed
echo insert into t2 values(12,200);
Statement Executed: Rows Affected = 1
echo insert into t2 values(12,NULL);
Statement Executed: Rows Affected = 1
echo insert into t2 (f1) values(12);
Statement Executed: Rows Affected = 1
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	12	200	
	12	201	
	12	202	
	
echo drop table t1;
Statement Executed
echo drop table t2;
Statement Executed
echo create table t1(f1 int auto_increment, f2 int auto_increment);
Statement prepare failed with error -19
echo create table t1(f1 int , f2 char(10) auto_increment);
Statement prepare failed with error -19
