drop table csql_log_int;
drop SEQUENCE CSQL_ID;
create table csql_log_int(tablename char(64), pkid number(9), operation number(9), cacheid number(9), id number(9) not null );
CREATE SEQUENCE   "CSQL_ID"  MINVALUE 1  INCREMENT BY 1 START WITH 1 ;
