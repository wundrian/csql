INCLUDES = -I$(top_srcdir)/include $(all_includes) 
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlsql.la
libcsqlsql_la_LDFLAGS = -module
libcsqlsql_la_SOURCES = dmlyacc.y dmllex.l ParsedData.c SelStatement.c \
	InsStatement.c UpdStatement.c DelStatement.c \
	SqlStatement.c  StatementFactory.c

noinst_HEADERS = Parser.h Statement.h SqlStatement.h SqlConnection.h
libcsqlsql_a_LIBADD = $(top_builddir)/src/server/libcsql.la
