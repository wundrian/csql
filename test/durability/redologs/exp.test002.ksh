Server Started
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	laks.f1	laks.f2	
---------------------------------------------------------
	40	40	
	50	50	
	
EXECDIRECT SID:1 TID:56 STMT:CREATE TABLE laks(f1 int, f2 int);
PREPARE: SID:2 INSERT INTO laks values (10, 10);
EXEC SID:2 TID:16
FREE SID:2 
PREPARE: SID:3 INSERT INTO laks values (20, 20);
EXEC SID:3 TID:16
FREE SID:3 
PREPARE: SID:4 INSERT INTO laks values (30, 30);
EXEC SID:4 TID:16
FREE SID:4 
PREPARE: SID:5 INSERT INTO laks values (40, 40);
EXEC SID:5 TID:16
FREE SID:5 
PREPARE: SID:6 INSERT INTO laks values (50, 50);
EXEC SID:6 TID:16
FREE SID:6 
PREPARE: SID:7 UPDATE laks set f2=60 where f1=30;
EXEC SID:7 TID:16
FREE SID:7 
PREPARE: SID:8 UPDATE laks set f2=70 where f1=30;
EXEC SID:8 TID:16
FREE SID:8 
PREPARE: SID:9 DELETE FROM laks where f1=20;
EXEC SID:9 TID:16
FREE SID:9 
Server Killed

Checking Durability
Server Started
