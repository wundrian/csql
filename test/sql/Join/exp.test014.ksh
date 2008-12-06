select f1,f7 from t2,t1;
OUTPUT : column 'f1' in field list is ambiguous.
select t11.f1,t12.f7 from t13,t11;
OUTPUT : unknown column 't12.f7' in 'field' list
