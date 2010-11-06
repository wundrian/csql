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
	
echo select * from t1 where f2='ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	
echo select * from t1 where f2<'ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	4	ABCCF	
	
echo select * from t1 where f2>'ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	ABCDE	
	3	ABCEF	
	5	ABCFF	
	6	ABCDG	
	7	ABDCG	
	
echo select * from t1 where f2<='ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	4	ABCCF	
	
echo select * from t1 where f2>='ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	ABCDE	
	3	ABCEF	
	5	ABCFF	
	6	ABCDG	
	7	ABDCG	
	
echo select * from t1 where f2!='ABCD';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	ABCDE	
	3	ABCEF	
	4	ABCCF	
	5	ABCFF	
	6	ABCDG	
	7	ABDCG	
	
Statement Executed
