INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql catalog cachetable csqlserver csqlreplserver csqlsqlserver repltable csqlcacheserver csqldump cacheverify
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/storage/.libs/libcsql $(top_builddir)/src/sql/.libs/libcsqlsql $(top_builddir)/src/sqllog/.libs/libcsqlsqllog $(top_builddir)/src/network/.libs/libcsqlnw $(top_builddir)/src/adapter/.libs/libcsqlodbcadapter $(top_builddir)/src/gateway/.libs/libcsqlgw $(top_builddir)/src/cache/.libs/libcacheload $(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw -lrt -lpthread -lcrypt -lodbc

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/storage/libcsql.la \
	$(top_builddir)/src/cache/libcacheload.la 
catalog_LDFLAGS = -lcrypt

cachetable_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsql.la $(top_builddir)/src/adapter/libcsqlodbcadapter.la 
cachetable_LDFLAGS = -lcrypt -lodbc
cachetable_SOURCES = cachetable.cxx

cacheverify_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
	$(top_builddir)/src/storage/libcsql.la $(top_builddir)/src/adapter/libcsqlodbcadapter.la 
cacheverify_LDFLAGS = -lcrypt -lodbc
cacheverify_SOURCES = cacheverify.cxx

repltable_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsql.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/gateway/libcsqlgw.la
repltable_LDFLAGS = -lcrypt -lodbc
repltable_SOURCES = repltable.cxx

csqlserver_LDADD = $(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsql.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/gateway/libcsqlgw.la -lrt -lpthread -lcrypt
csqlserver_LDFLAGS = -lcrypt -lodbc 
csqlserver_SOURCES = csqlserver.cxx

csqlreplserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqlreplserver_LDFLAGS = -lcrypt -lodbc
csqlreplserver_SOURCES = csqlreplserver.cxx

csqlsqlserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqlsqlserver_LDFLAGS = -lcrypt -lodbc
csqlsqlserver_SOURCES = csqlsqlserver.cxx

csqldump_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqldump_LDFLAGS = -lcrypt -lodbc
csqldump_SOURCES = csqldump.cxx

csqlcacheserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqlcacheserver_LDFLAGS = -lcrypt -lodbc
csqlcacheserver_SOURCES = csqlcacheserver.cxx
