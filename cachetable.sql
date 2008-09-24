#MySQL
Command
-------
$mysql -u root -p (or)
$mysql -u root -p <filename


Statements
----------
create table csql_log_int(tablename char(64), pkid int, operation int,cacheid int, id int not null unique auto_increment)engine='innodb';

#POSTGRES
Command
-------
$psql test (or)
$psql test -f filename

Statements
----------
create table csql_log_int(tablename varchar(64), pkid int, operation int,cacheid int);
alter table csql_log_int add id serial;
