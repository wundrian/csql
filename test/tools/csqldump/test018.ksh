#!/bin/ksh
# Create table t1 having two integer field f1 ,f2 with primary key f1 . create table t2 having two integer field f3,f4 with primary key f3 . and create table t3 having two integer field f5,f6 with foreign key f5 refers t1 (f1) and foreign key f6 refers t2 (f3)..It Should be passed. Test all valid and invalid DML Operation Related to Foreign Key.use csqldump toll for dumping the foreign key information.
#
input=${PWD}/tools/csqldump/foreign5.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

echo "DROP TABLE t3;" >$REL_PATH/drp1.sql
echo "DROP TABLE t2;" >>$REL_PATH/drp1.sql
echo "DROP TABLE t1;" >>$REL_PATH/drp1.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/foreign5.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/foreign5.sql >/dev/null 2>&1
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
        exit 3;
        rm -f $REL_PATH/drp1.sql
    fi
fi

rm -f $REL_PATH/drp1.sql
exit 0;
