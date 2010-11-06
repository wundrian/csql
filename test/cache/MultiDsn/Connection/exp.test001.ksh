Entries made for myodbc3  in csqlds.conf file.
Entries made for psql in csqlds.conf file.
Table 't1' is created in myodbc3
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from t1;
+-----------+-----------+
| f1        | f2        |
+-----------+-----------+
| 100       | Hi        |
| 200       | Hello     |
| 300       | Hi All    |
+-----------+-----------+
SQLRowCount returns 3
3 rows fetched
SQL> Table 't10' is created in psql
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from t10;
+------------+-----------+
| f1         | f2        |
+------------+-----------+
| 1          | one       |
| 2          | two       |
| 3          | three     |
+------------+-----------+
SQLRowCount returns 3
3 rows fetched
SQL> Table t1 is cached from myodbc3.
select * from t1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	100	Hi	
	200	Hello	
	300	Hi All	
	
Table 't10' is cached from psql.
select * from t10.
---------------------------------------------------------
	t10.f1	t10.f2	
---------------------------------------------------------
	1	one	
	2	two	
	3	three	
	
