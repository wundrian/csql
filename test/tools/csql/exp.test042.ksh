echo binary data type testing with primary key;
echo create table t1 (f1 int, f2 binary(4) DEFAULT 'abcd12' ,primary key(f2));
Statement Executed
Statement Executed: Rows Affected = 1
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
	10	12FE0000	
	10	ABCD1200	
	11	245AF000	
	12	2423FE00	
	-2147483648	DC230000	
	2147483647	323A3400	
	
echo select * from t1 where f2 = '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	
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
Illegal Operator:Not Supported for Binary

echo select * from t1 where f1 = 12 OR  f2 > 'dc23';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	2423FE00	
	
echo select * from t1 where f1 = 12 OR f2 < 'dc23';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	10	ABCD1200	
	11	245AF000	
	12	2423FE00	
	2147483647	323A3400	
	
echo select * from t1 where f1 = 12 OR f2 <> '245af';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	10	ABCD1200	
	12	2423FE00	
	-2147483648	DC230000	
	2147483647	323A3400	
	
echo select * from t1 where NOT f2 ='12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	ABCD1200	
	11	245AF000	
	12	2423FE00	
	-2147483648	DC230000	
	2147483647	323A3400	
	
echo select * from t1 where f2 != '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	ABCD1200	
	11	245AF000	
	12	2423FE00	
	-2147483648	DC230000	
	2147483647	323A3400	
	
echo select * from t1 where NOT  f2 != '12fe';
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f2 in ('245af','12fe');
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	11	245AF000	
	
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
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo update t1 set f2 = '435f3' where f1 != 13 and  f2='323a34' ;
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	12FE0000	
	10	ABCD1200	
	11	245AF000	
	12	2423FE00	
	-2147483648	DC230000	
	2147483647	435F3000	
	
echo update t1 set f2 = '23f3abc' ;
Statement Executed: Rows Affected = 6
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	23F3ABC0	
	10	23F3ABC0	
	11	23F3ABC0	
	12	23F3ABC0	
	-2147483648	23F3ABC0	
	2147483647	23F3ABC0	
	
echo update t1 set f2 = '23abc' where f2 = '245af';
Statement Executed: Rows Affected = 0
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	23F3ABC0	
	10	23F3ABC0	
	11	23F3ABC0	
	12	23F3ABC0	
	-2147483648	23F3ABC0	
	2147483647	23F3ABC0	
	
echo delete from t1 where f2 = '12fe';
Statement Executed: Rows Affected = 0
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	23F3ABC0	
	10	23F3ABC0	
	11	23F3ABC0	
	12	23F3ABC0	
	-2147483648	23F3ABC0	
	2147483647	23F3ABC0	
	
Statement Executed
