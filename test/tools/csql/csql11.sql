echo all data type create, insert, select test;
create table t1 (f1 int not null, f2 smallint not null, f3 char(10) not null,f4 float not null, f5 double not null,f6 date not null, f7 time not null, f8 timestamp not null,f9 tinyint not null,f10 bigint not null,f11 binary(10) not null);
insert into t1 values(1, 1,'NIHAR', 1.1,10000001.10000001, '2001-1-1', '01:01:01', '2001-11-30 01:01:01',1,10000000,'ABCD56789');
insert into t1 values(null,null,null,null,null,null,null,null,null,null,null);
select * from t1;
drop table t1;
