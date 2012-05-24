#!/bin/bash

NUM_CLIENTS=${1:-1000}
LOG_BASEPATH="/tmp/loadtest"

TEST_USER="mbickel"
TEST_PW="test"
SETUP_SQL="`dirname $0`/load/DCL/setup.sql"
TEARDOWN_SQL="`dirname $0`/load/DCL/teardown.sql"
CLIENT_SQL="`dirname $0`/load/DCL/test.sql"

__SERVER_PID=""
__CLIENT_PIDS=""

restart_server() {
	# not relying on __SERVER_PID, check for yourself
	ps ax | grep -v grep | grep csqlserver >/dev/null 2>&1
	if [[ $? -eq 0 ]] ; then
		echo "csqlserver already running, killing it."
		killall -2 csqlserver # execTests.ksh does -2 instead -9 (so server can act on it?)
		sleep 1 # give it time to shut down and unmap it's memory
	fi

	csqlserver &
	__SERVER_PID=$!
}


# taken from http://stackoverflow.com/questions/592620/check-if-a-program-exists-from-a-bash-script
command -v csql >/dev/null 2>&1 || { echo >&2 "csql not found on PATH. Have you run setupenv.ksh?"; exit 1; }
command -v csqlserver >/dev/null 2>&1 || { echo >&2 "csqlserver not found on PATH. Have you run setupenv.ksh?"; exit 1; }

# after this finishes, we should have a running csqlserver instance
restart_server

mkdir -p "${LOG_BASEPATH}"
rm -rf "${LOG_BASEPATH}/"* 

sleep 1

for testcase in "`dirname $0`"/sql/DCL/test*.sh ; do
	for i in `seq -w -s ' ' 1 $NUM_CLIENTS`
	do
		testname=`basename "$testcase" .sh`
		logfile="${LOG_BASEPATH}/${testname}_${i}_client.out"
		"${testcase}" &> "${logfile}"
	done
done

# wait for all clients (ie all processes this shell started, minus the csqlserver)
#alljobs="`jobs -p`"
#for job in ${alljobs/$__SERVER_PID/} ; do
#	wait $job
#done

#csql -u root -p manager -s "${TEARDOWN_SQL}" &> "${LOG_BASEPATH}/serv.out"
