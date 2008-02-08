INCLUDES = -I$(top_srcdir)/include $(all_includes) 
YACC = yacc -vd
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsql.la
libcsqlsql_la_LDFLAGS = -avoid-version -module
libcsqlsql_la_SOURCES = dmlyacc.yxx dmllex.lxx ParsedData.cxx SelStatement.cxx \
	InsStatement.cxx UpdStatement.cxx DelStatement.cxx \
	DdlStatement.cxx \
	SqlStatement.cxx  StatementFactory.cxx SqlFactory.cxx

noinst_HEADERS = Parser.h Statement.h 
libcsqlsql_a_LIBADD = $(top_builddir)/src/server/libcsql.la
