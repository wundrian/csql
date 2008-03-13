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
Bucket* LockManager::getLockBucket(void *tuple)
{
   int noOfBuckets = LOCK_BUCKET_SIZE;
   Bucket* buckets = systemDatabase_->getLockHashBuckets();
   unsigned long key =(unsigned long)tuple ;
   int bucketNo = HashIndex::computeHashBucket(typeULong, &key, noOfBuckets);

   Bucket *bucket = &(buckets[bucketNo]);
   printDebug(DM_Lock, "getLockBucket bucketno:%d bucket:%x",bucketNo, bucket);
   return bucket;
}

void LockManager::printUsageStatistics()
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

void LockManager::printDebugInfo()
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

DbRetVal LockManager::getSharedLock(void *tuple, Transaction **trans)
{
   //get the bucket list
   //take the bucket mutex for read
   //go the the next level bucket list
   //get the bucket iterator
   //go the node where the lock info resides
   //check which mode the lock is taken
   // if shared then
   //      upgrade the bucket mutex to write
   //      take it and increment the readers count
   //      release bucket mutex and exit
   // if exclusive then
   //       go into the loop
   //       upgrade the bucket mutex to write
   //       increment waitReaders count
   //       release the bucket mutex
   //       wait for timeout period or (takes shared lock and release it ) till it becomes free.
   //       if times out
   //            take bucket mutex for write
   //            decrement waitReaders count
   //            releaese bucket mutex

   //            return
   //       if it becomes free
   //            take bucket mutex for write
   //            increment readers
   //            releaese bucket mutex

   //            return
   LockInfo linfo;
   linfo.noOfReaders_ = 1;
   //keeping it ready for the allocation, because when
   //lock node is not present in the list, then it means we are the first
   //to acquire lock so for sure we will get it.
   printDebug(DM_Lock, "LockManager::getSharedLock Begin");
   Bucket *bucket = getLockBucket(tuple);
   int lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "LockManager::getSharedLock:End-Unable to get mutex");
       printError(ErrLockTimeOut,"Unable to acquire bucket mutex");
       return ErrLockTimeOut;
   }
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
        LockHashNode *node = allocLockNode(linfo, tuple);
        if (NULL == node)
        {
            printError(ErrNoMemory, "No memory to allocate Lock node");
            return ErrNoMemory;
            }
        printDebug(DM_Lock, "Bucket list is null: Allocating new LockHashNode %x", node);
        bucket->bucketList_ = (void*)node; //make it as head
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, node);
        printDebug(DM_Lock, "LockManager::getSharedLock End");
        return OK;

   }
   LockHashNode *cachedLockNode = NULL;

   LockHashNode *iter = lockNode;
   //Iterate though the list and find the element's lock info
   while(iter != NULL)
   {
       if(iter->ptrToTuple_ == tuple)
       {
           if (iter->lInfo_.noOfReaders_ == -1)
           {

               iter->lInfo_.waitReaders_++;
                       cachedLockNode = iter;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->updateWaitLock(iter);
               printDebug(DM_Lock, "lock node:%x exclusive locked",iter);
               break;
           }
           else if (iter->lInfo_.noOfReaders_ == 0)
           {
               if(iter->lInfo_.waitWriters_ >0)
               {
                   iter->lInfo_.waitReaders_++;
                   cachedLockNode = iter;
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   if (trans != NULL) (*trans)->updateWaitLock(iter);
                   printDebug(DM_Lock, "lock node:%x Writers waiting.",iter);
                   break;
               }
               else
               {
                   iter->lInfo_.noOfReaders_++;
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, iter);
                   printDebug(DM_Lock, "lock node:%x First to take shared lock",
                                                                          iter);
                   printDebug(DM_Lock, "LockManager::getSharedLock End");
                   return OK;
                }
           }else
           {
               iter->lInfo_.noOfReaders_++;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, iter);
               printDebug(DM_Lock, "lock node:%x incr readers",iter);
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   if (NULL == cachedLockNode)
   {
        LockHashNode *node = allocLockNode(linfo, tuple);
        if (NULL == node)
        {
            bucket->mutex_.releaseLock(systemDatabase_->procSlot);
            printError(ErrNoMemory, "No memory to allocate Lock node");
            return ErrNoMemory;
        }
        printDebug(DM_Lock,"Not Found.Created new lock node:%x",node);
        LockHashNode *it = lockNode;
        while (NULL != it->next_) it = it->next_;
        it->next_ = node;
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, node);
        printDebug(DM_Lock, "LockManager::getSharedLock End");
        return OK;
   }
   //bucket->mutex_.releaseLock();
   int tries = 0;
   int ret = 0;
   struct timeval timeout;
   timeout.tv_sec = Conf::config.getLockSecs();
   timeout.tv_usec = Conf::config.getLockUSecs();

   //printDebug(DM_Lock, "Trying to get mutex: for bucket %x\n", bucket);
   while (tries < Conf::config.getLockRetries())
   {
       lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
       if (lockRet != 0)
       {
           printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           printError(ErrLockTimeOut, "Unable to get bucket mutex");
           return ErrLockTimeOut;
       }
       if (cachedLockNode->lInfo_.noOfReaders_ == 0)
       {
           //if there are waiters allow then to take the lock
           if (cachedLockNode->lInfo_.waitWriters_ <0)
           {
               cachedLockNode->lInfo_.noOfReaders_++;
               cachedLockNode->lInfo_.waitReaders_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else if (cachedLockNode->lInfo_.noOfReaders_ == -1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else
       {
           cachedLockNode->lInfo_.noOfReaders_++;
           cachedLockNode->lInfo_.waitReaders_--;
           bucket->mutex_.releaseLock(systemDatabase_->procSlot);
           if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           return OK;
       }

       bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",cachedLockNode, tries);
   }
   printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
   printDebug(DM_Lock, "LockManager::getSharedLock End");
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   return ErrLockTimeOut;

}

DbRetVal LockManager::getExclusiveLock(void *tuple, Transaction **trans)
{
   LockInfo linfo;
   linfo.noOfReaders_ = -1;
   printDebug(DM_Lock, "LockManager::getExclusiveLock Begin");
   //keeping it ready for the allocation, because when
   //lock node is not present in the list, then it means we are the first
   //to acquire lock so for sure we will get it.

   Bucket *bucket = getLockBucket(tuple);
   int lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Unable to acquire bucket mutex:May be deadlock");
       printError(ErrLockTimeOut, "Unable to acquire bucket mutex");
       return ErrLockTimeOut;
   }
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
        LockHashNode *node = allocLockNode(linfo, tuple);
        if (NULL == node)
        {
            printError(ErrNoMemory, "No memory to allocate Lock node");
            return ErrNoMemory;
            }
        printDebug(DM_Lock, "No head. So new lock node allocated:%x",node);
        bucket->bucketList_ = (void*)node; //make it as head
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, node);
        printDebug(DM_Lock, "LockManager::getExclusiveLock End");
        return OK;

   }
   LockHashNode *cachedLockNode = NULL;

   LockHashNode *iter = lockNode;
   //Iterate though the list and find the element's lock info
   while(iter != NULL)
   {
       if(iter->ptrToTuple_ == tuple)
       {
           if (iter->lInfo_.noOfReaders_ != 0)
           {
               iter->lInfo_.waitWriters_++;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->updateWaitLock(iter);
               cachedLockNode = iter;
               printDebug(DM_Lock, "Either some one has exclusive or shared lock:%x",iter);
               break;
           }
           else
           {
               iter->lInfo_.noOfReaders_ = -1;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, iter);
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   if (NULL == cachedLockNode)
   {
        LockHashNode *node = allocLockNode(linfo, tuple);
        if (NULL == node)
        {
            bucket->mutex_.releaseLock(systemDatabase_->procSlot);
            printError(ErrNoMemory, "No memory to allocate Lock node");
            return ErrNoMemory;
        }
        printDebug(DM_Lock, "Not Found:Creating new lock node:%x",node);
        LockHashNode *it = lockNode;
        while (NULL != it->next_) it = it->next_;
        it->next_ = node;
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, node);
        printDebug(DM_Lock, "LockManager::getExclusiveLock End");
        return OK;
   }
   //bucket->mutex_.releaseLock();
   int tries = 0;
   int ret = 0;
   struct timeval timeout;
   timeout.tv_sec = Conf::config.getLockSecs();
   timeout.tv_usec = Conf::config.getLockUSecs();

   while (tries < Conf::config.getLockRetries())
   {
       lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
       if (lockRet != 0)
       {
           printError(ErrLockTimeOut, "Unable to get bucket mutex");
           return ErrLockTimeOut;
       }
       if (cachedLockNode->lInfo_.noOfReaders_ == 0)
       {
           cachedLockNode->lInfo_.noOfReaders_ = -1;
           cachedLockNode->lInfo_.waitWriters_--;
           bucket->mutex_.releaseLock(systemDatabase_->procSlot);
           if (trans != NULL) (*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
           if (trans != NULL) (*trans)->removeWaitLock();
           printDebug(DM_Lock, "LockManager::getExclusiveLock End");
           return OK;
       }else if ( cachedLockNode->lInfo_.noOfReaders_ == 1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               printDebug(DM_Lock, "upgrading shared to exclusive lock:%x",
                                                           cachedLockNode);
               //upgrade it to exclusive lock
               cachedLockNode->lInfo_.noOfReaders_ = -1;
               cachedLockNode->lInfo_.waitWriters_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
           if (trans ==NULL && ProcessManager::hasLockList.exists(cachedLockNode->ptrToTuple_))
           {
               printDebug(DM_Lock, "upgrading shared to exclusive lock:%x",
                                                           cachedLockNode);
               //upgrade it to exclusive lock
               cachedLockNode->lInfo_.noOfReaders_ = -1;
               cachedLockNode->lInfo_.waitWriters_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }else if ( cachedLockNode->lInfo_.noOfReaders_ == -1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               printDebug(DM_Lock, "You already have exclusive lock:%x",
                                                        cachedLockNode);
               cachedLockNode->lInfo_.waitWriters_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
           if (trans ==NULL && ProcessManager::hasLockList.exists(cachedLockNode->ptrToTuple_))
           {
               printDebug(DM_Lock, "You already have exclusive lock:%x",
                                                           cachedLockNode);
               cachedLockNode->lInfo_.waitWriters_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }
       bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",cachedLockNode, tries);
   }
   printDebug(DM_Lock, "LockManager::getExclusiveLock End");
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   return ErrLockTimeOut;
}

DbRetVal LockManager::releaseLock(void *tuple)
{
   LockInfo linfo;
   linfo.noOfReaders_ = 0;
   //keeping it ready for the allocation, because when
   //lock node is not present in the list, then it means we are the first
   //to acquire lock so for sure we will get it.
   printDebug(DM_Lock, "LockManager:releaseLock Start");
   Bucket *bucket = getLockBucket(tuple);
   printDebug(DM_Lock,"Bucket is %x", bucket);
   int lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
       printDebug(DM_Lock, "LockManager:releaseLock End");
       printError(ErrLockTimeOut, "Unable to get bucket mutex");
       return ErrLockTimeOut;
   }
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
       bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       printDebug(DM_Lock, "LockManager:releaseLock End");
       printError(ErrSysFatal, "Lock Element Not found: Probable Data Corruption.\n");
       return ErrSysFatal;
   }

   LockHashNode *iter = lockNode;
   //Iterate though the list and find the element's lock info
   while(iter != NULL)
   {
       if(iter->ptrToTuple_ == tuple)
       {

           if (iter->lInfo_.noOfReaders_ == -1)
           {
               iter->lInfo_.noOfReaders_ = 0;
               if (iter->lInfo_.waitWriters_ == 0 || iter->lInfo_.waitReaders_ ==0)
               {
                   deallocLockNode(iter, bucket);
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "Releasing exclusive lock and dealloc node:%x",
                                                                                iter);
                   printDebug(DM_Lock, "LockManager:releaseLock End");
                   return OK;
               }
               else
               {
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "Releasing exclusive lock");
                   printDebug(DM_Lock, "LockManager:releaseLock End");
                   return OK;
               }
           }
           else if (iter->lInfo_.noOfReaders_ == 1)
           {
               iter->lInfo_.noOfReaders_ = 0;
               if (iter->lInfo_.waitWriters_ == 0 || iter->lInfo_.waitReaders_ ==0)
               {
                   deallocLockNode(iter, bucket);
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "Releasing read lock and dealloc node:%x",iter);
                   printDebug(DM_Lock, "LockManager:releaseLock End");
                   return OK;
               }
           }
           else
           {
               iter->lInfo_.noOfReaders_--;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "Decrementing read lock:%x",iter);
               printDebug(DM_Lock, "LockManager:releaseLock End");
               return OK;
           }

       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
   printError(ErrSysFatal, "Lock Element Not found: Probable Data Corruption");
   return ErrSysFatal;
}

DbRetVal LockManager::isExclusiveLocked(void *tuple, Transaction **trans, bool &status)
{
   Bucket *bucket = getLockBucket(tuple);
   printDebug(DM_Lock,"Bucket is %x", bucket);
   int lockRet = bucket->mutex_.getLock(systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
       printDebug(DM_Lock, "LockManager:releaseLock End");
       printError(ErrLockTimeOut, "Unable to get bucket mutex");
       return ErrLockTimeOut;
   }
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
       bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       printDebug(DM_Lock, "bucketList is empty. so data element not locked");
       status = false;
       return OK;
   }

   LockHashNode *iter = lockNode;
   //Iterate though the list and find the element's lock info
   //Only exclusive locks are checked. shared locks are not considered for this
   while(iter != NULL)
   {
       if(iter->ptrToTuple_ == tuple)
       {
           if (iter->lInfo_.noOfReaders_ == -1)
           {
               if (trans != NULL && (*trans)->findInHasList(systemDatabase_, iter))
               {
                   printDebug(DM_Lock, "You already have exclusive Lock: %x", iter);
                   status = false;
               }
               else 
                   status = true;
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               return OK;
           }
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
   status = false;
   return OK;
}

LockHashNode* LockManager::allocLockNode(LockInfo &info, void *tuple)
{
    //allocate lock node
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    LockHashNode *node = (LockHashNode*)chunk->allocate(systemDatabase_);
    if (NULL == node)
    {
        printError(ErrNoMemory,
                   "No memory to allocate Lock node");
        return NULL;
        }
    node->ptrToTuple_ = tuple;
    node->lInfo_ = info;
    node->next_ = NULL;
    return node;
}

void LockManager::deallocLockNode(LockHashNode *node, Bucket *bucket)
{
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    LockHashNode *nodeList = (LockHashNode*) bucket->bucketList_;
    LockHashNode *iter = nodeList, *prev = nodeList;
    if (NULL == nodeList)
    {
        printError(ErrSysFatal, "Lock Bucket corrupted");
        return;
    }
    //If it is the first node, then make the bucket point to the next node 
    //in the list
    if (nodeList == node)
    {
       bucket->bucketList_ = node->next_;
       chunk->free(systemDatabase_, node);
       return;
    }
    while(iter != node)
    {
        prev = iter;
        iter = iter->next_;
    }
    //delete the node by making previous element point to the next element 
    //of the deleted element in the list
    prev->next_ = iter->next_;
    chunk->free(systemDatabase_, node);
    return ;
}
