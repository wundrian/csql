echo Create table t1(f1 date, f2 date);
Create table t1(f1 date, f2 date);
insert into t1 values('2001-05-01', '2001-05-01');
insert into t1 values('2001-06-01', '2001-06-01');
insert into t1 values('2001-07-01', '2002-07-01');
insert into t1 values('2001-08-01', '2002-08-01');
insert into t1 values('2001-09-01', '2002-09-01');
echo select * from t1;
select * from t1;
echo select * from t1 where date_add(f1 interval 5 month) < '2001-12-01';
select * from t1 where date_add(f1 interval 5 month) < '2001-12-01';
echo select * from t1 where date_add(f1 interval 6 month) = '2002-01-01';
select * from t1 where date_add(f1 interval 6 month) = '2002-01-01';
echo select * from t1 where date_add(f1 interval 18 month)>= '2003-01-01';
select * from t1 where date_add(f1 interval 18 month)>= '2003-01-01';

