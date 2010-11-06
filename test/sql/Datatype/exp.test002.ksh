echo Create table t1( f1 int, f2 varchar(15) NOT NULL);
Statement Executed
Statement Executed: Rows Affected = 1
Statement execute failed with error -22
Statement Executed: Rows Affected = 1
Statement execute failed with error -22
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	Lakshya1	
	3	Lakshya3	
	5	Lakshya5	
	
echo update t1 set f2=NULL where f1<=3;
Statement prepare failed with error -22
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	Lakshya1	
	3	Lakshya3	
	5	Lakshya5	
	
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
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
</Index Information of all Indexs>
Statement Executed
