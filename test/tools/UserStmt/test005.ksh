#!/bin/ksh
#Test Case : Creation of user with same name twice should be failed
# Connect to root user as:
# # csql -u root -p manager
# create a user say nihar as:
# CSQL> create user nihar password 'nihar123';
# create another user with same name nihar
# CSQL> create user nihar password 'nihar123';
# It should be failed, saying user name in this name already exist.
 
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

echo "echo create user nihar password 'nihar123';" >${REL_PATH}/usr.sql
echo "create user nihar password 'nihar123';" >>${REL_PATH}/usr.sql
echo "echo create user nihar password 'nihar321';" >>${REL_PATH}/usr.sql
echo "create user nihar password 'nihar321';" >>${REL_PATH}/usr.sql
echo "echo drop user nihar;" >>${REL_PATH}/usr.sql
echo "drop user nihar;" >>${REL_PATH}/usr.sql
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
