INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql catalog cachetable csqlserver csqlsqlserver csqlcacheserver csqldump cacheverify redo recover checkpoint csqlds csqlasyncserver
csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/storage/.libs/libcsql \
	$(top_builddir)/src/sql/.libs/libcsqlsql \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog \
	$(top_builddir)/src/network/.libs/libcsqlnw \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter \
	$(top_builddir)/src/gateway/.libs/libcsqlgw \
	$(top_builddir)/src/cache/.libs/libcacheload \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw \
	-lrt -lpthread -lcrypt -lodbc -lreadline

redo_SOURCES = redo.cxx
redo_LDADD = $(top_builddir)/src/storage/.libs/libcsql  $(top_builddir)/src/sql/.libs/libcsqlsql $(top_builddir)/src/sqllog/.libs/libcsqlsqllog  $(top_builddir)/src/network/.libs/libcsqlnw $(top_builddir)/src/adapter/.libs/libcsqlodbcadapter $(top_builddir)/src/gateway/.libs/libcsqlgw $(top_builddir)/src/cache/.libs/libcacheload $(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw -lrt -lpthread -lcrypt -lodbc

recover_SOURCES = recover.cxx
recover_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
	$(top_builddir)/src/sql/.libs/libcsqlsql  \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
	$(top_builddir)/src/gateway/.libs/libcsqlgw  \
	$(top_builddir)/src/cache/.libs/libcacheload  \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  
recover_LDFLAGS = -lcrypt -lrt -lpthread -lcrypt -lodbc

checkpoint_SOURCES = checkpoint.cxx
checkpoint_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
	$(top_builddir)/src/sql/.libs/libcsqlsql  \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
	$(top_builddir)/src/gateway/.libs/libcsqlgw  \
	$(top_builddir)/src/cache/.libs/libcacheload  \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  
checkpoint_LDFLAGS = -lcrypt -lrt -lpthread -lcrypt -lodbc

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
	$(top_builddir)/src/sql/.libs/libcsqlsql  \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
	$(top_builddir)/src/gateway/.libs/libcsqlgw  \
	$(top_builddir)/src/cache/.libs/libcacheload  \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  
catalog_LDFLAGS = -lcrypt -lrt

cachetable_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
	$(top_builddir)/src/sql/.libs/libcsqlsql  \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
	$(top_builddir)/src/gateway/.libs/libcsqlgw  \
	$(top_builddir)/src/cache/.libs/libcacheload  \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  
cachetable_LDFLAGS = -lcrypt -lodbc -lrt
cachetable_SOURCES = cachetable.cxx

cacheverify_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
	$(top_builddir)/src/storage/libcsql.la $(top_builddir)/src/adapter/libcsqlodbcadapter.la 
cacheverify_LDFLAGS = -lcrypt -lodbc
cacheverify_SOURCES = cacheverify.cxx

csqlserver_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
	$(top_builddir)/src/sql/.libs/libcsqlsql  \
	$(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
	$(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
	$(top_builddir)/src/gateway/.libs/libcsqlgw  \
	$(top_builddir)/src/cache/.libs/libcacheload  \
	$(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  -lrt -lpthread -lcrypt 
csqlserver_LDFLAGS = -lcrypt -lodbc 
csqlserver_SOURCES = csqlserver.cxx

csqlasyncserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqlasyncserver_LDFLAGS = -lcrypt -lodbc
csqlasyncserver_SOURCES = csqlasyncserver.cxx

csqlsqlserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqlsqlserver_LDFLAGS = -lcrypt -lodbc
csqlsqlserver_SOURCES = csqlsqlserver.cxx

csqldump_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la -lrt -lpthread -lcrypt
csqldump_LDFLAGS = -lcrypt -lodbc
csqldump_SOURCES = csqldump.cxx

csqlcacheserver_LDADD = $(top_builddir)/src/storage/.libs/libcsql  \
    $(top_builddir)/src/sql/.libs/libcsqlsql  \
    $(top_builddir)/src/sqllog/.libs/libcsqlsqllog  \
    $(top_builddir)/src/network/.libs/libcsqlnw  \
    $(top_builddir)/src/adapter/.libs/libcsqlodbcadapter  \
    $(top_builddir)/src/gateway/.libs/libcsqlgw  \
    $(top_builddir)/src/cache/.libs/libcacheload  \
    $(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw  -lrt -lpthread -lcrypt
csqlcacheserver_LDFLAGS = -lcrypt -lodbc -lrt -lpthread 
csqlcacheserver_SOURCES = csqlcacheserver.cxx

csqlds_LDADD = $(top_builddir)/src/storage/.libs/libcsql 
csqlds_LDFLAGS = -lcrypt
csqlds_SOURCES = csqlds.cxx
