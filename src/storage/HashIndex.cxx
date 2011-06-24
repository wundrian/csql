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
    if (typeInt == type) {
        int val = *(int*)key;
        return val % noOfBuckets;
    }else if (typeString == type || typeVarchar == type) {
        unsigned int val = hashString((char*)key);
        return val % noOfBuckets;
    }else if (typeShort == type) {
        short val = *(short*) key;
        return val % noOfBuckets;
    }else if (typeLong == type) {
        long val = *(long*) key;
        return val % noOfBuckets;
    }else if (typeLongLong == type) {
        long long val = *(long long*) key;
        return val % noOfBuckets;
    }else if (typeByteInt == type) {
        ByteInt val = *(ByteInt*)key;
        return val % noOfBuckets;
    }else if (typeDate == type) {
        int val = *(int*)key;
        return val % noOfBuckets;
    }else if (typeTime == type) {
        int val = *(int*)key;
        return val % noOfBuckets;
    }else if (typeComposite == type) {
        unsigned int val = hashBinary((char*)key, length);
        return val % noOfBuckets;
    }else if (typeBinary == type) {
        unsigned int val = hashBinary((char*)key, length);
        return val % noOfBuckets;
    }else if (typeULong == type) {
        unsigned long val = *(unsigned long*)key;
        return val % noOfBuckets;
    }
    printError(ErrSysFatal,"Type not supported for hashing\n");
    return -1;
}

bool HashIndex::checkForUniqueKey(IndexNode *head, HashIndexInfo *info, void *tuple)
{
    if (!head) return false;
    int offset = info->fldOffset;
    DataType type = info->type;
    BucketList list(head);
    BucketIter iter = list.getIterator();
    IndexNode *node;
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
             FieldDef *def = fldIter.nextElement();
             if (def->type_ != typeVarchar) {
                res = AllDataType::compareVal(
                      (char *)bucketTuple + def->offset_,
                      (char *)tuple + def->offset_,
                      OpEquals, def->type_, def->length_);
             } else {
                char *tvcptr = (char *) *(long *)
                                   ((char *)tuple + def->offset_);
                char *btvcptr = (char *) *(long *)
                                   ((char *)bucketTuple + def->offset_);
                res = AllDataType::compareVal(tvcptr, btvcptr,
                                           OpEquals, def->type_, def->length_);
             }
             if (!res) break;
          }
       }
       else {
          if (type != typeVarchar)
             res = AllDataType::compareVal((void*)((char*)bucketTuple +offset), 
                                  (void*)((char*)tuple +offset), OpEquals,
                                  type, info->compLength);
          else 
             res = AllDataType::compareVal((void*)*(long *)((char*)bucketTuple +offset), 
                                           (void*)*(long *)((char*)tuple +offset), 
                                            OpEquals,type, info->compLength);
       }
       if (res)
       {
          if (type == typeLongLong)
             printError(ErrUnique, "Unique key violation for id:%lld",
                                    *(long long*) ((char*)tuple +offset) );
          else
             printError(ErrUnique, "Unique key violation");
          return true;
       }
    }
    return false;
}

DbRetVal HashIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
{
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    DbRetVal rc = OK;
    int noOfBuckets = info->noOfBuckets;
    int offset = info->fldOffset;
    DataType type = info->type;

    printDebug(DM_HashIndex, "Inserting hash index node for  %s", iptr->indName_);
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();
    void *keyPtr =(void*)((char*)tuple + offset);
    int bucketNo = 0;
    if (type == typeComposite) {
        char *keyBuffer = (char*) malloc(info->compLength);
        memset(keyBuffer, 0, info->compLength);
        void* keyStartBuffer = keyBuffer;
        FieldIterator iter = info->idxFldList.getIterator();
        while(iter.hasElement())
        {
            FieldDef *def = iter.nextElement();
            keyPtr = (char *)tuple + def->offset_;
            if (def->type_ != typeVarchar) {
                AllDataType::copyVal(keyBuffer, keyPtr, def->type_,
                                                                 def->length_);
            } else {
                void *ptr = (void *) *(long *) keyPtr;
                if (ptr)
                    AllDataType::copyVal(keyBuffer, ptr, def->type_, 
                                                                 def->length_);
            }  
            keyBuffer = keyBuffer + AllDataType::size(def->type_,def->length_);
        }
        bucketNo = computeHashBucket(type, keyStartBuffer, noOfBuckets, 
                                                             info->compLength);
        ::free(keyStartBuffer);
    }
    else {
        if (type != typeVarchar)
            bucketNo =
                computeHashBucket(type, keyPtr, noOfBuckets, info->compLength);
        else {
            void *ptr = (void *) *(long *) keyPtr;
            if (ptr) 
                bucketNo = computeHashBucket(type, ptr, noOfBuckets,
                                                             info->compLength);
            else bucketNo = 0;
        } 
    }
    printDebug(DM_HashIndex, "HashIndex insert bucketno %d", bucketNo);
    Bucket *bucket =  &(buckets[bucketNo]);
    HashUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.bucket_ = bucket;
    hInfo.tuple_ = tuple;
    hInfo.hChunk_ = ((CINDEX *)indexPtr)->hashNodeChunk_;
    hInfo.keyPtr_ = keyPtr;

    IndexNode *head = (IndexNode*) bucket->bucketList_;
    if (info->isUnique)
    {
        bool isKeyPresent = checkForUniqueKey(head, info, tuple);
        if (isKeyPresent) return ErrUnique;
    }        
    Chunk *hIdxNodeChunk = (Chunk*)iptr->hashNodeChunk_;
    printDebug(DM_HashIndex, "HashIndex insert into bucket list");
    if (!head)
    {
        printDebug(DM_HashIndex, "HashIndex insert head is empty");
        DbRetVal rv = OK;
        IndexNode *firstNode= NULL; 

        int tries=0;
        int totalTries = Conf::config.getMutexRetries();
        while (tries < totalTries)
        {
            rv = OK;
            firstNode= (IndexNode*) hIdxNodeChunk->allocate(tbl->db_, &rv);
            if (firstNode !=NULL) break;
            if (rv != ErrLockTimeOut)
            {
                printError(rv, "Unable to allocate hash index node");
                return rv;
            }
            tries++;
        }
        if (firstNode == NULL){
            printError(rv, "Unable to allocate hash index node after %d retry", tries);
            return rv;
        }
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        if (0 != Mutex::CASL((long*)&bucket->bucketList_, 0, (long)firstNode)) {
            printError(ErrLockTimeOut, "Hash Index bucket lock timeout.. retry");
            hIdxNodeChunk->free(tbl->db_, firstNode);
            return ErrLockTimeOut; 
        }
       
        printDebug(DM_HashIndex, "HashIndex insert new node %x in empty bucket", bucket->bucketList_);
    }
    else
    {
        BucketList list(head);
        rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
        if (rc !=OK) {
            printError(rc, "unable to insert into bucketlist rv:%d", rc);
            return rc;
        }
        
    }
    if (!loadFlag) {
         rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, InsertHashIndexOperation, &hInfo, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            printError(rc, "Unable to append logical log before rc:%d", rc);
            BucketList list(head);
            DbRetVal rv = list.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
            //bucket->bucketList_ = list.getBucketListHead();
            if (rv == SplCase) {
              printError(ErrWarning, "SplCase occured");
              if (0 != Mutex::CASL((long*)&bucket->bucketList_, 
                     (long)bucket->bucketList_, (long)list.getBucketListHead())) {
                printError(ErrSysFatal, "Double failure, may lead to hash node leak\n");
              }
            }else if (rv !=OK) printError(ErrSysFatal, "double failure on undo log insert followed by hash bucket list remove\n");
        }
    }
    return rc;
}


DbRetVal HashIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
{
    CINDEX *iptr = (CINDEX*)indexPtr;

    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    DataType type = info->type;
    int offset  = info->fldOffset;
    int noOfBuckets = info->noOfBuckets;

    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();

    void *keyPtr =(void*)((char*)tuple + offset);
    int bucket = 0;
    if (type == typeComposite) {
        char *keyBuffer = (char*) malloc(info->compLength);
        memset(keyBuffer, 0, info->compLength);
        void *keyStartBuffer = keyBuffer; 
        FieldIterator iter = info->idxFldList.getIterator();
        while(iter.hasElement())
        {
            FieldDef *def = iter.nextElement();
            keyPtr = (char *)tuple + def->offset_;
            if (def->type_ != typeVarchar) {
                AllDataType::copyVal(keyBuffer, keyPtr, def->type_, 
                                                                 def->length_);
            } else {
                void *ptr = (void *) *(long *) keyPtr;
                if (ptr) 
                    AllDataType::copyVal(keyBuffer, ptr, def->type_, 
                                                                 def->length_);
            }
            keyBuffer = keyBuffer + AllDataType::size(def->type_,def->length_);
        }
        bucket = HashIndex::computeHashBucket(type, keyStartBuffer, noOfBuckets, info->compLength);
        ::free(keyStartBuffer);
    }
    else {
        if (type != typeVarchar)
            bucket = HashIndex::computeHashBucket(type, keyPtr, noOfBuckets,
                                                             info->compLength);
        else {
            void *ptr = (void *) *(long *) keyPtr;
            if (ptr)
                bucket = HashIndex::computeHashBucket(type, ptr, noOfBuckets, 
                                                             info->compLength);
            else bucket = 0;
        }      
    }

    Bucket *bucket1 = &buckets[bucket];
    HashUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.bucket_ = bucket1;
    hInfo.tuple_ = tuple;
    hInfo.hChunk_ = ((CINDEX *)indexPtr)->hashNodeChunk_;
    hInfo.keyPtr_ = keyPtr;
    
    IndexNode *head = (IndexNode*) bucket1->bucketList_;

    if (!head) { printError(ErrNotExists, "Hash index does not exist:should never happen\n"); 
       return ErrNotExists; 
    }
    BucketList list(head);
    printDebug(DM_HashIndex, "Removing hash index node from head %x", head);

    DbRetVal rc = list.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
    if (SplCase == rc) 
    { 
       printDebug(DM_HashIndex, "Removing hash index node from head "); 
       //bucket1->bucketList_ = list.getBucketListHead(); 
       if (0 != Mutex::CASL((long*)&bucket1->bucketList_, 
                (long)head, (long)list.getBucketListHead())) {
           printError(ErrSysFatal, "Lock time out for hash bucket. retry\n");
           return ErrLockTimeOut;
       }
       rc = OK;
    }
    if (!loadFlag) {
        rc =tr->appendLogicalHashUndoLog(tbl->sysDB_, DeleteHashIndexOperation, &hInfo, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
            if (rc !=OK) printError(ErrSysFatal, "double failure on undo log remove followed by hash bucket list insert\n");
            //bucket1->bucketList_ = list.getBucketListHead();
            if (0 != Mutex::CASL((long*)&bucket1->bucketList_, 
                (long)bucket1->bucketList_, (long)list.getBucketListHead())) {
                printError(ErrSysFatal, "Double failure on index insert");
            }
        }
    }
    return rc;
}

DbRetVal HashIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
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
    memset(oldKeyBuffer, 0, info->compLength);
    void *oldKeyStartBuffer = oldKeyBuffer;
    FieldIterator iter = info->idxFldList.getIterator();
    while(iter.hasElement()) {
        FieldDef *def = iter.nextElement();
        keyPtr = (char *)tuple + def->offset_;
        AllDataType::copyVal(oldKeyBuffer, keyPtr, def->type_, def->length_);
        oldKeyBuffer = oldKeyBuffer + AllDataType::size(def->type_, def->length_);
    }

    keyPtr = (void *) kPtr;
    //Iterate through the bind list and check
    FieldIterator idxFldIter = info->idxFldList.getIterator();
    char *keyBindBuffer ;
    if(type==typeBinary) {
        keyBindBuffer = (char*) malloc(2 * info->compLength);
        memset(keyBindBuffer, 0, 2 * info->compLength);
    } else {
        keyBindBuffer = (char*) malloc(info->compLength);
        memset(keyBindBuffer, 0, info->compLength);
    }
    void *keyStartBuffer = (void*) keyBindBuffer;
    bool keyUpdated = false;

    while (idxFldIter.hasElement()) {
        FieldDef *idef = idxFldIter.nextElement();
        FieldIterator fldIter = tbl->fldList_.getIterator();
        while (fldIter.hasElement()) {
            FieldDef *def = fldIter.nextElement();
            if (0 == strcmp(def->fldName_, idef->fldName_)) {
                if (NULL != def->bindVal_) {
                    if(type==typeBinary) {
                        AllDataType::copyVal(keyBindBuffer, def->bindVal_,
                                                   def->type_, 2*def->length_);
                        keyStartBuffer=calloc(1,info->compLength);
                        AllDataType::convertToBinary(keyStartBuffer, keyBindBuffer, typeString, info->compLength);
                        free(keyBindBuffer);
                    } else {
                        AllDataType::copyVal(keyBindBuffer, def->bindVal_,
                                                   def->type_, def->length_);
                        keyBindBuffer = keyBindBuffer + AllDataType::size(def->type_, def->length_);
                    }
                } else {
                     AllDataType::copyVal(keyBindBuffer, (char *) tuple + def->offset_, def->type_, def->length_);
                     keyBindBuffer = keyBindBuffer + AllDataType::size(def->type_, def->length_);
                } 
                keyUpdated = true;
                break;
            }
        }
    }
    if (!keyUpdated) { 
        //printf("DEBUG::key not updated\n");
        free(keyStartBuffer); 
        free(oldKeyStartBuffer);
        return OK; 
    }
    //printf("DEBUG::it is wrong coming here\n");
    bool result = false;
    if (type == typeComposite) 
        result = AllDataType::compareVal(oldKeyStartBuffer, keyStartBuffer,
                                OpEquals, info->type, info->compLength);
    else result = AllDataType::compareVal(keyPtr, keyStartBuffer,
                                OpEquals, info->type, info->compLength);
    if (result) {
        free(keyStartBuffer); 
        free(oldKeyStartBuffer);
        return OK;
    }
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
    hInfo1->metaData_ = tbl->db_->getMetaDataPtr();
    hInfo1->bucket_ = bucket;
    hInfo1->tuple_ = tuple; 
    hInfo1->hChunk_ = ((CINDEX *)indexPtr)->hashNodeChunk_;
    hInfo1->keyPtr_ = keyPtr;
    
    //it may run into deadlock, when two threads updates tuples which falls in
    //same buckets.So take both the mutex one after another, which will reduce the
    //deadlock window.
    int ret = bucket->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        delete hInfo1;
        free(keyStartBuffer); 
        free(oldKeyStartBuffer);
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
        return ErrLockTimeOut;
    }
    //insert node for the updated key value
    int newBucketNo = computeHashBucket(type,
                        keyStartBuffer, noOfBuckets, info->compLength);
    printDebug(DM_HashIndex, "Updating hash index node: Bucket for new value is %d", newBucketNo);

    Bucket *bucket1 = &buckets[newBucketNo];
    HashUndoLogInfo *hInfo2 = new HashUndoLogInfo();
    hInfo2->metaData_ = tbl->db_->getMetaDataPtr();
    hInfo2->bucket_ = bucket;
    hInfo2->tuple_ = tuple;
    hInfo2->hChunk_ = ((CINDEX *)indexPtr)->hashNodeChunk_;
    hInfo2->keyPtr_ = keyPtr; 
    bucket1->mutex_.getLock(tbl->db_->procSlot);
    if (ret != 0)
    {
        delete hInfo1;
        delete hInfo2;
        free(keyStartBuffer); 
        free(oldKeyStartBuffer);
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",newBucketNo);
        return ErrLockTimeOut;
    }

    IndexNode *head1 = (IndexNode*) bucket->bucketList_;
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
        delete hInfo1;
        delete hInfo2;
        free(keyStartBuffer); 
        free(oldKeyStartBuffer);
        return ErrSysInternal;
    }
    DbRetVal rc = OK;
    if (!loadFlag) {
         rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, DeleteHashIndexOperation, hInfo1, sizeof(HashUndoLogInfo));
        if (rc !=OK) 
        { 
            BucketList list((IndexNode*) bucket->bucketList_);
            rc = list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
            if (rc !=OK) printError(ErrSysFatal, "double failure on undo log remove followed by hash bucket list insert\n");
            bucket->bucketList_ = list.getBucketListHead();
            bucket1->mutex_.releaseLock(tbl->db_->procSlot);
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            delete hInfo1;
            delete hInfo2;
            free(keyStartBuffer); 
            free(oldKeyStartBuffer);
            return rc; 
        }
    }
    IndexNode *head2 = (IndexNode*) bucket1->bucketList_;
    //Note:: the tuple will be in the same address location
    //so not changing the keyptr and tuple during append
    //only bucket where this node resides will only change
    //if the index key is updated.
    if (!head2)
    {
        DbRetVal rv = OK;
        IndexNode *firstNode= (IndexNode*)(((Chunk*)iptr->hashNodeChunk_)->allocate(tbl->db_, &rv));
        if (firstNode == NULL)
        { 
            printError(rv, "Error in allocating hash node");
            bucket1->mutex_.releaseLock(tbl->db_->procSlot);
            bucket->mutex_.releaseLock(tbl->db_->procSlot);
            delete hInfo1;
            delete hInfo2;
            free(keyStartBuffer); 
            free(oldKeyStartBuffer);
            return rv;
        }
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        bucket1->bucketList_ = (IndexNode*)firstNode;
        printDebug(DM_HashIndex, "Updating hash index node: Adding new node %x:Head is empty", firstNode);
    }
    else
    {
        BucketList list2(head2);
        printDebug(DM_HashIndex, "Updating hash index node: Adding node to list with head %x", head2);
        list2.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
        bucket1->bucketList_ = list2.getBucketListHead();
    }
    if (!loadFlag) {

        rc = tr->appendLogicalHashUndoLog(tbl->sysDB_, InsertHashIndexOperation, hInfo2, sizeof(HashUndoLogInfo));
        if (rc !=OK)
        {
            //reverting back the changes:delete new node and add the old 
            //node + remove logical undo log of the  DeleteHashIndexOperation
            BucketList list1((IndexNode*) bucket->bucketList_);
            BucketList list2((IndexNode*) bucket1->bucketList_);
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
    delete hInfo1;
    delete hInfo2;
    free(keyStartBuffer); 
    free(oldKeyStartBuffer);
    return rc;
}

//Following three methods are used to undo Logical Hash Indexes
DbRetVal HashIndex::insertLogicalUndoLog(Database *sysdb, void *data)
{
    HashUndoLogInfo *info = (HashUndoLogInfo *) data;
    Chunk *hChunk = (Chunk *) info->hChunk_;
    Database db; 
    db.setMetaDataPtr((DatabaseMetaData *) info->metaData_);
    db.setProcSlot(sysdb->procSlot);
    IndexNode *head = (IndexNode *)((Bucket *)info->bucket_)->bucketList_; 
    BucketList list(head);
    DbRetVal rv = list.insert(hChunk, &db, info->keyPtr_, info->tuple_);
    if (rv != OK)
    {
        printError(ErrLockTimeOut, "Unable to add to bucket..retry\n");
        return ErrLockTimeOut;
    }
    //((Bucket *)info->bucket_)->bucketList_ = list.getBucketListHead();
    if (0 != Mutex::CASL((long*)& (((Bucket *)info->bucket_)->bucketList_),
            (long)(((Bucket *)info->bucket_)->bucketList_),
            (long)list.getBucketListHead())) 
    {
        printError(ErrLockTimeOut, "Unable to add to bucket..retry\n");
        return ErrLockTimeOut;
    }
    return OK;
}

DbRetVal HashIndex::deleteLogicalUndoLog(Database *sysdb, void *data)
{
    HashUndoLogInfo *info = (HashUndoLogInfo *) data;
    Chunk *hChunk = (Chunk *) info->hChunk_;
    Database db; 
    db.setMetaDataPtr((DatabaseMetaData *)info->metaData_);
    db.setProcSlot(sysdb->procSlot);
    IndexNode *head = (IndexNode *)((Bucket *)info->bucket_)->bucketList_;
    BucketList list(head);
    DbRetVal rc = list.remove(hChunk, &db, info->keyPtr_);
    //((Bucket *)info->bucket_)->bucketList_ = list.getBucketListHead();
    if (SplCase == rc) {
        if (0 != Mutex::CASL((long*)& (((Bucket *)info->bucket_)->bucketList_),
            (long)(((Bucket *)info->bucket_)->bucketList_),
            (long)list.getBucketListHead())) 
         {
             printError(ErrLockTimeOut, "Unable to set the head of hash index bucket\n");
             return ErrLockTimeOut;
         }
    }else if (rc != OK) {
         printError(ErrLockTimeOut, "Unable to remove hash index node");
         return ErrLockTimeOut;
    }
    return OK;
}
