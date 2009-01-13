Table t5 and t6 created in target DB.
cachetable -t t5 -D -c "f1>=10"
cachetable -t t6 -D -c "f1>=10" 
select query on t1 and t2 table
Statement Executed: Rows Affected = 1
Statement execute failed with error -14
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	11	
	11	12	
	12	13	
	13	14	
	14	15	
	15	16	
	
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	11	
	11	12	
	12	13	
	13	14	
	14	15	
	15	16	
	
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from t5;
+-----------+-----------+
| f1        | f2        |
+-----------+-----------+
| 5         | 6         |
| 6         | 7         |
| 7         | 8         |
| 8         | 9         |
| 9         | 10        |
| 10        | 11        |
| 11        | 12        |
| 12        | 13        |
| 13        | 14        |
| 14        | 15        |
| 15        | 16        |
| 16        | 20        |
+-----------+-----------+
SQLRowCount returns 12
12 rows fetched
SQL> select * from t6;
+-----------+-----------+
| f1        | f2        |
+-----------+-----------+
| 5         | 6         |
| 6         | 7         |
| 7         | 8         |
| 8         | 9         |
| 9         | 10        |
| 10        | 11        |
| 11        | 12        |
| 12        | 13        |
| 13        | 14        |
| 14        | 15        |
| 15        | 16        |
| 16        | 20        |
| 15        | 21        |
+-----------+-----------+
SQLRowCount returns 13
13 rows fetched
SQL> 