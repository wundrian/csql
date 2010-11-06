echo select * from t1,t2,t3 where t1.f1 = t2.f1 and t2.f1=100;
select * from t1,t2,t3 where t1.f1 = t2.f1 and t2.f1=100;
echo select * from t2,t1,t3 where t1.f1 = t2.f1 and t2.f1=100;
select * from t2,t1,t3 where t1.f1 = t2.f1 and t2.f1=100;
echo select * from t3,t1,t2 where t1.f1 = t2.f1 and t2.f1=100;
select * from t3,t1,t2 where t1.f1 = t2.f1 and t2.f1=100;
