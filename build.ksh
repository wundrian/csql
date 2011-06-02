#!/bin/sh
if [ -z "$JDK_HOME" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi

cp src/tools/Makefile.am.full src/tools/Makefile.am
cp src/odbc/Makefile.am.full src/odbc/Makefile.am
cp src/jdbc/Makefile.am.full src/jdbc/Makefile.am
cp src/Makefile.am.full src/Makefile.am

make -f Makefile.cvs
./configure --prefix=`pwd`/install CXXFLAGS="-g  -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
#./configure --prefix=`pwd`/install CXXFLAGS="-O2  -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
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
