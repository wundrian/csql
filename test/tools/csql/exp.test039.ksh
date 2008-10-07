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
	f1	f2	f3	
---------------------------------------------------------
	10	india	1234321	
	20	INDIA	NULL	
	NULL	orissa	123432	
	30	NULL	123432	
	
echo select f1,f2,f3 from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	10	india	1234321	
	20	INDIA	NULL	
	NULL	orissa	123432	
	30	NULL	123432	
	
echo select f2,f1,f3 from t1;
---------------------------------------------------------
	f2	f1	f3	
---------------------------------------------------------
	india	10	1234321	
	INDIA	20	NULL	
	orissa	NULL	123432	
	NULL	30	123432	
	
echo select f1,f1,f1,f1,f1 from t1;
---------------------------------------------------------
	f1	f1	f1	f1	f1	
---------------------------------------------------------
	10	10	10	10	10	
	20	20	20	20	20	
	NULL	NULL	NULL	NULL	NULL	
	30	30	30	30	30	
	
echo select f2,f2,f2,f2,f2 from t1;
---------------------------------------------------------
	f2	f2	f2	f2	f2	
---------------------------------------------------------
	india	india	india	india	india	
	INDIA	INDIA	INDIA	INDIA	INDIA	
	orissa	orissa	orissa	orissa	orissa	
	NULL	NULL	NULL	NULL	NULL	
	
echo select f3,f3,f3,f3,f3 from t1;
---------------------------------------------------------
	f3	f3	f3	f3	f3	
---------------------------------------------------------
	1234321	1234321	1234321	1234321	1234321	
	NULL	NULL	NULL	NULL	NULL	
	123432	123432	123432	123432	123432	
	123432	123432	123432	123432	123432	
	
echo select f1,f1,f2,f2,f3,f3 from t1;
---------------------------------------------------------
	f1	f1	f2	f2	f3	f3	
---------------------------------------------------------
	10	10	india	india	1234321	1234321	
	20	20	INDIA	INDIA	NULL	NULL	
	NULL	NULL	orissa	orissa	123432	123432	
	30	30	NULL	NULL	123432	123432	
	
echo select f1,f2,f1,f3,f3,f2,f1,f3 from t1;
---------------------------------------------------------
	f1	f2	f1	f3	f3	f2	f1	f3	
---------------------------------------------------------
	10	india	10	1234321	1234321	india	10	1234321	
	20	INDIA	20	NULL	NULL	INDIA	20	NULL	
	NULL	orissa	NULL	123432	123432	orissa	NULL	123432	
	30	NULL	30	123432	123432	NULL	30	123432	
	
echo drop table t1;
Statement Executed
