Table t1 created in target DB.
cachetable -t t1 -c "f1<3" -f "f1,f3,f5"
select from t1 table
---------------------------------------------------------
	t1.f1	t1.f3	t1.f5	
---------------------------------------------------------
	1	111	1111	
	2	222	2222	
	
Table t1 unloaded from CSQL
