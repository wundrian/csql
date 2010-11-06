echo select min(t1.notexist) from t1;
select min(t1.notexist) from t1;

echo select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100;
select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100;

echo select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100 group by t1.f2;
select max(t1.f1), sum(t2.f1) from t1,t2 where t1.f1 = t2.f1 and t1.f1 <100 group by t1.f2;

echo select max(t1.f1), max(t2.notexist) from t1,t2 group by t1.f2;
select max(t1.f1), max(t2.notexist) from t1,t2 group by t1.f2;
