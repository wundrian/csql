echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 group by f1,f2;
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 group by f1,f2;
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 group by f1,f2 having max(f4)>='K';
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 group by f1,f2 having max(f4)>='K';
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 group by f1,f2;
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 group by f1,f2;
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 group by f1,f2 having max(f8)>='11:59:55';
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 group by f1,f2 having max(f8)>='11:59:55';
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2;
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2;
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having max(f9)>='2009-03-03 11:59:59';
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having max(f9)>='2009-03-03 11:59:59';
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having max(f4)>='K' and max(f8) <'11:59:58';
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having max(f4)>='K' and max(f8) <'11:59:58';
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 ;
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 ;
echo select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 having max(f7)>='2009/3/2' and max(f9)<>'2009-03-01 11:59:59';
select f1,f2,max(f4),max(f7),max(f8),max(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 having max(f7)>='2009/3/2' and max(f9)<>'2009-03-01 11:59:59';
echo select f7,f8,f9,max(f4) from t1 group by f7,f8,f9;
select f7,f8,f9,max(f4) from t1 group by f7,f8,f9;
echo select f9,f7,f8,max(f4) from t1 group by f7,f8,f9;
select f9,f7,f8,max(f4) from t1 group by f7,f8,f9;
echo select f7,f8,f9,max(f4) from t1 group by f7,f9,f8;
select f7,f8,f9,max(f4) from t1 group by f7,f9,f8;
echo select f7,f8,f9,max(f4) from t1 group by f7,f9,f8 having max(f4)>='K' and max(f4) <'Q';
select f7,f8,f9,max(f4) from t1 group by f7,f9,f8 having max(f4)>='K' and max(f4) <'Q';
echo select f4,f8,f9,max(f7) from t1 group by f4,f8,f9;
select f4,f8,f9,max(f7) from t1 group by f4,f8,f9;
echo select f4,f8,f9,max(f7) from t1 group by f4,f8,f9 having max(f7)<='2009-03-04' and max(f7) >'2009-03-02' ;
select f4,f8,f9,max(f7) from t1 group by f4,f8,f9 having max(f7)<='2009-03-04' and max(f7) >'2009-03-02' ;
echo select f9,f7,f4,max(f8) from t1 group by f4,f7,f9;
select f9,f7,f4,max(f8) from t1 group by f4,f7,f9;
echo select f9,f7,f4,max(f8) from t1 group by f4,f7,f9 having max(f8)<='11:59:59' and max(f8) >'11:59:57' ;
select f9,f7,f4,max(f8) from t1 group by f4,f7,f9 having max(f8)<='11:59:59' and max(f8) >'11:59:57' ;
echo select f7,f8,f4,max(f9) from t1 group by f4,f7,f8;
select f7,f8,f4,max(f9) from t1 group by f4,f7,f8;
echo select f7,f8,f4,max(f9) from t1 group by f4,f7,f8 having max(f9)<='2009-03-05 11:59:59' and max(f9) >'2009-03-02 11:59:59' ;
select f7,f8,f4,max(f9) from t1 group by f4,f7,f8 having max(f9)<='2009-03-05 11:59:59' and max(f9) >'2009-03-02 11:59:59' ;