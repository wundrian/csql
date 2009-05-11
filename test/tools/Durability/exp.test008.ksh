Durablity = TRUE
Server Started
CREATING TABLE
echo create table t2(f1 int,f2 float,f3 date);
Statement Executed
INSERTING INTO TABLE
DEFAULT AUTOCOMMIT MODE ON
echo insert into t2 values(10,100.001,'2001-1-1');
Statement Executed: Rows Affected = 1
echo insert into t2 values(50,500.005,'2005-5-5');
Statement Executed: Rows Affected = 1
Server Killed

Durablity = TRUE
Server Started
Checking Durability
Durability Works Fine
echo SET AUTOCOMMIT OFF;
AUTOCOMMIT Mode is set to OFF
echo insert into t2 values(100,1000.0001,'2001-1-1');
Statement Executed: Rows Affected = 1
echo insert into t2 values(500,5000.0005,'2005-5-5');
Statement Executed: Rows Affected = 1
echo ROLLBACK;
Server Killed

Durablity = TRUE
Server Started
Checking Durability
Durability Works Fine
Statement Executed
