#!/bin/ksh
#Testing Now() for Date 
#create table t1(f1 int,f2 date);
#insert into t1 values(1,'2003/12/10')
#insert into t1 values(2,'2004/12/10')
#insert into t1 values(3,'2005/12/10')
#insert into t1 values(4,'2006/12/10')
#insert into t1 values(5,now())
#insert into t1 values(6,'2007/12/10')
#insert into t1 values(7,now())
#select * from t1;
#select * from t1 where f2<=now();
#select * from t1 where f2>now();
#select * from t1;
#update t1 set f2=now() where f1<=2;
#select * from t1;
#update t1 set f2=now(),f1=10 where f2='2007/12/10';
#select * from t1;
#drop table t1;
CREATEFILE=${PWD}/sql/ScalarFunction/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/ScalarFunction
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/Date_with_now.sql

else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/Date_with_now.sql

    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

rm -f ${REL_PATH}/dropt1.sql
exit 0;
