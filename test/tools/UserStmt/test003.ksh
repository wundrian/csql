#!/bin/ksh
#Test Case : Creating and Dropping users through the users other than root user
#Test Case : Creating and Dropping users through the users other than root u
# Connect csql as root as:
# # csql -u root -p manager
# create a user say "lakshya" as:
# CSQL> create user lakshya password 'lakshya123';
# create another user say "lakshyasolutions" as:
# CSQL> create user lakshyasolutions password 'lakshya123';
# CSQL> quit;
# connect to "lakshya" user as
# # csql -u lakshya -p lakshya123
# Try to create another user say "lakshyatraining"
# CSQL> create user lakshyatraining password 'bbsr';
# It should be failed saying Other than root user no one can create user.
# Try to drop the user lakshyasolutions as:
# CSQL> drop user lakshyasolutions;
# It should be failed
# Try to drop "lakshya"
# It should be failed because you can not drop self user.
 
QUITFILE=${PWD}/tools/UserStmt/csql.conf
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/UserStmt
fi

exitStatus()
{
    rm -f ${REL_PATH}/usr.sql ${REL_PATH}/usrlakshya.sql ${REL_PATH}/usrroot.sql
    echo "Test $1"
    exit $2;  
}

echo "echo create user lakshya password 'lakshya123';" >${REL_PATH}/usr.sql
echo "create user lakshya password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo create user lakshyasolution password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "create user lakshyasolution password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo show users;" >>${REL_PATH}/usr.sql
echo "show users;" >>${REL_PATH}/usr.sql
echo "echo Disconnecting root user" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "echo create user lakshyatraining password 'lakshya123';" >${REL_PATH}/usrlakshya.sql
echo "create user lakshyatraining password 'lakshya123';" >>${REL_PATH}/usrlakshya.sql
echo "echo drop user lakshyasolution;" >>${REL_PATH}/usrlakshya.sql
echo "drop user lakshyasolution;" >>${REL_PATH}/usrlakshya.sql
echo "echo Disconnecting user lakshya" >>${REL_PATH}/usrlakshya.sql
echo "quit;" >>${REL_PATH}/usrlakshya.sql

echo "echo show users;" >${REL_PATH}/usrroot.sql
echo "show users;" >>${REL_PATH}/usrroot.sql
echo "echo drop user lakshyasolution;" >>${REL_PATH}/usrroot.sql
echo "drop user lakshyasolution;" >>${REL_PATH}/usrroot.sql
echo "echo  user lakshya;" >>${REL_PATH}/usrroot.sql
echo "drop user lakshya;" >>${REL_PATH}/usrroot.sql
echo "echo show users;" >>${REL_PATH}/usrroot.sql
echo "show users;" >>${REL_PATH}/usrroot.sql
echo "quit;" >>${REL_PATH}/usrroot.sql

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

echo "Connecting User lakshya"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u lakshya -p lakshya123 -s ${REL_PATH}/usrlakshya.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u lakshya -p lakshya123 -s ${REL_PATH}/usrlakshya.sql
   if [ $? -ne 0 ]
   then
      exitStatus Failed 2;
   fi
fi

echo "Connecting User root"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/usrroot.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/usrroot.sql
   if [ $? -ne 0 ]
   then
      exitStatus Failed 3;
   fi
fi

exitStatus Passed 0;
