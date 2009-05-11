Durablity = TRUE
Server Started
CREATING TABLE
echo create table t1 (f1 char(10), f2 tinyint, f3 smallint,f4 int, f5 bigint,f6 integer, f7 float, f8 real,f9 double,f10 long,f11 binary(128),f12 date,f13 time,f14 timestamp);
Statement Executed
Server Killed

Durablity = TRUE
Checking Durability
Server Started
INSERTING INTO TABLE
echo insert into t1 values('NIHAR', 1,1,-2147483648,9223372036854775807, 2147483648,1.1, 1000000000.000000,10000001.10000001,99999,'ABCDEF0123456789','2001-1-1', '01:01:01', '2001-11-30 01:01:01');
Statement Executed: Rows Affected = 1
echo insert into t1 values(NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
Statement Executed: Rows Affected = 1
Server Killed

Durablity = TRUE
Checking Durability
Server Started
UPDATING RECORDS IN TABLE
echo UPDATE t1 set f1='PAPU', f2=10, f3=2, f4=2147483647, f5=-9223372036854775808, f6=-2147483647, f7=10.01, f8=2000000002.000002, f9=20000002.200002, f10=2147483647, f11='9876543210DcAbEf', f12='2003-3-3', f13='03:03:03', f14='2003-3-3 03:03:03';
Statement Executed: Rows Affected = 2
Server Killed

Durablity = TRUE
Checking Durability
Server Started
DELETING RECORDS FROM TABLE
echo delete from t1;
Statement Executed: Rows Affected = 2
Server Killed

Durablity = TRUE
Checking Durability
Server Started
DROPPING TABLE
echo drop table t1;
Statement Executed
