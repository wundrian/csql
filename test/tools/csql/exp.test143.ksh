echo CREATE TABLE t1(f1 INT, f2 INT, PRIMARY KEY(f1));
Statement Executed
echo CREATE TABLE t2(f3 INT, f4 INT, PRIMARY KEY(f4), FOREIGN KEY(f3) REFERENCES t1(f1));
Statement Executed
echo CREATE TABLE t3(f5 INT, f6 INT, FOREIGN KEY(f5) REFERENCES t2(f4));
Statement Executed
Statement Executed
Statement Executed
Statement Executed
