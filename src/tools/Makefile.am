INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csql icsql catalog cachetable csqldump cacheverify redo recover checkpoint csqlds applyofflinelogs

csql_SOURCES = isql.cxx
csql_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csql_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -lreadline -lcurses -ldl

icsql_SOURCES = isql.cxx
icsql_CPPFLAGS = -DNO_READLINE_LIB
icsql_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/base/libcsqlbase.la \
        $(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la
icsql_LDFLAGS = -lrt -lpthread -lcrypt -lodbc  -ldl


redo_SOURCES = redo.cxx
redo_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la
redo_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -lreadline -lcurses -ldl

applyofflinelogs_SOURCES = applyofflinelogs.cxx
applyofflinelogs_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
applyofflinelogs_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -ldl

recover_SOURCES = recover.cxx
recover_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
recover_LDFLAGS = -lcrypt -lrt -lpthread -lodbc -ldl

checkpoint_SOURCES = checkpoint.cxx
checkpoint_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
checkpoint_LDFLAGS = -lcrypt -lrt -lpthread -lcrypt -lodbc -ldl

catalog_SOURCES = catalog.cxx
catalog_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
catalog_LDFLAGS = -lcrypt -lrt -ldl

cachetable_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
cachetable_LDFLAGS = -lcrypt -lodbc -lrt -ldl
cachetable_SOURCES = cachetable.cxx

cacheverify_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/storage/libcsqlstorage.la 
cacheverify_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -ldl
cacheverify_SOURCES = cacheverify.cxx

csqldump_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsqlstorage.la 
csqldump_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -ldl
csqldump_SOURCES = csqldump.cxx

csqlds_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/base/libcsqlbase.la 
csqlds_LDFLAGS = -lcrypt -ldl
csqlds_SOURCES = csqlds.cxx
