#!/bin/ksh
# Testing Join on 5 sales tables.
# CREATE TABLE writer (poet varchar(50) , anthology varchar(40) default NULL, copies_in_stock tinyint(4)) ;
# INSERT INTO writer VALUES ('Mongane Wally Serote','Tstetlo',3);
# INSERT INTO writer VALUES ('Douglas Livingstone', 'The Skull in the Mud',21);
# INSERT INTO writer VALUES ('Mongane Wally Serote', 'No Baby Must Weep',8);
# INSERT INTO writer VALUES ('Douglas Livingstone', 'A Littoral Zone',2);
# INSERT INTO writer VALUES ('Mongane Wally Serote', 'A Tough Tale',2);
# SELECT poet, MAX(copies_in_stock) , MIN(copies_in_stock) , AVG(copies_in_stock) , SUM(copies_in_stock)  FROM writer GROUP BY poet;
# SELECT poet, MAX(copies_in_stock), AVG(copies_in_stock) , SUM(copies_in_stock) FROM writer GROUP BY poet HAVING poet > 'E';
# This will give wrong value for min(tinyint datatype).
#

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi
echo "DROP TABLE writer;" >${REL_PATH}/drop_writer.sql
$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/writer.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   rm -f ${REL_PATH}/drop_writer.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/drop_writer.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/drop_writer.sql
   exit 3;
fi

rm -f ${REL_PATH}/drop_writer.sql
exit 0;
