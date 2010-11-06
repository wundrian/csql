echo Create table t1(f1 int, f2 varchar(15) default 'CSQL');
Statement Executed
echo insert into t1 values(1,'Lakshya1');
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,'Lakshya3');
Statement Executed: Rows Affected = 1
echo insert into t1 values(4,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1(f1) values(5);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	Lakshya1	
	2	NULL	
	3	Lakshya3	
	4	NULL	
	5	CSQL	
	
echo select * from t1 where f2='CSQL';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	5	CSQL	
	
echo update t1 set f2=NULL where f2='Lakshya3';
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	Lakshya1	
	2	NULL	
	3	NULL	
	4	NULL	
	5	CSQL	
	
echo select * from t1 where f2 IS NULL;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2	NULL	
	3	NULL	
	4	NULL	
	
<Table Information of all tables>
  <TableInfo> 
    <TableName> t1 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 32 </Type>
        <Length> 16 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 1 </Default>
        <DefaultValue> CSQL </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
</Index Information of all Indexs>
Statement Executed
