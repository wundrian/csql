echo select t11.f5, t13.f8 from t11,t13 where t11.f5=t13.f8;
select t11.f5, t13.f8 from t11,t13 where t11.f5=t13.f8;

echo select f1,f5,f8 from t11,t13 where t11.f5=t13.f8;
select f1,f5,f8 from t11,t13 where t11.f5=t13.f8;

echo select * from t11,t13 where t13.f8 > t11.f5;
select * from t11,t13 where t13.f8 > t11.f5;

echo select f1,f5,f8 from t11,t13 where t13.f8 < t11.f5;
select f1,f5,f8 from t11,t13 where t13.f8 < t11.f5;

echo select * from t11,t13 where f5 > f8;
select * from t11,t13 where f5 > f8;



