create index idx1 on t1 (f1) hash primary;
create index idx3 on t1 (f2) tree;
echo Multiple predicates Test Cases - 1,2,3
echo select * from t1 where f1=10 and f3=20;
explain plan select * from t1 where f1=10 and f3 =20;
echo select * from t1 where f2>10 and f3=20;
explain plan select * from t1 where f1>10 and f3 =20;
echo select * from t1 where f3=20 and f1 >10;
explain plan select * from t1 where f3 =20 and f1>10;


echo Disjunctive Queries Test case - 4,5,6,7,8
echo select * from t1 where f1!=10;
explain plan select * from t1 where f1!=10;
echo select * from t1 where f2!=10;
explain plan select * from t1 where f2!=10;
echo select * from t1 where f1=10 or f3=20;
explain plan select * from t1 where f1=10 or f3 =20;
echo select * from t1 where f2>10 or f3=20;
explain plan select * from t1 where f2>10 or f3 =20;
echo select * from t1 where f3=20 or f2 >10;
explain plan select * from t1 where f3 =20 or f2 >10;

