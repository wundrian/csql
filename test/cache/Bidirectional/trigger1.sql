use test;
drop trigger if exists triggerinsertt2;
drop trigger if exists triggerupdatet2;
drop trigger if exists triggerdeletet2;
create trigger triggerinsertt2 AFTER INSERT on t2 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', NEW.f1, 1,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', NEW.f1, 1,2);End; 
create trigger triggerupdatet2 AFTER UPDATE on t2 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', OLD.f1, 2,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', NEW.f1, 1,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', OLD.f1, 2,2);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', NEW.f1, 1,2); End; 
create trigger triggerdeletet2 AFTER DELETE on t2 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', OLD.f1, 2,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t2', OLD.f1, 2,2);End; 
