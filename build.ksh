#!/bin/sh
#if [ "$JDK_HOME" == "" ]
if [ -z "$JDK_HOME" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi

./configure --prefix=`pwd`/install CXXFLAGS="-g  -I$JDK_HOME/include -I$JDK_HOME/include/linux"
#./configure --prefix=`pwd`/install CXXFLAGS="-g  -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
#./configure --prefix=`pwd`/install CXXFLAGS=-g
make
make install
./csqlinstall.ksh
