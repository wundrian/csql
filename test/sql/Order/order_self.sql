echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno;
SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno;
echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid;
SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid;
echo SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid, b.ename DESC;
SELECT a.empid, a.ename, b.ename FROM emp as a, emp as b WHERE a.empid=b.mgrno ORDER BY a.empid, b.ename DESC;
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname;
SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname;
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename;
SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename;
echo SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename, b.empid DESC;
SELECT a.ename, b.ename FROM emp as a, emp as b WHERE a.ename=b.mgrname ORDER BY a.ename, b.empid DESC;
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances;
SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances;
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic;
SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic;
echo SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic DESC, b.ename DESC;
SELECT a.ename, b.ename, a.basic FROM emp as a, emp as b WHERE a.basic=b.allowances ORDER BY a.basic DESC, b.ename DESC;
echo SELECT a.ename, b.ename, b.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date;
SELECT a.ename, b.ename, b.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date;
echo SELECT a.ename, b.ename, a.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date;
SELECT a.ename, b.ename, a.mgr_date FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date;
echo SELECT a.ename, b.ename, a.join_date, b.join_date, a.basic, b.basic, a.empid, b.empid  FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date DESC;
SELECT a.ename, b.ename, a.join_date, b.join_date, a.basic, b.basic, a.empid, b.empid  FROM emp as a, emp as b WHERE a.mgr_date=b.join_date ORDER BY a.mgr_date DESC;
