Statement Executed
echo create index idx1 on t1(f1) tree unique;
Statement Executed
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 INT );
CREATE INDEX t1_idx1_Primary on t1 (  f1  )  HASH  UNIQUE;
CREATE INDEX idx1 on t1 (  f1  )  TREE  UNIQUE;
Statement Executed
