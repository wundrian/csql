select max(t1.f1),sum(t2.f1) from t1,t2 where t1.f1=t2.f1 and t1.f1<100;
