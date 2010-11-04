Table created
Index created for f1
Tables and Indexes are created
Total Tuples inserted is 100
Tuples inserted into table
Case 1: -T option for t1: with 100 tuple
<Table Info> 
  <TableName> t1 </TableName>
  <TupleCount> 100 </TupleCount>
  <PagesUsed> 1 </PagesUsed>
  <SpaceUsed> 1616 </SpaceUsed>
  <Indexes> 1 <Indexes>
  <TupleLength> 12 </TupleLength>
  <Fields> 2 </Fields>
  <Indexes>
<IndexName> t1idx1 </IndexName>
  </Indexes>
</Table Info> 
Case 2: -I option for idx1 of t1, with 100 tuple
<Index Info> 
<IndexName> t1idx1 </IndexName>
<Unique> 1 </Unique>
<Type> Hash Index </Type>
<HashBucket>
  <TotalPages> 1 </TotalPages>
  <TotalBuckets> 1009 </TotalBuckets> 
</HashBucket>
<IndexNodes>
  <TotalPages> 1 </TotalPages>
  <TotalNodes> 100 </TotalNodes>
<IndexNodes>
<Index Info> 
Total Tuples deleted is 1
Tuples deleted from table
Case 3: -T option for t1: after removing 1 tuple
<Table Info> 
  <TableName> t1 </TableName>
  <TupleCount> 99 </TupleCount>
  <PagesUsed> 1 </PagesUsed>
  <SpaceUsed> 1600 </SpaceUsed>
  <Indexes> 1 <Indexes>
  <TupleLength> 12 </TupleLength>
  <Fields> 2 </Fields>
  <Indexes>
<IndexName> t1idx1 </IndexName>
  </Indexes>
</Table Info> 
Case 4: -I option for idx1 of t1, after removing 1 tuple
<Index Info> 
<IndexName> t1idx1 </IndexName>
<Unique> 1 </Unique>
<Type> Hash Index </Type>
<HashBucket>
  <TotalPages> 1 </TotalPages>
  <TotalBuckets> 1009 </TotalBuckets> 
</HashBucket>
<IndexNodes>
  <TotalPages> 1 </TotalPages>
  <TotalNodes> 99 </TotalNodes>
<IndexNodes>
<Index Info> 
Table Dropped
Tables and Indexes are dropped
