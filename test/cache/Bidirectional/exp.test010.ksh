table csql_log_int is created with records in target db
server 1 started
cache node 2
echo select * from t1;
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
	
echo select * from t2;
---------------------------------------------------------
	t2.t2f1	t2.t2f2	
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
	
server 2 started
cache node 1
echo select * from t1;
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
	
echo select * from t2;
---------------------------------------------------------
	t2.t2f1	t2.t2f2	
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
	
Update operation in cache node 1
cache node 1
echo select * from t1;
---------------------------------------------------------
	t1.t1f1	t1.t2f2	
---------------------------------------------------------
	1	50	
	2	50	
	3	50	
	4	50	
	5	50	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
echo select * from t2;
---------------------------------------------------------
	t2.t2f1	t2.t2f2	
---------------------------------------------------------
	1	110	
	2	110	
	3	110	
	4	110	
	5	110	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
cache node 2
echo select * from t1;
---------------------------------------------------------
	t1.t1f1	t1.t2f2	
---------------------------------------------------------
	1	50	
	2	50	
	3	50	
	4	50	
	5	50	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
echo select * from t2;
---------------------------------------------------------
	t2.t2f1	t2.t2f2	
---------------------------------------------------------
	1	110	
	2	110	
	3	110	
	4	110	
	5	110	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
