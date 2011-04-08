Server Started
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed
Statement execute failed with error -21
Statement Executed: Rows Affected = 1
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed
Statement Redo log filename is :/tmp/csql/db/csql.db.stmt
EXECDIRECT SID:1 TID:64 STMT:CREATE TABLE laks(f1 int not null, f2 int);
PREPARE: SID:2 INSERT INTO laks values (10, 10);
EXEC SID:2 TID:16
FREE SID:2 
EXECDIRECT SID:3 TID:64 STMT:create index idx on laks (f1) primary hash;
PREPARE: SID:4 INSERT INTO laks values (10, 10);
FREE SID:4 
PREPARE: SID:5 INSERT INTO laks values (50, 50);
EXEC SID:5 TID:16
FREE SID:5 
EXECDIRECT SID:6 TID:36 STMT:DROP Index idx;
PREPARE: SID:7 INSERT INTO laks values (50, 50);
EXEC SID:7 TID:16
FREE SID:7 
EXECDIRECT SID:8 TID:40 STMT:DROP table laks;
Server Killed

Checking Durability
Server Started
