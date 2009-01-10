echo binary data type testing with primary key;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement execute failed with error -21
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where f2 = '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	
echo select * from t1 where f2 != '323a34' AND f1 = 13;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = 12 AND f2 >= '245af';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo select * from t1 where f1 = 12 OR  f2 > 'dc23';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	11	245AF	
	12	2423FE	
	2147483647	323A34	
	
echo select * from t1 where f1 = 12 OR f2 < 'dc23';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	12	2423FE	
	
echo select * from t1 where f1 = 12 OR f2 <> '245af';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where NOT f2 ='12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	11	245AF	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where f2 != '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	11	245AF	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where NOT  f2 != '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f2 in ('245af','12fe');
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	
echo select * from t1 where f2 between '00000000' and 'ffffffff';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo select * from t1 where f2 between '122' and '12a2';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo update t1 set f2 = '435f3' where f1 != 13 and  f2='323a34' ;
Statement prepare failed with error -21
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo delete from t1 where f2 = '23abc';
Statement Executed: Rows Affected = 0
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	12	2423FE	
	-2147483648	DC23	
	2147483647	323A34	
	
Statement Executed
