table t1(to be cached) inserted into target db
table t1 cached into csql
table t2(not cached) inserted into target db
table t3 inserted into csql db
csql server is down
csql down: insert into t1(cached table) success
csql down: insert into t2(not cached mysql table) success
csql down: insert into t3(not cached csql table) failed
