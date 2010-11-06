echo create table t1(f1 bigint, f2 int, f3 smallint, f4 tinyint, f5 char(10), f6 varchar(10), f7 float,f8 double, f9 time, f10 date, f11 timestamp);
Statement Executed
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	t1.f10	t1.f11	
---------------------------------------------------------
	1001	101	11	1	CSQL1	Lakshya1	2010.000000	5012010.000000	10:0:0.0	2010/1/5	2010/1/5 10:0:0.0	
	1002	102	12	2	CSQL2	Lakshya2	2010.000000	5012010.000000	10:0:0.0	2010/2/5	2010/2/5 10:0:0.0	
	1003	103	13	3	CSQL3	Lakshya3	2010.000000	5012010.000000	10:0:0.0	2010/3/5	2010/3/5 10:0:0.0	
	
echo truncate table t1;
Statement Executed: Rows Affected = 3
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	t1.f10	t1.f11	
---------------------------------------------------------
	
Statement Executed
