echo "<<<<<<<<<<<<<<<<<<<<<<<< UPDATE t1 SET f2=NULL >>>>>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11,NULL,NULL);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo update t1 set f2=NULL;
Statement Executed: Rows Affected = 5
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	NULL	3	
	2	NULL	4	
	3	NULL	NULL	
	10	NULL	30	
	11	NULL	NULL	
	
echo drop table t1;
Statement Executed
echo "<<<<<<<<<<<<<<<<<<<<<<<< UPDATE t1 SET f1=NULL >>>>>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11,NULL,NULL);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo update t1 set f1=NULL;
Statement prepare failed with error -22
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo drop table t1;
Statement Executed
echo "<<<<<<<<<<<<<<<<<<<<<< UPDATE t1 SET f1=f1+f2+f3 >>>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11,NULL,NULL);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo update t1 set f1=f1+f2+f3;
Statement Executed: Rows Affected = 5
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	6	2	3	
	2	NULL	4	
	3	4	NULL	
	60	20	30	
	11	NULL	NULL	
	
echo drop table t1;
Statement Executed
echo "<<<<<<<<<<<<<<<<<< UPDATE t1 SET f2=0 WHERE f3>=1 >>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11,NULL,NULL);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo UPDATE t1 SET f2=0 where f3>=1;
Statement Executed: Rows Affected = 3
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	0	3	
	2	0	4	
	3	4	NULL	
	10	0	30	
	11	NULL	NULL	
	
echo drop table t1;
Statement Executed
echo "<<<<<<<<<<<<<<<<<<< DELETE FROM t1 WHERE f3>=4 >>>>>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
Statement Executed
echo insert into t1 values(1,2,3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL,4);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,20,30);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11,NULL,NULL);
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	2	NULL	4	
	3	4	NULL	
	10	20	30	
	11	NULL	NULL	
	
echo DELETE FROM t1 WHERE f3>=4;
Statement Executed: Rows Affected = 2
echo commit;
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	2	3	
	3	4	NULL	
	11	NULL	NULL	
	
echo drop table t1;
Statement Executed
