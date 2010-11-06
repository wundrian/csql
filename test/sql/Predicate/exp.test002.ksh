echo CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	ABCDE	
	3	ABCEF	
	4	ABCCF	
	5	ABCFF	
	6	ABCDG	
	7	ABDCG	
	
echo select * from t1 where f2 like 'ABC%';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	ABCDE	
	3	ABCEF	
	4	ABCCF	
	5	ABCFF	
	6	ABCDG	
	
echo select * from t1 where f2 like 'ABCD%';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	ABCDE	
	6	ABCDG	
	
echo select * from t1 where f2 like 'ABC%F';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3	ABCEF	
	4	ABCCF	
	5	ABCFF	
	
echo select * from t1 where f2 like 'ABCD_';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	ABCDE	
	6	ABCDG	
	
echo select * from t1 where f2 in ('ABCDE','ABCCF','ABCDG');
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	ABCDE	
	4	ABCCF	
	6	ABCDG	
	
echo select * from t1 where f2 in ('ABCDE','ADCBF','ABCDG');
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	ABCDE	
	6	ABCDG	
	
echo select * from t1 where f2 in ('ABCDE','ADCBF',NULL);
Statement prepare failed with error -19
Statement Executed
