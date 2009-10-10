#!/bin/sh
if [ -z "$JDK_HOME" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi
make -f Makefile.cvs
./configure --prefix=`pwd`/install CXXFLAGS="-g  -I$JDK_HOME/include -I$JDK_HOME/include/linux"
#./configure --prefix=`pwd`/install CXXFLAGS="-g  -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
#./configure --prefix=`pwd`/install CXXFLAGS=-g
libtoolavailable=`which libtool`
if [ -z "$libtoolavailable" ]
then
    echo "libtool not available. Build may fail"
else
    mv libtool libtool.bk
    ln -s $libtoolavailable libtool
fi
make
make install
./csqlinstall.ksh
