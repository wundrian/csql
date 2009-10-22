#!/bin/sh
# Start CSQL Server
VERBOSE=$1
OS=`uname`
LOGFILE=`grep LOG_FILE $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
LOGDIR=`dirname $LOGFILE`

TOTPROC=`ps -ef | grep csqlserver| wc -l` 
if [ $TOTPROC -ne 1 ]
then
  if [ "$OS" = "SunOS" ]
  then
    CSQLPID=`ps -ef | grep csqlserver |head -1| awk -F" " '{ print $2 }'`
  else
    CSQLPID=`ps -e | grep csqlserver |tail -1| awk -F" " '{ print $1 }'`
  fi
  if [ "$CSQLPID" != "" ]
  then
    echo "Server Already running with PID $CSQLPID"
    exit 0;
  fi
fi

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
