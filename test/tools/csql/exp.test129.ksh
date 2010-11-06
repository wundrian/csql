echo CREATE TABLE t1(f1 SMALLINT,f2 INT,f3 BIGINT,f4 FLOAT,f5 DOUBLE,f6 CHAR(20),f7 DATE,f8 TIME,f9 TIMESTAMP);
Statement Executed
echo INSERT INTO t1 values(1,111,11111111,1111.1111,1111111.111111,'AAAA','2001-01-01','01:01:01','2001-01-01 01:01:01');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 values(2,222,22222222,2222.2222,2222222.222222,'BBBB','2002-02-02','02:02:02','2002-02-02 02:02:02');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 values(4,444,44444444,4444.4444,4444444.444444,'CCCC','2004-04-04','04:04:04','2004-04-04 04:04:04');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 values(3,333,33333333,3333.3333,3333333.333333,'CCCC','2003-03-03','03:03:03','2003-03-03 03:03:03');
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	111	11111111	1111.111084	1111111.111111	AAAA	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	2	222	22222222	2222.222168	2222222.222222	BBBB	2002/2/2	2:2:2.0	2002/2/2 2:2:2.0	
	4	444	44444444	4444.444336	4444444.444444	CCCC	2004/4/4	4:4:4.0	2004/4/4 4:4:4.0	
	3	333	33333333	3333.333252	3333333.333333	CCCC	2003/3/3	3:3:3.0	2003/3/3 3:3:3.0	
	
echo SELECT COUNT(*) FROM t1;
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f1) FROM t1;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f2) FROM t1;
---------------------------------------------------------
	COUNT(f2)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f3) FROM t1;
---------------------------------------------------------
	COUNT(f3)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f4) FROM t1;
---------------------------------------------------------
	COUNT(f4)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f5) FROM t1;
---------------------------------------------------------
	COUNT(f5)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f6) FROM t1;
---------------------------------------------------------
	COUNT(f6)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f7) FROM t1;
---------------------------------------------------------
	COUNT(f7)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f8) FROM t1;
---------------------------------------------------------
	COUNT(f8)	
---------------------------------------------------------
	4	
	
echo SELECT COUNT(f9) FROM t1;
---------------------------------------------------------
	COUNT(f9)	
---------------------------------------------------------
	4	
	
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	111	11111111	1111.111084	1111111.111111	AAAA	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	2	222	22222222	2222.222168	2222222.222222	BBBB	2002/2/2	2:2:2.0	2002/2/2 2:2:2.0	
	4	444	44444444	4444.444336	4444444.444444	CCCC	2004/4/4	4:4:4.0	2004/4/4 4:4:4.0	
	3	333	33333333	3333.333252	3333333.333333	CCCC	2003/3/3	3:3:3.0	2003/3/3 3:3:3.0	
	
echo SELECT SUM(f1) FROM t1;
---------------------------------------------------------
	SUM(f1)	
---------------------------------------------------------
	10	
	
echo SELECT SUM(f2) FROM t1;
---------------------------------------------------------
	SUM(f2)	
---------------------------------------------------------
	1110	
	
echo SELECT SUM(f3) FROM t1;
---------------------------------------------------------
	SUM(f3)	
---------------------------------------------------------
	111111110	
	
echo SELECT SUM(f4) FROM t1;
---------------------------------------------------------
	SUM(f4)	
---------------------------------------------------------
	11111.110352	
	
echo SELECT SUM(f5) FROM t1;
---------------------------------------------------------
	SUM(f5)	
---------------------------------------------------------
	11111111.111110	
	
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	111	11111111	1111.111084	1111111.111111	AAAA	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	2	222	22222222	2222.222168	2222222.222222	BBBB	2002/2/2	2:2:2.0	2002/2/2 2:2:2.0	
	4	444	44444444	4444.444336	4444444.444444	CCCC	2004/4/4	4:4:4.0	2004/4/4 4:4:4.0	
	3	333	33333333	3333.333252	3333333.333333	CCCC	2003/3/3	3:3:3.0	2003/3/3 3:3:3.0	
	
echo SELECT AVG(f1) FROM t1;
---------------------------------------------------------
	AVG(f1)	
---------------------------------------------------------
	2.500000	
	
echo SELECT AVG(f2) FROM t1;
---------------------------------------------------------
	AVG(f2)	
---------------------------------------------------------
	277.500000	
	
echo SELECT AVG(f3) FROM t1;
---------------------------------------------------------
	AVG(f3)	
---------------------------------------------------------
	27777777.500000	
	
echo SELECT AVG(f4) FROM t1;
---------------------------------------------------------
	AVG(f4)	
---------------------------------------------------------
	2777.777710	
	
echo SELECT AVG(f5) FROM t1;
---------------------------------------------------------
	AVG(f5)	
---------------------------------------------------------
	2777777.777777	
	
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	111	11111111	1111.111084	1111111.111111	AAAA	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	2	222	22222222	2222.222168	2222222.222222	BBBB	2002/2/2	2:2:2.0	2002/2/2 2:2:2.0	
	4	444	44444444	4444.444336	4444444.444444	CCCC	2004/4/4	4:4:4.0	2004/4/4 4:4:4.0	
	3	333	33333333	3333.333252	3333333.333333	CCCC	2003/3/3	3:3:3.0	2003/3/3 3:3:3.0	
	
echo SELECT MIN(f1) FROM t1;
---------------------------------------------------------
	MIN(f1)	
---------------------------------------------------------
	1	
	
echo SELECT MIN(f2) FROM t1;
---------------------------------------------------------
	MIN(f2)	
---------------------------------------------------------
	111	
	
echo SELECT MIN(f3) FROM t1;
---------------------------------------------------------
	MIN(f3)	
---------------------------------------------------------
	11111111	
	
echo SELECT MIN(f4) FROM t1;
---------------------------------------------------------
	MIN(f4)	
---------------------------------------------------------
	1111.111084	
	
echo SELECT MIN(f5) FROM t1;
---------------------------------------------------------
	MIN(f5)	
---------------------------------------------------------
	1111111.111111	
	
echo SELECT MIN(f7) FROM t1;
---------------------------------------------------------
	MIN(f7)	
---------------------------------------------------------
	2001/1/1	
	
echo SELECT MIN(f8) FROM t1;
---------------------------------------------------------
	MIN(f8)	
---------------------------------------------------------
	1:1:1.0	
	
echo SELECT MIN(f9) FROM t1;
---------------------------------------------------------
	MIN(f9)	
---------------------------------------------------------
	2001/1/1 1:1:1.0	
	
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	111	11111111	1111.111084	1111111.111111	AAAA	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	2	222	22222222	2222.222168	2222222.222222	BBBB	2002/2/2	2:2:2.0	2002/2/2 2:2:2.0	
	4	444	44444444	4444.444336	4444444.444444	CCCC	2004/4/4	4:4:4.0	2004/4/4 4:4:4.0	
	3	333	33333333	3333.333252	3333333.333333	CCCC	2003/3/3	3:3:3.0	2003/3/3 3:3:3.0	
	
echo SELECT MAX(f1) FROM t1;
---------------------------------------------------------
	MAX(f1)	
---------------------------------------------------------
	4	
	
echo SELECT MAX(f2) FROM t1;
---------------------------------------------------------
	MAX(f2)	
---------------------------------------------------------
	444	
	
echo SELECT MAX(f3) FROM t1;
---------------------------------------------------------
	MAX(f3)	
---------------------------------------------------------
	44444444	
	
echo SELECT MAX(f4) FROM t1;
---------------------------------------------------------
	MAX(f4)	
---------------------------------------------------------
	4444.444336	
	
echo SELECT MAX(f5) FROM t1;
---------------------------------------------------------
	MAX(f5)	
---------------------------------------------------------
	4444444.444444	
	
echo SELECT MAX(f7) FROM t1;
---------------------------------------------------------
	MAX(f7)	
---------------------------------------------------------
	2004/4/4	
	
echo SELECT MAX(f8) FROM t1;
---------------------------------------------------------
	MAX(f8)	
---------------------------------------------------------
	4:4:4.0	
	
echo SELECT MAX(f9) FROM t1;
---------------------------------------------------------
	MAX(f9)	
---------------------------------------------------------
	2004/4/4 4:4:4.0	
	
echo SELECT COUNT(*),COUNT(f5),SUM(F1),AVG(f3),MIN(f5),MAX(f8) FROM t1;
---------------------------------------------------------
	COUNT(*)	COUNT(f5)	SUM(f1)	AVG(f3)	MIN(f5)	MAX(f8)	
---------------------------------------------------------
	4	4	10	27777777.500000	1111111.111111	4:4:4.0	
	
Statement Executed
