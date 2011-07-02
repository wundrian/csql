echo create table t1 (f1 varchar(10), f2 smallint);
Statement Executed
echo create table t2 (f1 varchar(10), f2 smallint);
Statement Executed
echo create index idx1 on t1(f1) hash;
Statement Executed
echo create index idx2 on t2(f1) hash unique;
Statement Executed
Statement Executed: Rows Affected = 1
echo insert into t2 values('Lakshya1',20);
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	Lakshya1	10	
	
<Table Information of all tables>
  <TableInfo> 
    <TableName> t1 </TableName>
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
        <Type> 3 </Type>
        <Length> 1 </Length>
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
        <Type> 3 </Type>
        <Length> 1 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
    <Index Name> idx1 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
    <Index Name> idx2 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t2 </Table Name> 
        <Field Name> f1 </Field Name> 
</Index Information of all Indexs>
Statement Executed
Statement Executed
