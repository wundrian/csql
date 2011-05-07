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

//converts the given value into 0 to TRIE_SIZE 
//value could be 0-9, A-Z, a-z and special chars
char hashString(char value)
{
    if (value > 47 && value <58) return value - 48;
    else if (value > 64 && value <91 ) return (value - 64)/3;
    else if (value > 96 && value <123) return (value - 96)/3;
    //for all special and other chars return 9
    return 9;
}

void TrieIndex::computeHashValues(DataType type, void *key, char *in, int length)
{
    if (typeInt == type ) {
        int val = *(int*)key;
        sprintf(in, "%d", val);
        int i=0;
        while (in[i] != '\0')
        {
            in[i] = hashString(in[i]);
            printDebug(DM_TrieIndex, "Hash Value Pos:%d Hash:%d\n", i, in[i]);
            i++;
        }
        in[i] = -1;
    }else if (typeLongLong == type) {
        long val = *(long*)key;
        sprintf(in, "%lld", val);
        int i=0;
        while (in[i] != '\0')
        {
            in[i] = hashString(in[i]);
            printDebug(DM_TrieIndex, "Hash Value Pos:%d Hash:%d\n", i, in[i]);
            i++;
        }
        in[i] = -1;
    }else if (typeString == type || typeVarchar == type) {
        char *val = (char*) key;
        int i=0;
        while (*val != '\0')
        {
            in[i] = hashString(*val);
            printDebug(DM_TrieIndex, "Hash Value Pos:%d Hash:%d\n", i, in[i]);
            val++;
            i++;
        }
        in[i] = (char)-1;
    }else
        printError(ErrSysFatal,"Type not supported for trie hashing\n");
    return ;
}
/*
bool HashIndex::checkForUniqueKey(IndexNode *head, HashIndexInfo *info, void *tuple)
{
    return false;
}
*/

DbRetVal TrieIndex::insert(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
{
    DbRetVal rv = OK;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    char hashValue[TRIE_MAX_LENGTH];
    void *keyPtr =(void*)((char*)tuple + info->fldOffset);
    //for varchar ptr to value is stored in tuple
    if (info->type == typeVarchar) keyPtr = (void *) *(long *) keyPtr;
    computeHashValues(info->type, keyPtr, hashValue, info->compLength);
    Chunk *hIdxNodeChunk = (Chunk*)iptr->hashNodeChunk_;
    Chunk *chunk = (Chunk*) iptr->chunkPtr_;
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    TrieNode* start = (TrieNode*)citer.nextElement();
    //if(start) displayAll(start);
    int cnt=0;
    if (NULL == start) {
        //first value is inserted into the trie index
        start = (TrieNode*) chunk->tryAllocate(tbl->db_, &rv);
        if (NULL == start) {
            printError(ErrSysInternal, "Could not allocate trie node %d\n", rv);
            return rv;
        }
    }
    char **prev = NULL;
    while(-1 != hashValue[cnt+1]) {
        prev = (char**)&(start->next_[hashValue[cnt]]);
        if (*prev)
        {
            start = (TrieNode*) *prev;
            cnt++;
            continue;
        }
        //allocate trie node
        TrieNode *newNode = (TrieNode*) chunk->tryAllocate(tbl->db_, &rv);
        if (NULL == newNode) {
            printError(ErrSysInternal, "Could not allocate trie node %d\n", rv);
            return rv;
        }
        //set the previous trie node ptr to this node
        *prev = (char*)newNode; 
        start = newNode;
        cnt++;
    }
    void **ptr = (void**)&(start->head_[hashValue[cnt]]);
    rv = addToValueList(tbl->db_, ptr, hIdxNodeChunk, tuple, keyPtr);
    if (OK != rv) return rv;
    
    //create logical undo log
    TrieUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.bucket_ = NULL;
    hInfo.tuple_ = tuple;
    hInfo.keyPtr_ = keyPtr;

    if (!loadFlag) {
        rv = tr->appendLogicalTrieUndoLog(tbl->sysDB_, InsertTrieIndexOperation, &hInfo, sizeof(TrieUndoLogInfo));
         //TODO:: if it fails need to remove the element from the bucket
    }
    return rv;
}
DbRetVal TrieIndex::addToValueList(Database *db, void **ptr, Chunk *hIdxNodeChunk, void *tuple, void *keyPtr)
{
    IndexNode *head = (IndexNode*) *ptr;
    printDebug(DM_TrieIndex, "TrieIndex insert into bucket list");
    DbRetVal rv = OK;
    if (!head)
    {
        printDebug(DM_TrieIndex, "TrieIndex insert head is empty");
        IndexNode *firstNode= NULL;
        firstNode= (IndexNode*) hIdxNodeChunk->tryAllocate(db, &rv);
        if (firstNode == NULL){
            printError(rv, "Unable to allocate index node for Trie index after retry");
            return rv;
        }
        firstNode->ptrToKey_ = keyPtr;
        firstNode->ptrToTuple_ = tuple;
        firstNode->next_ = NULL;
        if (0 != Mutex::CASL((long*)ptr, 0, (long)firstNode)) {
            printError(ErrLockTimeOut, "Trie Index bucket lock timeout.. retry");
            hIdxNodeChunk->free(db, firstNode);
            return ErrLockTimeOut;
        }
        printDebug(DM_TrieIndex, "TrieIndex insert new node %x in empty bucket", head);
    }
    else
    {
        BucketList list(head);
        rv = list.insert(hIdxNodeChunk, db, keyPtr, tuple);
        if (rv !=OK) {
            printError(rv, "unable to insert into Trie bucketlist rv:%d", rv);
            return rv;
        }
    }
    return OK;
}

DbRetVal TrieIndex::removeFromValueList(Database *db, void **ptr, Chunk *hIdxNodeChunk, void *tuple, void *keyPtr)
{
    IndexNode *head = (IndexNode*) *ptr;
    printDebug(DM_TrieIndex, "TrieIndex remove from bucket list");
    DbRetVal rv = OK;
    if (!head)
    {
        printError(rv, "Trie value list head is empty");
        return rv;
    }
    else
    {
        BucketList list(head);
        rv = list.remove(hIdxNodeChunk, db, keyPtr);
        if (SplCase == rv)
        {
            rv = OK;
            printDebug(DM_TrieIndex, "Removing trie index node from head ");
            if (0 != Mutex::CASL((long*)ptr,
                (long)head, (long)list.getBucketListHead())) {
               printError(ErrSysFatal, "Lock time out for trie bucket. retry\n");
               return ErrLockTimeOut;
             }
        }
        if (rv !=OK) {
            printError(rv, "unable to remove from Trie bucketlist rv:%d", rv);
            return rv;
        }
    }
    return OK;

}

DbRetVal TrieIndex::remove(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
{
    DbRetVal rv = OK;
    HashIndexInfo *info = (HashIndexInfo*) indInfo;
    CINDEX *iptr = (CINDEX*)indexPtr;
    char hashValue[TRIE_MAX_LENGTH];
    void *keyPtr =(void*)((char*)tuple + info->fldOffset);
    Chunk *hIdxNodeChunk = (Chunk*)iptr->hashNodeChunk_;
    //for varchar ptr to value is stored in tuple
    if (info->type == typeVarchar) keyPtr = (void *) *(long *) keyPtr;
    computeHashValues(info->type, keyPtr, hashValue, info->compLength);
    ChunkIterator citer = CatalogTableINDEX::getIterator(indexPtr);
    TrieNode* start = (TrieNode*)citer.nextElement();
    int cnt=0;
    if (NULL == start) {
        printError(ErrSysInternal, "No trie nodes found %d\n", rv);
        return rv;
    }
    char **iter = NULL;
    while(-1 != hashValue[cnt+1]) {
        iter = (char**)&(start->next_[hashValue[cnt]]);
        if (! *iter)
        {
            printError(ErrNotFound, "No trie node found %d\n", rv);
            return ErrNotFound;
        }
        //traverse till the end
        start = (TrieNode*) *iter;
        cnt++;
    }
    void **ptr = (void**)&(start->head_[hashValue[cnt]]);
    rv = removeFromValueList(tbl->db_, ptr, hIdxNodeChunk, tuple, keyPtr);
    if (OK != rv) return rv;

    //create logical undo log
    TrieUndoLogInfo hInfo;
    hInfo.metaData_ = tbl->db_->getMetaDataPtr();
    hInfo.bucket_ = NULL;
    hInfo.tuple_ = tuple;
    hInfo.keyPtr_ = keyPtr;

    if (!loadFlag) {
        rv = tr->appendLogicalTrieUndoLog(tbl->sysDB_, DeleteTrieIndexOperation, &hInfo, sizeof(TrieUndoLogInfo));
         //TODO:: if it fails need to remove the element from the bucket
    }
    return rv;
}

DbRetVal TrieIndex::update(TableImpl *tbl, Transaction *tr, void *indexPtr, IndexInfo *indInfo, void *tuple, bool loadFlag)
{
    DbRetVal rv = OK;
    return rv;
}

DbRetVal TrieIndex::insertLogicalUndoLog(Database *sysdb, void *data)
{
    TrieUndoLogInfo *info = (TrieUndoLogInfo *) data;
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
    return OK;
}

DbRetVal TrieIndex::deleteLogicalUndoLog(Database *sysdb, void *data)
{
    TrieUndoLogInfo *info = (TrieUndoLogInfo *) data;
    Chunk *hChunk = (Chunk *) info->hChunk_;
    Database db;
    db.setMetaDataPtr((DatabaseMetaData *)info->metaData_);
    db.setProcSlot(sysdb->procSlot);
    IndexNode *head = (IndexNode *)((Bucket *)info->bucket_)->bucketList_;
    BucketList list(head);
    DbRetVal rc = list.remove(hChunk, &db, info->keyPtr_);
    if (SplCase == rc) {
     ;//TODO
    }else if (rc != OK) {
         printError(ErrLockTimeOut, "Unable to remove hash index node");
         return ErrLockTimeOut;
    }
    return OK;
}
void TrieIndex::displayAll(TrieNode *start, int level)
{
   printTrieNode(start, level);
   level++;
   for (int i=0; i < TRIE_SIZE; i++)
   {
       if (start->next_[i]) displayAll(start->next_[i], level);
   }
}
void TrieIndex::printTrieNode(TrieNode *node, int level)
{
    printf("Trie %x Level %d child:", node, level);
    for (int i=0; i < TRIE_SIZE; i++)
    {
        printf("%x ", node->next_[i]);
    }
    printf("bucket:", node);
    for (int i=0; i < TRIE_SIZE; i++)
    {
        printf("%x ", node->head_[i]);
        if ( node->head_[i]) {
            printf("{ ");
            BucketList list(node->head_[i]);
            list.print();
            printf("} ");
        }
    }
    printf("\n");
}
