echo all data type create, insert, select test;
create table t1 (f1 int, f2 long, f3 float, f4 date, f5 time, f6 timestamp);
insert into t1  (f1, f2, f3, f4, f5, f6) values (1, 1, 1.1, '1-1-2001', '01:01:01', '1-1-2001, 01:01:01');
select * from t1;
drop table t1;
