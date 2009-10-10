INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlodbcadapter.la
libcsqlodbcadapter_la_LDFLAGS = -avoid-version -module -lodbc
libcsqlodbcadapter_la_SOURCES = SqlOdbcConnection.cxx   SqlOdbcStatement.cxx

libcsqlodbcadapter_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la 
