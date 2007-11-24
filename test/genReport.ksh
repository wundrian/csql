#!/bin/sh
##################Test Report Generator main starts here##############

#TEST_RUN_DIR should be set before running this
if [ ! "$TEST_RUN_ROOT" ]
then
    echo "TEST_RUN_ROOT should be set before running the tests"
    exit 1
fi
#if [ -s "$TEST_RUN_ROOT" ]
#then
#    echo "TEST_RUN_ROOT directory does not exist. Create it and try again."
#    exit 1
#fi
ROOT_DIR=`pwd`
TOTALPASSED=0
TOTALFAILED=0
echo "===================================================================="
echo "           MODULE                       TESTPASSED     TESTFAILED   "
echo "===================================================================="
while read MODULE
do
    echo $MODULE | grep "#" >/dev/null
    if [ $? -eq 0 ] 
    then
       continue
    fi
    TEST_RUN_DIR=${TEST_RUN_ROOT}/${MODULE}
    TEST_LOG=$TEST_RUN_DIR/testlog
    TESTPASSED=`grep PASSED $TEST_LOG | wc -l`
    TESTFAILED=`grep FAILED $TEST_LOG | wc -l`
    printf "%25s\t\t %5d\t\t %5d\t\t\n" $MODULE $TESTPASSED $TESTFAILED
    (( TOTALPASSED = TOTALPASSED + TESTPASSED ))
    (( TOTALFAILED = TOTALFAILED + TESTFAILED ))

done < TestModules

TOTSTRING=TOTAL
echo "===================================================================="
printf "%25s\t\t %5d\t\t %5d\t\t\n" $TOTSTRING $TOTALPASSED $TOTALFAILED
echo "===================================================================="
(( TOTALEXECUTED= TOTALPASSED + TOTALFAILED ))
echo "TOTAL Executed: $TOTALEXECUTED"
exit 0
