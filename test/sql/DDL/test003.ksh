#!/bin/ksh
# Test truncating primary key table having dependancy with foreign key table.
#create table t1(f1 int, f2 varchar(10), primary key(f1));
#create table t2(f1 int, f2 varchar(10), foreign key(f1) references t1(f1));
#insert into t1 values(1,'CSQL1');
#insert into t1 values(2,'CSQL2');
#insert into t2 values(1,'Nihar');
#insert into t2 values(2,'Bijay');
#insert into t2 values(1,'Kishor');
#insert into t2 values(2,'Jitendra');
#truncate table t1; truncate should fail due to parent-child dependancy
#truncate table t2;
#truncate table t1; truncate should delete all records from table t1, because table t2 is already truncated.
#
QUITFILE=${PWD}/sql/DDL/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/DDL
fi

echo "drop table t2;" >${REL_PATH}/dropt2t1.sql
echo "drop table t1;">>${REL_PATH}/dropt2t1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt2t1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/truncate_primary.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/truncate_primary.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt2t1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt2t1.sql 
rm -f ${REL_PATH}/dropt2t1.sql
exit 0;

