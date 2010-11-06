echo CREATE TABLE t1(f1 SMALLINT DEFAULT NULL, f2 INT DEFAULT NULL, f3 BIGINT DEFAULT NULL, f4 TINYINT DEFAULT NULL, f5 CHAR(15) DEFAULT NULL, f6 FLOAT DEFAULT NULL, f7 DOUBLE DEFAULT NULL, f8 DATE DEFAULT NULL, f9 TIME DEFAULT NULL, f10 TIMESTAMP);
Statement Executed
echo INSERT INTO t1(f10) VALUES('2009-07-19 05:37:01');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1, 1234, 12345678, 45, 'CSQL', 1.23, 12345.6789, '2009/10/01', '12:34:56', '2009-07-19 05:37:01');
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	t1.f10	
---------------------------------------------------------
	NULL	NULL	NULL	NULL	NULL	NULL	NULL	NULL	NULL	2009/7/19 5:37:1.0	
	1	1234	12345678	45	CSQL	1.230000	12345.678900	2009/10/1	12:34:56.0	2009/7/19 5:37:1.0	
	
Statement Executed
