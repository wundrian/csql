echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 IN(12,10,14) OR t1.f1=t2.f1;
SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 IN(12,10,14) OR t1.f1=t2.f1;
echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 BETWEEN 11 AND 14;
SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f1 BETWEEN 11 AND 14;
echo SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f4 >= 'K' AND t1.f4 LIKE 'N%' OR t1.f4 LIKE '%a';
SELECT t1.f1, t1.f4, t2.f1, t2.f4 FROM t1 INNER JOIN t2 ON t1.f4 >= 'K' AND t1.f4 LIKE 'N%' OR t1.f4 LIKE '%a';
