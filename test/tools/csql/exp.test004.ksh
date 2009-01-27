echo Same as csql2 but with primary key;
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
	10	20	
	11	21	
	12	22	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where f1 = 100;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = 10;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	
echo select f1 from t1 where f1 = 11;
---------------------------------------------------------
	f1	
---------------------------------------------------------
	11	
	
echo select f2 from t1 where f1 = 11;
---------------------------------------------------------
	f2	
---------------------------------------------------------
	21	
	
echo select f1, f2 from t1 where f1 = 12;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	22	
	
echo select * from t1 where f1 != 12 AND f2 <= 13;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = 12 AND f2 >= 22;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	22	
	
echo select * from t1 where f1 = 12 OR  f1 > 13;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	22	
	14	24	
	50	50	
	
echo select * from t1 where f1 = 12 OR f2 < 13;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	22	
	
echo select * from t1 where f1 = 12 OR f2 <> 22;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	12	22	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where NOT f1 = 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where f1 != 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where NOT f1 != 12;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	22	
	
echo select * from t1 where NOT (f1 = 12 AND f2 =22);
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	13	23	
	14	24	
	50	50	
	
echo select * from t1 where NOT (f1 = 12 OR f2 = 23);
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	14	24	
	50	50	
	
echo select * from t1 where f1 = 12 OR f2 = 23 OR f2 = 22;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	22	
	13	23	
	
echo select * from t1 where  f1+12 = 20;
Statement prepare failed with error -19
echo select * from t1 where f1 = 12 + f2;
Statement prepare failed with error -19
echo select * from t1 where f1 =  f2;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	50	50	
	
echo select * from t1 where f1=12 and f1<=13 or f1>=11;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	21	
	12	22	
	13	23	
	14	24	
	50	50	
	
Statement Executed
