Table t1 and t2 created in target DB.
cachetable -t t1
cachetable -t t2 -c "t2f1<5" 
select query on t1 and t2 table
---------------------------------------------------------
	t1.t1f1	t1.t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
---------------------------------------------------------
	t2.t2f1	t2.t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	
