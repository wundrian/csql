drop trigger if exists triggerinsertt1;
drop trigger if exists triggerupdatet1;
drop trigger if exists triggerdeletet1;
create trigger triggerinsertt1 AFTER INSERT on t1 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', NEW.f1, 1,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', NEW.f1, 1,2);End; 
create trigger triggerupdatet1 AFTER UPDATE on t1 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', OLD.f1, 2,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', NEW.f1, 1,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', OLD.f1, 2,2);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', NEW.f1, 1,2); End; 
create trigger triggerdeletet1 AFTER DELETE on t1 FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', OLD.f1, 2,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t1', OLD.f1, 2,2);End; 

