echo select t11.f5, t13.f8 from t11,t13 where t11.f5=t13.f8;
select t11.f5, t13.f8 from t11,t13 where t11.f5=t13.f8;

echo select t11.f1,t11.f5,t13.f8 from t11,t13 where t11.f5=t13.f8;
select t11.f1,t11.f5,t13.f8 from t11,t13 where t11.f5=t13.f8;

echo select * from t11,t13 where t13.f8 > t11.f5;
select * from t11,t13 where t13.f8 > t11.f5;

echo select t11.f1,t11.f5,t13.f8 from t11,t13 where t13.f8 < t11.f5;
select t11.f1,t11.f5,t13.f8 from t11,t13 where t13.f8 < t11.f5;
