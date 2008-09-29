echo create table t2 ( f1 int, f2 int, primary key(f1, f2));
Statement Executed
echo create index ind on t2(f1);
Statement Executed
echo create table t1 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
Statement Executed
echo create index indx1 on t1 (f1,f3);
Statement Executed
echo create index indx2 on t1 (f3);
Statement Executed
echo create index indx3 on t1 (f2,f4);
Statement Executed
echo create index indx4 on t1 (f2,f3);
Statement Executed
echo create index indx5 on t1 (f1,f3,f4);
Statement Executed
echo create index indx6 on t1 (f1,f3,f2);
Statement Executed
echo create index indx7 on t1 (f1,f3,f2);
Statement Executed
echo create table t3 (f1 int,f2 char(10),f3 smallint,f4 tinyint,primary key(f1,f2));
Statement Executed
echo create index indx11 on t3 (f1,f3);
Statement Executed
echo create index indx12 on t3 (f3);
Statement Executed
echo create index indx13 on t3 (f2,f4);
Statement Executed
echo create index indx14 on t3 (f2,f3);
Statement Executed
echo create index indx15 on t1 (f1,f3,f4);
Statement Executed
echo create index indx16 on t1 (f1,f3,f2);
Statement Executed
echo create index indx17 on t1 (f1,f3,f2);
Statement Executed
<Table Information of all tables>
  <TableInfo> 
    <TableName> t2 </TableName>
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
  <TableInfo> 
    <TableName> t1 </TableName>
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
        <Type> 30 </Type>
        <Length> 11 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f3 </FieldName>
        <Type> 3 </Type>
        <Length> 2 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f4 </FieldName>
        <Type> 4 </Type>
        <Length> 1 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
  <TableInfo> 
    <TableName> t3 </TableName>
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
        <Type> 30 </Type>
        <Length> 11 </Length>
        <Primary> 1 </Primary>
        <Null> 1 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f3 </FieldName>
        <Type> 3 </Type>
        <Length> 2 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f4 </FieldName>
        <Type> 4 </Type>
        <Length> 1 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
    <Index Name> t2_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t2 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> ind </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t2 </Table Name> 
        <Field Name> f1 </Field Name> 
    <Index Name> t1_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> indx1 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx2 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx3 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f2 </Field Name> 
        <Field Name> f4 </Field Name> 
    <Index Name> indx4 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f2 </Field Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx5 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
        <Field Name> f4 </Field Name> 
    <Index Name> indx6 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> indx7 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f4 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> t3_idx1_Primary </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> indx11 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx12 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx13 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f2 </Field Name> 
        <Field Name> f4 </Field Name> 
    <Index Name> indx14 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f2 </Field Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> indx15 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
        <Field Name> f4 </Field Name> 
    <Index Name> indx16 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f3 </Field Name> 
        <Field Name> f2 </Field Name> 
    <Index Name> indx17 </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t3 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f4 </Field Name> 
        <Field Name> f2 </Field Name> 
</Index Information of all Indexs>
echo drop table t1;
echo drop table t2;
echo drop table t3;
Statement Executed
Statement Executed
Statement Executed
