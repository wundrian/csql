#!/bin/sh
# Stop CSQL Server
OS=`uname`
AWK=awk
FORCE=$1
LOGFILE=`grep LOG_FILE $CSQL_CONFIG_FILE| tail -1 | awk -F"=" '{ print $2 }'`
LOGDIR=`dirname $LOGFILE`

echo "CSQL Server Stopped: " + `date` >>$LOGDIR/csqlserver.log
while true
do
   if [ "$OS" = "SunOS" ]
   then
      SQLPID=`ps -ef | grep csqlsqlserver |head -1| awk -F" " '{ print $2 }'`
   else
      SQLPID=`ps -e | grep csqlsqlserver |tail -1| awk -F" " '{ print $1 }'`
   fi

   if [ "$SQLPID" != "" ]
   then
       echo Killing $SQLPID
       kill -2 $SQLPID
       if [ $? -ne 0 ]
       then
          break;
       fi
       sleep 1
   else break;
   fi
done
if [ "$OS" = "SunOS" ]
then
    REPLPID=`ps -ef | grep csqlreplserver |head -1| awk -F" " '{ print $2 }'`
else
    REPLPID=`ps -e | grep csqlreplserver |tail -1| awk -F" " '{ print $1 }'`
fi
if [ "$REPLPID" != "" ]
then
    kill -2 $REPLPID
fi
if [ "$OS" = "SunOS" ]
then
   CACHEPID=`ps -ef | grep csqlcacheserver |head -1| awk -F" " '{ print $2 }'`
else
   CACHEPID=`ps -e | grep csqlcacheserver |tail -1| awk -F" " '{ print $1 }'`
fi
if [ "$CACHEPID" != "" ]
then
    kill -2 $CACHEPID
fi
if [ "$OS" = "SunOS" ]
then
   CSQLPID=`ps -ef | grep csqlserver |head -1| awk -F" " '{ print $2 }'`
else
   CSQLPID=`ps -e | grep csqlserver |tail -1| awk -F" " '{ print $1 }'`
fi

if [ "$CSQLPID" = "" ]
then
    echo "returning early"
    exit 0;
fi
kill -2 $CSQLPID
if [ "$OS" = "SunOS" ]
then
   CSQLPID=`ps -ef | grep csqlserver |head -1| awk -F" " '{ print $2 }'`
else
   CSQLPID=`ps -e | grep csqlserver |tail -1| awk -F" " '{ print $1 }'`
fi

if [ "$CSQLPID" = "" ]
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
