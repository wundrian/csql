if [ -z "$JDK_HOME" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi
cp src/sql/Makefile.am.mmdb src/sql/Makefile.am
cp src/tools/Makefile.am.mmdb src/tools/Makefile.am
cp src/odbc/Makefile.am.mmdb src/odbc/Makefile.am
cp src/jdbc/Makefile.am.mmdb src/jdbc/Makefile.am
cp src/Makefile.am.mmdb src/Makefile.am

make -f Makefile.cvs

#./configure --prefix=`pwd`/install CXXFLAGS="-g  -DMMDB -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
./configure --prefix=`pwd`/install CXXFLAGS="-g  -DMMDB -DEMBED -I$JDK_HOME/include -I$JDK_HOME/include/linux -Wno-write-strings"
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
./csqlinstallmmdb.ksh
