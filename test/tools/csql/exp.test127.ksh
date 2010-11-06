echo CREATE TABLE t1(f1 int default 1,f2 smallint default 10,f3 bigint default 100,f4 float default 1.9,f5 double default 987654321.123456,f6 char(20) default 'CSQl-CACHE',f7 date default '2001-01-01',f8 time default '01:01:01',f9 timestamp default '2001-01-01 01:01:01');
Statement Executed
echo INSERT INTO t1(f1) VALUES(9);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f2) VALUES(999);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f3) VALUES(999999);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f4) VALUES(9.9);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f5) VALUES(123456789.987654);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f6) VALUES('TCSQL-MMDB');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f7) VALUES('2009-06-09');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f8) VALUES('21:09:09');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f9) VALUES('2009-06-09 21:09:09');
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	9	10	100	1.900000	987654321.123456	CSQl-CACHE	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	999	100	1.900000	987654321.123456	CSQl-CACHE	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	999999	1.900000	987654321.123456	CSQl-CACHE	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	100	9.900000	987654321.123456	CSQl-CACHE	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	100	1.900000	123456789.987654	CSQl-CACHE	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	100	1.900000	987654321.123456	TCSQL-MMDB	2001/1/1	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	100	1.900000	987654321.123456	CSQl-CACHE	2009/6/9	1:1:1.0	2001/1/1 1:1:1.0	
	1	10	100	1.900000	987654321.123456	CSQl-CACHE	2001/1/1	21:9:9.0	2001/1/1 1:1:1.0	
	1	10	100	1.900000	987654321.123456	CSQl-CACHE	2001/1/1	1:1:1.0	2009/6/9 21:9:9.0	
	
Statement Executed
