#!/bin/ksh
# Test Case
# 3. Run cacheverify on a non existing table. 
#    It should give an error saying the table is not present.

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
$CSQL_INSTALL_ROOT/bin/cacheverify -t not_exists > /dev/null 2>&1
if [ $? -eq 0 ]
then
   exit 1;
fi

exit 0;

