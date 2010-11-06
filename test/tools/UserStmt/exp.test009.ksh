Connecting User root
echo create table t1(f1 int,f2 char(10));
Statement Executed
echo insert into t1 values(1,'root1');
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	root1	
	
echo create user lakshya password 'lakshya123';
Statement Executed
echo show users;
=============UserNames===================
   root 
   lakshya 
=========================================
echo Disconnecting User root
quit;
Connecting User lakshya
echo create table t2(f1 int,f2 char(10));
Statement Executed
echo insert into t1 values(2,'root2');
Statement Executed: Rows Affected = 1
echo insert into t2 values(10,'lakshya');
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	root1	
	2	root2	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	10	lakshya	
	
echo Disconnecting user lakshya
quit;
Connecting User root
echo drop user lakshya;
Statement Executed
Statement Executed
Statement Executed
Test Passed
