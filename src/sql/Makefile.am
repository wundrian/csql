INCLUDES = -I$(top_srcdir)/include $(all_includes) 
YACC = yacc -vd
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsql.la
libcsqlsql_la_LDFLAGS = -avoid-version -module \
	$(top_builddir)/src/storage/libcsqlstorage.la \
	$(top_builddir)/src/sqllog/libcsqlsqllog.la \
	$(top_builddir)/src/sqlnetwork/libcsqlsqlnw.la
libcsqlsql_la_SOURCES = dmlyacc.yxx dmllex.lxx ParsedData.cxx SelStatement.cxx \
	InsStatement.cxx UpdStatement.cxx DelStatement.cxx \
	DdlStatement.cxx CopyTblStatement.cxx MetadataStatement.cxx \
	SqlStatement.cxx  StatementFactory.cxx SqlFactory.cxx AlterTblStatement.cxx \
	DclStatementImpl.cxx

libcsqlsql_a_LIBADD = $(top_builddir)/src/storage/libcsqlstorage.la 
