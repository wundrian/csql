#!/bin/ksh
# ExecuteUpdate for SELECT statement it should not return resultset throw exception
# TestScript4.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript4
if [ $? -ne 0 ]
then
   echo "Drop table T1;"| $CSQL_INSTALL_ROOT/bin/csql
   exit 1;
fi
echo "Drop table T1;"| $CSQL_INSTALL_ROOT/bin/csql
exit 0;
