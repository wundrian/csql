table t1(to be cached) inserted into target db
table t1 cached into csql
table t2(not cached) inserted into target db
table t3 inserted into csql db
csql server is down
csql down: select from t1(cached table) success
csql down: select from t2(not cached mysql table) success
csql down: select from t3(not cached csql table) failed
