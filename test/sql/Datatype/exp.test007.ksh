echo Create table t1(f1 varchar(10), f2 bigint);
Statement Executed
echo alter table t1 rename column f1 to F1;
Statement Executed: Rows Affected = 0
echo rename table t1 to T1;
Statement Executed: Rows Affected = 0
echo show tables;
=============TableNames===================
   T1 
==========================================
<Table Information of all tables>
  <TableInfo> 
    <TableName> T1 </TableName>
      <FieldInfo>
        <FieldName> F1 </FieldName>
        <Type> 32 </Type>
        <Length> 12 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 2 </Type>
        <Length> 8 </Length>
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
