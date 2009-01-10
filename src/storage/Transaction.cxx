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

DbRetVal Transaction::insertIntoHasList(Database *sysdb, LockHashNode *node)
{
    //allocate lock node
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    DbRetVal rv = OK;
    TransHasNode *hasNode = (TransHasNode*)chunk->allocate(sysdb, &rv);
    if (NULL == hasNode)
    {
        printError(rv, "Could not allocate Lock node");
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
    return OK;
}

DbRetVal Transaction::removeFromHasList(Database *sysdb, void *tuple)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    TransHasNode *iter = hasLockList_, *prev = hasLockList_;
    if (NULL == iter)
    {
        printError(ErrNotFound, "There are no tuple lock in has list.");
        return ErrNotFound;
    }
    while (iter != NULL)
    {
        if (tuple == iter->node_->ptrToTuple_)
        {
            prev->next_ = iter->next_;
            chunk->free(sysdb, iter);
            if (iter == hasLockList_) hasLockList_ = NULL;
            return OK;
        }
        prev = iter;
        iter = iter->next_;
    }
    printError(ErrNotFound, "There are no tuple lock in has list.");
    return ErrNotFound;
}


DbRetVal Transaction::releaseAllLocks(LockManager *lockManager_)
{
    Database *sysdb =lockManager_->systemDatabase_;
    Chunk *chunk = sysdb->getSystemDatabaseChunk(TransHasTableId);
    TransHasNode *iter  = hasLockList_, *prev;
    while (NULL != iter)
    {
        prev = iter;
        iter = iter->next_;
        printDebug(DM_Transaction, "Releasing lock %x",prev->node_->ptrToTuple_);
        lockManager_->releaseLock(prev->node_->ptrToTuple_);
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
    os::memcpy((char*)logInfo + sizeof(UndoLogInfo), data, size);
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

UndoLogInfo* Transaction::createUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size, DbRetVal *rv)
{
    Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);
    UndoLogInfo *logInfo = (UndoLogInfo*)chunk->allocate(sysdb,
                                                size + sizeof(UndoLogInfo), rv);
    if (logInfo == NULL) {
        printError(*rv, "Unable to allocate undo log record\n");
        return NULL;
    }
    logInfo->opType_ = type;
    logInfo->ptrToTuple_ = data;
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
        switch(logInfo->opType_)
        {
                case InsertOperation:
                *((int*)(logInfo->ptrToTuple_) - 1) = 0;
                //May memcpy is not needed as no one will update this
                //as lock is taken on this tuple
                os::memcpy(logInfo->ptrToTuple_, (char*) logInfo +
                            sizeof(UndoLogInfo), logInfo->size_);
                break;
                case DeleteOperation:
                *((int*)(logInfo->ptrToTuple_) - 1) = 1;
                os::memcpy(logInfo->ptrToTuple_, (char*) logInfo +
                            sizeof(UndoLogInfo), logInfo->size_);
                break;
                case UpdateOperation:
                os::memcpy(logInfo->ptrToTuple_, (char*) logInfo +
                            sizeof(UndoLogInfo), logInfo->size_);
                break;

                case InsertHashIndexOperation:
                HashIndex::deleteLogicalUndoLog(sysdb, (char *)logInfo 
                                                    + sizeof(UndoLogInfo));
                break;
                //case UpdateHashIndexOperation:
                //HashIndex::updateLogicalUndoLog((char *)logInfo 
                //                                    + sizeof(UndoLogInfo));
                //break;
                case DeleteHashIndexOperation:
                HashIndex::insertLogicalUndoLog(sysdb, (char *)logInfo 
                                                    + sizeof(UndoLogInfo));
                break;
            }
        chunk->free(sysdb, logInfo);
    }
    return OK;
}
