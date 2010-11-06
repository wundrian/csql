echo Create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 float, f8 double,f9 Date, f10 Time, f11 Timestamp);
Statement Executed
echo create index hashidxtinyvar on t1(f1, f6);
Statement Executed
echo create index hashidxsmallvar on t1(f2, f6);
Statement Executed
echo create index hashidxvarint on t1(f6, f3);
Statement Executed
echo create index hashidxvarbig on t1(f6, f4);
Statement Executed
echo create index hashidxcharvar on t1(f5, f6);
Statement Executed
echo create index hashidxvardate on t1(f6, f9);
Statement Executed
echo create index hashidxvartime on t1(f6, f10);
Statement Executed
echo create index hashidxvarfloat on t1(f6, f7);
Statement execute failed with error -16
echo create index hashidxvardouble on t1(f6, f8);
Statement execute failed with error -16
echo create index hashidxvartimestamp on t1(f6, f11);
Statement execute failed with error -16
<Table Information of all tables>
  <TableInfo> 
    <TableName> t1 </TableName>
      <FieldInfo>
        <FieldName> f1 </FieldName>
        <Type> 4 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f2 </FieldName>
        <Type> 3 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f3 </FieldName>
        <Type> 0 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f4 </FieldName>
        <Type> 2 </Type>
        <Length> 8 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f5 </FieldName>
        <Type> 30 </Type>
        <Length> 12 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f6 </FieldName>
        <Type> 32 </Type>
        <Length> 12 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f7 </FieldName>
        <Type> 11 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f8 </FieldName>
        <Type> 10 </Type>
        <Length> 8 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f9 </FieldName>
        <Type> 20 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f10 </FieldName>
        <Type> 21 </Type>
        <Length> 4 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
      <FieldInfo>
        <FieldName> f11 </FieldName>
        <Type> 22 </Type>
        <Length> 8 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
    <Index Name> hashidxtinyvar </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f1 </Field Name> 
        <Field Name> f6 </Field Name> 
    <Index Name> hashidxsmallvar </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f2 </Field Name> 
        <Field Name> f6 </Field Name> 
    <Index Name> hashidxvarint </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f6 </Field Name> 
        <Field Name> f3 </Field Name> 
    <Index Name> hashidxvarbig </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f6 </Field Name> 
        <Field Name> f4 </Field Name> 
    <Index Name> hashidxcharvar </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f5 </Field Name> 
        <Field Name> f6 </Field Name> 
    <Index Name> hashidxvardate </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f6 </Field Name> 
        <Field Name> f9 </Field Name> 
    <Index Name> hashidxvartime </Index Name> 
        <Index Type> Hash Index </Index Type> 
        <Table Name> t1 </Table Name> 
        <Field Name> f6 </Field Name> 
        <Field Name> f10 </Field Name> 
</Index Information of all Indexs>
Statement Executed
