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
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	1	
	2	2	
	3	3	
	4	4	
	5	5	
	6	6	
	7	7	
	8	8	
	9	9	
	10	10	
	11	11	
	12	12	
	13	13	
	14	14	
	15	15	
	16	16	
	17	17	
	18	18	
	19	19	
	20	20	
	21	21	
	22	22	
	23	23	
	24	24	
	25	25	
	26	26	
	27	27	
	28	28	
	29	29	
	30	30	
	31	31	
	32	32	
	33	33	
	34	34	
	35	35	
	36	36	
	37	37	
	38	38	
	39	39	
	40	40	
	41	41	
	42	42	
	43	43	
	44	44	
	45	45	
	46	46	
	47	47	
	48	48	
	49	49	
	50	50	
	
50 rows selected
echo select * from t1 where f1=10;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	10	
	
echo select * from t1 where f1=99;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1>27;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	28	28	
	29	29	
	30	30	
	31	31	
	32	32	
	33	33	
	34	34	
	35	35	
	36	36	
	37	37	
	38	38	
	39	39	
	40	40	
	41	41	
	42	42	
	43	43	
	44	44	
	45	45	
	46	46	
	47	47	
	48	48	
	49	49	
	50	50	
	
echo select * from t1 where f1>=27;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	27	27	
	28	28	
	29	29	
	30	30	
	31	31	
	32	32	
	33	33	
	34	34	
	35	35	
	36	36	
	37	37	
	38	38	
	39	39	
	40	40	
	41	41	
	42	42	
	43	43	
	44	44	
	45	45	
	46	46	
	47	47	
	48	48	
	49	49	
	50	50	
	
echo select * from t1 where f1<=27;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	1	
	2	2	
	3	3	
	4	4	
	5	5	
	6	6	
	7	7	
	8	8	
	9	9	
	10	10	
	11	11	
	12	12	
	13	13	
	14	14	
	15	15	
	16	16	
	17	17	
	18	18	
	19	19	
	20	20	
	21	21	
	22	22	
	23	23	
	24	24	
	25	25	
	26	26	
	27	27	
	
echo select * from t1 where f1<27;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	1	1	
	2	2	
	3	3	
	4	4	
	5	5	
	6	6	
	7	7	
	8	8	
	9	9	
	10	10	
	11	11	
	12	12	
	13	13	
	14	14	
	15	15	
	16	16	
	17	17	
	18	18	
	19	19	
	20	20	
	21	21	
	22	22	
	23	23	
	24	24	
	25	25	
	26	26	
	
echo select * from t1 where f1>99;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1<-1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1=40 and f1> 27;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	40	40	
	
echo select * from t1 where f1> 27 and f1=40;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	40	40	
	
echo select * from t1 where f1> 27 and f2=40;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	40	40	
	
echo select * from t1 where f1 >10 and f1 <20;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	11	11	
	12	12	
	13	13	
	14	14	
	15	15	
	16	16	
	17	17	
	18	18	
	19	19	
	
echo select * from t1 where f1 >10 and f1 <20 and f2=15;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	15	15	
	
Statement Executed
