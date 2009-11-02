INCLUDES = -I$(top_srcdir)/include $(all_includes) 
YACC = yacc -vd
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsql.la
libcsqlsql_la_LDFLAGS = -avoid-version -module 
libcsqlsql_la_SOURCES = dmlyacc.yxx dmllex.lxx ParsedData.cxx SelStatement.cxx \
	InsStatement.cxx UpdStatement.cxx DelStatement.cxx \
	DdlStatement.cxx \
	SqlStatement.cxx  StatementFactory.cxx SqlFactory.cxx \
        CopyTblStatement.cxx MetadataStatement.cxx \
	AlterTblStatement.cxx
