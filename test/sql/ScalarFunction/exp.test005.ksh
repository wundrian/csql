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
	2008/1/20	2010/1/1	
	2009/4/20	2011/2/1	
	2010/2/27	2010/3/1	
	2011/2/28	2013/2/1	
	2012/2/29	2014/1/1	
	
echo select * from t1 where date_add(f1 interval 2 day) = '2010-03-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2010/2/27	2010/3/1	
	
echo select * from t1 where date_add(f1 interval 15 day) <= '2008-02-04';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2008/1/20	2010/1/1	
	
echo select * from t1 where date_add(f1 interval 15 day) >= '2009-05-05';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2009/4/20	2011/2/1	
	2010/2/27	2010/3/1	
	2011/2/28	2013/2/1	
	2012/2/29	2014/1/1	
	
echo select * from t1 where date_add(f1 interval 40 day) <= '2008-03-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2008/1/20	2010/1/1	
	
echo select * from t1 where date_add(f1 interval 40 day) >= '2009-05-30';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2009/4/20	2011/2/1	
	2010/2/27	2010/3/1	
	2011/2/28	2013/2/1	
	2012/2/29	2014/1/1	
	
echo select * from t1 where date_add(f1 interval 365 day) <= '2010-04-20';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2008/1/20	2010/1/1	
	2009/4/20	2011/2/1	
	
echo select * from t1 where date_add(f1 interval 366 day) >= '2010-04-21';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2009/4/20	2011/2/1	
	2010/2/27	2010/3/1	
	2011/2/28	2013/2/1	
	2012/2/29	2014/1/1	
	
Statement Executed