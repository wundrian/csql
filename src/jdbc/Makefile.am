INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqljdbc.la
libcsqljdbc_la_LDFLAGS = -avoid-version -module \
		-L$(top_srcdir)/src/storage -lcsql \
		-L$(top_srcdir)/src/network -lcsqlnw \
		-L$(top_srcdir)/src/sql -lcsqlsql \
		-L$(top_srcdir)/src/sqlnetwork -lcsqlsqlnw \
		-L$(top_srcdir)/src/sqllog -lcsqlsqllog \
		-L$(top_srcdir)/src/adapter -lcsqlodbcadapter \
		-L$(top_srcdir)/src/gateway -lcsqlgw \
		-L$(top_builddir)/src/cache -lcacheload \
-lcrypt 
libcsqljdbc_la_SOURCES = JSqlConnection.cxx JSqlStatement.cxx

noinst_HEADERS = JSqlConnection.h JSqlStatement.h
libcsqljdbc_a_LIBADD = 
libcsqljdbc_la_DEPENDENCIES = 

