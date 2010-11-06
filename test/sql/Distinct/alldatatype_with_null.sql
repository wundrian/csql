create table t1(f0 tinyint, f1 smallint,f2 int,f3 bigint,f4 char(10),f5 float,f6 double,f7 date,f8 time,f9 timestamp);
insert into t1 values(1,   10  ,100 ,1000,  'Bijay' ,1000,100000,'2009-03-01','11:59:59','2009-03-01 11:59:59');
insert into t1 values(NULL,11  ,110 ,1100, 'Jitendr',NULL,200000,'2009-03-02',    NULL  ,'2009-03-02 11:59:59');
insert into t1 values(3,   12  ,120 ,1000,   NULL   ,3000,NULL  ,    NULL    ,'11:59:57','2009-03-03 11:59:59');
insert into t1 values(4, NULL ,NULL ,1100,  'Kishor',4000,400000,'2009-03-04','11:59:59','2009-03-04 11:59:59');
insert into t1 values(5,   14  ,100 ,1000,   'Praba',5000,500000,'2009-03-01',    NULL  ,'2009-03-01 11:59:59');
insert into t1 values(6,   15  ,110 ,NULL,  'Sanjit',6000,600000,'2009-03-02','11:59:57','2009-03-02 11:59:59');
insert into t1 values(7,   16  ,120 ,1000,  'Sanjay',7000,700000,    NULL    ,'11:59:59','2009-03-03 11:59:59');
insert into t1 values(1,   17, NULL ,1100, 'Arindam',8000,800000,'2009-03-04',    NULL  ,'2009-03-04 11:59:59');
insert into t1 values(NULL,10  ,100 ,NULL,   'Bijay',9000,900000,'2009-03-01','11:59:57','2009-03-01 11:59:59');
insert into t1 values(3,   11  ,110 ,1100, 'Jitendr',1000,100000,    NULL    ,    NULL  ,'2009-03-02 11:59:59');
insert into t1 values(4,   12  ,120 ,1000,    NULL  ,NULL,200000,    NULL    ,'11:59:57','2009-03-03 11:59:59');
insert into t1 values(5, NULL ,NULL ,NULL,    NULL  ,3000,NULL  ,'2009-03-05','11:59:56','2009-03-05 11:59:59');
insert into t1 values(6,   14  ,100 ,1000,   'Praba',4000,400000,'2009-03-01','11:59:55','2009-03-04 11:59:59');
insert into t1 values(7,   15  ,110 ,1100,  'Sanjit',5000,500000,'2009-03-02','11:59:56','2009-03-01 11:59:59');
insert into t1 values(NULL,NULL,120 ,1000,  'Sanjay',NULL,NULL  ,    NULL    ,    NULL  ,'2009-03-03 11:59:59');
insert into t1 values(NULL,17  ,130 ,1100, 'Arindam',7000,700000,'2009-03-01','11:59:59','2009-03-01 11:59:59');
select * from t1;