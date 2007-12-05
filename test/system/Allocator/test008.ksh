#!/bin/sh
#Test Case: undo log allocation should return error message
#when db is full
#this test starts a large transaction which generates huge
#undo logs

#Run this test only under csql/test or on this directory.
FILENAME=${PWD}/system/Allocator/dbsizelimit
REL_PATH=.
if [ -s "$FILENAME" ]
then
    REL_PATH=`pwd`/system/Allocator
fi
${REL_PATH}/dbsizelimit 2>${REL_PATH}/tmp.out
cat ${REL_PATH}/tmp.out | gawk -F: '{ print $5 }'
rm ${REL_PATH}/tmp.out 

