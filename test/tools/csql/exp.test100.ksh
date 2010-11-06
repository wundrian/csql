echo Create table t1(f1 int, f2 char(10000));
Statement Executed
echo insert into t1 values(1,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(3,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(4,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(5,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(6,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(7,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(8,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(9,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo insert into t1 values(10,'wraFASDvgaserrerqwe');
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	wraFASDvgaserrerqwe	
	2	wraFASDvgaserrerqwe	
	3	wraFASDvgaserrerqwe	
	4	wraFASDvgaserrerqwe	
	5	wraFASDvgaserrerqwe	
	6	wraFASDvgaserrerqwe	
	7	wraFASDvgaserrerqwe	
	8	wraFASDvgaserrerqwe	
	9	wraFASDvgaserrerqwe	
	10	wraFASDvgaserrerqwe	
	
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
        <Type> 30 </Type>
        <Length> 10000 </Length>
        <Primary> 0 </Primary>
        <Null> 0 </Null>
        <Default> 0 </Default>
        <DefaultValue>  </DefaultValue>
      </FieldInfo>
  </TableInfo> 
</Table Information of all tables>
<Index Information of all Indexs>
</Index Information of all Indexs>
update t1 set f2='LAKSHYA-CSQL' where f1>=3;
Statement Executed: Rows Affected = 8
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	wraFASDvgaserrerqwe	
	2	wraFASDvgaserrerqwe	
	3	LAKSHYA-CSQL	
	4	LAKSHYA-CSQL	
	5	LAKSHYA-CSQL	
	6	LAKSHYA-CSQL	
	7	LAKSHYA-CSQL	
	8	LAKSHYA-CSQL	
	9	LAKSHYA-CSQL	
	10	LAKSHYA-CSQL	
	
delete from t1 where f1<= 7;
Statement Executed: Rows Affected = 7
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	8	LAKSHYA-CSQL	
	9	LAKSHYA-CSQL	
	10	LAKSHYA-CSQL	
	
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
        <Type> 30 </Type>
        <Length> 10000 </Length>
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
