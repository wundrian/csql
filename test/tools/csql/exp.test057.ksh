Statement Executed
echo create index idx1 on t1(f1) hash unique;
Statement Executed
echo drop index idx1;
Statement Executed
echo create index idx2 on t1(f1) hash primary;
Statement Executed
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 INT );
CREATE INDEX idx2 on t1 (  f1  )  HASH  UNIQUE;
SET AUTOCOMMIT OFF;
Statement Executed
