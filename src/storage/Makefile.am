INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsql.la
libcsql_la_LDFLAGS = -avoid-version -module
libcsql_la_SOURCES = Util.cxx FixedHeapAllocator.cxx VarHeapAllocator.cxx \
	BucketIter.cxx TreeIter.cxx BucketList.cxx Chunk.cxx VarChunk.cxx \
	Config.cxx TableConfig.cxx HashMap.cxx\
	CatalogTables.cxx CatalogTablesIdx.cxx CatalogTablesFk.cxx \
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx \
	DatabaseManagerImpl.cxx DataType.cxx \
	Debug.cxx FieldList.cxx Index.cxx LockManager.cxx \
	LockTable.cxx Logger.cxx Mutex.cxx os.cxx \
	PageInfo.cxx PredicateImpl.cxx SessionImpl.cxx \
	TableDef.cxx TableImpl.cxx Transaction.cxx \
	TransactionManager.cxx TupleIterator.cxx \
	UserManagerImpl.cxx HashIndex.cxx TreeIndex.cxx TrieIndex.cxx \
	Process.cxx AggTableImpl.cxx JoinTableImpl.cxx \
	Expression.cxx OrderTableImpl.cxx OrderByTree.cxx
