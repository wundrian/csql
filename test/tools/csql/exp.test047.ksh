Statement Executed
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
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1 where f1>5 and f1<15;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	6	6	
	7	7	
	8	8	
	9	9	
	11	11	
	12	12	
	13	13	
	14	14	
	
echo delete from t1 where f1>40;
Statement Executed: Rows Affected = 10
echo commit;
echo select * from t1 where f1>35 and f1<55;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	36	36	
	37	37	
	38	38	
	39	39	
	40	40	
	
echo delete from t1 where f1<8;
Statement Executed: Rows Affected = 7
echo commit;
echo select * from t1 where f1>=-5 and f1<15;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	8	8	
	9	9	
	11	11	
	12	12	
	13	13	
	14	14	
	
echo insert into t1 values(10,10);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1 where f1 >5 and f1 <15;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	8	8	
	9	9	
	10	10	
	11	11	
	12	12	
	13	13	
	14	14	
	
Statement Executed
