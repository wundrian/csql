echo create table t1 ( f1 int, f2 int, primary key(f1, f2));
Statement Executed
echo create index ind on t1(f1);
Statement execute failed with error -4
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  NOT NULL );
CREATE INDEX t1_idx1_Primary on t1 (  f1  ,f2  )  UNIQUE;
SET AUTOCOMMIT OFF;
Statement Executed

wrong expected file test failed
