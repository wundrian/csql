echo Create table t1(f1 timestamp, f2 timestamp);
Create table t1(f1 timestamp, f2 timestamp);
insert into t1 values('2001-01-01 01:01:01', '2001-01-25 01:01:01');
insert into t1 values('2002-01-01 01:01:01', '2002-02-25 01:01:01');
insert into t1 values('2003-01-01 01:01:01', '2003-02-25 01:01:01');
insert into t1 values('2004-01-01 01:01:01', '2004-02-25 01:01:01');
insert into t1 values('2005-01-01 01:01:01', '2005-11-25 01:01:01');
echo select * from t1;
select * from t1;
echo select * from t1 where timestamp_add(f2 interval 4 hour) ='2003-02-25 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 4 hour) ='2003-02-25 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 4 hour)<='2003-02-25 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 4 hour)<='2003-02-25 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 4 hour) >'2003-02-25 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 4 hour) >'2003-02-25 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour) ='2001-02-04 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour) ='2001-02-04 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour)>='2001-02-04 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour)>='2001-02-04 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour) ='2002-03-07 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour) ='2002-03-07 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour)<='2002-03-07 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour)<='2002-03-07 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour) ='2004-03-06 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour) ='2004-03-06 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 244 hour)>='2004-03-06 05:01:01'; 
select * from t1 where timestamp_add(f2 interval 244 hour)>='2004-03-06 05:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 960 hour) ='2006-01-04 01:01:01'; 
select * from t1 where timestamp_add(f2 interval 960 hour) ='2006-01-04 01:01:01'; 
echo select * from t1 where timestamp_add(f2 interval 960 hour)!='2006-01-04 01:01:01'; 
select * from t1 where timestamp_add(f2 interval 960 hour)!='2006-01-04 01:01:01'; 
