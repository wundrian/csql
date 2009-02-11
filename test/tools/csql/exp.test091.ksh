echo create table t1(f1 int);
Statement Executed
echo create index idx1 on t1(f1);
Statement Executed
echo insert into t1 values(1);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11);
Statement Executed: Rows Affected = 1
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo insert into t1  values(8);
Statement Executed: Rows Affected = 1
echo insert into t1  values(10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo insert into t1 values(12);
Statement Executed: Rows Affected = 1
echo insert into t1 values(11);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	12	
	11	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo update t1 set f1=15 where f1=3;
Statement Executed: Rows Affected = 1
echo update t1 set f1=11 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	15	
	11	
	11	
	10	
	8	
	10	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	3	
	2	
	11	
	10	
	8	
	10	
	
echo select * from t1 where f1=3;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	3	
	
echo update t1 set f1=30 where f1=3;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	30	
	2	
	11	
	10	
	8	
	10	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	30	
	2	
	11	
	10	
	8	
	10	
	
echo delete from t1 where f1=30;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	2	
	11	
	10	
	8	
	10	
	
echo delete from t1 where f1=3;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	2	
	11	
	10	
	8	
	10	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	30	
	2	
	11	
	10	
	8	
	10	
	
echo delete from t1 where f1=30;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	2	
	11	
	10	
	8	
	10	
	
echo delete from t1 where f1=3;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	2	
	11	
	10	
	8	
	10	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1	
	2	
	11	
	10	
	8	
	10	
	
echo delete  from t1 where f1<=10;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	11	
	
echo delete from t1;
Statement Executed: Rows Affected = 1
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo quit;
echo create table t1(f1 int,f2 int,f3 int);
Statement Executed
echo create index idx1 on t1(f1,f2);
Statement Executed
echo insert into t1 values(1,10,100);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,33,444);
Statement Executed: Rows Affected = 1
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1 where f1=33;
---------------------------------------------------------
	t1f1	t1f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo select * from t1 where f1=2 and f2=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select *from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f1=1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2 and f2=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f1=3 and f2=33;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f1 in(1,5) and f2 in(50,10);
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	4	40	400	
	
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo delete from t1;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f1=3 and f2=33;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f1 in(1,5) and f2 in(50,10);
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	4	40	400	
	
echo commit;
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo delete from t1;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo quit;
echo create table t1(f1 int,f2 int,f3 int);
Statement Executed
echo create index idx1 on t1(f1,f3);
Statement Executed
echo insert into t1 values(1,10,100);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,33,444);
Statement Executed: Rows Affected = 1
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1 where f1=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo select * from t1 where f1=2 and f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select *from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f1=1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2 and f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f1=3 and f3=333;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f1 in(1,5) and f3 in(50,100);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	444	
	4	40	400	
	
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	444	
	
echo delete from t1;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f1=3 and f3=333;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f1 in(1,5) and f3 in(50,100);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	444	
	4	40	400	
	
echo commit;
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	444	
	
echo delete from t1;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo quit;
echo create table t1(f1 int,f2 int,f3 int);
Statement Executed
echo create index idx1 on t1(f3,f2);
Statement Executed
echo insert into t1 values(1,10,100);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,33,444);
Statement Executed: Rows Affected = 1
echo set autocommit off;
AUTOCOMMIT Mode is set to OFF
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	
echo insert into t1 values(4,40,400);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,33,333);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	2	33	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo rollback;
echo select * from t1 where f1=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo select * from t1 where f1=2 and f2=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	2	33	444	
	
echo update t1 set f1=20 where f1=2;
Statement Executed: Rows Affected = 1
echo select * from t1 where f1=20;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	33	444	
	
echo update t1 set f2=333 where f3=444;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f3=444;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	20	333	444	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	20	333	444	
	4	40	400	
	3	33	333	
	
echo update t1 set f1=1,f2=10 where f1=20;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo commit;
echo select *from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo select * from t1 where f1=1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo select * from t1 where f1=2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=2 and f2=33;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f3=333 and f2=33;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f2 in(10,40) and f3 in(400,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo rollback;
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	3	33	333	
	1	10	444	
	4	40	400	
	3	33	333	
	
echo delete from t1 where f3=333 and f2=33;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	4	40	400	
	
echo delete from t1 where f2 in(10,40) and f3 in(400,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo commit;
echo delete from t1 where f2 between 33 and 45;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	10	444	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo quit;
