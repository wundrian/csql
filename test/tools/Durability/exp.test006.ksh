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
echo insert into t2 values(10,100.001,'2001-1-1');
Statement Executed: Rows Affected = 1
echo insert into t2 values(20,200.002,'2002-2-2');
Statement Executed: Rows Affected = 1
echo insert into t2 values(30,300.003,'2003-3-3');
Statement Executed: Rows Affected = 1
echo SET AUTOCOMMIT OFF;
AUTOCOMMIT Mode is set to OFF
echo insert into t2 values(100,1000.0001,'2001-1-1');
Statement Executed: Rows Affected = 1
echo insert into t2 values(500,5000.0005,'2005-5-5');
Statement Executed: Rows Affected = 1
echo insert into t2 values(100,1000.0001,'2001-1-1');
Statement Executed: Rows Affected = 1
echo insert into t2 values(200,2000.0002,'2002-2-2');
Statement Executed: Rows Affected = 1
echo insert into t2 values(300,3000.0003,'2003-3-3');
Statement Executed: Rows Affected = 1
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	10	100.000999	2001/1/1	
	50	500.005005	2005/5/5	
	10	100.000999	2001/1/1	
	20	200.001999	2002/2/2	
	30	300.002991	2003/3/3	
	100	1000.000122	2001/1/1	
	500	5000.000488	2005/5/5	
	100	1000.000122	2001/1/1	
	200	2000.000244	2002/2/2	
	300	3000.000244	2003/3/3	
	
echo ROLLBACK;
Server Killed

Durablity = TRUE
Checking Durability
Server Started
Statement Executed
