echo CREATE TABLE t1(f1 int default 1,f2 smallint default 10,f3 bigint default 100,f4 float default 1.9,f5 double default 987654321.123456,f6 char(20) default 'CSQl-CACHE',f7 date default '2001-01-01',f8 time default '01:01:01',f9 timestamp default '2001-01-01 01:01:01');
CREATE TABLE t1(f1 int default 1,f2 smallint default 10,f3 bigint default 100,f4 float default 1.9,f5 double default 987654321.123456,f6 char(20) default 'CSQl-CACHE',f7 date default '2001-01-01',f8 time default '01:01:01',f9 timestamp default '2001-01-01 01:01:01');
echo INSERT INTO t1(f7,f8,f9) VALUES('2009-06-09','21:09:09','2009-06-09 21:09:09');
INSERT INTO t1(f7,f8,f9) VALUES('2009-06-09','21:09:09','2009-06-09 21:09:09');
echo SELECT * FROM t1;
SELECT * FROM t1;
