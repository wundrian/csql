#!/bin/sh
# Create table t1 having two integer field f1 ,f2 with primary key f1 . 
# Create table t2 having two integer field f3,f4 with primary key f3 . 
# Create table t3 having two integer field f5,f6 with foreign key f5 refers t1 (f1) and foreign key f6 refers t2 (f3). 
# Drop table t2. It should be failed. because child t3 is exist.
#
echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t1(f1 int,f2 int,primary key(f1));
echo CREATE TABLE t2(f3 int,f4 int,primary key(f3));
CREATE TABLE t2(f3 int,f4 int,primary key(f3));
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3));
CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3));
echo DROP TABLE t2;
DROP TABLE t2;
