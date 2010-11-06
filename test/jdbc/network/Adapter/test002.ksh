#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/Adapter/ConTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
	REL_PATH=`pwd`/jdbc/network/Adapter
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}

rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
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

java ConTest02
if [ $? -ne 0 ]
then
  exit 1;
fi
exit 0;
                
