Statement Executed
echo create index idx1 on t1(f1) unique;
Statement Executed
echo create index idx2 on t1(f1) primary;
Statement execute failed with error -4
echo create index idx3 on t1(f1) hash primary;
Statement execute failed with error -4
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 INT );
CREATE INDEX idx1 on t1 (  f1  )  HASH  UNIQUE;
SET AUTOCOMMIT OFF;
Statement Executed
