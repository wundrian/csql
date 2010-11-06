echo Create table t1(f1 date, f2 time);
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	23:59:59.0	
	2002/1/1	22:58:58.0	
	2003/1/3	12:30:30.0	
	2004/1/1	2:2:2.0	
	2005/1/1	1:1:1.0	
	
echo select * from t1 where extract(hour from f2) = 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/3	12:30:30.0	
	
echo select * from t1 where extract(hour from f2) < 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2004/1/1	2:2:2.0	
	2005/1/1	1:1:1.0	
	
echo select * from t1 where extract(hour from f2)<= 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/3	12:30:30.0	
	2004/1/1	2:2:2.0	
	2005/1/1	1:1:1.0	
	
echo select * from t1 where extract(hour from f2) > 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	23:59:59.0	
	2002/1/1	22:58:58.0	
	
echo select * from t1 where extract(hour from f2)>= 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	23:59:59.0	
	2002/1/1	22:58:58.0	
	2003/1/3	12:30:30.0	
	
echo select * from t1 where extract(hour from f2)!= 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	23:59:59.0	
	2002/1/1	22:58:58.0	
	2004/1/1	2:2:2.0	
	2005/1/1	1:1:1.0	
	
Statement Executed
