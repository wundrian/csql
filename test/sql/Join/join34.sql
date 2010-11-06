create table emp(eno int,ename char(10),dno int);
insert into emp values(1,'Nihar',10);
insert into emp values(2,'Papu',20);
insert into emp values(3,'Sima',30);
insert into emp values(4,'Nama',40);
insert into emp values(5,'Pinu',50);
create table dept(deptno int,dname char(10),lid int);
insert into dept values(20,'IT',101);
insert into dept values(40,'Sales',102);
insert into dept values(60,'Mkt',103);
insert into dept values(30,'Store',104);
select * from emp;
select * from dept;
select * from emp,dept;
		     ~

