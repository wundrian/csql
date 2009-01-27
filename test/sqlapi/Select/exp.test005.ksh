Case 1: create table t1 ,test for SET AUTOCOMMIT OFF and some records 
[Parser: syntax error] SET
[Parser: syntax error] commiter
[Parser: syntax error] rollbacked
[Parser: syntax error] show
[Parser: syntax error] SET
echo create table t1 (f1 int,f2 int);
Statement Executed
echo check for SET AUTOCOMMIT OFF;
Statement prepare failed with error -19
echo insert some record;
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	20	30	
	30	40	
	40	50	
	50	60	
	
AUTOCOMMIT Mode is set to OFF
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
echo test for commit;
Statement prepare failed with error -19
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	20	30	
	30	40	
	40	50	
	50	60	
	
echo test for rollback;
echo insert 5 records;
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement prepare failed with error -19
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	20	30	
	30	40	
	40	50	
	50	60	
	20	40	
	20	40	
	20	40	
	20	40	
	20	40	
	
echo check for show tables;
Statement prepare failed with error -19
echo check for SET AUTOCOMMIT ON;
Statement prepare failed with error -19
echo insert some records;
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	20	30	
	30	40	
	40	50	
	50	60	
	20	40	
	20	40	
	20	40	
	20	40	
	20	40	
	
echo drop teble;
Statement Executed
