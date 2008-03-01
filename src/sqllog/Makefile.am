INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsqllog.la
libcsqlsqllog_la_LDFLAGS = -avoid-version -module
libcsqlsqllog_la_SOURCES = SqlLogConnection.cxx  SqlLogStatement.cxx

libcsqlsqllog_a_LIBADD = $(top_builddir)/src/sql/libcsqlsql.la $(top_builddir)/src/network/libcsqlnw.la
