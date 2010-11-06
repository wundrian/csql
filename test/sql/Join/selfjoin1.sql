CREATE TABLE emp10(eno int,ename char(10),job char(8),mgrno int);
INSERT INTO emp10 VALUES(1,'ALLEN','SALES',4);
INSERT INTO emp10 VALUES(2,'PITTER','IT',3);
INSERT INTO emp10 VALUES(3,'JACK','MKTING',1);
INSERT INTO emp10 VALUES(4,'TOM','CLERK',1);
INSERT INTO emp10 VALUES(5,'HARRY','MANAGERi',5);
SELECT * FROM emp10;
echo SELECT emp.ename,mgr.ename FROM emp10 as emp,emp10 as mgr WHERE emp.mgrno=mgr.eno;
SELECT emp.ename,mgr.ename FROM emp10 as emp,emp10 as mgr WHERE emp.mgrno=mgr.eno;
