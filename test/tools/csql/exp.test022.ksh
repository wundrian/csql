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
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	12	C	
	13	D	
	14	14	
	50	E	
	This is really a very b	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '10';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	
echo select * from t1 where f1 != '12' AND f2 <= '13';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = '12' AND f2 >= '22';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	C	
	
echo select * from t1 where f1 = '12' OR  f1 > '13';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	C	
	14	14	
	50	E	
	This is really a very b	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 = '12' OR f2 = '13';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	C	
	
echo select * from t1 where f1 = '12' OR f2 < '22';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	12	C	
	13	D	
	14	14	
	50	E	
	This is really a very b	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where NOT f1 = '12';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	13	D	
	14	14	
	50	E	
	This is really a very b	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where f1 != '12';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	13	D	
	14	14	
	50	E	
	This is really a very b	E	
	UPPERCASE	UPPER	
	uppercase	LOWER	
	upperletter	LOWER	
	uppercaseletter	LOWER	
	
echo select * from t1 where NOT f1 != '12';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	C	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	14	14	
	
echo select * from t1 where f2 between 'A' AND 'C';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	A	
	11	B	
	12	C	
	
echo update t1 set f2 = '2' where f1 != f2;
Statement Executed: Rows Affected = 10
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	50	2	
	This is really a very b	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
echo update t1 set f2 = '3' where f1 = '50';
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	50	3	
	This is really a very b	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	14	14	
	This is really a very b	2	
	UPPERCASE	2	
	uppercase	2	
	upperletter	2	
	uppercaseletter	2	
	
Statement Executed
