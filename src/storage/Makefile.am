INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsql.la
libcsql_la_LDFLAGS = -avoid-version -module
libcsql_la_SOURCES = BucketIter.cxx TreeIter.cxx BucketList.cxx \
	Chunk.cxx VarChunk.cxx \
	TableConfig.cxx \
	CatalogTables.cxx CatalogTablesIdx.cxx CatalogTablesFk.cxx \
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx \
	DatabaseManagerImpl.cxx DatabaseRecovery.cxx  \
	FieldList.cxx Index.cxx LockManager.cxx \
	LockTable.cxx  \
	PageInfo.cxx PredicateImpl.cxx SessionImpl.cxx \
	TableDef.cxx TableImpl.cxx Transaction.cxx \
	TransactionManager.cxx TupleIterator.cxx \
	UserManagerImpl.cxx HashIndex.cxx TreeIndex.cxx TrieIndex.cxx \
	Process.cxx AggTableImpl.cxx JoinTableImpl.cxx \
	Expression.cxx OrderTableImpl.cxx OrderByTree.cxx
