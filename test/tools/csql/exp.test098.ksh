echo create table t1 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f1) size 1500);
Statement Executed
echo create index ind1 on t1(f2) hash size 750;
Statement Executed
echo create index ind2 on t1(f3) tree size 10000;
Statement Executed
echo create table t2 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f2) size 1500);
Statement Executed
echo create index ind3 on t2(f1) hash unique size 750;
Statement Executed
CREATE TABLE t1 (f1 INT  NOT NULL , f2 CHAR (12), f3 INT , f4 INT , f5 BIGINT );
CREATE INDEX t1_idx1_Primary on t1 (  f1  )  HASH  UNIQUE SIZE 1500 ;
CREATE INDEX ind1 on t1 (  f2  )  HASH  SIZE 750 ;
CREATE INDEX ind2 on t1 (  f3  )  TREE  SIZE 10000 ;
CREATE TABLE t2 (f1 INT , f2 CHAR (12) NOT NULL , f3 INT , f4 INT , f5 BIGINT );
CREATE INDEX t2_idx1_Primary on t2 (  f2  )  HASH  UNIQUE SIZE 1500 ;
CREATE INDEX ind3 on t2 (  f1  )  HASH  UNIQUE SIZE 750 ;
SET AUTOCOMMIT OFF;
Statement Executed
Statement Executed
