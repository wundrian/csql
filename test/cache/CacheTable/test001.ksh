#!/bin/ksh
# Test Case
# 1. Check for help message: $ cachetable -? 
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/cachetable ?
if [ $? -ne 0 ]
then
   exit 2;
fi
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
exit 0;
