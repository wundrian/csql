#!/bin/ksh
# Test Case
# 1. Check for help message: $ cacheverify -? 

cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
DS="$DSN $DBUSER $PASSWORD"
echo DSN=$DSN >>$CSQL_CONFIG_FILE
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/cacheverify ?
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;

