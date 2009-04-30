INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src/sql -I$(top_srcdir)/include/odbc $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlodbc.la
libcsqlodbc_la_LDFLAGS = -avoid-version -module \
	$(top_builddir)/src/storage/.libs/libcsql \
	$(top_builddir)/src/sql/.libs/libcsqlsql \
	$(top_builddir)/src/gateway/.libs/libcsqlgw \
	$(top_builddir)/src/network/.libs/libcsqlnw \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog \
	$(top_builddir)/src/cache/.libs/libcacheload \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter -lcrypt
libcsqlodbc_la_SOURCES = odbcCommon.cxx odbcDbc.cxx odbcDesc.cxx \
odbcError.cxx odbcEnv.cxx odbcState.cxx \
odbcStmt.cxx

noinst_HEADERS = odbcCommon.h odbcDbc.h odbcDesc.h \
odbcEnv.h odbcError.h odbcStmt.h
libcsqlodbc_a_LIBADD = $(top_builddir)/src/odbc/libcsqlodbc.la
