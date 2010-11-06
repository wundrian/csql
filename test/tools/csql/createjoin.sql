CREATE TABLE T1(f1 int,f2 int,f3 int,f4 int,f5 int);
CREATE INDEX idx1 on T1(f2);
CREATE INDEX idx2 on T1(f3);
CREATE INDEX idx3 on T1(f4);
CREATE INDEX idx4 on T1(f5);
CREATE TABLE T2(f1 int,f2 int,primary key(f2));
CREATE TABLE T3(f1 int,f3 int,primary key(f3));
CREATE TABLE T4(f1 int,f4 int,primary key(f4));
CREATE TABLE T5(f1 int,f5 int,primary key(f5));
