echo create table t1(f1 int, f2 varchar(10), primary key(f1));
Statement Executed
echo create table t2(f1 int, f2 varchar(10), foreign key(f1) references t1(f1));
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	CSQL1	
	2	CSQL2	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	1	Nihar	
	2	Bijay	
	1	Kishor	
	2	Jitendra	
	
echo truncate table t1;
Statement execute failed with error -36
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	CSQL1	
	2	CSQL2	
	
echo truncate table t2;
Statement Executed: Rows Affected = 4
echo truncate table t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	
Statement Executed
Statement Executed
