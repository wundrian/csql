echo CREATE TABLE t1(f1 int,f2 int);
Statement Executed
echo CREATE INDEX idx1 on t1(f1);
Statement Executed
echo SET AUTOCOMMIT OFF;
AUTOCOMMIT Mode is set to OFF
echo INSERT INTO t1 VALUES(1,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,30);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(4,40);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(5,50);
Statement Executed: Rows Affected = 1
echo COMMIT;
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 116 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 65540 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 24 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 4 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TransHasTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 12 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 5 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UndoLogTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 0 </SizeOfDataNodes> 
                <Allocation Type> VariableSizeAllocator </Allocation Type>
        <Chunk Id> 10 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > DatabaseTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 84 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 92 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 144 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 104 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 17 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 76 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 18 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 101 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 5 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 102 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > idx1 </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 32292 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 103 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > idx1 </ChunkName> 
                <TotalDataNodes> 5 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
echo SET AUTOCOMMIT OFF;
AUTOCOMMIT Mode is set to OFF
echo INSERT INTO t1 VALUES(6,60);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(7,70);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(8,80);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(9,90);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(10,100);
Statement Executed: Rows Affected = 1
echo ROLLBACK;
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 3 </TotalDataNodes> 
                <SizeOfDataNodes> 116 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 65540 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 24 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 4 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TransHasTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 12 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 5 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UndoLogTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 0 </SizeOfDataNodes> 
                <Allocation Type> VariableSizeAllocator </Allocation Type>
        <Chunk Id> 10 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > DatabaseTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 84 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 92 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 144 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 132 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 104 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 17 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 76 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 18 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > ForeignKeyFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 101 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 5 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 102 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > idx1 </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 32292 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 103 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > idx1 </ChunkName> 
                <TotalDataNodes> 5 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
Statement Executed
