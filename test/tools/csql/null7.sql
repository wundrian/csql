echo update t1 set f1=f1+NULL;
update t1 set f1=f1+NULL;
echo commit;
commit;
echo select * from t1;
select * from t1;
echo drop table t1;
drop table t1;

