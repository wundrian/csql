echo create table t1(f1 int not null,f2 int,f3 int);
create table t1(f1 int not null,f2 int,f3 int);
echo create index idx1 on t1(f1,f2) hash unique;
create index idx1 on t1(f1,f2) hash unique;
echo insert into t1 values(1,2,3);
insert into t1 values(1,2,3);
echo insert into t1 values(1,2,4);
insert into t1 values(1,2,4);
echo select * from t1;
select * from t1;
echo drop table t1;
drop table t1;

echo create table t1(f1 int not null,f2 int not null,f3 int);
create table t1(f1 int not null,f2 int not null,f3 int);
echo create index idx2 on t1(f1,f2) hash primary;
create index idx2 on t1(f1,f2) hash primary;
echo insert into t1 values(1,2,3);
insert into t1 values(1,2,3);
echo insert into t1 values(1,2,4);
insert into t1 values(1,2,4);
echo select * from t1;
select * from t1;
echo drop table t1;
drop table t1;

echo create table t1(f1 int not null,f2 int,f3 int,primary key(f1,f2));
create table t1(f1 int not null,f2 int,f3 int,primary key(f1,f2));
echo insert into t1 values(1,2,3);
insert into t1 values(1,2,3);
echo insert into t1 values(1,2,4);
insert into t1 values(1,2,4);
echo select * from t1;
select * from t1;
echo drop table t1;
drop table t1;
