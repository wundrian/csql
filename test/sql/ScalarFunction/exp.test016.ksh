echo Create table t1(f1 timestamp, f2 timestamp);
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
	2001/1/1 1:1:1.0	2001/1/1 2:1:1.0	
	2002/1/1 1:1:1.0	2001/2/1 1:1:1.0	
	2003/1/1 1:1:1.0	2001/3/1 1:1:1.0	
	2004/1/1 1:1:1.0	2001/4/1 1:1:1.0	
	2005/1/1 1:1:1.0	2001/5/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 10 month) ='2002-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1 1:1:1.0	2001/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 10 month)<='2002-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/1/1 2:1:1.0	
	2002/1/1 1:1:1.0	2001/2/1 1:1:1.0	
	2003/1/1 1:1:1.0	2001/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 10 month) >'2002-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2004/1/1 1:1:1.0	2001/4/1 1:1:1.0	
	2005/1/1 1:1:1.0	2001/5/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 10 month)!='2002-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/1/1 2:1:1.0	
	2002/1/1 1:1:1.0	2001/2/1 1:1:1.0	
	2004/1/1 1:1:1.0	2001/4/1 1:1:1.0	
	2005/1/1 1:1:1.0	2001/5/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 130 month) ='2012-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1 1:1:1.0	2001/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 130 month)<='2012-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/1/1 2:1:1.0	
	2002/1/1 1:1:1.0	2001/2/1 1:1:1.0	
	2003/1/1 1:1:1.0	2001/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 130 month) >'2012-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2004/1/1 1:1:1.0	2001/4/1 1:1:1.0	
	2005/1/1 1:1:1.0	2001/5/1 1:1:1.0	
	
echo select * from t1 where timestamp_add(f2 interval 130 month)!='2012-01-01 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/1/1 2:1:1.0	
	2002/1/1 1:1:1.0	2001/2/1 1:1:1.0	
	2004/1/1 1:1:1.0	2001/4/1 1:1:1.0	
	2005/1/1 1:1:1.0	2001/5/1 1:1:1.0	
	
Statement Executed
