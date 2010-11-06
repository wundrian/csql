Case 1: create two table t4,t5 
echo create table t4 (f1 int,f2 int,primary key(f1));
Statement Executed
echo create table t5 (f1 int,f2 int,primary key(f1, f2));
Statement Executed
Case 2: With -l option after for primary flag checking:
<Table Information of all tables>
  <TableInfo> 
    <TableName> t4 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
  <TableInfo> 
    <TableName> t5 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
    <Index Name> t4_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t4 </Table Name> 
        <Field Name> f1 </Field Name> 
    <Index Name> t5_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t5 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f2 </Field Name> 
</Index Information of all Indexs>
case 3 : drop two table 
Statement Executed
Statement Executed
t4 ,t5 table droped 
