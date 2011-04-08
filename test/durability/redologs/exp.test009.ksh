Server Started
Statement Executed
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
PREPARE: SID:2 INSERT INTO t1 VALUES(1234,?);
EXECDIRECT SID:1 TID:72 STMT:CREATE TABLE t1(f1 int not null, f2 int not null);
SET SID:2 POS:1 ISNULL:FALSE TYPE:0 LEN:4 Value:100
Server Killed

Checking Durability
Server Started
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  NOT NULL );
