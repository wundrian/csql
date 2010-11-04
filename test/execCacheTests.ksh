#!/bin/ksh

# First argument is the data source name to be used
# Second argument is the target database name
#                 valid names: MYSQL, PSQL, ORACLE
# Third argument is user name
# Fourth argument is password

################### Settings ########################################
#Timeout value for the hanging scripts
HANG_TIMEOUT=200

################### TIMEOUT HANDLER #################################
timeout_handler() {
if [ $CMD_PID != "" ]
then
    HANG_FLAG=Yes
    echo "HANG_FLAG is set here"
    kill -9 $CMD_PID 2>/dev/null
fi
}
restart_csqlserver() {
   echo "Restarting the server"
   kill -2 ${SERVER_PID}
   killcsqlsqlserver
   SRVPID=`ps -ef | grep csqlserver|grep -v "grep" |tail -1| awk -F" " '{ print $2 }'`
   if [ "$SRVPID" != "" ]
   then
       echo CSQL Server $SRVPID is being killed
       kill -2 $SRVPID
       sleep 1
       kill -9 $SRVPID
       ipcrm -M 2222 -M 3333 -M 1947
   fi

   echo "csqlserver killed PID=${SERVER_PID}" >>$TEST_LOG
#   rm -f /tmp/csql.conf
   rm -rf /tmp/csql/*
   mkdir /tmp/csql/log
   mkdir /tmp/csql/db
   cp $CSQL_SRCROOT/csql.conf /tmp/csql/csql.conf
   export CSQL_CONFIG_FILE=/tmp/csql/csql.conf
   echo "MMAP=false" >>/tmp/csql/csql.conf
   echo "CSQL_SQL_SERVER=true">>/tmp/csql/csql.conf
#   rm -rf /tmp/csql/*
#   mkdir /tmp/csql/log
#   mkdir /tmp/csql/db
   touch /tmp/csql/csqltable.conf
   touch /tmp/csql/csqlnw.conf
   touch /tmp/csql/csqlds.conf
   $CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
   $CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} &
   SERVER_PID=$!
   echo "csqlserver restarted with PID=${SERVER_PID}" >>$TEST_LOG
   sleep 5
}

killcsqlsqlserver() {
   #return;
   while true
   do
   SQLPID=`ps -ef | grep csqlsqlserver|grep -v "grep" |tail -1| awk -F" " '{ print $2 }'`
   if [ "$SQLPID" != "" ]
   then
       echo SQL Server $SQLPID is being killed
       kill -2 $SQLPID
       sleep 1
   else break;
   fi
   done
   #kill checkpoint setver
   while true
   do
   CHKPTPID=`ps -ef | grep csqlcheckpointserver |grep -v "grep" |tail -1| awk -F" " '{ print $2 }'`
   if [ "$CHKPTPID" != "" ]
   then
       echo Checkpoint server $CHKPTPID is being killed
       kill -2 $CHKPTPID
       sleep 1
   else break;
   fi
   done
}

##################### Test Executor main starts here ##################
echo MY pid is $$
if [ ! "$CSQL_CONFIG_FILE" ]
then
    echo "setupenv.ksh script is not run"
    exit 1
fi
SHELL=/bin/sh
#TEST_RUN_DIR should be set before running this
if [ ! "$TEST_RUN_ROOT" -a ! "$MODULE_NAME" ]
then
    echo "TEST_RUN_ROOT should be set before running the tests"
    exit 1
fi
if [ ! "$CSQL_INSTALL_ROOT" ]
then
    echo "CSQL_INSTALL_ROOT should be set before running the tests"
    exit 1
fi

cp $CSQL_SRCROOT/csql.conf /tmp/csql/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql/csql.conf
echo "MMAP=false" >>/tmp/csql.conf
echo "CSQL_SQL_SERVER=true">>/tmp/csql.conf
export DSN=$1
export DBUSER=$3
export PASSWORD=$4
export TDB=$2
echo "First argument is " $1
if [ $# -ne 4 ]
then
  isql $1 $3 $4 </dev/null >/dev/null 2>/dev/null
  if [ $? -ne 0 ]
  then
      echo "Unable to connect to data source"
      exit 1
  fi
  echo DSN=$1 >>$CSQL_CONFIG_FILE
else
  isql $1 $3 $4</dev/null >/dev/null 2>/dev/null
  if [ $? -ne 0 ]
  then
      echo "Unable to connect to data source"
      exit 1
  fi
  echo DSN=$1 >>$CSQL_CONFIG_FILE
fi

#setting up multiDSN
. ./setMultiDsn.ksh 
if [ ! "$MYSQL_DSN" ] 
then
   echo "Set up needs to be done for MultiDSN by edit setMultiDsn.ksh file for all TDBs."
 exit 1
fi

ROOT_DIR=`pwd`
if [ ! "$MODULE_NAME" ]
then
{
mkdir -p $TEST_RUN_ROOT
SERVOUT=$TEST_RUN_ROOT/serv.out
touch $SERVOUT
$CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} &
SERVER_PID=$!
echo "Starting Server"
sleep 5
while read MODULE
do
    echo $MODULE | grep "#" >/dev/null
    if [ $? -eq 0 ] 
    then
       continue
    fi
    echo "MODULE READ is $MODULE"
#if [ "$MODULE" = "adapter/Connect" -o "$MODULE" = "adapter/Parameter" -o "$MODULE" = "adapter/Select" ]
#then
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    $CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
#fi
TEST_SCRIPT_DIR=${ROOT_DIR}/${MODULE}
TEST_RUN_DIR=${TEST_RUN_ROOT}/${MODULE}
if [ -s "$TEST_RUN_DIR" ]
then
    kill -9 $SERVER_PID
    ipcrm -M 2222 -M 3333 -M 1947
    echo "TEST_RUN_ROOT directory is not empty. Clean and try again."
    exit 1
fi
mkdir -p $TEST_RUN_DIR

# TODO::check whether server is running 

TEST_LOG=$TEST_RUN_DIR/testlog

if [ -s "$TEST_LOG" ]
then
    echo "TEST_RUN_DIR has files in it. Remove before running the tests"
    exit 1
fi

TEST_EXEC_DIR=$TEST_RUN_DIR/tests
mkdir $TEST_EXEC_DIR


echo "Test Executor log file" >$TEST_LOG
echo "----------------------" >>$TEST_LOG

TestList=`ls ${TEST_SCRIPT_DIR}/test*`
for test in $TestList
do
echo "Running $test" 
echo "Running $test" >>$TEST_LOG
echo "Test started at : `date` " 
echo "Test started at : `date` " >>$TEST_LOG

expPresent="no"
arch="no"
os="no"
EXPECTED_FILE=exp.`basename ${test}`
ARCH=`uname -m`
EXP_FILE=$EXPECTED_FILE
if [  "$ARCH" = "x86_64" ] 
then
   EXP_FILE=$EXPECTED_FILE.$ARCH
   arch="yes"
fi
if [ -s "${TEST_SCRIPT_DIR}/${EXP_FILE}" -a "$arch" = "yes" ]
then
    expPresent="yes"
fi
OS=`uname`
if [ "$OS" = "SunOS"  ]
then
  EXP_FILE=$EXPECTED_FILE.$OS
  os="yes"
fi
if [ -s "${TEST_SCRIPT_DIR}/${EXP_FILE}" -a "$os" = "yes"   ] 
then
    expPresent="yes"
fi
if [ "$expPresent" = "no" ]
then
   EXP_FILE=$EXPECTED_FILE.$DSN
fi
if [ -s "${TEST_SCRIPT_DIR}/${EXP_FILE}" ]
then
    expPresent="yes"
fi
if [ "$expPresent" = "no" ]
then 
  if [ -s "${TEST_SCRIPT_DIR}/${EXPECTED_FILE}" ]
  then
    expPresent="yes"
    EXP_FILE=$EXPECTED_FILE
  fi
fi

echo "EXP_FILE is $EXP_FILE"

HANG_FLAG=No
trap timeout_handler USR1
sleep ${HANG_TIMEOUT} && kill -s USR1 $$ &
SLEEP_PID=$!

if [ "$expPresent" = "yes" ]
then
    cp ${TEST_SCRIPT_DIR}/${EXP_FILE} ${TEST_EXEC_DIR}
    ${test} > ${TEST_EXEC_DIR}/cur.${EXP_FILE} 2>/dev/null &
else
    ${test} >> ${TEST_LOG} 2>/dev/null &
fi
CMD_PID=$!
wait ${CMD_PID} 2>/dev/null
ret=$?
echo "Test Ended at : `date` " 
echo "Test Ended at : `date` " >>$TEST_LOG
unset CMD_PID
trap "" USR1
kill -9 ${SLEEP_PID} 2>/dev/null

if [ "$HANG_FLAG" = "Yes" ]
then
   echo "Test Hung. so it is killed." >>$TEST_LOG
   echo "FAILED:Test $test failed" >>$TEST_LOG
   #TODO::Reinitalize the database, as it may be in corrupted state.
   CURTIME=`date +%s`
   mv ${SERVOUT} ${SERVOUT}.${SERVER_PID}.${CURTIME}
   restart_csqlserver
   continue
fi

HANG_FLAG=No

if [ $ret -eq 0 ]
then
   if [ "$expPresent" = "yes" ]
   then 
       #compare exp and current output
       diff ${TEST_SCRIPT_DIR}/${EXP_FILE} ${TEST_EXEC_DIR}/cur.${EXP_FILE} > ${TEST_EXEC_DIR}/diff.${EXP_FILE}
       if [ $? -eq 0 ]
       then
          
           echo "Exp and current output matched."
           echo "Test $test passed"  
           echo "Exp and current output matched." >>$TEST_LOG
           echo "PASSED:Test $test passed" >>$TEST_LOG
           rm ${TEST_EXEC_DIR}/cur.${EXP_FILE}
           rm ${TEST_EXEC_DIR}/diff.${EXP_FILE}
           rm ${TEST_EXEC_DIR}/${EXP_FILE}
       else
           echo "Exp and current output not matched."
           echo "Test $test failed"  
           echo "Exp and current output not matched." >>${TEST_LOG}
           echo "FAILED:Test $test failed" >>$TEST_LOG
           #TODO::Reinitalize the database, as it may be in corrupted state.
           CURTIME=`date +%s`
           mv ${SERVOUT} ${SERVOUT}.${SERVER_PID}.${CURTIME}
           echo "Refer ${SERVOUT}.${SERVER_PID}.${CURTIME} file for server log" >>$TEST_LOG
           restart_csqlserver
        fi
   else
           echo "Returned 0."
           echo "Test $test passed"  
           echo "Returned 0." >>$TEST_LOG
           echo "PASSED:Test $test passed" >>$TEST_LOG
   fi
   
else
   echo "Returned $ret "
   echo "Test $test failed"  
   echo "Returned $ret " >>$TEST_LOG
   echo "FAILED:Test $test failed" >>$TEST_LOG
   #TODO::Reinitalize the database, as it may be in corrupted state.
   CURTIME=`date +%s`
   mv ${SERVOUT} ${SERVOUT}.${SERVER_PID}.${CURTIME}
   echo "Refer ${SERVOUT}.${SERVER_PID}.${CURTIME} file for server log" >>$TEST_LOG
   restart_csqlserver
fi

done
done < CacheTestModules
kill -9 ${SERVER_PID}
killcsqlsqlserver
ipcrm -M 2222 -M 3333 -M 1947
echo "csqlserver killed PID=${SERVER_PID}" >>${TEST_LOG}
}
else
{
#For Single Script Test
    if [ ! "$SCRIPT_NAME" ]
    then
       echo "Set SCRIPT_NAME to execute single script"
       exit 1
    fi
    $CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
    SERVER_PID=$!
    echo "Starting Server"
    sleep 5
    echo "MODULE Name is $MODULE_NAME"
    echo "SCRIPT Name is $SCRIPT_NAME"
    if [ "$MODULE_NAME" = "adapter/Connect" -o "$MODULE_NAME" = "adapter/Parameter" -o "$MODULE_NAME" = "adapter/Select" ]
    then
        rm -f /tmp/csql/csqlds.conf
        touch /tmp/csql/csqlds.conf
        $CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
        if [ $? -ne 0 ]
        then
           exit 1;
        fi
    fi
    test=${ROOT_DIR}/${MODULE_NAME}/${SCRIPT_NAME}
    echo "Running $test" 
    echo "Test started at : `date` " 
    expPresent="no"
    EXPECTED_FILE=exp.`basename ${test}`
    EXP_FILE=$EXPECTED_FILE.$DSN
    TEST_SCRIPT_DIR=${ROOT_DIR}/${MODULE_NAME}
    if [ -s "${TEST_SCRIPT_DIR}/${EXP_FILE}" ]
    then
        expPresent="yes"
    fi
    if [ "$expPresent" = "no" ]
    then
        if [ -s "${TEST_SCRIPT_DIR}/${EXPECTED_FILE}" ]
        then
            expPresent="yes"
            EXP_FILE=$EXPECTED_FILE
        fi
    fi
    echo "EXP_FILE is $EXP_FILE"
    HANG_FLAG=No
    trap timeout_handler USR1
    sleep ${HANG_TIMEOUT} && kill -s USR1 $$ &
    SLEEP_PID=$!
    if [ "$expPresent" = "yes" ]
    then
       cp ${TEST_SCRIPT_DIR}/${EXP_FILE} ${ROOT_DIR}
       ${test} >${ROOT_DIR}/cur.${EXP_FILE} 2>/dev/null &
    else
        ${test} 2>/dev/null &
    fi
    CMD_PID=$!
    wait ${CMD_PID} 2>/dev/null
    ret=$?
    echo "Test Ended at : `date` "
    unset CMD_PID
    trap "" USR1
    kill -9 ${SLEEP_PID} 2>/dev/null
    if [ "$HANG_FLAG" = "Yes" ]
    then
        CURTIME=`date +%s`
        mv ${SERVOUT} ${SERVOUT}.${SERVER_PID}.${CURTIME}
        kill -9 ${SERVER_PID}
        ipcrm -M 2222 -M 3333
        echo "csqlserver killed due to HANG_FLAG PID=${SERVER_PID}"
    fi
    HANG_FLAG=No
    if [ $ret -eq 0 ]
    then
       if [ "$expPresent" = "yes" ]
       then
           diff ${TEST_SCRIPT_DIR}/${EXP_FILE} ${ROOT_DIR}/cur.${EXP_FILE} > ${ROOT_DIR}/diff.${EXP_FILE}
           if [ $? -eq 0 ]
           then
               echo "Exp and current output matched."
               echo "Test $test passed"
               rm -f ${ROOT_DIR}/cur.${EXP_FILE} ${ROOT_DIR}/diff.${EXP_FILE} ${ROOT_DIR}/${EXP_FILE}
           else
                echo "Exp and current output not matched."
                echo "Test $test failed" 
           fi
       else
           echo "Returned 0."
           echo "Test $test passed"
       fi   
    else
       echo "Returned $ret "
       echo "Test $test failed"
    fi
    kill -9 ${SERVER_PID}
    killcsqlsqlserver
    ipcrm -M 2222 -M 3333 -M 1947
}
fi  
exit 0
