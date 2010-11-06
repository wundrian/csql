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
	2001/1/1	2005/1/1	
	2002/1/1	2006/1/1	
	2003/1/1	2007/1/1	
	2004/1/1	2009/1/1	
	2005/1/1	2010/1/1	
	
echo select * from t1 where date_add(f1 interval 4 year) = '2007-01-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1	2007/1/1	
	
echo select * from t1 where date_add(f1 interval 4 year) = f2;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2005/1/1	
	2002/1/1	2006/1/1	
	2003/1/1	2007/1/1	
	
echo select * from t1 where date_add(f1 interval 4 year) <= '2007-01-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2005/1/1	
	2002/1/1	2006/1/1	
	2003/1/1	2007/1/1	
	
echo select * from t1 where date_add(f1 interval 4 year) > '2007-01-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2004/1/1	2009/1/1	
	2005/1/1	2010/1/1	
	
Statement Executed
