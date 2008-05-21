#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/Recovery/createt1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi

isql myodbc3 < $REL_PATH/createt1.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    exit 1;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
if [ $? -ne 0 ]
then
    exit 2;
fi
touch /tmp/csql/csqltable.conf
if [ $? -ne 0 ]
then
    exit 3;
fi
for (( a=1; a<2; a++ ))
do
    echo "1:t$a"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
if [ $? -ne 0 ]
then
    exit 4;
fi
pid=$!
sleep 5


$CSQL_INSTALL_ROOT/bin/csqldump 

if [ $? -ne 0 ]
then
    exit 5;
fi

kill $pid > /dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 6;
fi

isql myodbc3 < $REL_PATH/drop.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 7;
fi

exit 0;

