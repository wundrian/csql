/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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

    if (fullTableScan == scanType_)
    {
        cIter = new ChunkIterator();
        *cIter = ((Chunk*)chunkPtr_)->getIterator();
    }else if (hashIndexScan == scanType_)
    {
        SingleFieldHashIndexInfo *hIdxInfo = (SingleFieldHashIndexInfo*)info;
        PredicateImpl *predImpl = (PredicateImpl*) pred_;
        void *keyPtr = (void*)predImpl->valPtrForIndexField(hIdxInfo->fldName);

        int bucketNo = HashIndex::computeHashBucket(hIdxInfo->type,
                        keyPtr, hIdxInfo->noOfBuckets);
        Bucket *bucket =  &(hIdxInfo->buckets[bucketNo]);
        int ret = bucket->mutex_.tryLock();
        if (ret != 0)
        {
            printError(ErrLockTimeOut,"Unable to acquire bucket Mutex for bucket %d",bucketNo);
            return ErrLockTimeOut;
        }
        HashIndexNode *head = (HashIndexNode*) bucket->bucketList_;
        if (!head)
        {
            bIter = NULL ;
            return OK;
        }
        bIter  = new BucketIter(head);
        bucket->mutex_.releaseLock();
    }
    return OK;
}


void* TupleIterator::next()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    void *tuple = NULL;
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
                predImpl->setTuple(tuple);
                predImpl->evaluate(result);
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
            tuple = node->ptrToTuple_;
            if(NULL == tuple) return NULL;
            predImpl->setTuple(tuple);
            predImpl->evaluate(result);
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
        }
    scanType_ = unknownScan;
    return OK;
}
