#!/bin/ksh
#Test Case : Showing all users and Dropping users except root user through root user should be allowed
# Connect root user as:
# # csql -u root -p manager
# create 3 user other than root
# Show all users using "show users" statement. It should show all users including root user.
# Drop all the users. U should be able to drop all the users except root user.
 
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

echo "echo create user lakshya password 'lakshya123';" >${REL_PATH}/usr.sql
echo "create user lakshya password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo create user lakshyatraining password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "create user lakshyatraining password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo create user lakshyasolution password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "create user lakshyasolution password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo show users;" >>${REL_PATH}/usr.sql
echo "show users;" >>${REL_PATH}/usr.sql
echo "echo drop user lakshya;" >>${REL_PATH}/usr.sql
echo "drop user lakshya;" >>${REL_PATH}/usr.sql
echo "echo drop user lakshyatraining;" >>${REL_PATH}/usr.sql
echo "drop user lakshyatraining;" >>${REL_PATH}/usr.sql
echo "echo drop user lakshyasolution;" >>${REL_PATH}/usr.sql
echo "drop user lakshyasolution;" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

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
