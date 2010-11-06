Network CSql
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
	t1.f1	t1.f2	
---------------------------------------------------------
	0.107374	10.234000	
	-0.107374	11.234000	
	12.234000	11.456000	
	13.123000	11.987000	
	14.467000	12.123000	
	50.345000	10.234000	
	
echo select * from t1 where f1 BETWEEN 0.1073741822 AND 0.1073741824
select * from t1 where  f1 BETWEEN 0.1073741822 AND 0.1073741824;
echo select * from t1 where f1 BETWEEN -0.1073741824 AND -0.1073741822
select * from t1 where  f1 BETWEEN -0.1073741824 AND -0.1073741822;
echo select * from t1 where f2 < f1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12.234000	11.456000	
	13.123000	11.987000	
	14.467000	12.123000	
	50.345000	10.234000	
	
echo update t1 set f2 = 3.4345 where f2 >11;
Statement Executed: Rows Affected = 4
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	0.107374	10.234000	
	-0.107374	3.433500	
	12.234000	3.433500	
	13.123000	3.433500	
	14.467000	3.433500	
	50.345000	10.234000	
	
echo delete from t1 where f1 > 14.234;
Statement Executed: Rows Affected = 2
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	0.107374	10.234000	
	-0.107374	3.433500	
	12.234000	3.433500	
	13.123000	3.433500	
	
Statement Executed
