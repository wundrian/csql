create table t1(f1 int,f2 int,f3 int,f4 char(10));
insert into t1 values(98,1,10,'AAA');
insert into t1 values(99,2,20,'BBB');
insert into t1 values(100,2,10,'CCC'); 
insert into t1 values(101,3,10,'AAA'); 
insert into t1 values(99,2,20,'BBB');

echo select * from t1;
select * from t1;

echo select distinct * from t1 ;
select distinct * from t1 ;

echo select distinct f2 from t1 ;
select distinct f2 from t1 ;

echo select distinct f4 from t1 ;
select distinct f4 from t1 ;

echo select distinct f2, f4 from t1 ;
select distinct f2, f4 from t1 ;
