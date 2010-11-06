SELECT * FROM T1;

Tuple value is 2008-03-21 0 Nihar0
Tuple value is 2009-11-10 1 Nihar1
Tuple value is 2008-03-24 2 Nihar2
Tuple value is 2009-11-10 3 Nihar3
Tuple value is 2008-03-21 4 Nihar4
Tuple value is 2009-11-10 5 Nihar5

SELECT * FROM T1 where f1 = '2009-11-10';

Tuple value is 2009-11-10 1 Nihar1
Tuple value is 2009-11-10 3 Nihar3
Tuple value is 2009-11-10 5 Nihar5

SELECT * FROM T1 where f2 >= ? and f3 <= ?;

Tuple value is 2009-11-10 1 Nihar1
Tuple value is 2008-03-24 2 Nihar2
Tuple value is 2009-11-10 3 Nihar3

SELECT * FROM T1 where f1='2009-11-10' and f2 >= ? and f3 <= ?;

Tuple value is 2009-11-10 1 Nihar1
Tuple value is 2009-11-10 3 Nihar3
