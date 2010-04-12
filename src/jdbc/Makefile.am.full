INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqljdbc.la
libcsqljdbc_la_LDFLAGS = -avoid-version -module \
		-L$(top_srcdir)/src/storage/.libs -lcsql \
		-L$(top_srcdir)/src/network/.libs -lcsqlnw \
		-L$(top_srcdir)/src/sql/.libs -lcsqlsql \
		-L$(top_srcdir)/src/sqlnetwork/.libs -lcsqlsqlnw \
		-L$(top_srcdir)/src/sqllog/.libs -lcsqlsqllog \
		-L$(top_srcdir)/src/adapter/.libs -lcsqlodbcadapter \
		-L$(top_srcdir)/src/gateway/.libs -lcsqlgw \
		-L$(top_builddir)/src/cache/.libs -lcacheload \
-lcrypt 
libcsqljdbc_la_SOURCES = JSqlConnection.cxx JSqlStatement.cxx

noinst_HEADERS = JSqlConnection.h JSqlStatement.h
libcsqljdbc_a_LIBADD = 
libcsqljdbc_la_DEPENDENCIES = 

