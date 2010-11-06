#!/bin/ksh
export  START=1
export  END=1000000
echo "Loading 1000000 record ...."
./ODBCLoad csql
export  ITERATION=100
export  START=1000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=1000001
export  END=2000000
echo "Loading 1000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=2000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=2000001
export  END=5000000
echo "Loading 5000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=5000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=5000001
export  END=10000000
echo "Loading 5000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=10000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=10000001
export  END=20000000
echo "Loading 10000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=20000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=20000001
export  END=50000000
echo "Loading 30000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=50000001
echo "Operation After Loading $END Record"
./ODBCTest
export  START=50000001
export  END=100000000
echo "Loading 50000000 record ...."
./ODBCLoad
export  ITERATION=100
export  START=100000001
echo "Operation After Loading $END Record"

