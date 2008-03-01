INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql catalog cachetable csqlserver csqlreplserver repltable
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/server/.libs/libcsql $(top_builddir)/src/sql/.libs/libcsqlsql $(top_builddir)/src/sqllog/.libs/libcsqlsqllog $(top_builddir)/src/network/.libs/libcsqlnw -lrt -lpthread -lcrypt

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/server/libcsql.la
catalog_LDFLAGS = -lcrypt

cachetable_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/server/libcsql.la
cachetable_LDFLAGS = -lcrypt -lodbc
cachetable_SOURCES = cachetable.cxx

repltable_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/server/libcsql.la
repltable_LDFLAGS = -lcrypt -lodbc
repltable_SOURCES = repltable.cxx

csqlserver_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/server/libcsql.la -lrt -lpthread -lcrypt
csqlserver_LDFLAGS = -lcrypt -lodbc 
csqlserver_SOURCES = csqlserver.cxx

csqlreplserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/server/libcsql.la -lrt -lpthread -lcrypt
csqlreplserver_LDFLAGS = -lcrypt
csqlreplserver_SOURCES = csqlreplserver.cxx
