CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t2(f1 int NOT NULL,f2 int,foreign key(f1) references t1(f1));
CREATE INDEX idx1 on t2(f1) HASH UNIQUE;

