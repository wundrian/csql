INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsqlnw.la
libcsqlsqlnw_la_LDFLAGS = -version-info 2:4:0 -module 
libcsqlsqlnw_la_SOURCES = SqlNwConnection.cxx   SqlNwStatement.cxx

libcsqlsqlnw_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la 
