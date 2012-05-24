INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
lib_LTLIBRARIES = libcsqlstorage.la
libcsqlstorage_la_LDFLAGS = -avoid-version -module -lrt
libcsqlstorage_la_SOURCES = BucketIter.cxx \
	Chunk.cxx VarChunk.cxx BucketList.cxx\
	CatalogTables.cxx CatalogTablesIdx.cxx CatalogTablesFk.cxx \
	ChunkIterator.cxx Condition.cxx Connection.cxx Database.cxx \
	DatabaseManagerImpl.cxx DbMgrTableImpl.cxx DbMgrIndexImpl.cxx \
	DbMgrFkImpl.cxx DatabaseRecovery.cxx  \
	LockManager.cxx UserManagerImpl.cxx \
	LockTable.cxx  SessionImpl.cxx Transaction.cxx \
	PageInfo.cxx Process.cxx \
	TransactionManager.cxx \
	../relational/table/TableDef.cxx \
	../relational/table/PredicateImpl.cxx \
	../relational/table/PredicateEvalImpl.cxx \
	../relational/table/TableImpl.cxx \
	../relational/table/TableImplModifyOp.cxx \
	../relational/table/TableImplReadOp.cxx \
	../relational/table/TupleIterator.cxx \
	../relational/table/FieldList.cxx \
	../relational/index/Index.cxx \
	../relational/index/HashIndex.cxx \
	../relational/index/TreeIndex.cxx \
	../relational/index/TreeNode.cxx \
	../relational/index/TrieIndex.cxx \
	../relational/index/TreeIter.cxx \
	../relational/relop/AggTableImpl.cxx \
	../relational/relop/JoinTableImpl.cxx \
	../relational/relop/Expression.cxx \
	../relational/relop/OrderTableImpl.cxx \
	../relational/relop/OrderByTree.cxx
