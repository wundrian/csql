echo Description:BETWEEN and IN test;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo  select * from t1 where f1 between 12 and 14;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	12	22	12	
	13	23	13	
	14	24	14	
	
echo  select * from t1 where f1 not between 12 and 14;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	10	20	10	
	11	21	11	
	50	50	50	
	
echo  select * from t1 where f3 between 12 and 14;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	12	22	12	
	13	23	13	
	14	24	14	
	
echo select * from t1 where f1 IN (12, 14, 50);
echo select * from t1 where f1 IN (12, 14, 50);
echo select * from t1 where f1 IN (12, 14, 50) AND f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) AND f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) OR f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) OR f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) AND f3 between 12 and 14;
echo select * from t1 where f1 IN (12, 14, 50) AND f3 between 12 and 14;
echo select * from t1 where f1 NOT IN (12, 14, 50);
echo select * from t1 where f1 NOT IN (12, 14, 50);
Statement Executed
