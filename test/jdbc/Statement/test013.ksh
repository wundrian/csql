#!/bin/sh
# ExecuteUpdate for SELECT statement it should not return resultset throw exception
# TestScript4.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
echo "Drop table T1;" > ${REL_PATH}/tmp.sql
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript4
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/tmp.sql
   rm -f ${REL_PATH}/tmp.sql
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/tmp.sql
rm -f ${REL_PATH}/tmp.sql
exit 0;
