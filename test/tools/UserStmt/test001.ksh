#!/bin/ksh
#Test Case : Working with a user other than root user
# Connect root user as:
# # csql -u root -p manager
# create a user other than root
# connect to that user as
# #csql -u <new_username> password <Password>
# It should be passed.

QUITFILE=${PWD}/tools/UserStmt/csql.conf
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/UserStmt
fi

exitStatus()
{
    rm -f ${REL_PATH}/usr.sql ${REL_PATH}/qut.sql ${REL_PATH}/drusr.sql
    echo "Test $1"
    exit $2;  
}

echo "echo create user lakshya password 'lakshya123';" >${REL_PATH}/usr.sql
echo "create user lakshya password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "echo quit;" >${REL_PATH}/qut.sql
echo "quit;" >>${REL_PATH}/qut.sql

echo "echo drop user lakshya;" >${REL_PATH}/drusr.sql
echo "drop user lakshya;" >>${REL_PATH}/drusr.sql

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
echo "User Created"

echo "Connecting to lakshya"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u lakshya -p lakshya123 -s ${REL_PATH}/qut.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u lakshya -p lakshya123 -s ${REL_PATH}/qut.sql
   if [ $? -ne 0 ]
   then
      exitStatus Failed 2;
   fi
fi

if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drusr.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drusr.sql
   if [ $? -ne 0 ]
   then
      exitStatus Failed 3;
   fi
fi
echo "User Dropped"

exitStatus Passed 0;
