echo create table t1(f1 varchar(20),f2 varchar(30));
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL1	Lakshya1	
	CSQL2	Lakshya2	
	CSQL3	Lakshya3	
	CSQL4	Lakshya4	
	CSQL5	Lakshya5	
	
echo select * from t1 where f1='CSQL4' or f1='CSQL2';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL2	Lakshya2	
	CSQL4	Lakshya4	
	
echo update t1 set f2='LAKSHYA' where f1='CSQL2' or f1='CSQL4';
Statement Executed: Rows Affected = 2
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL1	Lakshya1	
	CSQL2	LAKSHYA	
	CSQL3	Lakshya3	
	CSQL4	LAKSHYA	
	CSQL5	Lakshya5	
	
echo delete from t1 where f1 in ('CSQL1','CSQL3','CSQL5');
Statement Executed: Rows Affected = 3
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL2	LAKSHYA	
	CSQL4	LAKSHYA	
	
<Table Information of all tables>
  <TableInfo> 
    <TableName> t1 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 32 </Type>
        <Length> 21 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 32 </Type>
        <Length> 30 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
</Index Information of all Indexs>
Statement Executed
