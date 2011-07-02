echo create table t1 (f1 varchar(10), f2 smallint);
Statement Executed
echo create table t2 (f1 varchar(10), f2 smallint);
Statement Executed
echo create index idx1 on t1(f1) tree;
Statement execute failed with error -16
echo create index idx2 on t2(f1) tree unique;
Statement execute failed with error -16
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
</Index Information of all Indexs>
Statement Executed
Statement Executed
