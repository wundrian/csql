echo Create table t1(f1 date, f2 time);
Create table t1(f1 date, f2 time);
insert into t1 values('2001-01-01', '23:59:59');
insert into t1 values('2002-01-01', '22:58:58');
insert into t1 values('2003-01-03', '12:30:30');
insert into t1 values('2004-01-01', '02:02:02');
insert into t1 values('2005-01-01', '01:01:01');
echo select * from t1;
select * from t1;
echo select * from t1 where extract(hour from f2) = 12;
select * from t1 where extract(hour from f2) = 12;
echo select * from t1 where extract(hour from f2) < 12;
select * from t1 where extract(hour from f2) < 12;
echo select * from t1 where extract(hour from f2)<= 12;
select * from t1 where extract(hour from f2)<= 12;
echo select * from t1 where extract(hour from f2) > 12;
select * from t1 where extract(hour from f2) > 12;
echo select * from t1 where extract(hour from f2)>= 12;
select * from t1 where extract(hour from f2)>= 12;
echo select * from t1 where extract(hour from f2)!= 12;
select * from t1 where extract(hour from f2)!= 12;
