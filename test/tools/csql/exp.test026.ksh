echo double data type testing;
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
	-0.000000	0.000000	
	53.000023	0.000000	
	0.000000	0.000000	
	53.000008	53.000008	
	0.000000	0.000000	
	0.000000	0.000000	
	
echo select * from t1 where f1 BETWEEN 0.1073741822 AND 0.1073741824
select * from t1 where  f1 BETWEEN 0.1073741822 AND 0.1073741824;
echo select * from t1 where f1 BETWEEN -0.1073741824 AND -0.1073741822
select * from t1 where  f1 BETWEEN -0.1073741824 AND -0.1073741822;
echo select * from t1 where f2 < f1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	53.000023	0.000000	
	0.000000	0.000000	
	53.000008	53.000008	
	0.000000	0.000000	
	0.000000	0.000000	
	
echo update t1 set f2 = 3.4345 where f2 >11;
Statement Executed: Rows Affected = 6
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	-0.000000	-0.000000	
	53.000023	-0.000000	
	0.000000	-0.000000	
	53.000008	-0.000000	
	0.000000	-0.000000	
	0.000000	-0.000000	
	
echo delete from t1 where f1 > 14.234;
Statement Executed: Rows Affected = 5
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	-0.000000	-0.000000	
	
Statement Executed
