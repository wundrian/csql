echo  select * from t11,t12 where t11.f5=t12.f1;
select * from t11,t12 where t11.f5=t12.f1;

echo  select * from t11,t12 where t11.f5 > t12.f1;
select * from t11,t12 where t11.f5 > t12.f1;

echo select * from t11,t12 where t12.f1 <= t11.f5;
select * from t11,t12 where t12.f1 <= t11.f5;

echo select * from t11,t12 where t12.f1 != t11.f5;
select * from t11,t12 where t12.f1 != t11.f5;
      
echo select * from t11,t12 where t12.f1 > 20;
select * from t11,t12 where t12.f1 > 20;

