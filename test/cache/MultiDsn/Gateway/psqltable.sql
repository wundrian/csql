create table tt1(f1 int,f2 char(10),primary key(f1));
insert into tt1 values(11,'one');
insert into tt1 values(22,'two');
insert into tt1 values(33,'three');
commit;
create table tt2(f1 int,f2 char(10),primary key(f1));
insert into tt2 values(1111,'psql');
insert into tt2 values(2222,'open');
insert into tt2 values(3333,'source');
commit;


