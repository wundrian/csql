#!/bin/ksh
# Test Case
# create table 't1' with 5 fields in Target DB with records.
# Load the table 't1' in field mode in csql without condition.
# Example  : select f1,f2,f3 from t1 ; 
# Select query executes the selected records from csql.
#

#Author : Jitendra Lenka
input=${PWD}/cache/CacheTable/csql.conf
REL_PATH=.
if [ -s "$input" ]
then
      REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < ${REL_PATH}/createtable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then 
	exit 2;
fi

echo Table t1,t2,t3,t4,t5 created with 2 records in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.db  
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.db  

# cache from target to csql with -f option.
echo "cachetable -t t1 "
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/cachetable -t t1  
if [ $? -ne 0 ]
then 
	rm -f /tmp/csql/csqltable.conf
	touch /tmp/csql/csqltable.conf
        $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql > /dev/null 2>&1
        isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
        kill -9 $pid
        ipcrm -M 4000 -M 4500
	exit 3;
fi

echo "select * from t1;"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql

#setting for "psql dsn"
DSNAME="psql"

if [ $DSN != $DSNAME ]
 then  
    echo "$DSNAME $POSTGRES_USER $POSTGRES_PASSWORD postgres" >>/tmp/csql/csqlds.conf  # entries for csqlds.conf file.
    isql $DSNAME $POSTGRES_USER  $POSTGRES_PASSWORD < ${REL_PATH}/createtable.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
	     rm -f /tmp/csql/csqltable.conf  /tmp/csql/csqlds.conf  
	     touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf  
	     $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql > /dev/null 2>&1
	     isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
             kill -9 $pid
             ipcrm -M 4000 -M 4500
             exit 4;
     fi
else
  DSNAME="myodbc3"
    echo "$DSNAME NULL NULL postgres" >>/tmp/csql/csqlds.conf  # entries for csqlds.conf file.
    isql $DSNAME < ${REL_PATH}/createtable.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
	    rm -f /tmp/csql/csqltable.conf  /tmp/csql/csqlds.conf  
	    touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf  
	    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql > /dev/null 2>&1
	    isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
            kill -9 $pid
            ipcrm -M 4000 -M 4500
	   exit 5;    
    fi

fi


# cahetable with -d optiopn
# 'cachetable -t <tabName> -d <dsnName>

echo Table t1,t2,t3,t4,t5 created with 2 records in target DB.
echo "cachetable -t t2 -d psql"

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -d $DSNAME
if [ $? -ne 0 ]
then
   rm -f  /tmp/csql/csqlds.conf 
   touch  /tmp/csql/csqlds.conf 
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql > /dev/null 2>&1
   isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
   isql $DSNAME < ${REL_PATH}/dropall.sql >/dev/null 2>&1
   kill -9 $pid
   ipcrm -M 4000 -M 4500
   exit 6;
fi

echo "select * from t2;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt2.sql


    
rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds. conf  
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf  
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
isql $DSNAME ${REL_PATH}/dropall.sql >/dev/null 2>&1
kill -9 $pid
ipcrm -M 4000 -M 4500
 
exit 0;


