#!/bin/ksh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

# dump the data of not existing table, should say table does not exist

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full CSQL_INSTALL_ROOT/bin/csqldump -T t1 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump -T t1 
    if [ $? -ne 0 ]
    then
        exit 0;
    fi
fi

exit 1;
