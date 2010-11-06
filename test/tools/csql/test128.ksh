#!/bin/sh
# The same is present in testnw028.ksh (wih network)
# Default and 'now' testing for Date, Time and Timestamp datatypes
#

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/csqlnow.sql 2> $0.valgr
else
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/csqlnow.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
fi


sleep 1
echo "echo INSERT INTO t1(f2) VALUES('NOW');" >${REL_PATH}/insnow.sql
echo "INSERT INTO t1(f2) VALUES('NOW');" >>${REL_PATH}/insnow.sql
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql
    if [ $? -ne 0 ]
    then
       rm -f ${REL_PATH}/insnow.sql
       $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
       exit 2;
    fi
fi

sleep 1
echo "echo INSERT INTO t1(f3) VALUES('NOW');" >${REL_PATH}/insnow.sql
echo "INSERT INTO t1(f3) VALUES('NOW');" >>${REL_PATH}/insnow.sql
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql
    if [ $? -ne 0 ]
    then
       rm -f ${REL_PATH}/insnow.sql
       $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
       exit 3;
    fi
fi

sleep 1
echo "echo INSERT INTO t1(f4) VALUES('NOW');" >${REL_PATH}/insnow.sql
echo "INSERT INTO t1(f4) VALUES('NOW');" >>${REL_PATH}/insnow.sql
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insnow.sql
    if [ $? -ne 0 ]
    then
       rm -f ${REL_PATH}/insnow.sql
       $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
       exit 4;
    fi
fi

echo "echo SELECT * FROM t1;" >${REL_PATH}/selnow.sql
echo "SELECT * FROM t1;" >>${REL_PATH}/selnow.sql
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selnow.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selnow.sql
    if [ $? -ne 0 ]
    then
       rm -f ${REL_PATH}/insnow.sql
       rm -f ${REL_PATH}/selnow.sql
       $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
       exit 5;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/insnow.sql
   exit 6;
fi

rm -f ${REL_PATH}/insnow.sql
rm -f ${REL_PATH}/selnow.sql
exit 0;
