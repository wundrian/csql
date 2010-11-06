Network CSql
echo "----------Table having single field f1 and index on t1(f1)--------------";
echo create table t1(f1 int);
Statement Executed
echo create index idx1 on t1(f1);
Statement Executed
echo insert into t1 values(10);
Statement Executed: Rows Affected = 1
echo insert into t1 values(21);
Statement Executed: Rows Affected = 1
echo insert into t1 values(32);
Statement Executed: Rows Affected = 1
echo insert into t1 values(123);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483648);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2147483647);
Statement Executed: Rows Affected = 1
echo select * from t1 where f1>-5;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	21	
	32	
	123	
	2147483647	
	
echo select * from t1 where f1<-10;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	-2147483648	
	
echo select f1 from t1 where f1 in (10,30,123);
---------------------------------------------------------
	f1	
---------------------------------------------------------
	10	
	123	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	21	
	32	
	123	
	-2147483648	
	2147483647	
	
echo update t1 set f1=25 where f1=21;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	10	
	25	
	32	
	123	
	-2147483648	
	2147483647	
	
echo update t1 set f1=1010101 where f1 in(32,10,40);
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1010101	
	25	
	1010101	
	123	
	-2147483648	
	2147483647	
	
echo update t1 set f1=987654 where f1 between 25 and 200;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1010101	
	987654	
	1010101	
	987654	
	-2147483648	
	2147483647	
	
echo delete from t1 where f1=2147483647;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	1010101	
	987654	
	1010101	
	987654	
	-2147483648	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	-2147483648	
	
echo delete from t1;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo "-----Table having two fields f1 int,f2 int and index on t1(f1)-----";
echo create table t1(f1 int,f2 int);
Statement Executed
echo create index idx1 on t1(f1);
Statement Executed
echo insert into t1 values(10,2147483647);
Statement Executed: Rows Affected = 1
echo insert into t1 values(21,-2147483648);
Statement Executed: Rows Affected = 1
echo insert into t1 values(32,1000000000);
Statement Executed: Rows Affected = 1
echo insert into t1 values(123,999999999);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483648,0);
Statement Executed: Rows Affected = 1
echo insert into t1 values(2147483647,-2147483648);
Statement Executed: Rows Affected = 1
echo insert into t1 values(123,9);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2147483647	
	21	-2147483648	
	32	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo select * from t1 where f1>-5;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2147483647	
	21	-2147483648	
	32	1000000000	
	123	999999999	
	2147483647	-2147483648	
	123	9	
	
echo select * from t1 where f1<-10;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	-2147483648	0	
	
echo select f1 from t1 where f1 in (10,30,123);
---------------------------------------------------------
	f1	
---------------------------------------------------------
	10	
	123	
	123	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2147483647	
	21	-2147483648	
	32	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=25 where f1=21;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2147483647	
	25	-2147483648	
	32	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=21 where f1=25 and f2=-2147483648;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	2147483647	
	21	-2147483648	
	32	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=1010101 where f1 in(32,10,40);
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1010101	2147483647	
	21	-2147483648	
	1010101	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=7777 where f1=1010101 and f2 in(1000000000,999999999);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1010101	2147483647	
	21	-2147483648	
	7777	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=2020202 where f2 in(1000000000,999999999) and f1>=7777;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1010101	2147483647	
	21	-2147483648	
	2020202	1000000000	
	123	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	123	9	
	
echo update t1 set f1=987654 where f1 between 25 and 200;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1010101	2147483647	
	21	-2147483648	
	2020202	1000000000	
	987654	999999999	
	-2147483648	0	
	2147483647	-2147483648	
	987654	9	
	
echo delete from t1 where f1=2147483647;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1010101	2147483647	
	21	-2147483648	
	2020202	1000000000	
	987654	999999999	
	-2147483648	0	
	987654	9	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	21	-2147483648	
	-2147483648	0	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo "--Table having 5 fields f1,f2,f3,f4,f5(all int) index on t1(f1,f2)--";
echo create table t1(f1 int,f2 int,f3 int,f4 int,f5 int);
Statement Executed
echo create index idx1 on t1(f1,f2);
Statement Executed
echo insert into t1 values(11,222,3333,44444,555555);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,12345,123456);
Statement Executed: Rows Affected = 1
echo insert into t1 values(234,4567,56789,1234,4321);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483647,1,101,212,2147483647);
Statement Executed: Rows Affected = 1
echo insert into t1 values(101,12121,0,32123,78987);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1000,1111,1);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1000	1111	1	
	
echo select * from t1 where f1>0 and f2<=222 and f3=3333 and f4>44443 and f5!=555550;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	
echo select f1,f3,f5 from t1 where f1=234 or f5>4000 or f3>=50000;
---------------------------------------------------------
	f1	f3	f5	
---------------------------------------------------------
	11	3333	555555	
	12	1234	123456	
	234	56789	4321	
	-2147483647	101	2147483647	
	101	0	78987	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=101;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	-2147483647	1	101	212	2147483647	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=1234;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	12	123	1234	12345	123456	
	-2147483647	1	101	212	2147483647	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1000	1111	1	
	
echo update t1 set f1=22 where f1=11;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	22	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1000	1111	1	
	
echo update t1 set f1=11 where f1=22 and f2=222;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1000	1111	1	
	
echo update t1 set f1=10 where f1 in(234,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	10	4567	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1000	1111	1	
	
echo update t1 set f2=100 where f1 in(12,10);
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	100	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1000	1111	1	
	
echo update t1 set f2=222 where f3=56789 and f2 in(100,4567) and f4 between 100 and 20000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	222	56789	1234	4321	
	-2147483647	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1000	1111	1	
	
echo update t1 set f2=5 where f3=56789 or f2 in(123,222) or f4 between 100 and 20000;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483647	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1000	1111	1	
	
echo update t1 set f2=101,f2=12121 where f3=0;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483647	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1000	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) or f1>=7777;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	2020202	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1000	1111	1	
	
echo update t1 set f1=987654 where f1 between 25 and 200;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	2020202	5	101	212	2147483647	
	987654	12121	0	32123	78987	
	12	5	1000	1111	1	
	
echo delete from t1 where f1=2147483647;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	2020202	5	101	212	2147483647	
	987654	12121	0	32123	78987	
	12	5	1000	1111	1	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	12	5	1000	1111	1	
	
echo delete from t1;
Statement Executed: Rows Affected = 4
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo "--Table having 5 fields f1,f2,f3,f4,f5(all int) index on t1(f1,f3)--";
echo create table t1(f1 int,f2 int,f3 int,f4 int,f5 int);
Statement Executed
echo create index idx1 on t1(f1,f3);
Statement Executed
echo insert into t1 values(11,222,3333,44444,555555);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,12345,123456);
Statement Executed: Rows Affected = 1
echo insert into t1 values(234,4567,56789,1234,4321);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483648,1,101,212,2147483647);
Statement Executed: Rows Affected = 1
echo insert into t1 values(101,12121,0,32123,78987);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,100,1234,1111,1);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo select * from t1 where f1>0 and f2<=222 and f3=3333 and f4>44443 and f5!=555550;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	
echo select f1,f3,f5 from t1 where f1=234 or f5>4000 or f3>=50000;
---------------------------------------------------------
	f1	f3	f5	
---------------------------------------------------------
	11	3333	555555	
	12	1234	123456	
	234	56789	4321	
	-2147483648	101	2147483647	
	101	0	78987	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=101;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	-2147483648	1	101	212	2147483647	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=1234;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	12	123	1234	12345	123456	
	-2147483648	1	101	212	2147483647	
	12	100	1234	1111	1	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f1=22 where f1=11;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	22	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f1=11 where f1=22 and f2=222;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f1=10 where f1 in(234,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	10	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=100 where f1 in(12,10);
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	100	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=222 where f3=56789 and f2 in(100,4567) and f4 between 100 and 20000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	222	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=5 where f3=56789 or f2 in(123,222) or f4 between 100 and 20000;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f2=101,f2=12121 where f3=0;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) or f1>=7777;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=987654 where f1 between 25 and 200 and f3>=4000;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo delete from t1 where f1=-2147483648 or f3=1234;
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	101	12121	0	32123	78987	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo "--Table having 5 fields f1,f2,f3,f4,f5(all int) index on t1(f1,f3,f2)--";
echo create table t1(f1 int,f2 int,f3 int,f4 int,f5 int);
Statement Executed
echo create index idx1 on t1(f1,f3,f2);
Statement Executed
echo insert into t1 values(11,222,3333,44444,555555);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,12345,123456);
Statement Executed: Rows Affected = 1
echo insert into t1 values(234,4567,56789,1234,4321);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483648,1,101,212,2147483647);
Statement Executed: Rows Affected = 1
echo insert into t1 values(101,12121,0,32123,78987);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,1111,1);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo select * from t1 where f1>0 and f2<=222 and f3=3333 and f4>44443 and f5!=555550;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	
echo select f1,f3,f5 from t1 where f1=234 or f5>4000 or f3>=50000;
---------------------------------------------------------
	f1	f3	f5	
---------------------------------------------------------
	11	3333	555555	
	12	1234	123456	
	234	56789	4321	
	-2147483648	101	2147483647	
	101	0	78987	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=101;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	-2147483648	1	101	212	2147483647	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=1234;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	12	123	1234	12345	123456	
	-2147483648	1	101	212	2147483647	
	12	123	1234	1111	1	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=22 where f1=11;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	22	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=11 where f1=22 and f2=222;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=10 where f1 in(234,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	10	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f2=100 where f1 in(12,10);
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	100	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=222 where f3=56789 and f2 in(100,4567) and f4 between 100 and 20000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	222	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=5 where f3=56789 or f2 in(123,222) or f4 between 100 and 20000;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f2=101,f2=12121 where f3=0;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) and f2=1 and f3=101;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) or f1>=7777;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=987654 where f1 between 25 and 200 and f3>=4000;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo delete from t1 where f1=-2147483648 or f3=1234;
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	101	12121	0	32123	78987	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
echo "--Table having 5 fields f1,f2,f3,f4,f5(all int) index on t1(f5,f1,f3,f2)--";
echo create table t1(f1 int,f2 int,f3 int,f4 int,f5 int);
Statement Executed
echo create index idx1 on t1(f5,f1,f3,f2);
Statement Executed
echo insert into t1 values(11,222,3333,44444,555555);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,12345,123456);
Statement Executed: Rows Affected = 1
echo insert into t1 values(234,4567,56789,1234,4321);
Statement Executed: Rows Affected = 1
echo insert into t1 values(-2147483648,1,101,212,2147483647);
Statement Executed: Rows Affected = 1
echo insert into t1 values(101,12121,0,32123,78987);
Statement Executed: Rows Affected = 1
echo insert into t1 values(12,123,1234,1111,1);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo select * from t1 where f1>0 and f2<=222 and f3=3333 and f4>44443 and f5!=555550;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	
echo select f1,f3,f5 from t1 where f1=234 or f5>4000 or f3>=50000;
---------------------------------------------------------
	f1	f3	f5	
---------------------------------------------------------
	11	3333	555555	
	12	1234	123456	
	234	56789	4321	
	-2147483648	101	2147483647	
	101	0	78987	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=101;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	-2147483648	1	101	212	2147483647	
	
echo select * from t1 where f1<-1 and f2>=1 or f3=1234;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	12	123	1234	12345	123456	
	-2147483648	1	101	212	2147483647	
	12	123	1234	1111	1	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=22 where f1=11;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	22	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=11 where f1=22 and f2=222;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	234	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f1=10 where f1 in(234,10);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	123	1234	12345	123456	
	10	4567	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	123	1234	1111	1	
	
echo update t1 set f2=100 where f1 in(12,10);
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	100	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=222 where f3=56789 and f2 in(100,4567) and f4 between 100 and 20000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	222	3333	44444	555555	
	12	100	1234	12345	123456	
	10	222	56789	1234	4321	
	-2147483648	1	101	212	2147483647	
	101	12121	0	32123	78987	
	12	100	1234	1111	1	
	
echo update t1 set f2=5 where f3=56789 or f2 in(123,222) or f4 between 100 and 20000;
Statement Executed: Rows Affected = 5
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) and f2=1 and f3=101;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo update t1 set f1=2020202 where f1 in(-2147483647,2147483647) or f1>=7777;
Statement Executed: Rows Affected = 0
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	12	5	1234	12345	123456	
	10	5	56789	1234	4321	
	-2147483648	5	101	212	2147483647	
	101	12121	0	32123	78987	
	12	5	1234	1111	1	
	
echo delete from t1 where f1=-2147483648 or f3=1234;
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	101	12121	0	32123	78987	
	
echo delete from t1 where f1 between 25 and 6000000;
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	11	5	3333	44444	555555	
	10	5	56789	1234	4321	
	
echo delete from t1;
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	
echo drop table t1;
Statement Executed
Network CSql
Statement execute failed with error -4
