Inserting records into table T1
5 rows inserted into table T1
Inserting records into table T2
5 rows inserted into table T2
Inserting records into table T3
5 rows inserted into table T3
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> SELECT * FROM T1;
+-----------+-----------------------------------+
| f1        | f2                                |
+-----------+-----------------------------------+
| 0         | lakshya                           |
| 1         | lakshya                           |
| 2         | lakshya                           |
| 3         | lakshya                           |
| 4         | lakshya                           |
+-----------+-----------------------------------+
SQLRowCount returns 5
5 rows fetched
SQL> SELECT * FROM T2;
+-----------+-----------------------------------+
| f1        | f2                                |
+-----------+-----------------------------------+
| 5         | lakshya                           |
| 6         | lakshya                           |
| 7         | lakshya                           |
| 8         | lakshya                           |
| 9         | lakshya                           |
+-----------+-----------------------------------+
SQLRowCount returns 5
5 rows fetched
SQL> SELECT * FROM T3;
+-----------+-----------------------------------+
| f1        | f2                                |
+-----------+-----------------------------------+
| 10        | lakshya                           |
| 11        | lakshya                           |
| 12        | lakshya                           |
| 13        | lakshya                           |
| 14        | lakshya                           |
+-----------+-----------------------------------+
SQLRowCount returns 5
5 rows fetched
SQL> ---------------------------------------------------------
	T1.f1	T1.f2	
---------------------------------------------------------
	0	lakshya	
	1	lakshya	
	2	lakshya	
	3	lakshya	
	4	lakshya	
	
---------------------------------------------------------
	T2.f1	T2.f2	
---------------------------------------------------------
	5	lakshya	
	6	lakshya	
	7	lakshya	
	8	lakshya	
	9	lakshya	
	
---------------------------------------------------------
	T3.f1	T3.f2	
---------------------------------------------------------
	10	lakshya	
	11	lakshya	
	12	lakshya	
	13	lakshya	
	14	lakshya	
	
