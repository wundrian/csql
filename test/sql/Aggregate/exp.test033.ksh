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
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 group by f1,f2;
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	10	100	Bijay	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	
	11	110	Jitendr	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	15	110	Sanjit	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	17	130	Arindam	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	
	11	NULL	Jitendr	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 group by f1,f2 having min(f4)>='K';
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	15	110	Sanjit	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 group by f1,f2;
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	15	110	Sanjit	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	17	130	Arindam	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 group by f1,f2 having min(f8)>='11:59:55';
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	15	110	Sanjit	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	17	130	Arindam	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2;
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having min(f9)>='2009-03-03 11:59:59';
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	13	130	Kishor	2009/3/4	11:59:56.0	2009/3/4 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having min(f4)>='K' and min(f8) <'11:59:56';
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 ;
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	14	100	Praba	2009/3/1	11:59:55.0	2009/3/1 11:59:59.0	
	15	110	Sanjit	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	
echo select f1,f2,min(f4),min(f7),min(f8),min(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 having min(f7)>='2009/3/2' and min(f9)<>'2009-03-01 11:59:59';
---------------------------------------------------------
	f1	f2	MIN(f4)	MIN(f7)	MIN(f8)	MIN(f9)	
---------------------------------------------------------
	12	120	Nihar	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	
	16	120	Sanjay	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	
	
echo select f7,f8,f9,min(f4) from t1 group by f7,f8,f9;
---------------------------------------------------------
	f7	f8	f9	MIN(f4)	
---------------------------------------------------------
	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	Arindam	
	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	Jitendr	
	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	Nihar	
	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	Kishor	
	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	Praba	
	2009/3/2	11:59:57.0	2009/3/2 11:59:59.0	Sanjit	
	2009/3/3	11:59:59.0	2009/3/3 11:59:59.0	Sanjay	
	2009/3/4	11:59:58.0	2009/3/4 11:59:59.0	Arindam	
	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	Bijay	
	2009/3/3	NULL	2009/3/3 11:59:59.0	Nihar	
	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	Kishor	
	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	Praba	
	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	Sanjit	
	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	Sanjay	
	
echo select f9,f7,f8,min(f4) from t1 group by f7,f8,f9;
---------------------------------------------------------
	f9	f7	f8	MIN(f4)	
---------------------------------------------------------
	2009/3/1 11:59:59.0	2009/3/1	11:59:59.0	Arindam	
	2009/3/2 11:59:59.0	2009/3/2	11:59:58.0	Jitendr	
	2009/3/3 11:59:59.0	2009/3/3	11:59:57.0	Nihar	
	2009/3/4 11:59:59.0	2009/3/4	11:59:59.0	Kishor	
	2009/3/1 11:59:59.0	2009/3/1	11:59:58.0	Praba	
	2009/3/2 11:59:59.0	2009/3/2	11:59:57.0	Sanjit	
	2009/3/3 11:59:59.0	2009/3/3	11:59:59.0	Sanjay	
	2009/3/4 11:59:59.0	2009/3/4	11:59:58.0	Arindam	
	2009/3/1 11:59:59.0	2009/3/1	11:59:57.0	Bijay	
	2009/3/3 11:59:59.0	2009/3/3	NULL	Nihar	
	2009/3/5 11:59:59.0	2009/3/5	11:59:56.0	Kishor	
	2009/3/4 11:59:59.0	2009/3/1	11:59:55.0	Praba	
	2009/3/1 11:59:59.0	2009/3/2	11:59:56.0	Sanjit	
	2009/3/3 11:59:59.0	2009/3/3	11:59:55.0	Sanjay	
	
echo select f7,f8,f9,min(f4) from t1 group by f7,f9,f8;
---------------------------------------------------------
	f7	f8	f9	MIN(f4)	
---------------------------------------------------------
	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	Arindam	
	2009/3/2	11:59:58.0	2009/3/2 11:59:59.0	Jitendr	
	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	Nihar	
	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	Kishor	
	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	Praba	
	2009/3/2	11:59:57.0	2009/3/2 11:59:59.0	Sanjit	
	2009/3/3	11:59:59.0	2009/3/3 11:59:59.0	Sanjay	
	2009/3/4	11:59:58.0	2009/3/4 11:59:59.0	Arindam	
	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	Bijay	
	2009/3/3	NULL	2009/3/3 11:59:59.0	Nihar	
	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	Kishor	
	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	Praba	
	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	Sanjit	
	2009/3/3	11:59:55.0	2009/3/3 11:59:59.0	Sanjay	
	
echo select f7,f8,f9,min(f4) from t1 group by f7,f9,f8 having min(f4)>='K' and min(f4) <'Q';
---------------------------------------------------------
	f7	f8	f9	MIN(f4)	
---------------------------------------------------------
	2009/3/3	11:59:57.0	2009/3/3 11:59:59.0	Nihar	
	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	Kishor	
	2009/3/1	11:59:58.0	2009/3/1 11:59:59.0	Praba	
	2009/3/3	NULL	2009/3/3 11:59:59.0	Nihar	
	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	Kishor	
	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	Praba	
	
echo select f4,f8,f9,min(f7) from t1 group by f4,f8,f9;
---------------------------------------------------------
	f4	f8	f9	MIN(f7)	
---------------------------------------------------------
	Bijay	11:59:59.0	2009/3/1 11:59:59.0	2009/3/1	
	Jitendr	11:59:58.0	2009/3/2 11:59:59.0	2009/3/2	
	Nihar	11:59:57.0	2009/3/3 11:59:59.0	2009/3/3	
	Kishor	11:59:59.0	2009/3/4 11:59:59.0	2009/3/4	
	Praba	11:59:58.0	2009/3/1 11:59:59.0	2009/3/1	
	Sanjit	11:59:57.0	2009/3/2 11:59:59.0	2009/3/2	
	Sanjay	11:59:59.0	2009/3/3 11:59:59.0	2009/3/3	
	Arindam	11:59:58.0	2009/3/4 11:59:59.0	2009/3/4	
	Bijay	11:59:57.0	2009/3/1 11:59:59.0	2009/3/1	
	Nihar	NULL	2009/3/3 11:59:59.0	2009/3/3	
	Kishor	11:59:56.0	2009/3/5 11:59:59.0	2009/3/5	
	Praba	11:59:55.0	2009/3/4 11:59:59.0	2009/3/1	
	Sanjit	11:59:56.0	2009/3/1 11:59:59.0	2009/3/2	
	Sanjay	11:59:55.0	2009/3/3 11:59:59.0	2009/3/3	
	Arindam	11:59:59.0	2009/3/1 11:59:59.0	2009/3/1	
	
echo select f4,f8,f9,min(f7) from t1 group by f4,f8,f9 having min(f7)<='2009-03-04' and min(f7) >'2009-03-02' ;
---------------------------------------------------------
	f4	f8	f9	MIN(f7)	
---------------------------------------------------------
	Nihar	11:59:57.0	2009/3/3 11:59:59.0	2009/3/3	
	Kishor	11:59:59.0	2009/3/4 11:59:59.0	2009/3/4	
	Sanjay	11:59:59.0	2009/3/3 11:59:59.0	2009/3/3	
	Arindam	11:59:58.0	2009/3/4 11:59:59.0	2009/3/4	
	Nihar	NULL	2009/3/3 11:59:59.0	2009/3/3	
	Sanjay	11:59:55.0	2009/3/3 11:59:59.0	2009/3/3	
	
echo select f9,f7,f4,min(f8) from t1 group by f4,f7,f9;
---------------------------------------------------------
	f9	f7	f4	MIN(f8)	
---------------------------------------------------------
	2009/3/1 11:59:59.0	2009/3/1	Bijay	11:59:57.0	
	2009/3/2 11:59:59.0	2009/3/2	Jitendr	11:59:58.0	
	2009/3/3 11:59:59.0	2009/3/3	Nihar	11:59:57.0	
	2009/3/4 11:59:59.0	2009/3/4	Kishor	11:59:59.0	
	2009/3/1 11:59:59.0	2009/3/1	Praba	11:59:58.0	
	2009/3/2 11:59:59.0	2009/3/2	Sanjit	11:59:57.0	
	2009/3/3 11:59:59.0	2009/3/3	Sanjay	11:59:55.0	
	2009/3/4 11:59:59.0	2009/3/4	Arindam	11:59:58.0	
	2009/3/5 11:59:59.0	2009/3/5	Kishor	11:59:56.0	
	2009/3/4 11:59:59.0	2009/3/1	Praba	11:59:55.0	
	2009/3/1 11:59:59.0	2009/3/2	Sanjit	11:59:56.0	
	2009/3/1 11:59:59.0	2009/3/1	Arindam	11:59:59.0	
	
echo select f9,f7,f4,min(f8) from t1 group by f4,f7,f9 having min(f8)<='11:59:59' and min(f8) >'11:59:57' ;
---------------------------------------------------------
	f9	f7	f4	MIN(f8)	
---------------------------------------------------------
	2009/3/2 11:59:59.0	2009/3/2	Jitendr	11:59:58.0	
	2009/3/4 11:59:59.0	2009/3/4	Kishor	11:59:59.0	
	2009/3/1 11:59:59.0	2009/3/1	Praba	11:59:58.0	
	2009/3/4 11:59:59.0	2009/3/4	Arindam	11:59:58.0	
	2009/3/1 11:59:59.0	2009/3/1	Arindam	11:59:59.0	
	
echo select f7,f8,f4,min(f9) from t1 group by f4,f7,f8;
---------------------------------------------------------
	f7	f8	f4	MIN(f9)	
---------------------------------------------------------
	2009/3/1	11:59:59.0	Bijay	2009/3/1 11:59:59.0	
	2009/3/2	11:59:58.0	Jitendr	2009/3/2 11:59:59.0	
	2009/3/3	11:59:57.0	Nihar	2009/3/3 11:59:59.0	
	2009/3/4	11:59:59.0	Kishor	2009/3/4 11:59:59.0	
	2009/3/1	11:59:58.0	Praba	2009/3/1 11:59:59.0	
	2009/3/2	11:59:57.0	Sanjit	2009/3/2 11:59:59.0	
	2009/3/3	11:59:59.0	Sanjay	2009/3/3 11:59:59.0	
	2009/3/4	11:59:58.0	Arindam	2009/3/4 11:59:59.0	
	2009/3/1	11:59:57.0	Bijay	2009/3/1 11:59:59.0	
	2009/3/3	NULL	Nihar	2009/3/3 11:59:59.0	
	2009/3/5	11:59:56.0	Kishor	2009/3/5 11:59:59.0	
	2009/3/1	11:59:55.0	Praba	2009/3/4 11:59:59.0	
	2009/3/2	11:59:56.0	Sanjit	2009/3/1 11:59:59.0	
	2009/3/3	11:59:55.0	Sanjay	2009/3/3 11:59:59.0	
	2009/3/1	11:59:59.0	Arindam	2009/3/1 11:59:59.0	
	
echo select f7,f8,f4,min(f9) from t1 group by f4,f7,f8 having min(f9)<='2009-03-05 11:59:59' and min(f9) >'2009-03-02 11:59:59' ;
---------------------------------------------------------
	f7	f8	f4	MIN(f9)	
---------------------------------------------------------
	2009/3/3	11:59:57.0	Nihar	2009/3/3 11:59:59.0	
	2009/3/4	11:59:59.0	Kishor	2009/3/4 11:59:59.0	
	2009/3/3	11:59:59.0	Sanjay	2009/3/3 11:59:59.0	
	2009/3/4	11:59:58.0	Arindam	2009/3/4 11:59:59.0	
	2009/3/3	NULL	Nihar	2009/3/3 11:59:59.0	
	2009/3/5	11:59:56.0	Kishor	2009/3/5 11:59:59.0	
	2009/3/1	11:59:55.0	Praba	2009/3/4 11:59:59.0	
	2009/3/3	11:59:55.0	Sanjay	2009/3/3 11:59:59.0	
	
Statement Executed
