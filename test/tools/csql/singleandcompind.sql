echo create table t2 ( f1 int, f2 int, primary key(f1, f2));
create table t2( f1 int, f2 int, primary key(f1, f2));
echo create index ind on t2(f1);
create index ind on t2(f1);
echo create table t1 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
create table t1 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
echo create index indx1 on t1 (f1,f3);
create index indx1 on t1 (f1,f3);
echo create index indx2 on t1 (f3);
create index indx2 on t1 (f3);
echo create index indx3 on t1 (f2,f4);
create index indx3 on t1 (f2,f4);
echo create index indx4 on t1 (f2,f3);
create index indx4 on t1 (f2,f3);
echo create index indx5 on t1 (f1,f3,f4);
create index indx5 on t1 (f1,f3,f4);
echo create index indx6 on t1 (f1,f3,f2);
create index indx6 on t1 (f1,f3,f2);
echo create index indx7 on t1 (f1,f3,f2);
create index indx7 on t1 (f1,f4,f2);
echo create table t3 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
create table t3 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
echo create index indx11 on t3 (f1,f3);
create index indx11 on t3 (f1,f3);
echo create index indx12 on t3 (f3);
create index indx12 on t3 (f3);
echo create index indx13 on t3 (f2,f4);
create index indx13 on t3 (f2,f4);
echo create index indx14 on t3 (f2,f3);
create index indx14 on t3 (f2,f3);
echo create index indx15 on t1 (f1,f3,f4);
create index indx15 on t3 (f1,f3,f4);
echo create index indx16 on t1 (f1,f3,f2);
create index indx16 on t3 (f1,f3,f2);
echo create index indx17 on t1 (f1,f3,f2);
create index indx17 on t3 (f1,f4,f2);

