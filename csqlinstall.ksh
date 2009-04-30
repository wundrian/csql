#!/bin/sh
#Should run this command from the project root directory

#TODO:validate it is project root by checking some files
root_dir=`pwd`
install_dir=`grep "prefix =" Makefile|tail -1|awk '{ print $3 }'`
echo "installdir is ${install_dir}"
#cd src/sql
#sed -e "s/getc([ ]*yyin[ ]*)/(*lexInput++)/1" dmllex.cxx >tmp.c
#cp tmp.c dmllex.cxx
#make
#cd ../..
cd src/jdbc
./buildJdbcDriver.ksh
mkdir -p ${install_dir}/lib
cp CSqlJdbcDriver.jar ${install_dir}/lib
cd ${root_dir}
make install

#Any new libraries needs to be added here
cd ${install_dir}/lib
mv libcsql libcsql.so
mv libcsqlsql libcsqlsql.so
mv libcsqljdbc libcsqljdbc.so
mv libcsqlnw libcsqlnw.so
mv libcsqlsqllog libcsqlsqllog.so
mv libcsqlodbc libcsqlodbc.so
mv libcsqlodbcadapter libcsqlodbcadapter.so
mv libcsqlgw libcsqlgw.so
mv libcacheload libcacheload.so
ln -s libcsqlgw.so libcsqlgw
ln -s libcsqlodbcadapter.so libcsqlodbcadapter
ln -s libcsqlodbc.so libcsqlodbc
ln -s libcsqlsqllog.so libcsqlsqllog
ln -s libcsqlnw.so libcsqlnw
ln -s libcsqljdbc.so libcsqljdbc
ln -s libcsqlsql.so libcsqlsql
ln -s libcsql.so libcsql
ln -s libcacheload.so libcacheload


cp ${root_dir}/src/sql/Statement.h ${install_dir}/include
cp ${root_dir}/src/sql/Parser.h ${install_dir}/include
cd ${install_dir}/include

#rm Allocator.h CatalogTables.h Database.h 
#rm DatabaseManagerImpl.h
#rm Globals.h Index.h Lock.h PredicateImpl.h
#rm Process.h SessionImpl.h TableImpl.h Transaction.h UserManagerImpl.h 
cd ${install_dir}/bin
rm csqlreplserver  repltable

cp ${root_dir}/README ${install_dir}/README
cp ${root_dir}/COPYING ${install_dir}
cp ${root_dir}/AUTHORS ${install_dir}
cp ${root_dir}/ChangeLog ${install_dir}
cp ${root_dir}/csql.conf ${install_dir}
cp ${root_dir}/setupenv.ksh.install ${install_dir}/setupenv.ksh
cp -R ${root_dir}/examples ${install_dir}
find ${install_dir}/examples -name "CVS" -exec rm -rf {} \; 2>/dev/null
rm -rf ${install_dir}/examples/dbapi
rm -rf ${install_dir}/lib/*.a
rm -rf ${install_dir}/lib/*.la

cp -R ${root_dir}/docs ${install_dir}
find ${install_dir}/docs -name "CVS" -exec rm -rf {} \; 2>/dev/null
cp -R ${root_dir}/demo ${install_dir}
find ${install_dir}/demo -name "CVS" -exec rm -rf {} \; 2>/dev/null
cd ${root_dir}
echo "Build completed Successfully"
