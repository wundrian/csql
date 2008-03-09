INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlgw.la
libcsqlgw_la_LDFLAGS = -avoid-version -module
libcsqlgw_la_SOURCES = SqlGwConnection.cxx  SqlGwStatement.cxx

libcsqlgw_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la $(top_builddir)/src/network/libcsqlnw.la
