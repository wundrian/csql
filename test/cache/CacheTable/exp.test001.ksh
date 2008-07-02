Usage: cachetable [-U username] [-P passwd] -t tablename 
       [-R] [-s] [-r]
       username -> username to connect with csql.
       passwd -> password for the above username to connect with csql.
       tablename -> table name to be cached in csql from target db.
       R -> recover all cached tables from the target database.
       s -> load only the records from target db. Assumes table is already created in csql
       r -> reload the table. get the latest image of table from target db
       u -> unload the table. if used with -s option, removes only records and preserves the schema
       no option -> get table definition and records from target db and create in csql.
