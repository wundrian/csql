#!/bin/ksh
#Test Case : Changing Password of an existing user through root user and connecting to that user with new password should be passed. 
# Connect to root user as:
# # csql -u root -p manager
# create a user say nihar as:
# CSQL> create user nihar password 'nihar123'.
# Change the password of user nihar as:
# CSQL> alter user nihar set password 'papu123'.
# It should be passed.
# Connect User nihar with new password. Connection should be established.
 
QUITFILE=${PWD}/tools/UserStmt/csql.conf
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/UserStmt
fi

exitStatus()
{
    rm -f ${REL_PATH}/usr.sql ${REL_PATH}/qut.sql ${REL_PATH}/usrroot.sql
    echo "Test $1"
    exit $2;  
}

echo "echo create user nihar password 'nihar123';" >${REL_PATH}/usr.sql
echo "create user nihar password 'nihar123';" >>${REL_PATH}/usr.sql
echo "echo alter user nihar set password 'papu123';" >>${REL_PATH}/usr.sql
echo "alter user nihar set password 'papu123';" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "echo show users;" >${REL_PATH}/qut.sql
echo "show users;" >>${REL_PATH}/qut.sql
echo "echo Disconnecting User nihar" >>${REL_PATH}/qut.sql
echo "quit;" >>${REL_PATH}/qut.sql

echo "echo drop user nihar;" >${REL_PATH}/usrroot.sql
echo "drop user nihar;" >>${REL_PATH}/usrroot.sql
echo "echo show users;">>${REL_PATH}/usrroot.sql
echo "show users;">>${REL_PATH}/usrroot.sql
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

echo "Connecting User nihar using new Password"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u nihar -p papu123 -s ${REL_PATH}/qut.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u nihar -p papu123 -s ${REL_PATH}/qut.sql
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
