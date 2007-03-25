INCLUDES = -I../../include
METASOURCES = AUTO
bin_PROGRAMS = DMLTest UserAuthTest CreateTable
DMLTest_SOURCES = DMLTest.c
DMLTest_LDADD = $(top_builddir)/src/server/libcsql.la -lcrypt -lrt -lpthread
UserAuthTest_SOURCES = UserAuthTest.c
UserAuthTest_LDADD = $(top_builddir)/src/server/libcsql.la -lcrypt -lrt\
	-lpthread
CreateTable_LDADD = $(top_builddir)/src/server/libcsql.la -lcrypt -lrt -lpthread
CreateTable_SOURCES = CreateTable.c
