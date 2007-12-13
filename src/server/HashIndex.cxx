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

unsigned int HashIndex::computeHashBucket(DataType type, void *key, int noOfBuckets)

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
        case typeBinary:
        {
            //TODO
        }
        default:
        {
            break;
        }
    }
    return -1;
}

//TODO::composite keys are not supported currently
DbRetVal HashIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple)
{
    SingleFieldHashIndexInfo *info = (SingleFieldHashIndexInfo*) indInfo;
    INDEX *iptr = (INDEX*)indexPtr;

    DataType type = info->type;
    char *name = info->fldName;
    int offset  = info->offset;
    int noOfBuckets = info->noOfBuckets;
    int length = info->length;

    printDebug(DM_HashIndex, "Inserting hash index node for field %s", name);
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();
    void *keyPtr =(void*)((char*)tuple + offset);

    int bucketNo = computeHashBucket(type,
                        keyPtr, noOfBuckets);
    printDebug(DM_HashIndex, "HashIndex insert bucketno %d", bucketNo);
    Bucket *bucket =  &(buckets[bucketNo]);

    int ret = bucket->mutex_.getLock();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
        return ErrLockTimeOut;
    }
    HashIndexNode *head = (HashIndexNode*) bucket->bucketList_;
    if (info->isUnique)
    {
        BucketList list(head); 
        BucketIter iter = list.getIterator();
        HashIndexNode *node;
        void *bucketTuple;
        printDebug(DM_HashIndex, "HashIndex insert Checking for unique");
        while((node = iter.next()) != NULL)
        {
            bucketTuple = node->ptrToTuple_;
            if (AllDataType::compareVal((void*)((char*)bucketTuple +offset), 
                   (void*)((char*)tuple +offset), OpEquals,type, length)) 
            {
                printError(ErrUnique, "Unique key violation");
                bucket->mutex_.releaseLock();
                return ErrUnique;
            }
        }
    }

    printDebug(DM_HashIndex, "HashIndex insert into bucket list");
    if (!head)
    {
        printDebug(DM_HashIndex, "HashIndex insert head is empty");
        HashIndexNode *firstNode= (HashIndexNode*)(((Chunk*)iptr->hashNodeChunk_)->allocate(tbl->db_));
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        bucket->bucketList_ = (HashIndexNode*)firstNode;
        printDebug(DM_HashIndex, "HashIndex insert new node %x in empty bucket", bucket->bucketList_);
    }
    else
    {
        BucketList list(head);
        list.insert((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr, tuple);
    }
    DbRetVal rc = tr->appendLogicalUndoLog(tbl->sysDB_, InsertHashIndexOperation,
                                tuple, sizeof(void*), indexPtr);
    if (rc !=OK)
    {
        //TODO::remove it from the bucketlist
    }

    bucket->mutex_.releaseLock();
    return rc;
}


//TODO::composite keys are not supported currently
DbRetVal HashIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple)
{
    INDEX *iptr = (INDEX*)indexPtr;

    SingleFieldHashIndexInfo *info = (SingleFieldHashIndexInfo*) indInfo;
    DataType type = info->type;
    char *name = info->fldName;
    int offset  = info->offset;
    int noOfBuckets = info->noOfBuckets;

    printDebug(DM_HashIndex, "Removing hash index node for field %s", name);
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    Bucket* buckets = (Bucket*)citer.nextElement();
    void *keyPtr =(void*)((char*)tuple + offset);

    int bucket = HashIndex::computeHashBucket(type, keyPtr, noOfBuckets);

    Bucket *bucket1 = &buckets[bucket];

    int ret = bucket1->mutex_.getLock();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucket);
        return ErrLockTimeOut;
    }
    HashIndexNode *head = (HashIndexNode*) bucket1->bucketList_;

    if (!head) { printError(ErrNotExists, "Hash index does not exist:should never happen\n"); return ErrNotExists; }
    BucketList list(head);
    printDebug(DM_HashIndex, "Removing hash index node from head %x", head);

    DbRetVal rc = list.remove((Chunk*)iptr->hashNodeChunk_, tbl->db_, keyPtr);
    if (SplCase == rc) 
    { 
       printDebug(DM_HashIndex, "Removing hash index node from head with only none node"); 
       bucket1->bucketList_ = 0; 
    }
    rc =tr->appendLogicalUndoLog(tbl->sysDB_, DeleteHashIndexOperation,
                                tuple, sizeof(void*), indexPtr);
    if (rc !=OK)
    {
        //TODO::add it back to the bucketlist
    }
    bucket1->mutex_.releaseLock();
    return rc;
}

//TODO::composite keys are not supported currently
DbRetVal HashIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple)
{
    INDEX *iptr = (INDEX*)indexPtr;

    SingleFieldHashIndexInfo *info = (SingleFieldHashIndexInfo*) indInfo;
    DataType type = info->type;
    char *name = info->fldName;
    int offset  = info->offset;
    int noOfBuckets = info->noOfBuckets;

    printDebug(DM_HashIndex, "Updating hash index node for field %s", name);

    //check whether the index key is updated or not
    //if it is not updated return from here
    void *keyPtr =(void*)((char*)tuple + offset);
    //Iterate through the bind list and check
    FieldIterator fldIter = tbl->fldList_.getIterator();
    void *newKey = NULL;
    while (fldIter.hasElement())
    {
        FieldDef def = fldIter.nextElement();
        if (0 == strcmp(def.fldName_, name))
        {
            if (NULL == def.bindVal_)
                return OK;
            bool result = AllDataType::compareVal(keyPtr, def.bindVal_,
                                OpEquals, def.type_, def.length_);
            if (result) return OK; else newKey = def.bindVal_;
        }
    }
    printDebug(DM_HashIndex, "Updating hash index node: Key value is updated");

    if (newKey == NULL)
    { 
        printError(ErrSysInternal,"Internal Error:: newKey is Null");
        return ErrSysInternal;
    }
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);

    Bucket* buckets = (Bucket*)citer.nextElement();

    //remove the node whose key is updated
    int bucketNo = computeHashBucket(type,
                        keyPtr, noOfBuckets);
    printDebug(DM_HashIndex, "Updating hash index node: Bucket for old value is %d", bucketNo);
    Bucket *bucket = &buckets[bucketNo];

    //it may run into deadlock, when two threads updates tuples which falls in
    //same buckets.So take both the mutex one after another, which will reduce the
    //deadlock window.
    int ret = bucket->mutex_.getLock();
    if (ret != 0)
    {
        printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
        return ErrLockTimeOut;
    }
    //insert node for the updated key value
    int newBucketNo = computeHashBucket(type,
                        newKey, noOfBuckets);
    printDebug(DM_HashIndex, "Updating hash index node: Bucket for new value is %d", newBucketNo);

    Bucket *bucket1 = &buckets[newBucketNo];
    bucket1->mutex_.getLock();
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
    }
    else
    {
        printError(ErrSysInternal,"Update: Bucket list is null");
        return ErrSysInternal;
    }
    DbRetVal rc = tr->appendLogicalUndoLog(tbl->sysDB_, DeleteHashIndexOperation,
                                tuple, sizeof(void*), indexPtr);
    if (rc !=OK) 
    { 
        //TODO::add it back to the bucket list
        bucket1->mutex_.releaseLock();
        bucket->mutex_.releaseLock();
        return rc; 
    }
    HashIndexNode *head2 = (HashIndexNode*) bucket1->bucketList_;
    //Note:: the tuple will be in the same address location
    //so not changing the keyptr and tuple during append
    //only bucket where this node resides will only change
    //if the index key is updated.
    if (!head2)
    {
        HashIndexNode *firstNode= (HashIndexNode*)(((Chunk*)iptr->hashNodeChunk_)->allocate(tbl->db_));
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
    }
    rc = tr->appendLogicalUndoLog(tbl->sysDB_, InsertHashIndexOperation,
                                tuple, sizeof(void*), indexPtr);
    if (rc !=OK)
    {
        //TODO::revert back the changes:delete and add the node + remove the logical undo log 
        //of the  DeleteHashIndexOperation
    } 
    bucket1->mutex_.releaseLock();
    bucket->mutex_.releaseLock();
    return rc;
}
