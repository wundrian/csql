echo select min(t1.notexist) from t1;
Statement prepare failed with error -19
echo select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100;
---------------------------------------------------------
	MAX(t1.f1)	SUM(t2.f1)	
---------------------------------------------------------
	99	197	
	
echo select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100 group by t1.f2;
---------------------------------------------------------
	MAX(t1.f1)	SUM(t2.f1)	
---------------------------------------------------------
	98	98	
	99	99	
	
echo select max(t1.f1), max(t2.notexist) from t1,t2 group by t1.f2;
Statement prepare failed with error -19
