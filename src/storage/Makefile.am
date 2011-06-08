INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlstorage.la
libcsqlstorage_la_LDFLAGS = -avoid-version -module
libcsqlstorage_la_SOURCES = BucketIter.cxx TreeIter.cxx BucketList.cxx \
	Chunk.cxx VarChunk.cxx \
	CatalogTables.cxx CatalogTablesIdx.cxx CatalogTablesFk.cxx \
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx \
	DatabaseManagerImpl.cxx DbMgrTableImpl.cxx DbMgrIndexImpl.cxx \
	DbMgrFkImpl.cxx DatabaseRecovery.cxx  TableDef.cxx \
	FieldList.cxx Index.cxx LockManager.cxx UserManagerImpl.cxx \
	LockTable.cxx  SessionImpl.cxx Transaction.cxx \
	PageInfo.cxx PredicateImpl.cxx PredicateEvalImpl.cxx \
	TableImpl.cxx TableImplModifyOp.cxx TableImplReadOp.cxx \
	TransactionManager.cxx TupleIterator.cxx \
	HashIndex.cxx TreeIndex.cxx TreeNode.cxx TrieIndex.cxx \
	Process.cxx AggTableImpl.cxx JoinTableImpl.cxx \
	Expression.cxx OrderTableImpl.cxx OrderByTree.cxx
