echo create table t1(f1 int, f2 int);
create table t1(f1 int, f2 int);
echo create index hashidxt1f1 on t1(f1) hash;
create index hashidxt1f1 on t1(f1) hash;
echo create index hashidxt1f2 on t1(f2) hash;
create index hashidxt1f2 on t1(f2) hash;
echo explain plan select a.f1,b.f1 from t1 a, t1 b where a.f1=b.f1;
explain plan select a.f1,b.f1 from t1 a, t1 b where a.f1=b.f1;
