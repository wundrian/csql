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
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	10000.000000	2	1000000.000000	
	11	110	1100	Jitendr	1	2000.000000	1	200000.000000	
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	15	110	1100	Sanjit	1	6000.000000	1	600000.000000	
	16	120	1000	Sanjay	1	6000.000000	2	1300000.000000	
	17	130	1100	Arindam	2	15000.000000	2	1500000.000000	
	11	NULL	1100	Jitendr	1	1000.000000	1	100000.000000	
	13	130	1100	Kishor	1	3000.000000	1	300000.000000	
	15	110	NULL	Sanjit	1	5000.000000	1	500000.000000	
	
echo select f2,f1,f4,f3,count(f5),sum(f5), count(f6),sum(f6)  from t1 group by f1,f2,f3,f4;
---------------------------------------------------------
	f2	f1	f4	f3	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	100	10	Bijay	1000	2	10000.000000	2	1000000.000000	
	110	11	Jitendr	1100	1	2000.000000	1	200000.000000	
	120	12	Nihar	1000	2	5000.000000	2	500000.000000	
	130	13	Kishor	NULL	1	4000.000000	1	400000.000000	
	100	14	Praba	1000	2	9000.000000	2	900000.000000	
	110	15	Sanjit	1100	1	6000.000000	1	600000.000000	
	120	16	Sanjay	1000	1	6000.000000	2	1300000.000000	
	130	17	Arindam	1100	2	15000.000000	2	1500000.000000	
	NULL	11	Jitendr	1100	1	1000.000000	1	100000.000000	
	130	13	Kishor	1100	1	3000.000000	1	300000.000000	
	110	15	Sanjit	NULL	1	5000.000000	1	500000.000000	
	
echo select f3,f1,f4,f2,count(f5),sum(f5), count(f6),sum(f6)  from t1 group by f1,f2,f3,f4;
---------------------------------------------------------
	f3	f1	f4	f2	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	1000	10	Bijay	100	2	10000.000000	2	1000000.000000	
	1100	11	Jitendr	110	1	2000.000000	1	200000.000000	
	1000	12	Nihar	120	2	5000.000000	2	500000.000000	
	NULL	13	Kishor	130	1	4000.000000	1	400000.000000	
	1000	14	Praba	100	2	9000.000000	2	900000.000000	
	1100	15	Sanjit	110	1	6000.000000	1	600000.000000	
	1000	16	Sanjay	120	1	6000.000000	2	1300000.000000	
	1100	17	Arindam	130	2	15000.000000	2	1500000.000000	
	1100	11	Jitendr	NULL	1	1000.000000	1	100000.000000	
	1100	13	Kishor	130	1	3000.000000	1	300000.000000	
	NULL	15	Sanjit	110	1	5000.000000	1	500000.000000	
	
echo select f4,f3,f2,f1,count(f5),sum(f5), count(f6),sum(f6)  from t1 group by f1,f2,f3,f4;
---------------------------------------------------------
	f4	f3	f2	f1	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	Bijay	1000	100	10	2	10000.000000	2	1000000.000000	
	Jitendr	1100	110	11	1	2000.000000	1	200000.000000	
	Nihar	1000	120	12	2	5000.000000	2	500000.000000	
	Kishor	NULL	130	13	1	4000.000000	1	400000.000000	
	Praba	1000	100	14	2	9000.000000	2	900000.000000	
	Sanjit	1100	110	15	1	6000.000000	1	600000.000000	
	Sanjay	1000	120	16	1	6000.000000	2	1300000.000000	
	Arindam	1100	130	17	2	15000.000000	2	1500000.000000	
	Jitendr	1100	NULL	11	1	1000.000000	1	100000.000000	
	Kishor	1100	130	13	1	3000.000000	1	300000.000000	
	Sanjit	NULL	110	15	1	5000.000000	1	500000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 group by f1,f2,f3,f4 having sum(f5)>=5000;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	10	100	1000	Bijay	2	10000.000000	2	1000000.000000	
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	15	110	1100	Sanjit	1	6000.000000	1	600000.000000	
	16	120	1000	Sanjay	1	6000.000000	2	1300000.000000	
	17	130	1100	Arindam	2	15000.000000	2	1500000.000000	
	15	110	NULL	Sanjit	1	5000.000000	1	500000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	15	110	1100	Sanjit	1	6000.000000	1	600000.000000	
	16	120	1000	Sanjay	1	6000.000000	2	1300000.000000	
	17	130	1100	Arindam	2	15000.000000	2	1500000.000000	
	13	130	1100	Kishor	1	3000.000000	1	300000.000000	
	15	110	NULL	Sanjit	1	5000.000000	1	500000.000000	
	
echo select f4,f3,f1,f2,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
---------------------------------------------------------
	f4	f3	f1	f2	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	Nihar	1000	12	120	2	5000.000000	2	500000.000000	
	Kishor	NULL	13	130	1	4000.000000	1	400000.000000	
	Praba	1000	14	100	2	9000.000000	2	900000.000000	
	Sanjit	1100	15	110	1	6000.000000	1	600000.000000	
	Sanjay	1000	16	120	1	6000.000000	2	1300000.000000	
	Arindam	1100	17	130	2	15000.000000	2	1500000.000000	
	Kishor	1100	13	130	1	3000.000000	1	300000.000000	
	Sanjit	NULL	15	110	1	5000.000000	1	500000.000000	
	
echo select f4,f1,f2,f3,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
---------------------------------------------------------
	f4	f1	f2	f3	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	Nihar	12	120	1000	2	5000.000000	2	500000.000000	
	Kishor	13	130	NULL	1	4000.000000	1	400000.000000	
	Praba	14	100	1000	2	9000.000000	2	900000.000000	
	Sanjit	15	110	1100	1	6000.000000	1	600000.000000	
	Sanjay	16	120	1000	1	6000.000000	2	1300000.000000	
	Arindam	17	130	1100	2	15000.000000	2	1500000.000000	
	Kishor	13	130	1100	1	3000.000000	1	300000.000000	
	Sanjit	15	110	NULL	1	5000.000000	1	500000.000000	
	
echo select f4,f3,f1,f2,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
---------------------------------------------------------
	f4	f3	f1	f2	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	Nihar	1000	12	120	2	5000.000000	2	500000.000000	
	Kishor	NULL	13	130	1	4000.000000	1	400000.000000	
	Praba	1000	14	100	2	9000.000000	2	900000.000000	
	Sanjit	1100	15	110	1	6000.000000	1	600000.000000	
	Sanjay	1000	16	120	1	6000.000000	2	1300000.000000	
	Arindam	1100	17	130	2	15000.000000	2	1500000.000000	
	Kishor	1100	13	130	1	3000.000000	1	300000.000000	
	Sanjit	NULL	15	110	1	5000.000000	1	500000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	13	130	1100	Kishor	1	3000.000000	1	300000.000000	
	
echo select f2,f3,f4,f1,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
---------------------------------------------------------
	f2	f3	f4	f1	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	120	1000	Nihar	12	2	5000.000000	2	500000.000000	
	130	NULL	Kishor	13	1	4000.000000	1	400000.000000	
	100	1000	Praba	14	2	9000.000000	2	900000.000000	
	130	1100	Kishor	13	1	3000.000000	1	300000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	13	130	1100	Kishor	1	3000.000000	1	300000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4 having sum(f5)>=4000 and sum(f5)<6000;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	13	130	NULL	Kishor	1	4000.000000	1	400000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	15	110	1100	Sanjit	1	6000.000000	1	600000.000000	
	16	120	1000	Sanjay	1	6000.000000	2	1300000.000000	
	17	130	1100	Arindam	2	15000.000000	2	1500000.000000	
	13	130	1100	Kishor	1	3000.000000	1	300000.000000	
	15	110	NULL	Sanjit	1	5000.000000	1	500000.000000	
	
echo select f1,f2,f3,f4,count(f5),sum(f5), count(f6),sum(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4 having sum(f5)>=5000 and sum(f5)<10000;
---------------------------------------------------------
	f1	f2	f3	f4	COUNT(f5)	SUM(f5)	COUNT(f6)	SUM(f6)	
---------------------------------------------------------
	12	120	1000	Nihar	2	5000.000000	2	500000.000000	
	14	100	1000	Praba	2	9000.000000	2	900000.000000	
	15	110	1100	Sanjit	1	6000.000000	1	600000.000000	
	16	120	1000	Sanjay	1	6000.000000	2	1300000.000000	
	15	110	NULL	Sanjit	1	5000.000000	1	500000.000000	
	
Statement Executed
