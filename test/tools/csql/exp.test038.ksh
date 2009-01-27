echo create table t1 (f1 int, f2 char(10), f3 bigint);
Statement Executed
echo insert into t1 values(10,'india',1234321);
Statement Executed: Rows Affected = 1
echo insert into t1 (f1, f2 ) values(20,'INDIA');
Statement Executed: Rows Affected = 1
echo insert into t1 (f2, f3 ) values('orissa',123432);
Statement Executed: Rows Affected = 1
echo insert into t1 (f1, f3 ) values(30,123432);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	10	india	1234321	
	20	INDIA	NULL	
	NULL	orissa	123432	
	30	NULL	123432	
	
echo update t1 set f1=10;
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	10	india	1234321	
	10	INDIA	NULL	
	10	orissa	123432	
	10	NULL	123432	
	
echo update t1 set f2='hello';
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	10	hello	1234321	
	10	hello	NULL	
	10	hello	123432	
	10	hello	123432	
	
echo update t1 set f3=10000;
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	10	hello	10000	
	10	hello	10000	
	10	hello	10000	
	10	hello	10000	
	
echo create table t2 (f1 tinyint, f2 float);
Statement Executed
echo insert into t2 values (112, 235.50);
Statement Executed: Rows Affected = 1
echo insert into t2 (f1) values (220);
Statement Executed: Rows Affected = 1
echo insert into t2 (f2) values (100.50);
Statement Executed: Rows Affected = 1
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	112	235.500000	
	-36	NULL	
	NULL	100.500000	
	
echo update t2 set f2=250.50;
Statement Executed: Rows Affected = 3
echo update t2 set f1=125;
Statement Executed: Rows Affected = 3
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	125	250.500000	
	125	250.500000	
	125	250.500000	
	
echo drop table t1;
Statement Executed
echo drop table t2;
Statement Executed
