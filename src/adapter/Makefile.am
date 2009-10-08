INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlodbcadapter.la
libcsqlodbcadapter_la_LDFLAGS = -version-info 2:4:0 -module -lodbc
libcsqlodbcadapter_la_SOURCES = SqlOdbcConnection.cxx   SqlOdbcStatement.cxx

libcsqlodbcadapter_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la 
