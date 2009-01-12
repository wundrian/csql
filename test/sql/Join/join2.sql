echo select * from t1,t2 where t1.f1>100 or t2.f1<100;
select * from t1,t2 where t1.f1>100 or t2.f1<100; 

echo select t1.f1, t2.f1, t1.f2, t2.f2 from t1,t2;
select t1.f1, t2.f1, t1.f2, t2.f2 from t1,t2; 

echo select * from t1,t2 where t1.f1 = t2.f1 and t1.f1 >100;
select * from t1,t2 where t1.f1 = t2.f1 and t1.f1 >100;

