INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/server/.libs/libcsql $(top_builddir)/src/sql/.libs/libcsqlsql -lrt -lpthread -lcrypt

