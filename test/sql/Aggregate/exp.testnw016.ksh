Network CSql
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	98	1	10	
	99	NULL	20	
	100	3	30	
	101	4	NULL	
	102	5	50	
	
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	98	1	10	
	99	2	20	
	100	NULL	NULL	
	101	4	40	
	102	NULL	50	
	
Network CSql
echo select * from t1,t2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	98	1	10	98	1	10	
	98	1	10	99	2	20	
	98	1	10	100	NULL	NULL	
	98	1	10	101	4	40	
	98	1	10	102	NULL	50	
	99	NULL	20	98	1	10	
	99	NULL	20	99	2	20	
	99	NULL	20	100	NULL	NULL	
	99	NULL	20	101	4	40	
	99	NULL	20	102	NULL	50	
	100	3	30	98	1	10	
	100	3	30	99	2	20	
	100	3	30	100	NULL	NULL	
	100	3	30	101	4	40	
	100	3	30	102	NULL	50	
	101	4	NULL	98	1	10	
	101	4	NULL	99	2	20	
	101	4	NULL	100	NULL	NULL	
	101	4	NULL	101	4	40	
	101	4	NULL	102	NULL	50	
	102	5	50	98	1	10	
	102	5	50	99	2	20	
	102	5	50	100	NULL	NULL	
	102	5	50	101	4	40	
	102	5	50	102	NULL	50	
	
echo select f2 from t1,t2;
Statement prepare failed with error -19
echo select avg(f2) from t1,t2;
Statement prepare failed with error -19
Statement Executed
Statement Executed
