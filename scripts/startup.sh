#!/bin/sh
# Start CSQL Server
VERBOSE=$1
LOGDIR=/tmp
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

