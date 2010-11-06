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
	
echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 IN(12,10,14) OR t1.f1=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f4	t2.f1	t2.f4	
---------------------------------------------------------
	10	Bijay	13	Sanjit	
	10	Bijay	16	Sanjay	
	10	Bijay	17	Arindam	
	10	Bijay	10	Bijay	
	10	Bijay	11	Jitendr	
	11	Jitendr	11	Jitendr	
	12	Nihar	13	Sanjit	
	12	Nihar	16	Sanjay	
	12	Nihar	17	Arindam	
	12	Nihar	10	Bijay	
	12	Nihar	11	Jitendr	
	13	Kishor	13	Sanjit	
	14	Praba	13	Sanjit	
	14	Praba	16	Sanjay	
	14	Praba	17	Arindam	
	14	Praba	10	Bijay	
	14	Praba	11	Jitendr	
	
echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 BETWEEN 11 AND 14;
---------------------------------------------------------
	t1.f1	t1.f4	t2.f1	t2.f4	
---------------------------------------------------------
	11	Jitendr	13	Sanjit	
	11	Jitendr	16	Sanjay	
	11	Jitendr	17	Arindam	
	11	Jitendr	10	Bijay	
	11	Jitendr	11	Jitendr	
	12	Nihar	13	Sanjit	
	12	Nihar	16	Sanjay	
	12	Nihar	17	Arindam	
	12	Nihar	10	Bijay	
	12	Nihar	11	Jitendr	
	13	Kishor	13	Sanjit	
	13	Kishor	16	Sanjay	
	13	Kishor	17	Arindam	
	13	Kishor	10	Bijay	
	13	Kishor	11	Jitendr	
	14	Praba	13	Sanjit	
	14	Praba	16	Sanjay	
	14	Praba	17	Arindam	
	14	Praba	10	Bijay	
	14	Praba	11	Jitendr	
	
echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f4 >= 'K' AND t1.f4 LIKE 'N%' OR t1.f4 LIKE '%a';
---------------------------------------------------------
	t1.f1	t1.f4	t2.f1	t2.f4	
---------------------------------------------------------
	12	Nihar	13	Sanjit	
	12	Nihar	16	Sanjay	
	12	Nihar	17	Arindam	
	12	Nihar	10	Bijay	
	12	Nihar	11	Jitendr	
	14	Praba	13	Sanjit	
	14	Praba	16	Sanjay	
	14	Praba	17	Arindam	
	14	Praba	10	Bijay	
	14	Praba	11	Jitendr	
	
Statement Executed
Statement Executed
Statement Executed
