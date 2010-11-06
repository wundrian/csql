Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	emp.empid	emp.ename	emp.basic	emp.join_date	emp.mgrno	emp.mgrname	emp.allowances	emp.mgr_date	
---------------------------------------------------------
	7	SUMAN	7500.000000	2007/2/2 1:1:1.0	7	SUMAN	7500.000000	2007/2/2 1:1:1.0	
	1	JAMES	7000.000000	2007/2/2 1:1:1.0	3	PITER	8000.000000	2007/2/3 1:1:1.0	
	4	HARRY	8500.000000	2007/2/6 1:1:1.0	3	PITER	8000.000000	2007/2/3 1:1:1.0	
	2	LALIT	7500.000000	2007/2/1 1:1:1.0	1	JAMES	7000.000000	2007/2/2 1:1:1.0	
	3	PITER	8000.000000	2007/2/3 1:1:1.0	2	LALIT	7500.000000	2007/2/1 1:1:1.0	
	5	MAHES	6500.000000	2007/2/4 1:1:1.0	4	HARRY	8500.000000	2007/2/6 1:1:1.0	
	8	LATIF	7000.000000	2007/2/1 1:1:1.0	3	PITER	8000.000000	2007/2/3 1:1:1.0	
	6	RAMAN	6000.000000	2007/2/5 1:1:1.0	4	HARRY	8500.000000	2007/2/6 1:1:1.0	
	
echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno;
---------------------------------------------------------
	a.empid	a.ename	b.ename	
---------------------------------------------------------
	7	SUMAN	SUMAN	
	1	JAMES	LALIT	
	4	HARRY	MAHES	
	4	HARRY	RAMAN	
	2	LALIT	PITER	
	3	PITER	JAMES	
	3	PITER	HARRY	
	3	PITER	LATIF	
	
echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid;
---------------------------------------------------------
	a.empid	a.ename	b.ename	
---------------------------------------------------------
	1	JAMES	LALIT	
	2	LALIT	PITER	
	3	PITER	LATIF	
	3	PITER	HARRY	
	3	PITER	JAMES	
	4	HARRY	RAMAN	
	4	HARRY	MAHES	
	7	SUMAN	SUMAN	
	
echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid, b.ename DESC;
---------------------------------------------------------
	a.empid	a.ename	b.ename	
---------------------------------------------------------
	1	JAMES	LALIT	
	2	LALIT	PITER	
	3	PITER	LATIF	
	3	PITER	JAMES	
	3	PITER	HARRY	
	4	HARRY	RAMAN	
	4	HARRY	MAHES	
	7	SUMAN	SUMAN	
	
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname;
---------------------------------------------------------
	a.ename	b.ename	
---------------------------------------------------------
	SUMAN	SUMAN	
	JAMES	LALIT	
	HARRY	MAHES	
	HARRY	RAMAN	
	LALIT	PITER	
	PITER	JAMES	
	PITER	HARRY	
	PITER	LATIF	
	
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename;
---------------------------------------------------------
	a.ename	b.ename	
---------------------------------------------------------
	HARRY	RAMAN	
	HARRY	MAHES	
	JAMES	LALIT	
	LALIT	PITER	
	PITER	LATIF	
	PITER	HARRY	
	PITER	JAMES	
	SUMAN	SUMAN	
	
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename, b.empid DESC;
---------------------------------------------------------
	a.ename	b.ename	
---------------------------------------------------------
	HARRY	RAMAN	
	HARRY	MAHES	
	JAMES	LALIT	
	LALIT	PITER	
	PITER	LATIF	
	PITER	HARRY	
	PITER	JAMES	
	SUMAN	SUMAN	
	
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances;
---------------------------------------------------------
	a.ename	b.ename	a.basic	
---------------------------------------------------------
	SUMAN	SUMAN	7500.000000	
	SUMAN	PITER	7500.000000	
	JAMES	LALIT	7000.000000	
	HARRY	MAHES	8500.000000	
	HARRY	RAMAN	8500.000000	
	LALIT	SUMAN	7500.000000	
	LALIT	PITER	7500.000000	
	PITER	JAMES	8000.000000	
	PITER	HARRY	8000.000000	
	PITER	LATIF	8000.000000	
	LATIF	LALIT	7000.000000	
	
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic;
---------------------------------------------------------
	a.ename	b.ename	a.basic	
---------------------------------------------------------
	LATIF	LALIT	7000.000000	
	JAMES	LALIT	7000.000000	
	LALIT	PITER	7500.000000	
	LALIT	SUMAN	7500.000000	
	SUMAN	PITER	7500.000000	
	SUMAN	SUMAN	7500.000000	
	PITER	LATIF	8000.000000	
	PITER	HARRY	8000.000000	
	PITER	JAMES	8000.000000	
	HARRY	RAMAN	8500.000000	
	HARRY	MAHES	8500.000000	
	
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic DESC, b.ename DESC;
---------------------------------------------------------
	a.ename	b.ename	a.basic	
---------------------------------------------------------
	HARRY	RAMAN	8500.000000	
	HARRY	MAHES	8500.000000	
	PITER	LATIF	8000.000000	
	PITER	JAMES	8000.000000	
	PITER	HARRY	8000.000000	
	LALIT	SUMAN	7500.000000	
	SUMAN	SUMAN	7500.000000	
	LALIT	PITER	7500.000000	
	SUMAN	PITER	7500.000000	
	LATIF	LALIT	7000.000000	
	JAMES	LALIT	7000.000000	
	
echo SELECT a.ename, b.ename, b.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date;
---------------------------------------------------------
	a.ename	b.ename	b.mgr_date	
---------------------------------------------------------
	SUMAN	SUMAN	2007/2/2 1:1:1.0	
	SUMAN	JAMES	2007/2/3 1:1:1.0	
	JAMES	PITER	2007/2/1 1:1:1.0	
	HARRY	PITER	2007/2/1 1:1:1.0	
	LALIT	SUMAN	2007/2/2 1:1:1.0	
	LALIT	JAMES	2007/2/3 1:1:1.0	
	PITER	LALIT	2007/2/2 1:1:1.0	
	PITER	LATIF	2007/2/3 1:1:1.0	
	MAHES	HARRY	2007/2/3 1:1:1.0	
	LATIF	PITER	2007/2/1 1:1:1.0	
	RAMAN	HARRY	2007/2/3 1:1:1.0	
	
echo SELECT a.ename, b.ename, a.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date;
---------------------------------------------------------
	a.ename	b.ename	a.mgr_date	
---------------------------------------------------------
	PITER	LATIF	2007/2/1 1:1:1.0	
	PITER	LALIT	2007/2/1 1:1:1.0	
	LALIT	JAMES	2007/2/2 1:1:1.0	
	LALIT	SUMAN	2007/2/2 1:1:1.0	
	SUMAN	JAMES	2007/2/2 1:1:1.0	
	SUMAN	SUMAN	2007/2/2 1:1:1.0	
	LATIF	PITER	2007/2/3 1:1:1.0	
	HARRY	PITER	2007/2/3 1:1:1.0	
	JAMES	PITER	2007/2/3 1:1:1.0	
	RAMAN	HARRY	2007/2/6 1:1:1.0	
	MAHES	HARRY	2007/2/6 1:1:1.0	
	
echo SELECT a.ename, b.ename, a.join_date, b.join_date, a.basic, b.basic, a.empid, b.empid  FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date DESC;
---------------------------------------------------------
	a.ename	b.ename	a.join_date	b.join_date	a.basic	b.basic	a.empid	b.empid	
---------------------------------------------------------
	RAMAN	HARRY	2007/2/5 1:1:1.0	2007/2/6 1:1:1.0	6000.000000	8500.000000	6	4	
	MAHES	HARRY	2007/2/4 1:1:1.0	2007/2/6 1:1:1.0	6500.000000	8500.000000	5	4	
	LATIF	PITER	2007/2/1 1:1:1.0	2007/2/3 1:1:1.0	7000.000000	8000.000000	8	3	
	HARRY	PITER	2007/2/6 1:1:1.0	2007/2/3 1:1:1.0	8500.000000	8000.000000	4	3	
	JAMES	PITER	2007/2/2 1:1:1.0	2007/2/3 1:1:1.0	7000.000000	8000.000000	1	3	
	LALIT	JAMES	2007/2/1 1:1:1.0	2007/2/2 1:1:1.0	7500.000000	7000.000000	2	1	
	LALIT	SUMAN	2007/2/1 1:1:1.0	2007/2/2 1:1:1.0	7500.000000	7500.000000	2	7	
	SUMAN	JAMES	2007/2/2 1:1:1.0	2007/2/2 1:1:1.0	7500.000000	7000.000000	7	1	
	SUMAN	SUMAN	2007/2/2 1:1:1.0	2007/2/2 1:1:1.0	7500.000000	7500.000000	7	7	
	PITER	LATIF	2007/2/3 1:1:1.0	2007/2/1 1:1:1.0	8000.000000	7000.000000	3	8	
	PITER	LALIT	2007/2/3 1:1:1.0	2007/2/1 1:1:1.0	8000.000000	7500.000000	3	2	
	
Statement Executed
