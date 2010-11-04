#!/bin/ksh
FILE=${PWD}/dbapi/Threads/noindex
REL_PATH=.
if [ -s "$FILE" ]
then
    REL_PATH=`pwd`/dbapi/Threads
fi
sleep 1
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/noindex 2> $0.valgr
else
    $REL_PATH/noindex >/tmp/out 
fi
sleep 1
NO=`grep "Total rows :25000" /tmp/out |wc -l`
if [ $NO -ne 15 ]
then 
    echo failed with $NO
    rm /tmp/out
    exit 2
fi
rm /tmp/out
exit 0
