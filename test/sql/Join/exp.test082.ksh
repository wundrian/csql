echo create table t1(f1 int,f2 int);
Statement Executed
echo insert into t1 values(1,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(5,50);
Statement Executed: Rows Affected = 1
echo create table t2(f1 int,f2 int);
Statement Executed
echo insert into t2 values(1,NULL);
Statement Executed: Rows Affected = 1
echo insert into t2 values(2,20);
Statement Executed: Rows Affected = 1
echo insert into t2 values(3,30);
Statement Executed: Rows Affected = 1
echo insert into t2 values(4,40);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	2	NULL	
	3	30	
	5	50	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	1	NULL	
	2	20	
	3	30	
	4	40	
	
echo select * from t1,t2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	1	NULL	
	1	10	2	20	
	1	10	3	30	
	1	10	4	40	
	2	NULL	1	NULL	
	2	NULL	2	20	
	2	NULL	3	30	
	2	NULL	4	40	
	3	30	1	NULL	
	3	30	2	20	
	3	30	3	30	
	3	30	4	40	
	5	50	1	NULL	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
echo select * from t1,t2 where t1.f1=t2.f1 and t1.f2=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	3	30	3	30	
	
echo select * from t1,t2 where t1.f2=t2.f2 and t1.f1=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	3	30	3	30	
	
echo select * from t1,t2 where t1.f1>t2.f1 and t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	3	30	2	20	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
echo select * from t1,t2 where t1.f2<t2.f2 and t1.f1<=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	2	20	
	1	10	3	30	
	1	10	4	40	
	3	30	4	40	
	
echo select * from t1,t2 where t1.f1=t2.f1 or t1.f2=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	1	NULL	
	2	NULL	2	20	
	3	30	3	30	
	
echo select * from t1,t2 where t1.f2=t2.f2 or t1.f1=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	1	NULL	
	2	NULL	2	20	
	3	30	3	30	
	
echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	2	NULL	1	NULL	
	3	30	1	NULL	
	3	30	2	20	
	3	30	3	30	
	5	50	1	NULL	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
echo select * from t1,t2 where t1.f2<t2.f2 or t1.f1<t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	2	20	
	1	10	3	30	
	1	10	4	40	
	2	NULL	3	30	
	2	NULL	4	40	
	3	30	4	40	
	
echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	2	NULL	1	NULL	
	3	30	1	NULL	
	3	30	2	20	
	5	50	1	NULL	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
echo select * from t1,t2 where t1.f1=t2.f1 and not(t1.f2=t2.f2);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	
echo select * from t1,t2 where t1.f2=t2.f2 and not(t1.f1=t2.f1);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	
echo select * from t1,t2 where not(t1.f1>t2.f1) and t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	
echo select * from t1,t2 where not(t1.f2<t2.f2) and not(t1.f1<t2.f1);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	3	30	2	20	
	3	30	3	30	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
echo select * from t1,t2 where not(t1.f1=t2.f1) or not(t1.f2=t2.f2);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	2	20	
	1	10	3	30	
	1	10	4	40	
	2	NULL	1	NULL	
	2	NULL	3	30	
	2	NULL	4	40	
	3	30	1	NULL	
	3	30	2	20	
	3	30	4	40	
	5	50	1	NULL	
	5	50	2	20	
	5	50	3	30	
	5	50	4	40	
	
Statement Executed
Statement Executed
