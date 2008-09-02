Case 1: With -c option with empty database
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 112 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 49156 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
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
                <SizeOfDataNodes> 148 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 260 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 152 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 196 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 260 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 164 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
  </User Chunk >
</Chunk information>
echo create table and constraints with integer fields;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Case 2: With c  option after table creation:
<Chunk information>
  <System Chunk >
        <Chunk Id> 0 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserChunkTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 112 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 1 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableHashBucketId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 57348 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 2 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableMutexId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 49156 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 3 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > LockTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 20 </SizeOfDataNodes> 
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
                <SizeOfDataNodes> 148 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 11 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > UserTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 260 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 12 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > TableTableId </ChunkName> 
                <TotalDataNodes> 1 </TotalDataNodes> 
                <SizeOfDataNodes> 152 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 13 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > FieldTableId </ChunkName> 
                <TotalDataNodes> 2 </TotalDataNodes> 
                <SizeOfDataNodes> 196 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 14 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > AccessTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 260 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 15 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 164 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
        <Chunk Id> 16 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > IndexFieldTableId </ChunkName> 
                <TotalDataNodes> 0 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </System Chunk >
  <User Chunk >
        <Chunk Id> 117 </Chunk Id> 
                <TotalPages> 1 </TotalPages> 
                <ChunkName > t1 </ChunkName> 
                <TotalDataNodes> 10 </TotalDataNodes> 
                <SizeOfDataNodes> 16 </SizeOfDataNodes> 
                <Allocation Type> FixedSizeAllocator </Allocation Type>
  </User Chunk >
</Chunk information>
