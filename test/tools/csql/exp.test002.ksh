echo create table and constraints with integer fields;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	20	
	11	21	
	12	22	
	13	NULL	
	NULL	24	
	
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement execute failed with error -22
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	10	20	
	11	21	
	12	22	
	13	NULL	
	
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement execute failed with error -22
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement prepare failed with error -19
---------------------------------------------------------
	t3.f1	t3.f2	
---------------------------------------------------------
	10	NULL	
	11	21	
	12	22	
	13	NULL	
	100	NULL	
	
Statement Executed
Statement Executed
Statement Executed
