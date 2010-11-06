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
	2001/1/1 1:1:1.0	2001/5/10 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/10 1:1:1.0	
	2003/1/1 1:1:1.0	2003/3/10 1:1:1.0	
	2004/1/1 1:1:1.0	2004/3/10 1:1:1.0	
	2005/1/1 1:1:1.0	2005/2/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 15 day) ='2001-04-25 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/5/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 15 day)<='2002-02-23 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/5/10 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 15 day)>='2003-02-23 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1 1:1:1.0	2003/3/10 1:1:1.0	
	2004/1/1 1:1:1.0	2004/3/10 1:1:1.0	
	2005/1/1 1:1:1.0	2005/2/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 15 day) ='2004-02-24 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2004/1/1 1:1:1.0	2004/3/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 15 day)!='2005-01-26 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/5/10 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/10 1:1:1.0	
	2003/1/1 1:1:1.0	2003/3/10 1:1:1.0	
	2004/1/1 1:1:1.0	2004/3/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 45 day) ='2004-12-27 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2005/1/1 1:1:1.0	2005/2/10 1:1:1.0	
	
echo select * from t1 where timestamp_sub(f2 interval 45 day)!='2004-12-27 01:01:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1 1:1:1.0	2001/5/10 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/10 1:1:1.0	
	2003/1/1 1:1:1.0	2003/3/10 1:1:1.0	
	2004/1/1 1:1:1.0	2004/3/10 1:1:1.0	
	
Statement Executed
