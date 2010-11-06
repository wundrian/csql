Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	emp10.eno	emp10.ename	emp10.job	emp10.mgrno	
---------------------------------------------------------
	1	ALLEN	SALES	4	
	2	PITTER	IT	3	
	3	JACK	MKTING	1	
	4	TOM	CLERK	1	
	5	HARRY	MANAGER	5	
	
echo SELECT emp.ename,mgr.ename FROM emp10 as emp,emp10 as mgr WHERE emp.mgrno=mgr.eno;
---------------------------------------------------------
	emp.ename	mgr.ename	
---------------------------------------------------------
	ALLEN	TOM	
	PITTER	JACK	
	JACK	ALLEN	
	TOM	ALLEN	
	HARRY	HARRY	
	
Statement Executed
