create table t1 (f1 int not null, f2 int);
create index idx on t1 (f1) tree unique;
insert into t1 values(1,1);
insert into t1 values(2,2);
insert into t1 values(3,3);
insert into t1 values(4,4);
insert into t1 values(5,5);
insert into t1 values(6,6);
insert into t1 values(7,7);
insert into t1 values(8,8);
insert into t1 values(9,9);
insert into t1 values(10,10);
insert into t1 values(11,11);
insert into t1 values(12,12);
insert into t1 values(13,13);
insert into t1 values(14,14);
insert into t1 values(15,15);
insert into t1 values(16,16);
insert into t1 values(17,17);
insert into t1 values(18,18);
insert into t1 values(19,19);
insert into t1 values(20,20);
insert into t1 values(21,21);
insert into t1 values(22,22);
insert into t1 values(23,23);
insert into t1 values(24,24);
insert into t1 values(25,25);
insert into t1 values(26,26);
insert into t1 values(27,27);
insert into t1 values(28,28);
insert into t1 values(29,29);
insert into t1 values(30,30);
insert into t1 values(31,31);
insert into t1 values(32,32);
insert into t1 values(33,33);
insert into t1 values(34,34);
insert into t1 values(35,35);
insert into t1 values(36,36);
insert into t1 values(37,37);
insert into t1 values(38,38);
insert into t1 values(39,39);
insert into t1 values(40,40);
insert into t1 values(41,41);
insert into t1 values(42,42);
insert into t1 values(43,43);
insert into t1 values(44,44);
insert into t1 values(45,45);
insert into t1 values(46,46);
insert into t1 values(47,47);
insert into t1 values(48,48);
insert into t1 values(49,49);
insert into t1 values(50,50);
commit;
delete from t1 where f1=10;
commit;
echo select * from t1 where f1>5 and f1<15;
select * from t1 where f1>5 and f1<15;
echo delete from t1 where f1>40;
delete from t1 where f1>40;
echo commit;
commit;
echo select * from t1 where f1>35 and f1<55;
select * from t1 where f1>35 and f1<55;
echo delete from t1 where f1<8;
delete from t1 where f1<8;
echo commit;
commit;
echo select * from t1 where f1>=-5 and f1<15;
select * from t1 where f1>=-5 and f1<15;
echo insert into t1 values(10,10);
insert into t1 values(10,10);
echo commit;
commit;
echo select * from t1 where f1 >5 and f1 <15;
select * from t1 where f1 >5 and f1 <15;
