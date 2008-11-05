#!/bin/sh

################### Settings ########################################
#Timeout value for the hanging scripts
HANG_TIMEOUT=150

################### TIMEOUT HANDLER #################################
timeout_handler() {
if [ $CMD_PID != "" ]
then
    HANG_FLAG=Yes
    echo "HANG_FLAG is set here"
    kill -9 $CMD_PID 2>/dev/null
fi
}

##################### Test Executor main starts here ##################
echo MY pid is $$
#TEST_RUN_DIR should be set before running this
if [ ! "$TEST_RUN_ROOT" ]
then
    echo "TEST_RUN_ROOT should be set before running the tests"
    exit 1
fi
if [ ! "$CSQL_INSTALL_ROOT" ]
then
    echo "CSQL_INSTALL_ROOT should be set before running the tests"
    exit 1
fi

if [ ! "$CSQL_CONFIG_FILE" ]
then
    echo "setupenv.ksh should be run before running the tests"
    exit 1
fi
DBFILE=`grep DATABASE_FILE $CSQL_CONFIG_FILE| awk -F= '{ print $2}'`
CACHECONFFILE=`grep TABLE_CONFIG_FILE $CSQL_CONFIG_FILE| awk -F= '{ print $2}'`
rm $DBFILE
rm $CACHECONFFILE
echo $DBFILE
ROOT_DIR=`pwd`
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

if [ "$MODULE" = "system/lock" ]
then
   echo "Restarting the server for lock module"
   kill -9 ${SERVER_PID}
   ipcrm -M 2222 -M 3333 
   echo "csqlserver killed PID=${SERVER_PID}" >>$TEST_LOG
   rm $DBFILE
   $CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} &
   SERVER_PID=$!
   echo "csqlserver restarted with PID=${SERVER_PID}" >>$TEST_LOG
   echo "Restarting Server"
   sleep 5
fi
TEST_SCRIPT_DIR=${ROOT_DIR}/${MODULE}
TEST_RUN_DIR=${TEST_RUN_ROOT}/${MODULE}
if [ -s "$TEST_RUN_DIR" ]
then
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
EXP_FILE=exp.`basename ${test}`
#echo "EXP_FILE is $EXP_FILE"
if [ -s "${TEST_SCRIPT_DIR}/${EXP_FILE}" ]
then
    expPresent="yes"
fi

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
   kill -9 ${SERVER_PID}
   ipcrm -M 2222 -M 3333 
   echo "csqlserver killed PID=${SERVER_PID}" >>$TEST_LOG
   $CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} &
   SERVER_PID=$!
   echo "csqlserver restarted with PID=${SERVER_PID}" >>$TEST_LOG
   echo "Restarting Server"
   sleep 5
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
           kill -9 ${SERVER_PID}
           ipcrm -M 2222 -M 3333 
           echo "csqlserver killed PID=${SERVER_PID}" >>${TEST_LOG}
           rm $DBFILE
           $CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} &
           SERVER_PID=$!
           echo "csqlserver restarted with PID=${SERVER_PID}" >>${TEST_LOG}
           echo "Restarting Server"
           sleep 5
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
   kill -9 ${SERVER_PID}
   ipcrm -M 2222 -M 3333
   echo "csqlserver killed PID=${SERVER_PID}" >>$TEST_LOG
   rm $DBFILE
   $CSQL_INSTALL_ROOT/bin/csqlserver >${SERVOUT} 2>${SERVOUT} &
   SERVER_PID=$!
   echo "csqlserver restarted with PID=${SERVER_PID}" >>${TEST_LOG}
   echo "Restarting Server"
   sleep 5 
fi

done
done < TestModules

kill -9 ${SERVER_PID}
ipcrm -M 2222 -M 3333 
echo "csqlserver killed PID=${SERVER_PID}" >>${TEST_LOG}
rm $DBFILE

exit 0
