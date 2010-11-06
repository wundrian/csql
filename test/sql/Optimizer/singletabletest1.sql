echo No Primary key -Test Case - 1,2,3
echo select * from t1;
explain plan select * from t1;
echo select * from t1 where f1=10;
explain plan select * from t1 where f1=10;
echo select * from t1 where f1>10;
explain plan select * from t1 where f1>10;

create index idx1 on t1 (f1) hash primary;
echo Primary key -Test Case - 4,5,6
echo select * from t1;
explain plan select * from t1;
echo select * from t1 where f1=10;
explain plan select * from t1 where f1=10;
echo select * from t1 where f1>10;
explain plan select * from t1 where f1>10;

create index idx2 on t1 (f2) hash;
echo Hash Index -Test Case - 7,8,9
echo select * from t1;
explain plan select * from t1;
echo select * from t1 where f2=10;
explain plan select * from t1 where f2=10;
echo select * from t1 where f2>10;
explain plan select * from t1 where f2>10;

create index idx3 on t1 (f3) tree;
echo Tree Index -Test Case - 10,11,12
echo select * from t1;
explain plan select * from t1;
echo select * from t1 where f3=10;
explain plan select * from t1 where f3=10;
echo select * from t1 where f2>10;
explain plan select * from t1 where f3>10;

