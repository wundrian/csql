echo Create table t1(f1 date, f2 date);
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
	2001/5/1	2001/5/1	
	2001/6/1	2001/6/1	
	2001/7/1	2002/7/1	
	2001/8/1	2002/8/1	
	2001/9/1	2002/9/1	
	
echo select * from t1 where date_add(f1 interval 5 month) < '2001-12-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/5/1	2001/5/1	
	2001/6/1	2001/6/1	
	
echo select * from t1 where date_add(f1 interval 6 month) = '2002-01-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/7/1	2002/7/1	
	
echo select * from t1 where date_add(f1 interval 18 month)>= '2003-01-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/7/1	2002/7/1	
	2001/8/1	2002/8/1	
	2001/9/1	2002/9/1	
	
Statement Executed
