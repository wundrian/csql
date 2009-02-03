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
#include<Table.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<Debug.h>
#include<TableImpl.h>
#include<PredicateImpl.h>
DbRetVal TupleIterator::open()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    if (fullTableScan == scanType_)
    {
        cIter = new ChunkIterator();
        *cIter = ((Chunk*)chunkPtr_)->getIterator();
    }else if (hashIndexScan == scanType_)
    {
        HashIndexInfo *hIdxInfo = (HashIndexInfo*)info;
        bool isPtr = false;
        FieldIterator iter = hIdxInfo->idxFldList.getIterator();
        char *keyBuffer;
        int offset = hIdxInfo->fldOffset;
        keyBuffer = (char*) malloc(hIdxInfo->compLength);
        void *keyStartBuffer = (void*) keyBuffer, *keyPtr;
        while(iter.hasElement())
        {
           FieldDef *def = iter.nextElement();
           keyPtr = (void*)predImpl->valPtrForIndexField(def->fldName_);
           AllDataType::copyVal(keyBuffer, keyPtr, def->type_, def->length_); 
           keyBuffer = keyBuffer + def->length_;
        }
        int bucketNo = 0;
        if (hIdxInfo->type == typeComposite) 
            bucketNo = HashIndex::computeHashBucket(hIdxInfo->type,
                      (char *)keyStartBuffer, hIdxInfo->noOfBuckets, hIdxInfo->compLength);
        else bucketNo = HashIndex::computeHashBucket(hIdxInfo->type,
                      keyStartBuffer, hIdxInfo->noOfBuckets, hIdxInfo->compLength);
        free(keyStartBuffer);
        Bucket *bucket =  &(hIdxInfo->buckets[bucketNo]);
        int ret = bucket->mutex_.getLock(procSlot);
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
            return ErrLockTimeOut;
        }
        HashIndexNode *head = (HashIndexNode*) bucket->bucketList_;
        if (!head)
        {
            bucket->mutex_.releaseLock(procSlot);
            bIter = NULL ;
            return OK;
        }
        printDebug(DM_HashIndex, "open:head for bucket %x is :%x", bucket, head);
        bIter  = new BucketIter(head);
        bucket->mutex_.releaseLock(procSlot);
    }else if (treeIndexScan == scanType_)
    {
        HashIndexInfo *hIdxInfo = (HashIndexInfo*)info;
        bool isPtr = false;
        FieldIterator iter = hIdxInfo->idxFldList.getIterator();
        void *keyPtr; ComparisionOp op;
        if(iter.hasElement())
        {
           FieldDef *def = iter.nextElement();
           keyPtr = (void*)predImpl->valPtrForIndexField(def->fldName_);
           op = predImpl->opForIndexField(def->fldName_);
           //TODO::remove this predicate term as it is pushed to tree iter
        }
        CINDEX *iptr = (CINDEX*) hIdxInfo->indexPtr;
        tIter = new TreeIter((TreeNode*)iptr->hashNodeChunk_);
        tIter->setSearchKey(keyPtr, op);
        tIter->setFldOffset(hIdxInfo->fldOffset);
        tIter->setTypeLength(hIdxInfo->type, hIdxInfo->compLength);
    }
    if(predImpl) predImpl->setIfNoLeftRight();
    return OK;
}

//not returing previous tuple for all iterators and for tree iterator.
//it just decrements the nodeOffset for tree iterator.
void* TupleIterator::prev()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    void *tuple = NULL;
    if (treeIndexScan == scanType_)
    {
        if (NULL == tIter) return NULL;
        tuple = tIter->prev();
        predImpl->setTuple(tuple);
        if(NULL == tuple) {
            printDebug(DM_HashIndex, "prev::tuple is null");
        }
        //TODO::evaluate as it is done in next() before returning
    }
    return tuple;
}

void* TupleIterator::next()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    void *tuple = NULL;
    DbRetVal rv = OK;
    if (fullTableScan == scanType_)
    {

        if (NULL == pred_ )
        {
            //no predicates
            return cIter->nextElement();
        }
        else
        {
            //evaluate till it succeeds
            bool result = false;
            while (!result)
            {
                tuple = cIter->nextElement();
                if(NULL == tuple) return NULL;
                //predImpl->setTuple(tuple);
                printDebug(DM_Table, "Evaluating the predicate from fullTableScan");
                predImpl->evaluateForTable(result, (char*)tuple);
            }
        }
    }else if (hashIndexScan == scanType_)
    {
        if (NULL == bIter)
        {
            //if there are no nodes in bucket bIter will be null
            return NULL;
        }
        //evaluate till it succeeds
        bool result = false;
        while (!result)
        {
            HashIndexNode *node = bIter->next();
            if (node == NULL) return NULL;
            printDebug(DM_HashIndex, "next: returned HashIndexNode: %x", node);
            tuple = node->ptrToTuple_;
            if(NULL == tuple) {
                printDebug(DM_HashIndex, "next::tuple is null");
                return NULL;
           }

            //if (!predImpl->isSingleTerm()) {
               printDebug(DM_HashIndex, "next: predicate has more than single term");
               //predImpl->setTuple(tuple);
               printDebug(DM_Table, "Evaluating the predicate from hashIndexScan: has more than one term");
               predImpl->evaluateForTable(result, (char*)tuple);
            //} 
            //else 
            //    return tuple;
        }

    }else if (treeIndexScan == scanType_)
    {
        if (NULL == tIter) return NULL;
        bool result = false;
        while (!result)
        {
            tuple = tIter->next();
            if(NULL == tuple) {
                printDebug(DM_HashIndex, "next::tuple is null");
                return NULL;
           }
           //predImpl->setTuple(tuple);
           predImpl->evaluateForTable(result, (char*)tuple);
           if(!result && (isBetInvolved() || isPointLookInvolved()))  tIter->nextNode();
        }
    }
    return tuple;
}

DbRetVal TupleIterator::close()
{
    if (scanType_ == fullTableScan)
    {
        delete cIter;
        cIter = NULL;
    } else if (scanType_ == hashIndexScan)
    {
            delete bIter;
            bIter = NULL;
    } else if (scanType_ == treeIndexScan)
    {
        delete tIter;
        tIter = NULL;
    }

    scanType_ = unknownScan;
    return OK;
}

void TupleIterator::reset()
{
    DbRetVal rv = OK;
    if (scanType_ == fullTableScan) *cIter = ((Chunk*)chunkPtr_)->getIterator();
    else if (scanType_ == hashIndexScan) if(bIter) bIter->reset();
    else if (scanType_ == treeIndexScan) if(tIter) tIter->reset(); 
}    
