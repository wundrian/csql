STATEMENT CACHE START 
 SQL=INSERT INTO t1 VALUES(?, ?, 'CSQL'); hits=0 inuse=0
STATEMENT CACHE END
dropping index
After drop index 
STATEMENT CACHE START 
STATEMENT CACHE END
After reusing cached insert stmt
STATEMENT CACHE START 
 SQL=INSERT INTO t1 VALUES(?, ?, 'CSQL'); hits=0 inuse=0
STATEMENT CACHE END
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT , f3 VARCHAR (20));
CREATE INDEX t1_idx1_Primary on t1 (  f1  )  HASH  UNIQUE;
INSERT INTO t1 VALUES(1,1, 'First');
INSERT INTO t1 VALUES(2,1, 'Second');
INSERT INTO t1 VALUES(3,1, 'Third');
INSERT INTO t1 VALUES(4,1, 'Fourth');
INSERT INTO t1 VALUES(5,1, 'Fifth');
INSERT INTO t1 VALUES(100,100, 'CSQL');
INSERT INTO t1 VALUES(200,200, 'CSQL');
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	100	100	CSQL	
	
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	200	200	CSQL	
	
