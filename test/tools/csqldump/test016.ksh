#!/bin/ksh
# Create table t1 having three integer field f1 ,f2,f3 with composite primary key (f1,f2) and create table t2 having three integer field f1,f2,f3 with foreign key (f1,f3) refers t1 (f1,f2). It should pass.This case also tests field name( Means FK field name may or may not be same as PK field name.)use csqldump toll for dumping the foreign key information.
#
input=${PWD}/tools/csqldump/foreign3.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

echo "DROP TABLE t2;" >$REL_PATH/drp1.sql
echo "DROP TABLE t1;" >>$REL_PATH/drp1.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/foreign3.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/foreign3.sql >/dev/null 2>&1
    if [ $? -ne 0 ] 
    then 
        $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drp1.sql > /dev/null 2>&1
        rm -f $REL_PATH/drp1.sql
        exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump
    if [ $? -ne 0 ]
    then
        $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drp1.sql > /dev/null 2>&1
        rm -f $REL_PATH/drp1.sql
        exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drp1.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drp1.sql > /dev/null 2>&1
    if [ $? -ne 0 ]
    then
        rm -f $REL_PATH/drp1.sql
        exit 3;
    fi
fi

rm -f $REL_PATH/drp1.sql
exit 0;
