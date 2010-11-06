#!/bin/ksh
# Donot Start CSQL Server
# Open the connection through jdbc:gateway and then call isClosed(). It should return false.
# Close the connection jdbc:gateway and then call isClosed(). It should return true

# GwTest7.java

TESTFILE=${PWD}/jdbc/network/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
#export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo "CACHE_TABLE=true" >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

java GwTest7 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
