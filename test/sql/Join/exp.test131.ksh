echo Create table client_master(clientno char(6), name char(20) NOT NULL, address1 char(30), address2 char(30), city char(15), pincode int, state char(15), baldue float,PRIMARY KEY(clientno));
Statement Executed
echo Create table product_master(productno char(6), description char(15) NOT NULL,profitpercent float NOT NULL,unitmeasure char(10) NOT NULL,qtyonhand int NOT NULL,reorderlvl int NOT NULL,selprice float NOT NULL,costprice float NOT NULL, PRIMARY KEY(productno));
Statement Executed
echo Create table salesman_master(salesmanno char(6),salesmanname char(20) NOT NULL,address1 char(30) NOT NULL,address2 char(30),city char(20),pincode char(8),state char(20),salamt float NOT NULL,tgttoget float NOT NULL,ytdsales float NOT NULL,remarks char(30),PRIMARY KEY(salesmanno));
Statement Executed
echo Create table sales_order(orderno char(6),orderdate date,clientno char(6),delyaddr char(25),delytype char(1),billedyn char(1),salesmanno char(6),delydate date,orderstatus char(10),PRIMARY KEY(orderno),FOREIGN KEY(clientno) REFERENCES client_master(clientno),FOREIGN KEY(salesmanno) REFERENCES salesman_master(salesmanno));
Statement Executed
echo Create table sales_order_details(orderno char(6),productno char(6),qtyordered int,qtydisp int,productrate float,FOREIGN KEY(orderno) REFERENCES sales_order(orderno),FOREIGN KEY(productno) REFERENCES product_master(productno));
Statement Executed
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00001','Ivan Bayross','Mumbai',400054,'Maharastra',15000);
Statement Executed: Rows Affected = 1
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00002','mamta Muzumdar','Madras',780001,'Tamil Nadu',0);
Statement Executed: Rows Affected = 1
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00003','Chhaya Bankar','Mumbai',400057,'Maharastra',5000);
Statement Executed: Rows Affected = 1
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00004','Ashwini Joshi','Bangalore',560001,'MKarnataka',0);
Statement Executed: Rows Affected = 1
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00005','Hansel Colaco','Mumbai',400060,'Maharastra',2000);
Statement Executed: Rows Affected = 1
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00006','Deepak Sharma','Mangalore',560050,'Karnatakaa',0);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P00001','T-Shirts',5,'Piece',200,50,350,250);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P03453','Shirts',6,'Piece',150,50,500,350);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P06734','Cotton Jeans',5,'Piece',100,20,60,450);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P07865','Jeans',5,'Piece',100,20,750,500);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P07868','Trousers',2,'Piece',150,50,850,550);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P07885','Pull Overs',2.5,'Piece',80,30,700,450);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P07965','Denim Shirts',4,'Piece',100,40,350,250);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P07975','Lycra Tops',5,'Piece',70,30,300,175);
Statement Executed: Rows Affected = 1
echo insert into product_master values('P08865','Skirts',5,'Piece',75,30,450,300);
Statement Executed: Rows Affected = 1
echo insert into salesman_master values('S00001','Aman','A/14','Worli','Mumbai',400002,'Maharastra',3000,100,50,'Good');
Statement Executed: Rows Affected = 1
echo insert into salesman_master values('S00002','Omkar','65','Nariman','Mumbai',400001,'maharastra',3000,200,100,'Good');
Statement Executed: Rows Affected = 1
echo insert into salesman_master values('S00003','Raj','P-7','Banfra','Mumbai',400032,'Maharastra',3000,200,100,'Good');
Statement Executed: Rows Affected = 1
echo insert into salesman_master values('S00004','Ashish','A/5','Juhu','Bombay',400044,'Maharastra',3500,200,150,'Good');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19001','2002-06-12','C00001','F','N','S00001','2002-07-20','In Process');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19002','2002-06-25','C00002','P','N','S00002','2002-06-27','Cancelled');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46865','2002-02-18','C00003','F','Y','S00003','2002-02-20','Fulfilled');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19003','2002-04-03','C00001','F','Y','S00001','2002-04-07','Fulfilled');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46866','2002-05-20','C00004','P','N','S00002','2002-05-22','Cancelled');
Statement Executed: Rows Affected = 1
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19008','2002-05-24','C00005','F','N','S00004','2002-07-26','In Process');
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P00001',4,4,525);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07965',2,1,8400);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07885',2,1,5250);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19002','P00001',10,0,525);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07868',3,3,3150);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07885',3,1,5250);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P00001',10,10,525);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P03453',4,4,1050);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P03453',2,2,1050);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P06734',1,1,12000);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07965',1,0,8400);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07975',1,0,1050);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P00001',10,5,525);
Statement Executed: Rows Affected = 1
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P07975',5,3,1050);
Statement Executed: Rows Affected = 1
echo select * from client_master;
---------------------------------------------------------
	client_master.clientno	client_master.name	client_master.address1	client_master.address2	client_master.city	client_master.pincode	client_master.state	client_master.baldue	
---------------------------------------------------------
	C00001	Ivan Bayross	NULL	NULL	Mumbai	400054	Maharastra	15000.000000	
	C00002	mamta Muzumdar	NULL	NULL	Madras	780001	Tamil Nadu	0.000000	
	C00003	Chhaya Bankar	NULL	NULL	Mumbai	400057	Maharastra	5000.000000	
	C00004	Ashwini Joshi	NULL	NULL	Bangalore	560001	MKarnataka	0.000000	
	C00005	Hansel Colaco	NULL	NULL	Mumbai	400060	Maharastra	2000.000000	
	C00006	Deepak Sharma	NULL	NULL	Mangalore	560050	Karnatakaa	0.000000	
	
echo select * from product_master;
---------------------------------------------------------
	product_master.productno	product_master.description	product_master.profitpercent	product_master.unitmeasure	product_master.qtyonhand	product_master.reorderlvl	product_master.selprice	product_master.costprice	
---------------------------------------------------------
	P00001	T-Shirts	5.000000	Piece	200	50	350.000000	250.000000	
	P03453	Shirts	6.000000	Piece	150	50	500.000000	350.000000	
	P06734	Cotton Jeans	5.000000	Piece	100	20	60.000000	450.000000	
	P07865	Jeans	5.000000	Piece	100	20	750.000000	500.000000	
	P07868	Trousers	2.000000	Piece	150	50	850.000000	550.000000	
	P07885	Pull Overs	2.500000	Piece	80	30	700.000000	450.000000	
	P07965	Denim Shirts	4.000000	Piece	100	40	350.000000	250.000000	
	P07975	Lycra Tops	5.000000	Piece	70	30	300.000000	175.000000	
	P08865	Skirts	5.000000	Piece	75	30	450.000000	300.000000	
	
echo select * from salesman_master;
---------------------------------------------------------
	salesman_master.salesmanno	salesman_master.salesmanname	salesman_master.address1	salesman_master.address2	salesman_master.city	salesman_master.pincode	salesman_master.state	salesman_master.salamt	salesman_master.tgttoget	salesman_master.ytdsales	salesman_master.remarks	
---------------------------------------------------------
	S00001	Aman	A/14	Worli	Mumbai	400002	Maharastra	3000.000000	100.000000	50.000000	Good	
	S00002	Omkar	65	Nariman	Mumbai	400001	maharastra	3000.000000	200.000000	100.000000	Good	
	S00003	Raj	P-7	Banfra	Mumbai	400032	Maharastra	3000.000000	200.000000	100.000000	Good	
	S00004	Ashish	A/5	Juhu	Bombay	400044	Maharastra	3500.000000	200.000000	150.000000	Good	
	
echo select * from sales_order;
---------------------------------------------------------
	sales_order.orderno	sales_order.orderdate	sales_order.clientno	sales_order.delyaddr	sales_order.delytype	sales_order.billedyn	sales_order.salesmanno	sales_order.delydate	sales_order.orderstatus	
---------------------------------------------------------
	O19001	2002/6/12	C00001	NULL	F	N	S00001	2002/7/20	In Process	
	O19002	2002/6/25	C00002	NULL	P	N	S00002	2002/6/27	Cancelled	
	O46865	2002/2/18	C00003	NULL	F	Y	S00003	2002/2/20	Fulfilled	
	O19003	2002/4/3	C00001	NULL	F	Y	S00001	2002/4/7	Fulfilled	
	O46866	2002/5/20	C00004	NULL	P	N	S00002	2002/5/22	Cancelled	
	O19008	2002/5/24	C00005	NULL	F	N	S00004	2002/7/26	In Process	
	
echo select * from sales_order_details;
---------------------------------------------------------
	sales_order_details.orderno	sales_order_details.productno	sales_order_details.qtyordered	sales_order_details.qtydisp	sales_order_details.productrate	
---------------------------------------------------------
	O19001	P00001	4	4	525.000000	
	O19001	P07965	2	1	8400.000000	
	O19001	P07885	2	1	5250.000000	
	O19002	P00001	10	0	525.000000	
	O46865	P07868	3	3	3150.000000	
	O46865	P07885	3	1	5250.000000	
	O46865	P00001	10	10	525.000000	
	O46865	P03453	4	4	1050.000000	
	O19003	P03453	2	2	1050.000000	
	O19003	P06734	1	1	12000.000000	
	O46866	P07965	1	0	8400.000000	
	O46866	P07975	1	0	1050.000000	
	O19008	P00001	10	5	525.000000	
	O19008	P07975	5	3	1050.000000	
	
echo select sales_order_details.productno,description from sales_order_details,sales_order,product_master,client_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno and client_master.clientno=sales_order.clientno and client_master.name='Ivan Bayross';
---------------------------------------------------------
	sales_order_details.productno	description	
---------------------------------------------------------
	P00001	T-Shirts	
	P07965	Denim Shirts	
	P07885	Pull Overs	
	P03453	Shirts	
	P06734	Cotton Jeans	
	
echo drop table sales_order_details;
Statement Executed
echo drop table sales_order;
Statement Executed
echo drop table salesman_master;
Statement Executed
echo drop table product_master;
Statement Executed
echo drop table client_master;
Statement Executed
