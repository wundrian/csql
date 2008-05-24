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
	This is really a ver	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '10';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	A	
	
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
	Illegal Operator:Not Supported for String

echo select * from t1 where f1 = '12' OR  f1 > '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	C	
	14	14	
	50	E	
	This is really a ver	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '12' OR f2 = '13';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	C	
	
echo select * from t1 where f1 = '12' OR f2 < '22';
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
	
echo select * from t1 where NOT f1 = '12';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	A	
	11	B	
	13	D	
	14	14	
	50	E	
	This is really a ver	E	
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
	13	D	
	14	14	
	50	E	
	This is really a ver	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where NOT f1 != '12';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	C	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	14	14	
	
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

echo update t1 set f2 = '2' where f1 != f2;
Statement Executed: Rows Affected = 10
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	50	2	
	This is really a ver	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
echo update t1 set f2 = '3' where f1 = '50';
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	50	3	
	This is really a ver	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	This is really a ver	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
Statement Executed
