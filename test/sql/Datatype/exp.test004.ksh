echo Create table t1 (f1 varchar(10), f2 int, primary key(f1));
Statement Executed
echo Create table t2 (f1 varchar(10), f2 bigint, foreign key(f1) references t1(f1));
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo insert into t1 values(NULL,3);
Statement execute failed with error -22
echo insert into t1 values('CSQL2',4);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL1	1	
	CSQL2	2	
	
echo update t1 set f1='CSQL1' where f1='CSQL2';
Statement prepare failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL1	1	
	CSQL2	2	
	
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo insert into t2 values('CSQL3',30);
Statement execute failed with error -34
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	CSQL1	10	
	CSQL2	20	
	
echo delete from t1 where f1='CSQL1';
Statement execute failed with error -35
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	CSQL1	1	
	CSQL2	2	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	CSQL1	10	
	CSQL2	20	
	
<Table Information of all tables>
  <TableInfo> 
    <TableName> t1 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 32 </Type>
        <Length> 11 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 0 </Type>
        <Length> 3 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
  <TableInfo> 
    <TableName> t2 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 32 </Type>
        <Length> 11 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 2 </Type>
        <Length> 7 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
    <Index Name> t1_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
</Index Information of all Indexs>
Statement Executed
Statement Executed
