Network CSql
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
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	12	C	
	13	D	
	14	14	
	50	E	
	This is really a ve	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'UPP%';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 LIKE 'upp%';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'upper%letter';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 LIKE 'upper____letter';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 like 'UP__R%SE';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 = 'B';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 = 'UPPER';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
echo select * from t1 where f1 like 'UP__R%SE' and f2 like 'UPPER';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	UPPERCASE	UPPER	
	
Statement Executed
