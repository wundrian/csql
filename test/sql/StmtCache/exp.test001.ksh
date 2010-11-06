echo create table t1(f1 int, f2 timestamp);
Statement Executed
echo insert into t1 values(1,'now');
Statement Executed: Rows Affected = 1
echo select count(*) from t1 where f2 < 'now';
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	1	
	
echo insert into t1 values(2,'now');
Statement Executed: Rows Affected = 1
echo select count(*) from t1 where f2 < 'now';
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	2	
	
Statement Executed
