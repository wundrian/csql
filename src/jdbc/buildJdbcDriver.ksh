rm -rf classtmp
mkdir classtmp
javac -d classtmp -nowarn *.java 
cd classtmp
jar cvf CSqlJdbcDriver.jar *
mv CSqlJdbcDriver.jar ..
cd ..
