INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql catalog cachetable csqlserver csqlsqlserver csqlcacheserver csqldump cacheverify redo recover checkpoint csqlds csqlasyncserver csqlcheckpointserver applyofflinelogs

csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/storage/libcsql.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csql_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -lreadline

redo_SOURCES = redo.cxx
redo_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la
redo_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -lreadline

applyofflinelogs_SOURCES = applyofflinelogs.cxx
applyofflinelogs_LDADD = $(top_builddir)/src/storage/.libs/libcsql.so \
    $(top_builddir)/src/sql/.libs/libcsqlsql.so \
    $(top_builddir)/src/sqllog/.libs/libcsqlsqllog.so \
    $(top_builddir)/src/network/.libs/libcsqlnw.so \
    $(top_builddir)/src/adapter/.libs/libcsqlodbcadapter.so \
    $(top_builddir)/src/gateway/.libs/libcsqlgw.so \
    $(top_builddir)/src/cache/.libs/libcacheload.so \
    $(top_builddir)/src/sqlnetwork/.libs/libcsqlsqlnw.so 
applyofflinelogs_LDFLAGS = -lrt -lpthread -lcrypt -lodbc

recover_SOURCES = recover.cxx
recover_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
recover_LDFLAGS = -lcrypt -lrt -lpthread -lodbc

checkpoint_SOURCES = checkpoint.cxx
checkpoint_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
checkpoint_LDFLAGS = -lcrypt -lrt -lpthread -lcrypt -lodbc

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
catalog_LDFLAGS = -lcrypt -lrt

cachetable_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
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
	$(top_builddir)/src/storage/libcsql.la 
cacheverify_LDFLAGS = -lrt -lpthread -lcrypt -lodbc
cacheverify_SOURCES = cacheverify.cxx

csqlserver_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc 
csqlserver_SOURCES = csqlserver.cxx

csqlasyncserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la 
csqlasyncserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc 
csqlasyncserver_SOURCES = csqlasyncserver.cxx

csqlsqlserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la 
csqlsqlserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc
csqlsqlserver_SOURCES = csqlsqlserver.cxx

csqldump_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsql.la 
csqldump_LDFLAGS = -lrt -lpthread -lcrypt -lodbc
csqldump_SOURCES = csqldump.cxx

csqlcacheserver_LDADD = $(top_builddir)/src/storage/libcsql.la  \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlcacheserver_LDFLAGS = -lcrypt -lodbc -lrt -lpthread 
csqlcacheserver_SOURCES = csqlcacheserver.cxx

csqlcheckpointserver_LDADD = $(top_builddir)/src/storage/libcsql.la \
    $(top_builddir)/src/sql/libcsqlsql.la \
    $(top_builddir)/src/sqllog/libcsqlsqllog.la \
    $(top_builddir)/src/network/libcsqlnw.la \
    $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
    $(top_builddir)/src/gateway/libcsqlgw.la \
    $(top_builddir)/src/cache/libcacheload.la \
    $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlcheckpointserver_LDFLAGS = -lcrypt -lodbc -lrt -lpthread
csqlcheckpointserver_SOURCES = csqlcheckpointserver.cxx



csqlds_LDADD = $(top_builddir)/src/storage/libcsql.la
csqlds_LDFLAGS = -lcrypt
csqlds_SOURCES = csqlds.cxx
