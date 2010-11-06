echo create table t1(f1 int);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement prepare failed with error -16
echo update t1 set f1=10a;
Statement prepare failed with error -16
echo update t1 set f1=100a;
Statement prepare failed with error -16
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	
echo select * from t1 where f1=10a;
Statement prepare failed with error -16
echo drop table t1;
Statement Executed
echo create table t1(f1 tinyint);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement prepare failed with error -16
echo update t1 set f1=10a;
Statement prepare failed with error -16
echo update t1 set f1=100a;
Statement prepare failed with error -16
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	
echo select * from t1 where f1=10a;
Statement prepare failed with error -16
echo drop table t1;
Statement Executed
echo create table t1(f1 smallint);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement prepare failed with error -16
echo update t1 set f1=10a;
Statement prepare failed with error -16
echo update t1 set f1=100a;
Statement prepare failed with error -16
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	
echo select * from t1 where f1=10a;
Statement prepare failed with error -16
echo drop table t1;
Statement Executed
echo create table t1(f1 bigint);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement prepare failed with error -16
echo update t1 set f1=10a;
Statement prepare failed with error -16
echo update t1 set f1=100a;
Statement prepare failed with error -16
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	
echo select * from t1 where f1=10a;
Statement prepare failed with error -16
echo drop table t1;
Statement Executed
echo create table t1(f1 real);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement Executed: Rows Affected = 1
echo update t1 set f1=10a;
Statement Executed: Rows Affected = 2
echo update t1 set f1=100a;
Statement Executed: Rows Affected = 2
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	100.000000	
	100.000000	
	
echo select * from t1 where f1=10a;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo create table t1(f1 float);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(100a);
Statement Executed: Rows Affected = 1
echo update t1 set f1=10a;
Statement Executed: Rows Affected = 2
echo update t1 set f1=100a;
Statement Executed: Rows Affected = 2
echo update t1 f1=100 where f1=10a;
Statement prepare failed with error -19
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	100.000000	
	100.000000	
	
echo select * from t1 where f1=10a;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
