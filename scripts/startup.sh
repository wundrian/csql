#!/bin/sh
# Start CSQL Server
VERBOSE=$1
LOGFILE=`grep LOG_FILE $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
LOGDIR=`dirname $LOGFILE`

echo "CSQL Server Start: " + `date` >>$LOGDIR/csqlserver.log
if [ -z "$VERBOSE" ]
then
echo "Starting csqlserver without verbose"
nohup $CSQL_INSTALL_ROOT/bin/csqlserver >>$LOGDIR/csqlserver.log 2>>$LOGDIR/csqlserver.log &
sleep 2
else
echo "Start csqlserver with verbose"
$CSQL_INSTALL_ROOT/bin/csqlserver
fi

