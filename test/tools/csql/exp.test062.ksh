Statement Executed
echo create index idx1 on t1(f1) tree unique;
Statement Executed
echo create index idx2 on t1(f1) tree primary;
Statement execute failed with error -4
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 INT );
CREATE INDEX idx1 on t1 (  f1  )  TREE  UNIQUE;
Statement Executed
