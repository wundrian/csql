echo LIKE operator char datatype testing;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
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
	10	A	
	11	B	
	12	C	
	13	D	
	14	14	
	50	E	
	This is really a ver	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'UPP%';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 LIKE 'upp%';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'upper%letter';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'upper____letter';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 like 'UP__R%SE';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 = 'B';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 = 'UPPER';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 like 'UPPER';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
Statement Executed
