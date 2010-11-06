Connection opened
Table t1 Created
Hash Index Created on TINYINT field f1
Hash Index Created on SMALLINT field f2
Hash Index Created on INT field f3
Hash Index Created on BIGINT field f4
Hash Index Created on CHAR field f5
Hash Index Created on VARCHAR field f6
Hash Index Created on DATE field f9
Hash Index Created on TIME field f10
	 TABLES
	--------
	t1
Connection Closed
Usage: catalog [-u username] [-p passwd] [-l] [-i] [-d] [-T table] [-I index] [-D <lock|trans|proc|chunk>]
       l -> list all table with field information
            list all Index information
       i -> reinitialize catalog tables. Drops all tables.
       d -> print db usage statistics
       T -> list table information
       I -> list index information
       D -> print debug information for system tables
Note: If multiple options are specified, last one will be considered.
echo drop table t1;
Statement Executed
