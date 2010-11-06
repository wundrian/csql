echo Create table t1(f1 varchar(10), f2 char(10), f3 varchar(10), f4 int);
Statement Executed
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
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	CSQL1	LAKS2	BBSR3	30	
	CSQL1	LAKS2	BBSR4	40	
	CSQL2	LAKS3	BBSR5	50	
	CSQL2	LAKS3	BBSR6	60	
	CSQL2	LAKS4	BBSR7	70	
	CSQL2	LAKS4	BBSR8	80	
	
echo select * from t1 where f1='CSQL2';
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL2	LAKS3	BBSR5	50	
	CSQL2	LAKS3	BBSR6	60	
	CSQL2	LAKS4	BBSR7	70	
	CSQL2	LAKS4	BBSR8	80	
	
echo select * from t1 where not(f1='CSQL2');
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	CSQL1	LAKS2	BBSR3	30	
	CSQL1	LAKS2	BBSR4	40	
	
echo select * from t1 where f1='CSQL1' and f2='LAKS1';
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	
echo select * from t1 where f2='LAKS1' and not(f1='CSQL2');
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	
echo select * from t1 where f1='CSQL1' and f2='LAKS1' and f3='BBSR1';
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	
echo select * from t1 where f1='CSQL1' and f2='LAKS1' and not(f3='BBSR1');
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR2	20	
	
echo select * from t1 where f1='CSQL1' and f2='LAKS1' and not(f4=20);
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	
echo select * from t1 where f1='CSQL1' and f2='LAKS1' or not(f4=20);
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	CSQL1	LAKS2	BBSR3	30	
	CSQL1	LAKS2	BBSR4	40	
	CSQL2	LAKS3	BBSR5	50	
	CSQL2	LAKS3	BBSR6	60	
	CSQL2	LAKS4	BBSR7	70	
	CSQL2	LAKS4	BBSR8	80	
	
echo select * from t1 where f1='CSQL1' or f2='LAKS1' and not(f4=20);
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	CSQL1	LAKS1	BBSR1	10	
	CSQL1	LAKS1	BBSR2	20	
	CSQL1	LAKS2	BBSR3	30	
	CSQL1	LAKS2	BBSR4	40	
	
Statement Executed
