INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql catalog cachetable csqlserver
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/server/.libs/libcsql $(top_builddir)/src/sql/.libs/libcsqlsql -lrt -lpthread -lcrypt

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/server/libcsql.la
catalog_LDFLAGS = -lcrypt
cachetable_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/server/libcsql.la
cachetable_LDFLAGS = -lcrypt -lodbc
cachetable_SOURCES = cachetable.cxx

csqlserver_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/server/libcsql.la -lrt -lpthread -lcrypt
csqlserver_LDFLAGS = -lcrypt -lodbc 
csqlserver_SOURCES = csqlserver.cxx
