echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo create index idx1 on t1(f1,f2) hash unique;
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,2,4);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int not null,f2 int not null,f3 int);
Statement Executed
echo create index idx2 on t1(f1,f2) hash primary;
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,2,4);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int not null,f2 int,f3 int,primary key(f1,f2));
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,2,4);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo create index idx1 on t1(f1,f3) hash unique;
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,4,3);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int not null,f2 int,f3 int not null);
Statement Executed
echo create index idx2 on t1(f1,f3) hash primary;
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,4,3);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int not null,f2 int,f3 int,primary key(f1,f3));
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,4,3);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	2	3	
	
echo drop table t1;
Statement Executed
echo create table t1(f1 int,f2 int,f3 int,f4 int,primary key(f2,f4));
Statement Executed
echo insert into t1 values(1,2,3,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(1,2,5,4);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	2	3	4	
	
echo drop table t1;
Statement Executed
