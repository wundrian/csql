#!/bin/sh
# Stop CSQL Server
AWK=awk
FORCE=$1
LOGFILE=`grep LOG_FILE $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
LOGDIR=`dirname $LOGFILE`

echo "CSQL Server Stopped: " + `date` >>$LOGDIR/csqlserver.log
while true
do
   SQLPID=`ps -e | grep csqlsqlserver |tail -1| awk -F" " '{ print $1 }'`
   if [ "$SQLPID" != "" ]
   then
       kill -2 $SQLPID
       sleep 1
   else break;
   fi
done
REPLPID=`ps -e | grep csqlreplserver |tail -1| awk -F" " '{ print $1 }'`
if [ "$REPLPID" != "" ]
then
    kill -2 $REPLPID
fi
CACHEPID=`ps -e | grep csqlcacheserver |tail -1| awk -F" " '{ print $1 }'`
if [ "$CACHEPID" != "" ]
then
    kill -2 $CACHEPID
fi
CSQLPID=`ps -e | grep csqlserver |tail -1| awk -F" " '{ print $1 }'`
if [ "$CSQLPID" == "" ]
then
    echo "returning early"
    return;
fi
kill -2 $CSQLPID
CSQLPID=`ps -e | grep csqlserver |tail -1| awk -F" " '{ print $1 }'`
if [ "$CSQLPID" == "" ]
then
    FORCE=
fi

if [ -z "$FORCE" ]
then
   echo "stop server without force"
else
   echo "stop server with force"
   kill -9 $CSQLPID
   KEY=`grep SYS_DB_KEY $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
   echo removing key $KEY
   ipcrm -M $KEY
   KEY=`grep USER_DB_KEY $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
   echo removing key $KEY
   ipcrm -M $KEY
   KEY=`grep ID_SHM_KEY $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
   echo removing key $KEY
   ipcrm -M $KEY
   KEY=`grep MSG_KEY $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
   echo removing message queue key $KEY
   ipcrm -Q $KEY
fi
