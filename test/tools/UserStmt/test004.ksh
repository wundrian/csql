#!/bin/ksh
#Test Case : Dropping root user through the root user should be failed
# Connect to root user as:
# # csql -u root -p manager
# Try to drop root user as:
# CSQL> drop user root
# It should be failed because you can not drop self user.
 
QUITFILE=${PWD}/tools/UserStmt/csql.conf
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/UserStmt
fi

exitStatus()
{
    rm -f ${REL_PATH}/usr.sql 
    echo "Test $1"
    exit $2;  
}

echo "echo drop user root;" >${REL_PATH}/usr.sql
echo "drop user root;" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "Connecting User root"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/usr.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/usr.sql
   if [ $? -ne 0 ]
   then
      exitStatus Failed 1;
   fi
fi

exitStatus Passed 0;
