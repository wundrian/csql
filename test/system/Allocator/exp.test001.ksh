Table created
Index created for f1
Tables and Indexes are created
Total Tuples inserted is 1
Tuples inserted into table
Case 1: -T option for t1: with 1 tuple
<Table Info> 
  <TableName> t1 </TableName>
  <TupleCount> 1 </TupleCount>
  <PagesUsed> 1 </PagesUsed>
  <SpaceUsed> 32 </SpaceUsed>
  <Indexes> 1 <Indexes>
  <TupleLength> 12 </TupleLength>
  <Fields> 2 </Fields>
  <Indexes>
<IndexName> t1idx1 </IndexName>
  </Indexes>
</Table Info> 
Case 2: -I option for idx1 of t1, with 1 tuple
<Index Info> 
<IndexName> t1idx1 </IndexName>
<Unique> 1 </Unique>
<HashBucket>
  <TotalPages> 1 </TotalPages>
  <TotalBuckets> 1009 </TotalBuckets> 
</HashBucket>
<IndexNodes>
  <TotalPages> 1 </TotalPages>
  <TotalNodes> 1 </TotalNodes>
<IndexNodes>
<Index Info> 
Total Tuples deleted is 1
Tuples deleted from table
Case 3: -T option for t1: after removing 1 tuple
<Table Info> 
  <TableName> t1 </TableName>
  <TupleCount> 0 </TupleCount>
  <PagesUsed> 1 </PagesUsed>
  <SpaceUsed> 16 </SpaceUsed>
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
<HashBucket>
  <TotalPages> 1 </TotalPages>
  <TotalBuckets> 1009 </TotalBuckets> 
</HashBucket>
<IndexNodes>
  <TotalPages> 1 </TotalPages>
  <TotalNodes> 0 </TotalNodes>
<IndexNodes>
<Index Info> 
Table Dropped
Tables and Indexes are dropped
