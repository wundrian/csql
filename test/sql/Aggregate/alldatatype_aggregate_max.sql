echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f1,f2,f3,f4;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f1,f2,f3,f4;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f2,f1,f4,f3;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f2,f1,f4,f3;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f3,f1,f4,f2;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f3,f1,f4,f2;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f4,f3,f2,f1;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f4,f3,f2,f1;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f1,f2,f3,f4 having max(f5)>=5000;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 group by f1,f2,f3,f4 having max(f5)>=5000;

echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f1,f2,f3,f4;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f3,f1,f2;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f3,f1,f2;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f1,f2,f3;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f1,f2,f3;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f3,f1,f2;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 group by f4,f3,f1,f2;

echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f2,f3,f4,f1;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f2,f3,f4,f1;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f4,f3;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f4,f3;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4 having max(f5)>=4000 and max(f5)<6000;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f1<15 group by f1,f2,f3,f4 having max(f5)>=4000 and max(f5)<6000;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4;
echo select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4 having max(f5)>=5000 and max(f5)<10000;
select f1,f2,f3,f4,count(f5),max(f5) ,count(f6),max(f6)  from t1 where f1 >= 12 and f2<=130 group by f1,f2,f3,f4 having max(f5)>=5000 and max(f5)<10000;
