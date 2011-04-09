Server Started
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
EXECDIRECT SID:1 TID:48 STMT:CREATE TABLE laks(f1 int);
PREPARE: SID:2 INSERT INTO laks values (10);
EXEC SID:2 TID:16
FREE SID:2 
PREPARE: SID:3 INSERT INTO laks values (20);
EXEC SID:3 TID:16
FREE SID:3 
PREPARE: SID:4 INSERT INTO laks values (30);
EXEC SID:4 TID:16
FREE SID:4 
Server Killed

Checking Durability
Server Started
Statement Executed: Rows Affected = 1
PREPARE: SID:1 INSERT INTO laks values (50);
EXEC SID:1 TID:16
FREE SID:1 
