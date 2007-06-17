#!/bin/ksh
#Should run this command from the project root directory

#TODO:validate it is project root by checking some files
root_dir=`pwd`
install_dir=`grep "prefix =" Makefile|tail -1|awk '{ print $3 }'`
echo "installdir is ${install_dir}"
cd src/sql
sed -e "s/getc([ ]*yyin[ ]*)/(*lexInput++)/1" dmllex.cxx >tmp.c
cp tmp.c dmllex.cxx
make
cd ../..
cd src/jdbc
./buildJdbcDriver.ksh
cp CSqlJdbcDriver.jar ${install_dir}/lib
cd ${root_dir}
make install
cd ${install_dir}/lib
cp libcsql libcsql.so
cp libcsqlsql libcsqlsql.so
cp libcsqljdbc libcsqljdbc.so
cd ${root_dir}
