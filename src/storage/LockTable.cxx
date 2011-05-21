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
#include<Lock.h>
#include<Allocator.h>
#include<Database.h>
#include<CatalogTables.h>
#include<Transaction.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>
LockTable::LockTable()
{
}
LockTable::~LockTable()
{
}
void LockTable::setDb(Database *sysDb_)
{
    systemDatabase_ = sysDb_;
    lockBuckets = systemDatabase_->getLockHashBuckets();
}
Bucket* LockTable::getLockBucket(void *tuple)
{
   unsigned long key =(unsigned long)tuple ;
   int bucketNo = key % LOCK_BUCKET_SIZE;
   printDebug(DM_Lock, "getLockBucket bucketno:%d",bucketNo);
   return &(lockBuckets[bucketNo]);
}

void LockTable::printUsageStatistics()
{
   Bucket* buckets = systemDatabase_->getLockHashBuckets();
   Bucket* bucket;
   LockHashNode *lockNode;
   int nodeCount =0, bucketCount =0;
   for (int i =0; i< LOCK_BUCKET_SIZE; i++)
   {
       bucket = &(buckets[i]);
       lockNode = (LockHashNode*) bucket->bucketList_;
       if (lockNode) bucketCount++; else continue;
       while (NULL != lockNode) { nodeCount++; lockNode = lockNode->next_; }
   }
   printf("<LockTable>\n");
   printf("  <TotalBuckets> %d  </TotalBuckets>\n", LOCK_BUCKET_SIZE);
   printf("  <UsedBuckets> %d  </UsedBuckets>\n", bucketCount);
   printf("  <TotalLockNodes> %d  </TotalLockNodes>\n", nodeCount);
   printf("</LockTable>\n");

}
void LockTable::printMutexInfo()
{
   Bucket* buckets = systemDatabase_->getLockHashBuckets();
   Bucket* bucket;
   LockHashNode *lockNode;
   int nodeCount =0, bucketCount =0;
   printf("<LockTable>\n");
   for (int i =0; i< LOCK_BUCKET_SIZE; i++)
   {
       bucket = &(buckets[i]);
       bucket->mutex_.print();
   }
   printf("</LockTable>\n");
}

void LockTable::printDebugInfo()
{
   Bucket* buckets = systemDatabase_->getLockHashBuckets();
   Bucket* bucket;
   LockHashNode *lockNode;
   int nodeCount =0, bucketCount =0;
   printf("<LockTable>\n");
   for (int i =0; i< LOCK_BUCKET_SIZE; i++)
   {
       nodeCount =0;
       bucket = &(buckets[i]);
       //if (bucket) bucketCount++; else continue;
       lockNode = (LockHashNode*) bucket->bucketList_;

       while (NULL != lockNode) 
       { 
           nodeCount++; 
           lockNode->print();
           lockNode = lockNode->next_; 
       }
       if (nodeCount) {
           bucketCount++;
           printf("  <LockBucket> \n");
           printf("    <BucketNo> %d </BucketNo> \n", i); 
           printf("    <TotalNodes> %d </TotalNodes>\n", nodeCount); 
           printf("  <LockBucket>\n");
       }
   }

   printf("  <TotalUsedBuckets> %d </TotalUsedBuckets>\n", bucketCount); 
   Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
   printf("  <TotalPages> %d </TotalPages>\n", chunk->totalPages()); 
   printf("</LockTable>\n");

}
LockHashNode* LockTable::getLockNode(void *tuple, DbRetVal &rv, bool takeMutex)
{
   curBucket = getLockBucket(tuple);
   if (takeMutex)
   {
      int lockRet = getBucketMutex();
      if (lockRet != 0)
      {
          printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
          printError(ErrLockTimeOut, "Unable to get bucket mutex");
          rv = ErrLockTimeOut;
          return NULL;
      }
   }
   LockHashNode *iter = (LockHashNode*) curBucket->bucketList_;
   if (NULL == iter)
   {
      rv = ErrNotFound;
      return iter;
   }
   //Iterate though the list and find the element's lock info
   while(iter != NULL)
   {
      if(iter->ptrToTuple_ == tuple) break;
      printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
      iter = iter->next_;
   }
   if (NULL == iter)
   {
      rv = ErrNotFound;
   }
   return iter;
}

DbRetVal LockTable::addNewLockNode(void *tuple, Transaction **trans,
                           LockInfo &linfo)
{
   DbRetVal rv = OK;
   LockHashNode *newNode = allocLockNode(linfo, tuple, &rv);
   if (NULL == newNode) return rv;
   rv =OK;
   LockHashNode *it = (LockHashNode*) curBucket->bucketList_;
   if (NULL == it)
   {
       curBucket->bucketList_ = (void*)newNode; //make it as head
       (*trans)->insertIntoHasList(systemDatabase_, newNode);
       return OK;
   }
   while (NULL != it->next_) it = it->next_;
   it->next_ = newNode;
   (*trans)->insertIntoHasList(systemDatabase_, newNode);
   return OK;
}
DbRetVal LockTable::releaseLock(LockHashNode *node)
{
    DbRetVal rv = OK;
    node->lInfo_.noOfReaders_ = 0;
    if (node->lInfo_.waitWriters_ == 0 || node->lInfo_.waitReaders_ ==0)
    {
        int tries = Conf::config.getMutexRetries();
        do {
            rv = deallocLockNode(node, curBucket);
             if (tries == 0) {
                printError(ErrWarning, "Fatal:Leak: Unable to dealloc lock node %d tries", Conf::config.getMutexRetries());
                break;
             }
             tries--;
         }while (rv == ErrLockTimeOut);
         printDebug(DM_Lock, "Releasing exclusive lock and dealloc node:%x", node);
    }
    else
    {
         printDebug(DM_Lock, "Releasing exclusive lock");
    }
    return rv;
}

LockHashNode* LockTable::allocLockNode(LockInfo &info, void *tuple, DbRetVal *rv)
{
    //allocate lock node
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    LockHashNode *node = NULL; //(LockHashNode*)chunk->allocate(systemDatabase_, rv);
    int tries=0;
    int totalTries = Conf::config.getMutexRetries();
    while (tries < totalTries)
    {
        *rv = OK;
        node= (LockHashNode*)chunk->allocate(systemDatabase_, rv);
        if (node !=NULL) break;
        if (*rv != ErrLockTimeOut)
        {
            printError(*rv, "Unable to allocate hash index node");
            return NULL;
        }
        tries++;
    }
    if (NULL == node)
    {
        printError(*rv, "Unable to allocate lock node after %d retry", tries);
        return NULL;
    }
    node->ptrToTuple_ = tuple;
    node->lInfo_ = info;
    node->next_ = NULL;
    return node;
}
void LockTable::deallocLockNode(LockHashNode *node)
{
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    chunk->free(systemDatabase_, node);
    return;
}
DbRetVal LockTable::deallocLockNode(LockHashNode *node, Bucket *bucket)
{
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    LockHashNode *nodeList = (LockHashNode*) bucket->bucketList_;
    LockHashNode *iter = nodeList, *prev = nodeList;
    if (NULL == nodeList)
    {
        printError(ErrSysFatal, "Fatal:Lock Bucket is NULL");
        return ErrSysFatal;
    }
    //If it is the first node, then make the bucket point to the next node 
    //in the list
    if (nodeList == node)
    {
       bucket->bucketList_ = node->next_;
       chunk->free(systemDatabase_, node);
       return OK;
    }
    while(iter != NULL)
    {
        if (iter == node) {
            prev->next_ = iter->next_;
            chunk->free(systemDatabase_, node);
            return OK;
        }
        prev = iter;
        iter = iter->next_;
    }
    printError(ErrSysFatal, "Fatal: Lock node not found in bucket");
    return ErrSysFatal;
}
DbRetVal LockTable::getBucketMutex()
{
    int procSlot = systemDatabase_->procSlot;
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = curBucket->mutex_.getLock(procSlot, true);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;
}
void LockTable::releaseBucketMutex()
{
    curBucket->mutex_.releaseLock(systemDatabase_->procSlot);
}
