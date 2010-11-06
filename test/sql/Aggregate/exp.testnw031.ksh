Network CSql
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
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
	13	130	NULL	Kishor	4000.000000	400000.000000	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	
	14	100	1000	Praba	5000.000000	500000.000000	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	
	15	110	1100	Sanjit	6000.000000	600000.000000	2009/3/2	11:59:57.0	2009/3/2 11:59:59.0	
	16	120	1000	Sanjay	NULL	700000.000000	2009/3/3	11:59:59.0	2009/3/3 11:59:59.0	
	17	130	1100	Arindam	8000.000000	800000.000000	2009/3/4	11:59:58.0	2009/3/4 11:59:59.0	
	10	100	1000	Bijay	9000.000000	900000.000000	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	
	11	NULL	1100	Jitendr	1000.000000	100000.000000	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	
	12	120	1000	Nihar	2000.000000	200000.000000	2009/3/3	NULL	2009/3/3 11:59:59.0	
	13	130	1100	Kishor	3000.000000	300000.000000	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	
	14	100	1000	Praba	4000.000000	400000.000000	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	
	15	110	NULL	Sanjit	5000.000000	500000.000000	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	1000	Sanjay	6000.000000	600000.000000	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	17	130	1100	Arindam	7000.000000	700000.000000	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	
	
Network CSql
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	2	
	11	110	1100	Jitendr	1	1	
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	11	NULL	1100	Jitendr	1	1	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 group by f2,f1,f4,f3;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	2	
	11	110	1100	Jitendr	1	1	
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	11	NULL	1100	Jitendr	1	1	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 group by f3,f1,f4,f2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	2	
	11	110	1100	Jitendr	1	1	
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	11	NULL	1100	Jitendr	1	1	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 group by f4,f3,f2,f1;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	2	
	11	110	1100	Jitendr	1	1	
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	11	NULL	1100	Jitendr	1	1	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 group by f1,f2,f3,f4 having count(f5)>=2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	2	
	12	120	1000	Nihar	2	2	
	14	100	1000	Praba	2	2	
	17	130	1100	Arindam	2	2	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 group by f4,f3,f1,f2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 group by f4,f1,f2,f3;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 group by f4,f3,f1,f2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	13	130	1100	Kishor	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f1<15 group by f2,f3,f4,f1;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	13	130	1100	Kishor	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f1<15 group by f1,f2,f4,f3;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	13	130	1100	Kishor	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4 having count(f5)>=0 and count(f5)<2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	13	130	NULL	Kishor	1	1	
	13	130	1100	Kishor	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	2	
	13	130	NULL	Kishor	1	1	
	14	100	1000	Praba	2	2	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	17	130	1100	Arindam	2	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
echo select f1,f2,f3,f4,count(f5),count(f6) from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4 having count(f5)>=0 and count(f5)<2;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	COUNT(f6)	
---------------------------------------------------------
	13	130	NULL	Kishor	1	1	
	15	110	1100	Sanjit	1	1	
	16	120	1000	Sanjay	1	2	
	13	130	1100	Kishor	1	1	
	15	110	NULL	Sanjit	1	1	
	
Statement Executed
