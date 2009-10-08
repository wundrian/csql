INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsql.la
libcsql_la_LDFLAGS = -version-info 2:4:0 -module
libcsql_la_SOURCES = Util.cxx FixedHeapAllocator.cxx VarHeapAllocator.cxx Config.cxx HashMap.cxx \
	BucketIter.cxx TreeIter.cxx BucketList.cxx CatalogTables.cxx Chunk.cxx TableConfig.cxx\
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx DatabaseManagerImpl.cxx DataType.cxx \
	Debug.cxx FieldList.cxx Index.cxx LockListIter.cxx LockManager.cxx Logger.cxx Mutex.cxx os.cxx \
	PageInfo.cxx PredicateImpl.cxx SessionImpl.cxx TableDef.cxx TableImpl.cxx Transaction.cxx \
	TransactionManager.cxx TupleIterator.cxx UserManagerImpl.cxx HashIndex.cxx TreeIndex.cxx \
	Process.cxx AggTableImpl.cxx JoinTableImpl.cxx Expression.cxx OrderTableImpl.cxx OrderByTree.cxx
