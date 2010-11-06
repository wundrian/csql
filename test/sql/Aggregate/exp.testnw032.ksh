Network CSql
echo CREATE TABLE writer (poet char(50) , anthology char(40) , copies_in_stock tinyint(4)) ;
Statement Executed
echo INSERT INTO writer VALUES ('Mongane Wally Serote','Tstetlo',3);
Statement Executed: Rows Affected = 1
echo INSERT INTO writer VALUES ('Douglas Livingstone', 'The Skull in the Mud',21);
Statement Executed: Rows Affected = 1
echo INSERT INTO writer VALUES ('Mongane Wally Serote', 'No Baby Must Weep',8);
Statement Executed: Rows Affected = 1
echo INSERT INTO writer VALUES ('Douglas Livingstone', 'A Littoral Zone',2);
Statement Executed: Rows Affected = 1
echo INSERT INTO writer VALUES ('Mongane Wally Serote', 'A Tough Tale',2);
Statement Executed: Rows Affected = 1
echo SELECT * FROM writer;
---------------------------------------------------------
	writer.poet	writer.anthology	writer.copies_in_stock	
---------------------------------------------------------
	Mongane Wally Serote	Tstetlo	3	
	Douglas Livingstone	The Skull in the Mud	21	
	Mongane Wally Serote	No Baby Must Weep	8	
	Douglas Livingstone	A Littoral Zone	2	
	Mongane Wally Serote	A Tough Tale	2	
	
echo SELECT poet, MAX(copies_in_stock) , MIN(copies_in_stock) , AVG(copies_in_stock) , SUM(copies_in_stock)  FROM writer GROUP BY poet;
---------------------------------------------------------
	poet	MAX(copies_in_stock)	MIN(copies_in_stock)	AVG(copies_in_stock)	SUM(copies_in_stock)	
---------------------------------------------------------
	Mongane Wally Serote	8	2	4.333333	13	
	Douglas Livingstone	21	2	11.500000	23	
	
Network CSql
Statement Executed
