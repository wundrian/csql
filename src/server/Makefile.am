INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsql.la
libcsql_la_LDFLAGS = -avoid-version -module
libcsql_la_SOURCES = BucketIter.cxx BucketList.cxx CatalogTables.cxx Chunk.cxx \
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx DatabaseManagerImpl.cxx DataType.cxx \
	Debug.cxx FieldList.cxx Index.cxx LockListIter.cxx LockManager.cxx Logger.cxx Mutex.cxx os.cxx \
	PageInfo.cxx PredicateImpl.cxx SessionImpl.cxx TableDef.cxx TableImpl.cxx Transaction.cxx \
	TransactionManager.cxx TupleIterator.cxx UserManagerImpl.cxx HashIndex.cxx Config.cxx Process.cxx
#bin_PROGRAMS = csqlserver
#csqlserver_SOURCES = Server.cxx 
#csqlserver_LDADD = $(top_builddir)/src/cache/libcacheload.la \
#	$(top_builddir)/src/server/.libs/libcsql -lrt -lpthread -lcrypt
