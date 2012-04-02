INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src/sql -I$(top_srcdir)/include/odbc $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlodbc.la
libcsqlodbc_la_LDFLAGS = -avoid-version -module \
    -L$(top_srcdir)/src/storage -lcsqlstorage \
    -L$(top_srcdir)/src/sql -lcsqlsql \
    -L$(top_srcdir)/src/network -lcsqlnw \
    -L$(top_srcdir)/src/sqlnetwork -lcsqlsqlnw \
    -L$(top_srcdir)/src/sqllog -lcsqlsqllog \
	-lcrypt
libcsqlodbc_la_SOURCES = odbcCommon.cxx odbcDbc.cxx odbcDesc.cxx \
odbcError.cxx odbcEnv.cxx odbcState.cxx \
odbcStmt.cxx

noinst_HEADERS = odbcCommon.h odbcDbc.h odbcDesc.h \
odbcEnv.h odbcError.h odbcStmt.h
