#!/bin/sh
#USER_DB_KEY should not accept > 8192


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
echo "USER_DB_KEY=10000" >>${REL_PATH}/csqltmp.conf
${REL_PATH}/connect >${REL_PATH}/tmp.out
cat ${REL_PATH}/tmp.out | gawk -F: '{ print $5 }'
rm ${REL_PATH}/tmp.out ${REL_PATH}/csqltmp.conf
