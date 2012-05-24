#!/bin/bash

#Test Case : Need SELECT privileges on all tables involved in join

MY_PATH="$(dirname $0)"

TEST_USER="mbickel"
TEST_PW="test"

exitStatus()
{
    rm -f "${MY_PATH}/"*.sql
    echo "Test $1"
    exit $2;  
}

VALGRIND_RUN="valgrind --tool=memcheck --leak-check=full"
[ "$VALGRIND" = "true" ] || VALGRIND_RUN=""

echo "
create user ${TEST_USER} password '${TEST_PW}';
create table s (id integer);
create table t (id integer);
grant select on t to ${TEST_USER} where id = 1;
grant select on s to ${TEST_USER};
SET TIMER ON;
insert into t values (1);
SET TIMER OFF;
insert into t values (2);
insert into s values (1);
insert into s values (2);
insert into s values (3);
quit;" > "${MY_PATH}/as_root.sql"

echo "
SET TIMER ON;
select * from t, s;
SET TIMER OFF;
quit;" > "${MY_PATH}/as_usr.sql"

echo "
drop table t;
drop table s;
drop user ${TEST_USER};
quit;" > "${MY_PATH}/cleanup.sql"

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u root -p manager -s "${MY_PATH}/as_root.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 1

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u "${TEST_USER}" -p "${TEST_PW}" -s "${MY_PATH}/as_usr.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 2

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u root -p manager -s "${MY_PATH}/cleanup.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 3

exitStatus Passed 0;
