#!/bin/ksh
TESTFILE=${PWD}/jdbc/Statement/StmtTest6.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/ins.sql
java AggPara
if [ $? -ne 0 ]
then
   echo "DROP TABLE T1;" >${REL_PATH}/dropT1.sql
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropT1.sql
   rm -f ${REL_PATH}/dropT1.sql
   exit 1;
fi
exit 0;
