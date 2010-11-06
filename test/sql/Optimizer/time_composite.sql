echo create table t1(f1 time, f2 time, f3 time, f4 time);
create table t1(f1 time, f2 time, f3 time, f4 time);
echo create index hashtimef1f2f3 on t1(f2,f3,f1) hash;
create index hashtimef1f2f3 on t1(f2,f3,f1) hash;
echo explain plan select * from t1;
explain plan select * from t1;
echo explain plan select * from t1 where f1 = '03:03:03';
explain plan select * from t1 where f1 = '03:03:03';
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03';
explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03';
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and f3='03:03:03';
explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and f3='03:03:03';
echo explain plan select * from t1 where f1 = '03:03:03' or f2='03:03:03' or f3='03:03:03';
explain plan select * from t1 where f1 = '03:03:03' or f2='03:03:03' or f3='03:03:03';
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' or f3='03:03:03';
explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' or f3='03:03:03';
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and not(f3='03:03:03');
explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and not(f3='03:03:03');
echo explain plan select * from t1 where f1 in('03:03:03','03:03:03','03:03:03') and f2='03:03:03' and not(f3='03:03:03');
explain plan select * from t1 where f1 in('03:03:03','03:03:03','03:03:03') and f2='03:03:03' and not(f3='03:03:03');
echo explain plan select * from t1 where f1 in('03:03:03','05:05:05','06:06:06') and (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
explain plan select * from t1 where f1 in('03:03:03','05:05:05','06:06:06') and (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
echo explain plan select * from t1 where f1 in('05:05:05','06:06:06','03:03:03') or (f2 between '03:03:03' and '03:03:03') or not(f3='03:03:03');
explain plan select * from t1 where f1 in('05:05:05','06:06:06','03:03:03') or (f2 between '03:03:03' and '03:03:03') or not(f3='03:03:03');
echo explain plan select * from t1 where f1 in('03:03:03','06:06:06','05:05:05') or (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
explain plan select * from t1 where f1 in('03:03:03','06:06:06','05:05:05') or (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
