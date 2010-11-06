echo select * from t1,t2;
select * from t1,t2;

echo select * from t1,t2 where t1.f1=t2.f1 and t1.f2=t2.f2;
select * from t1,t2 where t1.f1=t2.f1 and t1.f2=t2.f2;

echo select * from t1,t2 where t1.f2=t2.f2 and t1.f1=t2.f1;
select * from t1,t2 where t1.f2=t2.f2 and t1.f1=t2.f1;

echo select * from t1,t2 where t1.f1>t2.f1 and t1.f2>t2.f2;
select * from t1,t2 where t1.f1>t2.f1 and t1.f2>t2.f2;

echo select * from t1,t2 where t1.f2<t2.f2 and t1.f1<=t2.f1;
select * from t1,t2 where t1.f2<t2.f2 and t1.f1<=t2.f1;

echo select * from t1,t2 where t1.f1=t2.f1 or t1.f2=t2.f2;
select * from t1,t2 where t1.f1=t2.f1 or t1.f2=t2.f2;

echo select * from t1,t2 where t1.f2=t2.f2 or t1.f1=t2.f1;
select * from t1,t2 where t1.f2=t2.f2 or t1.f1=t2.f1;

echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>=t2.f2;
select * from t1,t2 where t1.f1>t2.f1 or t1.f2>=t2.f2;

echo select * from t1,t2 where t1.f2<t2.f2 or t1.f1<t2.f1;
select * from t1,t2 where t1.f2<t2.f2 or t1.f1<t2.f1;

echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>t2.f2;
select * from t1,t2 where t1.f1>t2.f1 or t1.f2>t2.f2;

echo select * from t1,t2 where t1.f1=t2.f1 and not(t1.f2=t2.f2);
select * from t1,t2 where t1.f1=t2.f1 and not(t1.f2=t2.f2);

echo select * from t1,t2 where t1.f2=t2.f2 and not(t1.f1=t2.f1);
select * from t1,t2 where t1.f2=t2.f2 and not(t1.f1=t2.f1);

echo select * from t1,t2 where not(t1.f1>t2.f1) and t1.f2>t2.f2;
select * from t1,t2 where not(t1.f1>t2.f1) and t1.f2>t2.f2;

echo select * from t1,t2 where not(t1.f2<t2.f2) and not(t1.f1<t2.f1);
select * from t1,t2 where not(t1.f2<t2.f2) and not(t1.f1<t2.f1);

echo select * from t1,t2 where not(t1.f1=t2.f1) or not(t1.f2=t2.f2);
select * from t1,t2 where not(t1.f1=t2.f1) or not(t1.f2=t2.f2);
