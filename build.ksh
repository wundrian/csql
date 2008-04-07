
if [ "$JDK_HOME" == "" ]
then
	echo "Please set JDK_HOME"
	exit 1
fi

./configure --prefix=`pwd`/install CXXFLAGS="-g -I$JDK_HOME/include -I$JDK_HOME/include/linux"
#./configure --prefix=`pwd`/install CXXFLAGS=-g
#Note: You may have to fool the configure by making gcc link to g++, as it works only with g++
#./configure --prefix=`pwd`/install --enable-static=no CXXFLAGS="-O2"
#pdflatex -tex to pdf
#kpdf - to open pdf
