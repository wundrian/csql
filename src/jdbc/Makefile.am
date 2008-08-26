INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqljdbc.la
libcsqljdbc_la_LDFLAGS = -avoid-version -module $(top_srcdir)/src/sql/.libs/libcsqlsql  $(top_srcdir)/src/storage/.libs/libcsql $(top_srcdir)/src/sqllog/.libs/libcsqlsqllog $(top_srcdir)/src/network/.libs/libcsqlnw  -lcrypt 
libcsqljdbc_la_SOURCES = JSqlConnection.cxx JSqlStatement.cxx

noinst_HEADERS = JSqlConnection.h JSqlStatement.h
libcsqljdbc_a_LIBADD = 
libcsqljdbc_la_DEPENDENCIES = 

