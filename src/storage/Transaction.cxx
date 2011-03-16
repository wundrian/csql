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
#include<Transaction.h>
#include<Lock.h>
#include<Database.h>
#include<Allocator.h>
#include<CatalogTables.h>
#include<Debug.h>

//Code assumes that only one thread can work on a transaction
DbRetVal Transaction::insertIntoHasList(Database *sysdb, LockHashNode *node)
{
    //allocate lock node
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    DbRetVal rv = OK;
    TransHasNode *hasNode = NULL; //(TransHasNode*)chunk->allocate(sysdb, &rv);
    int tries=0;
    int totalTries = Conf::config.getMutexRetries();
    while (tries < totalTries)
    {
        rv = OK;
        hasNode= (TransHasNode*)chunk->allocate(sysdb, &rv);
        if (hasNode !=NULL) break;
        if (rv != ErrLockTimeOut)
        {
            printError(rv, "Unable to allocate trans has node");
            return rv;
        }
        tries++;
    }
    if (NULL == hasNode)
    {
        printError(rv, "Could not allocate Trans has node after %d retry", tries);
        return rv;
    }
    printDebug(DM_Transaction, "insertIntoHasList new TransHasNode created:%x",
                                                       hasNode);
    hasNode->node_ = node;
    hasNode->next_ = NULL;
    if (NULL == hasLockList_)
    {
        printDebug(DM_Transaction, "hasLockList is null:It is now %x",hasNode);
        hasLockList_ = hasNode;
        return OK;
    }

    TransHasNode *it = hasLockList_;
    while (NULL != it->next_) { it = it->next_; }
    it->next_ = hasNode;
    printDebug(DM_Transaction, "Added to hasLockList at end:%x",it);
    logFinest(Conf::logger, "Added locknode:%x to hasLockList", hasNode->node_);
    return OK;
}

DbRetVal Transaction::removeFromHasList(Database *sysdb, void *tuple)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    TransHasNode *iter = hasLockList_, *prev = hasLockList_;
    if (NULL == iter)
    {
        printError(ErrNotFound, "Fatal:HasList is empty");
        return ErrNotFound;
    }
    while (iter != NULL)
    {
        if (tuple == iter->node_->ptrToTuple_)
        {
            prev->next_ = iter->next_;
            chunk->free(sysdb, iter);
            if (iter == hasLockList_) hasLockList_ = NULL;
            logFinest(Conf::logger, "Removed locknode:%x from hasLockList",  
                                                       iter->node_);
            return OK;
        }
        prev = iter;
        iter = iter->next_;
    }
    printStackTrace();
    printError(ErrNotFound, "Fatal:There is no tuple lock in has list for tuple:%x", tuple);
    //TEMP::for debugging.do not remove
    /*iter=hasLockList_; 
    int cnt=0;
    while (iter != NULL)
    {
        printError(ErrWarning, "Element in hasList: %d %x: %x:%d\n", cnt, iter->node_, iter->node_->ptrToTuple_ , *(int*)iter->node_->ptrToTuple_);
        cnt++;
        iter = iter->next_;
    }*/
    return ErrNotFound;
}


DbRetVal Transaction::releaseAllLocks(LockManager *lockManager_)
{
    Database *sysdb =lockManager_->systemDatabase_;
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    TransHasNode *iter  = hasLockList_, *prev;
    DbRetVal rv = OK;
    while (NULL != iter)
    {
        prev = iter;
        iter = iter->next_;
        printDebug(DM_Transaction, "Releasing lock %x",prev->node_->ptrToTuple_);
        logFinest(Conf::logger, "Releasing lock for tuple:%x",prev->node_->ptrToTuple_);  
        rv = lockManager_->releaseLock(prev->node_->ptrToTuple_);
        chunk->free(sysdb, prev);
    }
    hasLockList_ = NULL;
    return OK;
}
bool Transaction::findInHasList(Database *sysdb, LockHashNode *node)
{
    TransHasNode *iter  = hasLockList_;
    while (NULL != iter)
    {
        if (iter->node_ == node) return true;
        iter = iter->next_;
    }
    return false;
}

DbRetVal Transaction::appendUndoLog(Database *sysdb, OperationType type,
                                               void *data, size_t size)
{
    DbRetVal rv =OK;
    UndoLogInfo *logInfo = createUndoLog(sysdb, type, data, size, &rv);
    if (logInfo == NULL) return rv;
    if (size) os::memcpy((char*)logInfo + sizeof(UndoLogInfo), data, size);
    addAtBegin(logInfo);
    printDebug(DM_Transaction, "creating undo log and append %x optype:%d",
                                               logInfo, type);
    return OK;
}



DbRetVal Transaction::appendLogicalUndoLog(Database *sysdb, OperationType type, void *data, size_t size, void* indexPtr)
{
    DbRetVal rv = OK;
    UndoLogInfo *logInfo = createUndoLog(sysdb, type, data, size, &rv);
    if (logInfo == NULL) return rv;
    char **indPtr = (char**)((char*)logInfo + sizeof(UndoLogInfo));
    *indPtr = (char*)  indexPtr;
    addAtBegin(logInfo);
    printDebug(DM_Transaction, "creating logical undo log and append %x optype:%d", logInfo, type);
    return rv;
}

DbRetVal Transaction::appendLogicalHashUndoLog(Database *sysdb, OperationType type, void *data, size_t size)
{
    DbRetVal rv = OK;
    HashUndoLogInfo *hInfo = (HashUndoLogInfo *) data;
    UndoLogInfo *logInfo = createUndoLog(sysdb, type, hInfo->tuple_, size, &rv);
    if (logInfo == NULL) return rv;
    memcpy((char*)logInfo + sizeof(UndoLogInfo), data, sizeof(HashUndoLogInfo));
    addAtBegin(logInfo);
    printDebug(DM_Transaction, "creating logical undo log and append %x optype:%d", logInfo, type);
    return rv;
}
DbRetVal Transaction::appendLogicalTreeUndoLog(Database *sysdb, OperationType type, void *data, size_t size)
{
    DbRetVal rv = OK;
    TreeUndoLogInfo *hInfo = (TreeUndoLogInfo *) data;
    UndoLogInfo *logInfo = createUndoLog(sysdb, type, hInfo->tuple_, size, &rv);
    if (logInfo == NULL) return rv;
    memcpy((char*)logInfo + sizeof(UndoLogInfo), data, sizeof(TreeUndoLogInfo));
    addAtBegin(logInfo);
    printDebug(DM_Transaction, "creating logical undo log and append %x optype:%d", logInfo, type);
    return rv;
}

UndoLogInfo* Transaction::createUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size, DbRetVal *rv)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);
    int reqSize = size + sizeof(UndoLogInfo);
    UndoLogInfo *logInfo = NULL;
    int tries=0;
    int totalTries = Conf::config.getMutexRetries();
    while (tries < totalTries)
    {
        *rv = OK;
        logInfo= (UndoLogInfo*)chunk->allocate(sysdb, reqSize, rv);
        if (logInfo !=NULL) break;
        if (*rv != ErrLockTimeOut)
        {
            printError(*rv, "Unable to allocate undo log");
            return NULL;
        }
        tries++;
    }

    if (logInfo == NULL) {
        printError(*rv, "Unable to allocate undo log record after %d retries", tries);
        return NULL;
    }
    logInfo->data_ = (char *)logInfo + sizeof(UndoLogInfo);
    logInfo->opType_ = type;
    logInfo->size_ = size;
    logInfo->next_ = NULL;
    return logInfo;
}

void Transaction::addAtBegin(UndoLogInfo* logInfo)
{
    //add it to the begin of the log list
    logInfo->next_ = firstUndoLog_;
    firstUndoLog_ = logInfo;
    return;
}

UndoLogInfo* Transaction::popUndoLog()
{
    UndoLogInfo *iter = firstUndoLog_, *prev = firstUndoLog_;
    if(NULL != iter)
    {
        prev = iter;
        iter = iter->next_;
    }
    firstUndoLog_ = iter;
    return prev;

}

int Transaction::noOfUndoLogs()
{
    UndoLogInfo *iter = firstUndoLog_;
    int count =0;
    while(NULL != iter)
    {
        count++;
        iter = iter->next_;
    }
    return count;
}
void Transaction::printDebugInfo(Database *sysdb)
{
   printf("<TransactionInfo>\n");
   if (waitLock_ != NULL) 
   {
       printf("<WaitLock>");
       waitLock_->print();
       printf("</WaitLock>");

   }
   printf("<UndoLogs>\n");
   Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);
   printf("  <TotalPages> %d </TotalPages>\n", chunk->totalPages());
   UndoLogInfo *iter = firstUndoLog_;
   int count =0;
   while(NULL != iter)
   {
      iter->print();
      iter = iter->next_;
      count++;
   }
   printf("</TotalNodes> %d </TotalNodes>\n", count);
   printf("</UndoLogs>\n");

   printf("<TransHasList>\n");
   chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
   printf("  <TotalPages> %d </TotalPages>\n", chunk->totalPages());
   TransHasNode *hasIter  = hasLockList_;
   count =0;
   while (NULL != hasIter)
   {
       hasIter->print();
       hasIter = hasIter->next_;
       count++;
   }
   printf("</TotalNodes> %d </TotalNodes>\n", count);
   printf("</TransHasList>\n");

   printf("</TransactionInfo>\n");
   return ;
}
DbRetVal Transaction::removeUndoLogs(Database *sysdb)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);
    UndoLogInfo *logInfo = NULL;
    while(NULL != (logInfo = popUndoLog()))
    {
        chunk->free(sysdb, logInfo);
    }
    return OK;
}


DbRetVal Transaction::applyUndoLogs(Database *sysdb)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);
    UndoLogInfo *logInfo = NULL;
    while(NULL != (logInfo = popUndoLog()))
    {
        logFinest(Conf::logger, "Apply undo log type:%d", logInfo->opType_);
        switch(logInfo->opType_)
        {
            case InsertOperation:
             {
                char *ptr = (char *)logInfo->data_;
                void *ptrToTuple = (void *)*(long *)ptr; 
                ptr += sizeof(void *);
                InUse *isUsed = ((InUse*)(ptrToTuple) - 1);
                if (*isUsed == 0) {
                   printError(ErrSysFatal, "Fatal: Row is already not in use");
                }
                *isUsed = 0;
                handleVarcharUndoInsert(sysdb, ptr);
                break;
             }
             case DeleteOperation:
             {
                char *ptr = (char *)logInfo->data_;
                void *ptrToTuple = (void *)*(long *)ptr; 
                ptr += sizeof(void *);
                InUse *isUsed = ((InUse*)(ptrToTuple) - 1);
                if (*isUsed == 1) {
                    printError(ErrSysFatal, "Fatal: Row is already in use");
                }
                *isUsed = 1;
                //data record will be intact as we have lock on that record
                handleVarcharUndoDelete(sysdb, ptr);
                break;
             }
             case UpdateOperation:
             {
                char *ptr = (char *)logInfo->data_;
                void *ptrToTuple = (void *)*(long *)ptr; 
                ptr += sizeof(void *);
                InUse *isUsed = ((InUse*)(ptrToTuple) - 1);
                if (*isUsed == 0) {
                    printError(ErrSysFatal, "Fatal: Row is not in use during update rollback");
                }
                handleVarcharUndoUpdate(sysdb, ptr, ptrToTuple);
                break;
             }
             case InsertHashIndexOperation:
             {
                HashIndex::deleteLogicalUndoLog(sysdb, (char *)logInfo 
                                                 + sizeof(UndoLogInfo));
                break;
             }
             case DeleteHashIndexOperation:
             {
                HashIndex::insertLogicalUndoLog(sysdb, (char *)logInfo 
                                                 + sizeof(UndoLogInfo));
                break;
             }
             case InsertTreeIndexOperation:
             {
                TreeIndex::deleteLogicalUndoLog(sysdb, (char *)logInfo
                                                 + sizeof(UndoLogInfo));
                break;
             }
             case DeleteTreeIndexOperation:
             {
                TreeIndex::insertLogicalUndoLog(sysdb, (char *)logInfo
                                                 + sizeof(UndoLogInfo));
                break;
             }
             default:
             {
                 printError(ErrSysFatal, "Illegal undo log type");
                 break;
             }
        }
        chunk->free(sysdb, logInfo);
    }
    return OK;
}
DbRetVal Transaction::handleVarcharUndoInsert(Database *sysdb, char *ptr)
{
    // ptr  will have following info encapsulated.
    // metadataPtr + nVarchars + varchar chunk ptr +
    // ptrs to varchars

    Database db;
    void *metaData = (void *)*(long *)ptr;
    ptr += sizeof(void *);
    db.setMetaDataPtr((DatabaseMetaData *) metaData);
    db.setProcSlot(sysdb->procSlot);

    int noOfVarchar = *(int *)ptr; 
    ptr += sizeof(int);
    Chunk *vcchunk = (Chunk *) *(long *)ptr; 
    ptr += sizeof(void *);
    void **ptrToVarchars = (void **) ptr;
    for (int i = 0; i < noOfVarchar; i++) {
        if (*(long *) ptrToVarchars[i] != 0L) {
            vcchunk->free(&db, (void *)*(long *)ptrToVarchars[i]);
            *(long *) ptrToVarchars[i] = 0L;
        }
    }
    return OK;
}

DbRetVal Transaction::handleVarcharUndoDelete(Database *sysdb, char *ptr)
{
    // ptr will have following info encapsulated.
    // metadataPtr + nVarchars + varchar chunk ptr + ptrs to varchars +
    // size and value pairs for varchars
    void *metaData = (void *)*(long *)ptr; 
    ptr += sizeof(void *);
    Database db;
    db.setMetaDataPtr((DatabaseMetaData *) metaData);
    db.setProcSlot(sysdb->procSlot);
    DbRetVal rv = OK;
    int noOfVarchar = *(int *) ptr; 
    ptr+= sizeof(int);
    Chunk *vcchunk = (Chunk *) *(long *)ptr; 
    ptr += sizeof(void *);
    void **ptrToVarchars = (void **) ptr;
    ptr += noOfVarchar * sizeof (void *);
    char *lenValPtr = (char *) ptr;
    for (int i = 0; i < noOfVarchar; i++) {
        int len = *(int *) lenValPtr; 
        lenValPtr += sizeof(int);
        if (len != 0) {
            void *ptr = vcchunk->allocate(&db, len, &rv);
            strcpy((char *)ptr, lenValPtr); 
            lenValPtr += len;
            *(long *) ptrToVarchars[i] =  (long)ptr;
        } else {
            *(long *) ptrToVarchars[i] = 0L;
        }
    }
    return rv;
}
DbRetVal Transaction::handleVarcharUndoUpdate(Database *sysdb, char *ptr, void *ptrToTuple)
{
    // logInfo->data_ will have following info encapsulated.
    // tupleptr + tuple length + actual tuple + metadataPtr +
    // nVarchars + varchar chunk ptr + ptrs to varchars +
    // size and value pairs for varchars

    int tupleLen = *(int *) ptr;
    ptr += sizeof(int);
    void *tuple = ptr;
    ptr += tupleLen;
    void *metaData = (void *)*(long *)ptr;
    ptr += sizeof(void *);
    Database db;
    db.setMetaDataPtr((DatabaseMetaData *) metaData);
    db.setProcSlot(sysdb->procSlot);
    DbRetVal rv = OK;
    int noOfVarchar = *(int *) ptr;
    ptr+= sizeof(int);
    Chunk *vcchunk = (Chunk *) *(long *)ptr; 
    ptr += sizeof(void *);
    void **ptrToVarchars = (void **) ptr;
    ptr += noOfVarchar * sizeof (void *);
    char *lenValPtr = (char *) ptr;
    for (int i = 0; i < noOfVarchar; i++) {
        if (*(long *) ptrToVarchars[i] != 0L) {
            vcchunk->free(&db, (void *)*(long *) ptrToVarchars[i]);
            *(long *) ptrToVarchars[i] = 0L;
        }
    }
    os::memcpy(ptrToTuple, tuple, tupleLen);
    for (int i = 0; i < noOfVarchar; i++) {
        int len = *(int *) lenValPtr; lenValPtr += sizeof(int);
        if (len != 0) {
            void *ptr = vcchunk->allocate(&db, len, &rv);
            strcpy((char *)ptr, lenValPtr); 
            lenValPtr += len;
            *(long *) ptrToVarchars[i] = (long) ptr;
        } else { 
            *(long *) ptrToVarchars[i] = 0L;
        }
    }
    return rv;
}
