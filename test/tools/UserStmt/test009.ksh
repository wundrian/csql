#!/bin/ksh
#Test Case : DDL and DML operations in users other than root user
# Connect root user as:
# # csql -u root -p manager
# Create a user lakshya as:
# CSQL> create user lakshya password 'lakshya123';
# Connect csql through lakshya as
# # csql -u lakshya -p lakshya123
# Do DDL and DML operations. All should work properly.
 
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

echo "echo create table t1(f1 int,f2 char(10));" >${REL_PATH}/usr.sql
echo "create table t1(f1 int,f2 char(10));" >>${REL_PATH}/usr.sql
echo "echo insert into t1 values(1,'root1');" >>${REL_PATH}/usr.sql
echo "insert into t1 values(1,'root1');" >>${REL_PATH}/usr.sql
echo "echo select * from t1;" >>${REL_PATH}/usr.sql
echo "select * from t1;" >>${REL_PATH}/usr.sql
echo "echo create user lakshya password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "create user lakshya password 'lakshya123';" >>${REL_PATH}/usr.sql
echo "echo show users;" >>${REL_PATH}/usr.sql
echo "show users;" >>${REL_PATH}/usr.sql
echo "echo Disconnecting User root" >>${REL_PATH}/usr.sql
echo "quit;" >>${REL_PATH}/usr.sql

echo "echo create table t2(f1 int,f2 char(10));" >${REL_PATH}/usrlakshya.sql
echo "create table t2(f1 int,f2 char(10));" >>${REL_PATH}/usrlakshya.sql
echo "echo insert into t1 values(2,'root2');" >>${REL_PATH}/usrlakshya.sql
echo "insert into t1 values(2,'root2');" >>${REL_PATH}/usrlakshya.sql
echo "echo insert into t2 values(10,'lakshya');" >>${REL_PATH}/usrlakshya.sql
echo "insert into t2 values(10,'lakshya');" >>${REL_PATH}/usrlakshya.sql
echo "echo select * from t1;" >>${REL_PATH}/usrlakshya.sql
echo "select * from t1;" >>${REL_PATH}/usrlakshya.sql
echo "echo select * from t2;" >>${REL_PATH}/usrlakshya.sql
echo "select * from t2;" >>${REL_PATH}/usrlakshya.sql
echo "echo Disconnecting user lakshya" >>${REL_PATH}/usrlakshya.sql
echo "quit;" >>${REL_PATH}/usrlakshya.sql

echo "echo drop user lakshya;" >${REL_PATH}/usrroot.sql
echo "drop user lakshya;" >>${REL_PATH}/usrroot.sql
echo "drop table t1;" >>${REL_PATH}/usrroot.sql
echo "drop table t2;" >>${REL_PATH}/usrroot.sql
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
