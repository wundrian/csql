#!/bin/ksh
#SYS_DB_KEY and USER_DB_KEY should not have same value


#Run this test only under csql/test or on this directory.
#Otherwise, it may fail as CSQL_CONFIG_FILE may not be able to read
CSQL_CONF=${PWD}/system/config/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=`pwd`/system/config
fi
cp ${REL_PATH}/csql.conf ${REL_PATH}/csqltmp.conf
export CSQL_CONFIG_FILE=${REL_PATH}/csqltmp.conf
echo "USER_DB_KEY=1000" >>${REL_PATH}/csqltmp.conf
echo "SYS_DB_KEY=1000" >>${REL_PATH}/csqltmp.conf
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/connect 2> $0.valgr
else
    ${REL_PATH}/connect 2>${REL_PATH}/tmp.out
fi
cat ${REL_PATH}/tmp.out | awk -F: '{ print $8 }'
rm ${REL_PATH}/tmp.out ${REL_PATH}/csqltmp.conf
