CREATE TABLE t1 (f1 INT , f2 INT , primary key(f1));
CREATE TABLE t2 (f1 INT , f2 INT , primary key(f1));
INSERT INTO t1 VALUES(1,1);
INSERT INTO t1 VALUES(2,2);
INSERT INTO t2 VALUES(1,1);
select * from t1 left join t2 on t1.f1=t2.f1;
