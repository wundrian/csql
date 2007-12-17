echo UPDATE and DELETE testing;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	20	
	11	21	
	12	22	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where f1 = 100;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	50	50	
	
echo update t1 set f2 = 100;
Statement Executed: Rows Affected = 6
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	100	
	11	100	
	12	100	
	13	100	
	14	100	
	50	100	
	
echo update t1 set f2 = 200 where f1 =50;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	100	
	11	100	
	12	100	
	13	100	
	14	100	
	50	200	
	
echo delete from t1 where f1 = 50;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	100	
	11	100	
	12	100	
	13	100	
	14	100	
	
echo delete from t1;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
Statement Executed
