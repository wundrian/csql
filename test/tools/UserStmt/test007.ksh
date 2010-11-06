#!/bin/ksh
#Test Case : Changing Password of a user through same user should be passed 
# Connect to root user as:
# # csql -u root -p manager
# create a user say nihar as:
# CSQL> create user nihar password 'nihar123'.
# connect the user nihar as
# # csql -u nihar -p nihar123
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
    rm -f ${REL_PATH}/usr.sql ${REL_PATH}angepassword.sql ${REL_PATH}/usrroot.sql
    echo "Test $1"
    exit $2;  
}
echo "echo create user nihar password 'nihar123';" >${REL_PATH}/usr.sql
echo "create user nihar password 'nihar123';" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "echo show users;" >${REL_PATH}/changepassword.sql
echo "show users;" >>${REL_PATH}/changepassword.sql
echo "echo alter user nihar set password 'papu123';" >>${REL_PATH}/changepassword.sql
echo "alter user nihar set password 'papu123';" >>${REL_PATH}/changepassword.sql
echo "echo Disconnecting User nihar" >>${REL_PATH}/changepassword.sql
echo "quit;" >>${REL_PATH}/changepassword.sql

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

echo "Connecting User nihar"
if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u nihar -p nihar123 -s ${REL_PATH}/changepassword.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u nihar -p nihar123 -s ${REL_PATH}/changepassword.sql
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
