AFTER UPDATE PREPARE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=1
STATEMENT CACHE END
AFTER STMT FREE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=0
STATEMENT CACHE END
AFTER DELETE PREPARE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=0
 SQL=DELETE from t1 where f2=?; hits=0 inuse=1
STATEMENT CACHE END
AFTER STMT FREE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=0
 SQL=DELETE from t1 where f2=?; hits=0 inuse=0
STATEMENT CACHE END
AFTER SELECT PREPARE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=0
 SQL=DELETE from t1 where f2=?; hits=0 inuse=0
 SQL=SELECT f1 from t1 where f2=?; hits=0 inuse=1
STATEMENT CACHE END
Tuple value 2
Tuple value 3
Tuple value 4
Tuple value 5
AFTER STMT FREE operation
STATEMENT CACHE START 
 SQL=UPDATE t1 set f2=? where f1=?; hits=0 inuse=0
 SQL=DELETE from t1 where f2=?; hits=0 inuse=0
 SQL=SELECT f1 from t1 where f2=?; hits=0 inuse=0
STATEMENT CACHE END
AFTER disconnect
STATEMENT CACHE START 
STATEMENT CACHE END
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 VARCHAR (20));
CREATE INDEX t1_idx1_Primary on t1 (  f1  )  HASH  UNIQUE;
INSERT INTO t1 VALUES(2,1, 'Second');
INSERT INTO t1 VALUES(3,1, 'Third');
INSERT INTO t1 VALUES(4,1, 'Fourth');
INSERT INTO t1 VALUES(5,1, 'Fifth');
