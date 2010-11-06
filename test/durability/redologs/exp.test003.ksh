Server Started
Statement Executed
Tuple value 200
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
PREPARE: SID:2 INSERT INTO t1 VALUES(1234,?);
FREE: SID:2 TID:12 
PREPARE: SID:3 UPDATE t1 set f1=? where f2=200;
FREE: SID:3 TID:12 
PREPARE: SID:4 DELETE from t1 where f2=?;
FREE: SID:4 TID:12 
Redo log filename is :/tmp/csql/db/csql.db.cur
EXECDIRECT SID:1 TID:56 STMT:CREATE TABLE t1(f1 int, f2 int);
SET SID:2 POS:1 TYPE:0 LEN:4 Value:100
EXEC SID:2 TID:72
SET SID:2 POS:1 TYPE:0 LEN:4 Value:200
EXEC SID:2 TID:72
FREE SID:2 
SET SID:3 POS:1 TYPE:0 LEN:4 Value:200
EXEC SID:3 TID:40
FREE SID:3 
SET SID:4 POS:1 TYPE:0 LEN:4 Value:100
EXEC SID:4 TID:40
FREE SID:4 
Server Killed

Checking Durability
Server Started
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
