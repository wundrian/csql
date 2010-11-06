echo SET AUTOCOMMIT OFF;
SET AUTOCOMMIT OFF;
echo insert into t2 values(100,1000.0001,'2001-1-1');
insert into t2 values(100,1000.0001,'2001-1-1');
echo insert into t2 values(500,5000.0005,'2005-5-5');
insert into t2 values(500,5000.0005,'2005-5-5');
echo ROLLBACK;
ROLLBACK;
