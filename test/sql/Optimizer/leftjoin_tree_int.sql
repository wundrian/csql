echo create table t1(f1 int, f2 int);
create table t1(f1 int, f2 int);
echo create index treeidxt1f1 on t1(f1) tree;
create index treeidxt1f1 on t1(f1) tree;
echo create index treeidxt1f2 on t1(f2) tree;
create index treeidxt1f2 on t1(f2) tree;
echo create table t2(f1 int, f2 int);
create table t2(f1 int, f2 int);
echo create index treeidxt2f1 on t2(f1) tree;
create index treeidxt2f1 on t2(f1) tree;
echo create index treeidxt2f2 on t2(f2) tree;
create index treeidxt2f2 on t2(f2) tree;
echo explain plan select * from t1,t2;
explain plan select * from t1,t2;
echo explain plan select * from t1 left join t2 on t1.f1=t2.f1;
explain plan select * from t1 left join t2 on t1.f1=t2.f1;
echo explain plan select * from t1 left join t2 on t1.f1<=t2.f1;
explain plan select * from t1 left join t2 on t1.f1<=t2.f1;
echo explain plan select * from t1 left join t2 on t1.f1!=t2.f1;
explain plan select * from t1 left join t2 on t1.f1!=t2.f1;
