CREATE TABLE t1(f1 INT,f2 INT, PRIMARY KEY(f1));
CREATE TABLE t2(f1 INT,f2 INT,FOREIGN KEY(f1) REFERENCES t1(f1));
CREATE TABLE t3(f1 INT,f2 INT,FOREIGN KEY(f1) REFERENCES t1(f1));
drop table t2;
drop table t1;
