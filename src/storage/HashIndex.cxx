/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<Table.h>
#include<TableImpl.h>
#include<Predicate.h>
#include<PredicateImpl.h>

/* Defines `hashpjw' function by P.J. Weinberger
   [see Aho/Sethi/Ullman, COMPILERS: Principles, Techniques and Tools,
   */

unsigned int hashString(char *strVal)
{
    unsigned int hval, g;
    hval = 0;
    char *str =strVal;
    while (*str != '\0')
    {
        hval <<= 4;
        hval += (unsigned int) *str++;
        g = hval & ((unsigned int) 0xf << (32 - 4));
        if (g != 0)
	    {
	        hval ^= g >> (32 - 8);
	        hval ^= g;
	    }
    }
    return hval;
}

unsigned int hashBinary(char *strVal, int length)
{
    unsigned int hval, g;
    hval = 0;
    char *str =strVal;
    int iter = 0;
    while (iter != length)
    {
        hval <<= 4;
        hval += (unsigned int) *str++;
        g = hval & ((unsigned int) 0xf << (32 - 4));
        if (g != 0)
	    {
	        hval ^= g >> (32 - 8);
	        hval ^= g;
	    }
        iter++;
    }
    return hval;
}

unsigned int HashIndex::computeHashBucket(DataType type, void *key, int noOfBuckets, int length)

{
    switch(type)
    {
        case typeInt:
        {
            int val = *(int*)key;
            return val % noOfBuckets;
            break;
        }
        case typeLong:
        {
            long val = *(long*)key;
            return val % noOfBuckets;
            break;
        }
        case typeULong:
        {
            unsigned long val = *(unsigned long*)key;
            return val % noOfBuckets;
            break;
        }
        case typeLongLong:
        {
            long long val = *(long long*)key;
            return val % noOfBuckets;
            break;
        }
        case typeShort:
        {
            short val = *(short*)key;
            return val % noOfBuckets;
            break;
        }
        case typeByteInt:
        {
            ByteInt val = *(ByteInt*)key;
            return val % noOfBuckets;
            break;
        }
        case typeDate:
        {
            int val = *(int*)key;
            return val % noOfBuckets;
            break;
        }
        case typeTime:
        {
            int val = *(int*)key;
            return val % noOfBuckets;
            break;
        }
        case typeTimeStamp:
        {
            TimeStamp val = *(TimeStamp*)key;
            //TODO return val % noOfBuckets;
            break;
        }
        case typeDouble:
        {
            //TODO
            break;
        }
        case typeFloat:
        {
            //TODO
            break;
        }
        case typeDecimal:
        {
            //TODO::for porting
        }
        case typeString:
        {
            unsigned int val = hashString((char*)key);
            return val % noOfBuckets;
        }
        case typeComposite:
        case typeBinary:
        {
            unsigned int val = hashBinary((char*)key, length);
            return val % noOfBuckets;
        }
        default:
        {
            break;
        }
    }
    return -1;
}

DbRetVal HashIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal rc = OK;
    int noOfBuckets = info->noOfBuckets;
    int offset = info->fldOffset;
    DataType type = info->type;
    char *keyBuffer = (char*) malloc(info->compLength);
    void *keyStartBuffer = keyBuffer, *keyPtr;
    FieldIterator iter = info->idxFldList.getIterator();
    while(iter.hasElement())
    {
        FieldDef def = iter.nextElement();
        keyPtr = (char *)tuple + def.offset_;
        AllDataType::copyVal(keyBuffer, keyPtr, def.type_, def.length_);
        keyBuffer = keyBuffer + AllDataType::size(def.type_, def.length_);
    }

    printDebug(DM_HashIndex, "Inserting hash index node for  %s", iptr->indName_);
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();
    keyPtr =(void*)((char*)tuple + offset);
    int bucketNo = 0;
    if (type == typeComposite)
        bucketNo = computeHashBucket(type, keyStartBuffer, noOfBuckets, info->compLength);
    else 
        bucketNo = computeHashBucket(type, keyPtr, noOfBuckets, info->compLength);
    printDebug(DM_HashIndex, "HashIndex insert bucketno %d", bucketNo);
    Bucket *bucket =  &(buckets[bucketNo]);
    HashUndoLogInfo *hInfo = new HashUndoLogInfo();
    hInfo->tblPtr_ = tbl;
    hInfo->bucket_ = bucket;
    hInfo->tuple_ = tuple;
    hInfo->indexPtr_ = indexPtr;
    hInfo->keyPtr_ = keyPtr;
    int ret = bucket->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
        return ErrLockTimeOut;
    }
    HashIndexNode *head = (HashIndexNode*) bucket->bucketList_;
    if (head && info->isUnique)
    {
        BucketList list(head); 
        BucketIter iter = list.getIterator();
        HashIndexNode *node;
        void *bucketTuple;
        printDebug(DM_HashIndex, "HashIndex insert Checking for unique");
        bool res = false;
        
        while((node = iter.next()) != NULL)
        {
            bucketTuple = node->ptrToTuple_;
            if (type == typeComposite) {
                FieldIterator fldIter = info->idxFldList.getIterator();
                int i = 0;
                while (fldIter.hasElement()) {
                    FieldDef def = fldIter.nextElement();
                    res = AllDataType::compareVal((char *)bucketTuple + def.offset_, (char *)tuple + def.offset_, OpEquals, def.type_, def.length_);
                    if (!res) break;  
                }
            }  
            else res = AllDataType::compareVal((void*)((char*)bucketTuple +offset), (void*)((char*)tuple +offset), OpEquals,type, info->compLength); 
            if (res) 
            {
                printError(ErrUnique, "Unique key violation");
                bucket->mutex_.releaseLock(tbl->db_->procSlot);
                return ErrUnique;
            }
        }
    }
    
    printDebug(DM_HashIndex, "HashIndex insert into bucket list");
    if (!head)
    {
        printDebug(DM_HashIndex, "HashIndex insert head is empty");
        DbRetVal rv = OK;
        HashIndexNode *firstNode= (HashIndexNode*)(((Chunk*)iptr->hashNodeChunk_)->allocate(tbl->db_, &rv));
        if (firstNode == NULL)
        {
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            return rv;
        }
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        bucket->bucketList_ = (HashIndexNode*)firstNode;
        printDebug(DM_HashIndex, "HashIndex insert new node %x in empty bucket", bucket->bucketList_);
    }
    else
    {
        BucketList list(head);
        rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
        if (rc !=OK) {
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            return rc;
        }
        
    }
    if (undoFlag) {
         rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, InsertHashIndexOperation, hInfo, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            BucketList list(head);
            rc = list.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
            if (rc !=OK) printError(ErrSysFatal, "double failure on undo log insert followed by hash bucket list remove\n");
            bucket->bucketList_ = list.getBucketListHead();
        }
    }
    delete hInfo; hInfo = NULL;
    bucket->mutex_.releaseLock(tbl->db_->procSlot);
    return rc;
}


DbRetVal HashIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    CINDEX *iptr = (CINDEX*)indexPtr;

    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    DataType type = info->type;
    int offset  = info->fldOffset;
    int noOfBuckets = info->noOfBuckets;

    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();

    char *keyBuffer = (char*) malloc(info->compLength);
    void *keyStartBuffer = keyBuffer, *keyPtr;
    FieldIterator iter = info->idxFldList.getIterator();
    while(iter.hasElement())
    {
        FieldDef def = iter.nextElement();
        keyPtr = (char *)tuple + def.offset_;
        AllDataType::copyVal(keyBuffer, keyPtr, def.type_, def.length_);
        keyBuffer = keyBuffer + AllDataType::size(def.type_, def.length_);
    }

    keyPtr =(void*)((char*)tuple + offset);
    int bucket = 0;
    if (type == typeComposite)
        bucket = HashIndex::computeHashBucket(type, keyStartBuffer, noOfBuckets, info->compLength);
    else bucket = HashIndex::computeHashBucket(type, keyPtr, noOfBuckets, info->compLength);

    Bucket *bucket1 = &buckets[bucket];
    HashUndoLogInfo *hInfo = new HashUndoLogInfo();
    hInfo->tblPtr_ = tbl;
    hInfo->bucket_ = bucket1;
    hInfo->tuple_ = tuple;
    hInfo->indexPtr_ = indexPtr;
    hInfo->keyPtr_ = keyPtr;
    
    int ret = bucket1->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucket);
        return ErrLockTimeOut;
    }
    HashIndexNode *head = (HashIndexNode*) bucket1->bucketList_;

    if (!head) { printError(ErrNotExists, "Hash index does not exist:should never happen\n"); 
       bucket1->mutex_.releaseLock(tbl->db_->procSlot);
       return ErrNotExists; 
    }
    BucketList list(head);
    printDebug(DM_HashIndex, "Removing hash index node from head %x", head);

    DbRetVal rc = list.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
    if (SplCase == rc) 
    { 
       printDebug(DM_HashIndex, "Removing hash index node from head "); 
       bucket1->bucketList_ = list.getBucketListHead(); 
       rc = OK;
    }
    if (undoFlag) {
        rc =tr->appendLogicalHashUndoLog(tbl->sysDB_, DeleteHashIndexOperation, hInfo, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
            if (rc !=OK) printError(ErrSysFatal, "double failure on undo log remove followed by hash bucket list insert\n");
            bucket1->bucketList_ = list.getBucketListHead();
        }
    }
    bucket1->mutex_.releaseLock(tbl->db_->procSlot);
    
    return rc;
}

DbRetVal HashIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool undoFlag)
{
    CINDEX *iptr = (CINDEX*)indexPtr;

    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    DataType type = info->type;
    int offset  = info->fldOffset;
    int noOfBuckets = info->noOfBuckets;

    //check whether the index key is updated or not
    //if it is not updated return from here
    void *keyPtr =(void*)((char*)tuple + offset);
    char *kPtr= (char*)keyPtr;
    
    //creating old key value buffer for composite primary keys
    char *oldKeyBuffer = (char*) malloc(info->compLength);
    void *oldKeyStartBuffer = oldKeyBuffer;
    FieldIterator iter = info->idxFldList.getIterator();
    while(iter.hasElement()) {
        FieldDef def = iter.nextElement();
        keyPtr = (char *)tuple + def.offset_;
        AllDataType::copyVal(oldKeyBuffer, keyPtr, def.type_, def.length_);
        oldKeyBuffer = oldKeyBuffer + AllDataType::size(def.type_, def.length_);
    }

    keyPtr = (void *) kPtr;
    //Iterate through the bind list and check
    FieldIterator idxFldIter = info->idxFldList.getIterator();
    char *keyBindBuffer ;
    if(type==typeBinary) keyBindBuffer = (char*) malloc(2 * info->compLength);
    else keyBindBuffer = (char*) malloc(info->compLength);
    void *keyStartBuffer = (void*) keyBindBuffer;
    bool keyUpdated = false;

    while (idxFldIter.hasElement()) {
        FieldDef idef = idxFldIter.nextElement();
        FieldIterator fldIter = tbl->fldList_.getIterator();
        while (fldIter.hasElement()) {
            FieldDef def = fldIter.nextElement();
            if (0 == strcmp(def.fldName_, idef.fldName_)) {
                if (NULL != def.bindVal_) {
                    if(type==typeBinary) {
                        AllDataType::copyVal(keyBindBuffer, def.bindVal_,
                                                   def.type_, 2*def.length_);
                        keyStartBuffer=calloc(1,info->compLength);
                        AllDataType::convertToBinary(keyStartBuffer, keyBindBuffer, typeString, info->compLength);
                        free(keyBindBuffer);
                    } else {
                        AllDataType::copyVal(keyBindBuffer, def.bindVal_,
                                                   def.type_, def.length_);
                        keyBindBuffer = keyBindBuffer + AllDataType::size(def.type_, def.length_);
                    }
                } else {
                     AllDataType::copyVal(keyBindBuffer, (char *) tuple + def.offset_, def.type_, def.length_);
                     keyBindBuffer = keyBindBuffer + AllDataType::size(def.type_, def.length_);
                } 
                keyUpdated = true;
                break;
            }
        }
    }
    if (!keyUpdated) { 
        //printf("PRABA::key not updated\n");
        free(keyStartBuffer); 
        return OK; 
    }
    //printf("PRABA::it is wrong coming here\n");
    bool result = false;
    if (type == typeComposite) 
        result = AllDataType::compareVal(oldKeyStartBuffer, keyStartBuffer,
                                OpEquals, info->type, info->compLength);
    else result = AllDataType::compareVal(keyPtr, keyStartBuffer,
                                OpEquals, info->type, info->compLength);
    if (result) return OK; 
    printDebug(DM_HashIndex, "Updating hash index node: Key value is updated");

    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);

    Bucket* buckets = (Bucket*)citer.nextElement();

    //remove the node whose key is updated
    int bucketNo = 0;
    if (type == typeComposite) 
        bucketNo = computeHashBucket(type, oldKeyStartBuffer, noOfBuckets, info->compLength);
    else bucketNo = computeHashBucket(type, keyPtr, noOfBuckets, info->compLength);
    printDebug(DM_HashIndex, "Updating hash index node: Bucket for old value is %d", bucketNo);
    Bucket *bucket = &buckets[bucketNo];
   
    HashUndoLogInfo *hInfo1 = new HashUndoLogInfo();
    hInfo1->tblPtr_ = tbl;
    hInfo1->bucket_ = bucket;
    hInfo1->tuple_ = tuple; 
    hInfo1->indexPtr_ = indexPtr;
    hInfo1->keyPtr_ = keyPtr;
    
    //it may run into deadlock, when two threads updates tuples which falls in
    //same buckets.So take both the mutex one after another, which will reduce the
    //deadlock window.
    int ret = bucket->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
        return ErrLockTimeOut;
    }
    //insert node for the updated key value
    int newBucketNo = computeHashBucket(type,
                        keyStartBuffer, noOfBuckets, info->compLength);
    printDebug(DM_HashIndex, "Updating hash index node: Bucket for new value is %d", newBucketNo);

    Bucket *bucket1 = &buckets[newBucketNo];
    HashUndoLogInfo *hInfo2 = new HashUndoLogInfo();
    hInfo2->tblPtr_ = tbl;
    hInfo2->bucket_ = bucket;
    hInfo2->tuple_ = tuple;
    hInfo2->indexPtr_ = indexPtr;
    hInfo2->keyPtr_ = keyPtr; 
    bucket1->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",newBucketNo);
        return ErrLockTimeOut;
    }

    HashIndexNode *head1 = (HashIndexNode*) bucket->bucketList_;
    if (head1)
    {
        BucketList list1(head1);
        printDebug(DM_HashIndex, "Updating hash index node: Removing node from list with head %x", head1);
        list1.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
        bucket->bucketList_=list1.getBucketListHead();
    }
    else
    {
        printError(ErrSysInternal,"Update: Bucket list is null");
        bucket1->mutex_.releaseLock(tbl->db_->procSlot);
        bucket->mutex_.releaseLock(tbl->db_->procSlot);
        return ErrSysInternal;
    }
    DbRetVal rc = OK;
    if (undoFlag) {
         rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, DeleteHashIndexOperation, hInfo1, sizeof(HashUndoLogInfo));
        if (rc !=OK) 
        { 
            BucketList list((HashIndexNode*) bucket->bucketList_);
            rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
            if (rc !=OK) printError(ErrSysFatal, "double failure on undo log remove followed by hash bucket list insert\n");
            bucket->bucketList_ = list.getBucketListHead();
            bucket1->mutex_.releaseLock(tbl->db_->procSlot);
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            return rc; 
        }
    }
    HashIndexNode *head2 = (HashIndexNode*) bucket1->bucketList_;
    //Note:: the tuple will be in the same address location
    //so not changing the keyptr and tuple during append
    //only bucket where this node resides will only change
    //if the index key is updated.
    if (!head2)
    {
        DbRetVal rv = OK;
        HashIndexNode *firstNode= (HashIndexNode*)(((Chunk*)iptr->hashNodeChunk_)->allocate(tbl->db_, &rv));
        if (firstNode == NULL)
        { 
            printError(rv, "Error in allocating hash node");
            bucket1->mutex_.releaseLock(tbl->db_->procSlot);
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            return rv;
        }
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        bucket1->bucketList_ = (HashIndexNode*)firstNode;
        printDebug(DM_HashIndex, "Updating hash index node: Adding new node %x:Head is empty", firstNode);
    }
    else
    {
        BucketList list2(head2);
        printDebug(DM_HashIndex, "Updating hash index node: Adding node to list with head %x", head2);
        list2.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
        bucket1->bucketList_ = list2.getBucketListHead();
    }
    if (undoFlag) {

        rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, InsertHashIndexOperation, hInfo2, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            //reverting back the changes:delete new node and add the old 
            //node + remove logical undo log of the  DeleteHashIndexOperation
            BucketList list1((HashIndexNode*) bucket->bucketList_);
            BucketList list2((HashIndexNode*) bucket1->bucketList_);
            list1.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
            list2.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
            bucket->bucketList_ = list1.getBucketListHead();
            bucket1->bucketList_ = list2.getBucketListHead();
            UndoLogInfo *logInfo = tr->popUndoLog();
            Chunk *chunk = tbl->sysDB_->getSystemDatabaseChunk(UndoLogTableID);
            chunk->free(tbl->sysDB_, logInfo); 
        } 
    }
    bucket1->mutex_.releaseLock(tbl->db_->procSlot);
    bucket->mutex_.releaseLock(tbl->db_->procSlot);

    return rc;
}

//Following three methods are used to undo Logical Hash Indexes
DbRetVal HashIndex::insertLogicalUndoLog(Database *sysdb, void *data)
{
    HashUndoLogInfo *info = (HashUndoLogInfo *) data;
    TableImpl * tbl = (TableImpl *)info->tblPtr_;
    Chunk *hChunk = (Chunk *) ((CINDEX *)info->indexPtr_)->hashNodeChunk_;
    HashIndexNode *head = (HashIndexNode *)((Bucket *)info->bucket_)->bucketList_; 
    BucketList list(head);
    list.insert(hChunk, tbl->db_, info->keyPtr_, info->tuple_);
    ((Bucket *)info->bucket_)->bucketList_ = list.getBucketListHead();
    return OK;
}

DbRetVal HashIndex::deleteLogicalUndoLog(Database *sysdb, void *data)
{
    HashUndoLogInfo *info = (HashUndoLogInfo *) data;
    TableImpl * tbl = (TableImpl *)info->tblPtr_;
    Chunk *hChunk = (Chunk *) ((CINDEX *)info->indexPtr_)->hashNodeChunk_;
    HashIndexNode *head = (HashIndexNode *)((Bucket *)info->bucket_)->bucketList_;
    BucketList list(head);
    list.remove(hChunk, tbl->db_, info->keyPtr_);
    ((Bucket *)info->bucket_)->bucketList_ = list.getBucketListHead();
    return OK;
}
