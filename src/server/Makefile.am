INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsql.la
libcsql_la_LDFLAGS = -module
libcsql_la_SOURCES = BucketIter.c BucketList.c CatalogTables.c Chunk.c \
	ChunkIterator.c Condition.c Connection.c Database.c DatabaseManagerImpl.c DataType.c \
	Debug.c FieldList.c Index.c LockListIter.c LockManager.c Logger.c Mutex.c os.c \
	PageInfo.c PredicateImpl.c SessionImpl.c TableDef.c TableImpl.c Transaction.c \
	TransactionManager.c TupleIterator.c UserManagerImpl.c HashIndex.c
bin_PROGRAMS = csqlserver
csqlserver_SOURCES = Server.c 
csqlserver_LDADD = $(top_builddir)/src/server/libcsql.la -lrt -lpthread -lcrypt
