
echo select t1.f2, t1.f1, t2.f1 from t1,t2;
select t1.f2, t1.f1, t2.f1 from t1,t2;

echo select t1.f2, t1.f1, t2.f1 from t1,t2 group by t1.f2;
select t1.f2, t1.f1, t2.f1 from t1,t2 group by t1.f2;

echo select t1.f2, max(t1.f1), sum(t2.f1) from t1, t2 group by t1.f2;
select t1.f2, max(t1.f1), sum(t2.f1) from t1, t2 group by t1.f2;

echo select f1, f2 from t1 group by f1,f2;
select f1, f2 from t1 group by f1,f2;

echo select f1, sum(f2) from t1 group by f3;
select f1, sum(f2) from t1 group by f3;
