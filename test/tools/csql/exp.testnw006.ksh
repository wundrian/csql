Network CSql
echo drop table test;
echo create table t1 (f1 integer);
Statement Executed
echo drop table t1;
Statement Executed
echo create table t1 (f1 integer);
Statement Executed
echo drop table t1;
Statement Executed
echo create table t1(f1 int,f2 int);
Statement Executed
echo create index idx1 on t1(f1);
Statement Executed
echo drop index idx1;
Statement Executed
echo create index idx1 on t1(f1);
Statement Executed
echo drop table t1;
Statement Executed
echo create table t1 (f1 integer not null, f2 integer not null,f3 int not null, f4 int not null,f5 int not null, f6 int not null,f7 int not null);
Statement Executed
echo create index idx1 on t1 (f1);
Statement Executed
echo create index idx2 on t1 (f2) UNIQUE;
Statement Executed
echo create index idx3 on t1 (f3) PRIMARY;
Statement Executed
echo create index idx4 on t1 (f4) HASH PRIMARY;
Statement Executed
echo create index idx4 on t1 (f5) HASH PRIMARY;
Statement execute failed with error -4
echo create index idx5 on t1 (f4) HASH PRIMARY;
Statement execute failed with error -4
echo create index idx5 on t1 (f5) TREE;
Statement Executed
echo create index idx6 on t1 (f6) TREE PRIMARY;
Statement Executed
echo create index idx6 on t1 (f7) TREE PRIMARY;
Statement execute failed with error -4
echo create index idx7 on t1 (f6) TREE PRIMARY;
Statement execute failed with error -4
echo drop index idx1;
Statement Executed
echo drop index idx2;
Statement Executed
echo drop index idx3;
Statement Executed
echo drop index idx4;
Statement Executed
echo drop index idx5;
Statement Executed
echo drop table t1;
Statement Executed
