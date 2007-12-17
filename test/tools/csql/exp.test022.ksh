echo char datatype testing;
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
	This is really a ve	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '10';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = '12' AND f1 = '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 != '12' AND f2 <= '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String

echo select * from t1 where f1 = '12' AND f2 >= '22';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = '12' OR  f1 > '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	This is really a ve	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '12' OR f2 = '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	A	
	11	B	
	12	C	
	13	D	
	14	14	
	50	E	
	This is really a ve	E	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '12' OR f2 <> '22';
echo select * from t1 where NOT f1 = '12';
---------------------------------------------------------
	f1	f2	
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
	
echo select * from t1 where f1 != '12';
---------------------------------------------------------
	f1	f2	
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
	
echo select * from t1 where NOT f1 != '12';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = f2;
echo select * from t1 where f2 between 'A' AND 'C';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String
Illegal Operator:Not Supported for String

echo select * from t1 where f1 LIKE 'UPP%';
echo select * from t1 where f1 LIKE 'upp%';
echo select * from t1 where f1 LIKE 'upper%letter';
echo select * from t1 where f1 LIKE 'upper____letter';
echo update t1 set f2 = '2' where f1 != f2;
---------------------------------------------------------
	f1	f2	
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
	
echo update t1 set f2 = '3' where f1 = '50';
Statement Executed: Rows Affected = 0
---------------------------------------------------------
	f1	f2	
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
	
Statement Executed: Rows Affected = 0
---------------------------------------------------------
	f1	f2	
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
	
Statement Executed
