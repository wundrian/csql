echo select * from t1;
select * from t1;

echo select min(t1.f2) from t1 group by t1.f1;
select min(t1.f2) from t1 group by t1.f1;

echo select avg(t1.f2) from t1 group by t1.f1;
select avg(t1.f2) from t1 group by t1.f1;

echo select sum(t1.f2) from t1 group by notexist;
select sum(t1.f2) from t1 group by notexist;

echo select sum(t1.f2) from t1 group by t1.notexist;
select sum(t1.f2) from t1 group by t1.notexist;

echo select sum(t1.f2) from t1 group by notexist.f1;
select sum(t1.f2) from t1 group by notexist.f1;
