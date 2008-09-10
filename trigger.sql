use test;
drop trigger if exists triggerinsertp1;
drop trigger if exists triggerupdatep1;
drop trigger if exists triggerdeletep1;

DELIMITER | 
create trigger triggerinsertp1
AFTER INSERT on p1
FOR EACH ROW
BEGIN
Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('p1', NEW.f1, 1,1);
End; 

create trigger triggerupdatep1
AFTER UPDATE on p1
FOR EACH ROW
BEGIN
Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('p1', OLD.f1, 2,1);
Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('p1', NEW.f1, 1,1);
End; 

create trigger triggerdeletep1
AFTER DELETE on p1
FOR EACH ROW
BEGIN
Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('p1', OLD.f1, 2,1);
End; 
|
