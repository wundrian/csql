#!/bin/ksh
# ExecuteUpdate for SELECT statement it should not return resultset throw exception


TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest13 
if [ $? -ne 0 ]
then
   echo "Drop table T1;"| $CSQL_INSTALL_ROOT/bin/csql
   exit 1;
fi
echo "Drop table T1;"| $CSQL_INSTALL_ROOT/bin/csql
exit 0;
