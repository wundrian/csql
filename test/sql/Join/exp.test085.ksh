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
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	10	100	1000	Bijay	1000.000000	100000.000000	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	
	11	110	1100	Jitendr	2000.000000	200000.000000	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	
	12	120	1000	Nihar	3000.000000	300000.000000	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	1500	Kishor	4000.000000	400000.000000	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	
	14	100	1000	Praba	5000.000000	500000.000000	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	t2.f4	t2.f5	t2.f6	t2.f7	t2.f8	t2.f9	
---------------------------------------------------------
	13	110	1100	Sanjit	6000.000000	600000.000000	2009/3/2	11:59:57.0	2009/3/2 11:59:59.0	
	16	120	1000	Sanjay	6500.000000	700000.000000	2009/3/3	11:59:59.0	2009/3/3 11:59:59.0	
	17	130	1100	Arindam	8000.000000	800000.000000	2009/3/4	11:59:58.0	2009/3/4 11:59:59.0	
	10	100	1000	Bijay	9000.000000	900000.000000	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	
	11	110	1100	Jitendr	1000.000000	100000.000000	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	
	
echo select * from t3;
---------------------------------------------------------
	t3.f1	t3.f2	t3.f3	t3.f4	t3.f5	t3.f6	t3.f7	t3.f8	t3.f9	
---------------------------------------------------------
	12	120	1000	Nihar	2000.000000	200000.000000	2009/3/3	11:59:56.0	2009/3/3 11:59:59.0	
	13	130	1100	Kishor	3000.000000	300000.000000	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	
	14	100	1000	Praba	4000.000000	400000.000000	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	
	15	110	1100	Sanjit	5000.000000	500000.000000	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	1000	Sanjay	6000.000000	600000.000000	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	
echo select t1.f1, t1.f2, t2.f1, t2.f2, t3.f1, t3.f2 from t1 inner join t2 on t1.f1 = t2.f1 inner join t3 on t2.f1 = t3.f1 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f2, t2.f1, t2.f2, t3.f1, t3.f2 from t1 inner join t2 on t1.f2 = t2.f2 inner join t3 on t2.f2 = t3.f2 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f3, t2.f1, t2.f3, t3.f1, t3.f3 from t1 inner join t2 on t1.f3 = t2.f3 inner join t3 on t2.f3 = t3.f3 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f4, t2.f1, t2.f4, t3.f1, t3.f4 from t1 inner join t2 on t1.f4 = t2.f4 inner join t3 on t2.f4 = t3.f4 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f5, t2.f1, t2.f5, t3.f1, t3.f5 from t1 inner join t2 on t1.f5 = t2.f5 inner join t3 on t2.f5 = t3.f5 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f6, t2.f1, t2.f6, t3.f1, t3.f6 from t1 inner join t2 on t1.f6 = t2.f6 inner join t3 on t2.f6 = t3.f6 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f7, t2.f1, t2.f7, t3.f1, t3.f7 from t1 inner join t2 on t1.f7 = t2.f7 inner join t3 on t2.f7 = t3.f7 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f8, t2.f1, t2.f8, t3.f1, t3.f8 from t1 inner join t2 on t1.f8 = t2.f8 inner join t3 on t2.f8 = t3.f8 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
echo select t1.f1, t1.f9, t2.f1, t2.f9, t3.f1, t3.f9 from t1 inner join t2 on t1.f9 = t2.f9 inner join t3 on t2.f9 = t3.f9 inner join t1 on t3.f1 = t1.f1;
Statement prepare failed with error -19
Statement Executed
Statement Executed
Statement Executed
