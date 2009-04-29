drop trigger if exists triggerinsertemployee;
drop trigger if exists triggerupdateemployee;
drop trigger if exists triggerdeleteemployee;
create trigger triggerinsertemployee AFTER INSERT on employee FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', NEW.eid, 1,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', NEW.eid, 1,2);End; 
create trigger triggerupdateemployee AFTER UPDATE on employee FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', OLD.eid, 2,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', NEW.eid, 1,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', OLD.eid, 2,2);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', NEW.eid, 1,2); End; 
create trigger triggerdeleteemployee AFTER DELETE on employee FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', OLD.eid, 2,1); Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('employee', OLD.eid, 2,2);End; 

