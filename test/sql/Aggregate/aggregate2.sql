echo select count(f1) from t1;
select count(t1.f1) from t1;

echo select count(*) from t1 where f4='AAA';
select count(*) from t1 where f4='AAA';

echo select sum(f1) from t1;
select sum(t1.f1) from t1;

echo select avg(f1) from t1;
select avg(t1.f1) from t1;

echo select min(t1.f1) from t1;
select min(t1.f1) from t1;

echo select min(f4) from t1;
select min(f4) from t1;

echo select max(t1.f1) from t1;
select max(t1.f1) from t1;

echo select max(f4) from t1;
select max(f4) from t1;
