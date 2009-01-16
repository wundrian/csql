echo create table t1 (f1 int, f2 int,f3 int);
Statement Executed
echo insert into t1 values(10,10,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(20,10,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(30,10,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(40,10,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(50,10,10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(60,10,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	10	10	10	
	20	10	10	
	30	10	10	
	40	10	10	
	50	10	10	
	60	10	10	
	
echo update t1 set f1=f1+f2+f3+7,f2=f3+23+f1,f3=12;
Statement Executed: Rows Affected = 6
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	37	43	12	
	47	53	12	
	57	63	12	
	67	73	12	
	77	83	12	
	87	93	12	
	
echo update t1 set f1=f2/f3+7,f2=f3+23+f1,f3=f2 where f3=12;
Statement Executed: Rows Affected = 6
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	10	72	43	
	11	82	53	
	12	92	63	
	13	102	73	
	13	112	83	
	14	122	93	
	
echo create table t2 (f1 tinyint, f2 bigint,f3 int);
Statement Executed
echo insert into t2 values(60,1110,5110);
Statement Executed: Rows Affected = 1
echo insert into t2 values(70,1115,1510);
Statement Executed: Rows Affected = 1
echo insert into t2 values(80,1150,1150);
Statement Executed: Rows Affected = 1
echo insert into t2 values(90,1510,1115);
Statement Executed: Rows Affected = 1
echo insert into t2 values(50,5110,1110);
Statement Executed: Rows Affected = 1
echo select * from t2;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	60	1110	5110	
	70	1115	1510	
	80	1150	1150	
	90	1510	1115	
	50	5110	1110	
	
echo update t2 set f1=NULL,f2=f1+f2+f3+10 where f2>1122;
Statement Executed: Rows Affected = 3
echo select * from t2;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	60	1110	5110	
	70	1115	1510	
	NULL	2390	1150	
	NULL	2725	1115	
	NULL	6280	1110	
	
echo update t2 set f2=f2+123 ,f3=23+f2;
Statement Executed: Rows Affected = 5
echo select * from t2;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	60	1233	1133	
	70	1238	1138	
	NULL	2513	2413	
	NULL	2848	2748	
	NULL	6403	6303	
	
echo drop table t1;
Statement Executed
echo drop table t2;
Statement Executed
