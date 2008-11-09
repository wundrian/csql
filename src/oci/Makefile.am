INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlociadapter.la
libcsqlociadapter_la_LDFLAGS = -avoid-version -module -lclntsh
libcsqlociadapter_la_SOURCES = SqlOciConnection.cxx   SqlOciStatement.cxx

libcsqlociadapter_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la 
