INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(top_srcdir)/src/sql
METASOURCES = AUTO
bin_PROGRAMS = csqlserver csqlsqlserver csqlcacheserver csqlasyncserver csqlcheckpointserver 

csqlserver_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc  -ldl
csqlserver_SOURCES = csqlserver.cxx

csqlasyncserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsqlstorage.la 
csqlasyncserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc  -ldl
csqlasyncserver_SOURCES = csqlasyncserver.cxx

csqlsqlserver_LDADD = $(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/storage/libcsqlstorage.la 
csqlsqlserver_LDFLAGS = -lrt -lpthread -lcrypt -lodbc -ldl
csqlsqlserver_SOURCES = csqlsqlserver.cxx

csqlcacheserver_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la  \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
        $(top_builddir)/src/sqllog/libcsqlsqllog.la \
        $(top_builddir)/src/network/libcsqlnw.la \
        $(top_builddir)/src/adapter/libcsqlodbcadapter.la \
        $(top_builddir)/src/gateway/libcsqlgw.la \
        $(top_builddir)/src/cache/libcacheload.la \
        $(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlcacheserver_LDFLAGS = -lcrypt -lodbc -lrt -lpthread -ldl
csqlcacheserver_SOURCES = csqlcacheserver.cxx

csqlcheckpointserver_LDADD = $(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/base/libcsqlbase.la \
	$(top_builddir)/src/sql/libcsqlsql.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/network/libcsqlnw.la \
	$(top_builddir)/src/adapter/libcsqlodbcadapter.la \
	$(top_builddir)/src/gateway/libcsqlgw.la \
	$(top_builddir)/src/cache/libcacheload.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la 
csqlcheckpointserver_LDFLAGS = -lcrypt -lodbc -lrt -lpthread -ldl
csqlcheckpointserver_SOURCES = csqlcheckpointserver.cxx
