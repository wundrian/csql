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
DbRetVal TupleIterator::setPlan()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    if (treeIndexScan == scanType_)
    {
        HashIndexInfo *hIdxInfo = (HashIndexInfo*)info;
        FieldIterator iter = hIdxInfo->idxFldList.getIterator();
        if(iter.hasElement())
        {
           FieldDef *def = iter.nextElement();
           keyPtr = (char*)predImpl->opAndValPtrForIndexField(def->fldName_, hIdxInfo->isUnique,op);
        }
        CINDEX *iptr = (CINDEX*) hIdxInfo->indexPtr;
        TreeNode *fstNode=(TreeNode *)iptr->hashNodeChunk_;
        if(fstNode!=NULL){
            TreeNode *start = (TreeNode *)*((char**)((char*)fstNode + sizeof(TreeNode)));
            tIter->set(start,(TreeNode*)iptr->hashNodeChunk_,procSlot);
        }else{
            tIter->set(NULL,(TreeNode*)iptr->hashNodeChunk_,procSlot);
        }
        tIter->setSearchKey(keyPtr, op);
        if (hIdxInfo->isUnique) tIter->setUnique();
        tIter->setFldOffset(hIdxInfo->fldOffset);
        tIter->setTypeLength(hIdxInfo->type, hIdxInfo->compLength);
    }
    if(predImpl) predImpl->setIfNoLeftRight();
    return OK;
}
DbRetVal TupleIterator::open()
{
    PredicateImpl *predImpl = (PredicateImpl*) pred_;
    if (fullTableScan == scanType_)
    {
        *cIter = ((Chunk*)chunkPtr_)->getIterator();
    }else if (hashIndexScan == scanType_)
    {
        HashIndexInfo *hIdxInfo = (HashIndexInfo*)info;
        FieldIterator iter = hIdxInfo->idxFldList.getIterator();
        int offset = hIdxInfo->fldOffset;
        if(!keyBuffer) keyBuffer = (char*) malloc(hIdxInfo->compLength);
        void *keyPtr = NULL;
        char *keyBufferIter = keyBuffer;
        while(iter.hasElement())
        {
           FieldDef *def = iter.nextElement();
           //keyPtr = (void*)predImpl->valPtrForIndexField(def->fldName_,hIdxInfo->isUnique);
           //TODO::PRABA::the below opt should be done for hash also
           keyPtr = (void*)predImpl->valPtrForIndexField(def->fldName_,false);
           if (NULL == keyPtr) {
               printError(ErrSysFatal, "Fatal: Should not come here");
               continue;
           }
           AllDataType::copyVal(keyBufferIter, keyPtr, def->type_, def->length_); 
           keyBufferIter = keyBufferIter + def->length_;
        }
        int bucketNo = HashIndex::computeHashBucket(hIdxInfo->type,
                      keyBuffer, hIdxInfo->noOfBuckets, hIdxInfo->compLength);
        Bucket *bucket =  &(hIdxInfo->buckets[bucketNo]);
        IndexNode *head = (IndexNode*) bucket->bucketList_;
        if (!head)
        {
            bIter->setHead(head);
            return OK;
        }
        printDebug(DM_HashIndex, "open:head for bucket %x is :%x", bucket, head);
        bIter->setHead(head);
    }else if (trieIndexScan == scanType_)
    {
        HashIndexInfo *indInfo = (HashIndexInfo*)info;
        char hashValue[TRIE_MAX_LENGTH];
        FieldIterator iter = indInfo->idxFldList.getIterator();
        FieldDef *def = iter.nextElement();
        void* keyPtr = (void*)predImpl->valPtrForIndexField(def->fldName_,false);
        if (NULL == keyPtr) {
           printError(ErrSysFatal, "Fatal: Should not come here");
        }
        TrieIndex::computeHashValues(indInfo->type, keyPtr, hashValue, indInfo->compLength);
        TrieNode* start = (TrieNode*)indInfo->buckets;
        if (NULL == start)
        {
           bIter->setHead(NULL);
           return OK;
        }
        char **next = NULL;
        int cnt  = 0;
        while(-1 != hashValue[cnt+1]) {
            next = (char**)&(start->next_[hashValue[cnt]]);
            if (! *next)
            {
                printError(ErrNotFound, "No trie node found \n");
                return ErrNotFound;
            }
            //traverse till the end
            start = (TrieNode*) *next;
            cnt++;
        }
        void **ptr = (void**)&(start->head_[hashValue[cnt]]);
        IndexNode *head = (IndexNode*) *ptr;
        if (!head)
        {
            bIter->setHead(head);
            return OK;
        }
        bIter->setHead(head);

    }else if (treeIndexScan == scanType_)
    {
        HashIndexInfo *hIdxInfo = (HashIndexInfo*)info;
        CINDEX *iptr = (CINDEX*) hIdxInfo->indexPtr;
        TreeNode *fstNode=(TreeNode *)iptr->hashNodeChunk_;
        if(fstNode!=NULL){
            TreeNode *start = (TreeNode *)*((char**)((char*)fstNode + sizeof(TreeNode)));        
            tIter->set(start,(TreeNode*)iptr->hashNodeChunk_,procSlot);
        }else{
            tIter->set(NULL,(TreeNode*)iptr->hashNodeChunk_,procSlot);
        }
        if (hIdxInfo->isUnique) tIter->setUnique();
    }
    isClosed = false;
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
        if (NULL == pred_)
        {
            //no predicates
            return cIter->nextElement();
        }
        else
        {
            int offset=0;
            bool isLargeSizeAllocator = cIter->isLargeSize();
            void *val = predImpl->getValIfPointLookupOnInt(offset);
            char *tup = NULL;
            if (val != NULL) {
               int value = *(int*)val;
               if (isLargeSizeAllocator) {
                   while (true)
                   {
                      tup = (char*)cIter->nextElement();
                      if(NULL == tup) return NULL;
                      if (value == *((int*)(tup+offset))) break;
                   }
                   return tup;
                }else {
                   tup = (char*)cIter->nextElementIntMatch(value, offset);
                   return tup;
                }
            }
            val = predImpl->getVal1IfBetweenOnInt(offset);
            if (val != NULL) {
              void *val2 = predImpl->getVal2IfBetweenOnInt(offset);
              int value1 = *(int*)val;
              int value2 = *(int*)val2;
              while (true)
              {
                if(isLargeSizeAllocator) 
                   tup = (char*)cIter->nextElement();
                else
                   tup = (char*)cIter->nextElementInt();
                if(NULL == tup) return NULL;
                if (*((int*)(tup+offset)) >= value1 &&
                    *((int*)(tup+offset)) <= value2) break;
              }
              return tup;
            }
      
            //evaluate till it succeeds
            bool result = false;
            while (!result)
            {
                if(isLargeSizeAllocator) 
                    tuple = cIter->nextElement();
                else
                    tuple = cIter->nextElementInt();
                if(NULL == tuple) return NULL;
                //predImpl->setTuple(tuple);
                printDebug(DM_Table, "Evaluating the predicate from fullTableScan");
                predImpl->evaluateForTable(result, (char*)tuple);
            }
        }
    }else if (hashIndexScan == scanType_ || trieIndexScan == scanType_)
    {
        //evaluate till it succeeds
        bool result = false;
        while (!result)
        {
            IndexNode *node = bIter->next();
            if (node == NULL) return NULL;
            printDebug(DM_HashIndex, "next: returned IndexNode: %x", node);
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
           if(!result && (isBetween || isPointLook))  tIter->nextNode();
        }
    }
    return tuple;
}

DbRetVal TupleIterator::close()
{
    if (isClosed) return OK;
    reset();
    isClosed = true;
    return OK;
}

void TupleIterator::reset()
{
    DbRetVal rv = OK;
    if (scanType_ == fullTableScan) {
        if (cIter) *cIter = ((Chunk*)chunkPtr_)->getIterator(); 
    }
    else if (scanType_ == hashIndexScan) { 
        if(bIter) bIter->reset();
    }
    else if (scanType_ == treeIndexScan) { if(tIter) tIter->reset(); }
}    
