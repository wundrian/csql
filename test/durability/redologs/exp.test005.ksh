Server Started
Statement Executed
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
PREPARE: SID:2 INSERT INTO t1 VALUES(1234,?);
FREE: SID:2 TID:12 
PREPARE: SID:4 INSERT INTO t1 VALUES(1234,?);
FREE: SID:4 TID:12 
PREPARE: SID:6 INSERT INTO t1 VALUES(1234,?);
FREE: SID:6 TID:12 
Redo log filename is :/tmp/csql/db/csql.db.cur
EXECDIRECT SID:1 TID:72 STMT:CREATE TABLE t1(f1 int not null, f2 int not null);
SET SID:2 POS:1 TYPE:0 LEN:4 Value:100
EXEC SID:2 TID:72
SET SID:2 POS:1 TYPE:0 LEN:4 Value:200
EXEC SID:2 TID:72
FREE SID:2 
EXECDIRECT SID:3 TID:64 STMT:create index idx on t1 (f2) primary hash;
SET SID:4 POS:1 TYPE:0 LEN:4 Value:100
FREE SID:4 
EXECDIRECT SID:5 TID:36 STMT:drop index idx;
SET SID:6 POS:1 TYPE:0 LEN:4 Value:100
EXEC SID:6 TID:40
FREE SID:6 
Server Killed

Checking Durability
Server Started
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  NOT NULL );
INSERT INTO t1 VALUES(1234,100);
INSERT INTO t1 VALUES(1234,200);
INSERT INTO t1 VALUES(1234,100);