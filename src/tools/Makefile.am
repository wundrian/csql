INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/server/libcsql.la $(top_builddir)/src/sql/libcsqlsql.la -lrt -lpthread -lcrypt

