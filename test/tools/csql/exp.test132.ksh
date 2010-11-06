[?1034hCSQL>create table t1(f1 int,f2 int);
Statement Executed
CSQL>insert into t1 values(12,23);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(13,24);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(14,25);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(15,26);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(NULL,27);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(NULL,28);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(16,29);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(12,NULL);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(17,NULL);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(NULL,31);
Statement Executed: Rows Affected = 1
CSQL>insert into t1 values(12,32);
Statement Executed: Rows Affected = 1
CSQL>select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	23	
	13	24	
	14	25	
	15	26	
	NULL	27	
	NULL	28	
	16	29	
	12	NULL	
	17	NULL	
	NULL	31	
	12	32	
	
CSQL>select * from t1 where f1 is null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	NULL	27	
	NULL	28	
	NULL	31	
	
CSQL>select * from t1 where f1 is not null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	23	
	13	24	
	14	25	
	15	26	
	16	29	
	12	NULL	
	17	NULL	
	12	32	
	
CSQL>select * from t1 where f2 is null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	NULL	
	17	NULL	
	
CSQL>select * from t1 where f2 is not null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	23	
	13	24	
	14	25	
	15	26	
	NULL	27	
	NULL	28	
	16	29	
	NULL	31	
	12	32	
	
CSQL>select * from t1 where f1 is null or f2 is not null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	23	
	13	24	
	14	25	
	15	26	
	NULL	27	
	NULL	28	
	16	29	
	NULL	31	
	12	32	
	
CSQL>select * from t1 where f2 is null or f1 is not null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	12	23	
	13	24	
	14	25	
	15	26	
	16	29	
	12	NULL	
	17	NULL	
	12	32	
	
CSQL>drop table t1;
Statement Executed
CSQL>
Statement prepare failed with error -19
CSQL>