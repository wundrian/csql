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
LockManager::LockManager(Database *sysDb_)
{
    systemDatabase_ = sysDb_;
    lockBuckets = systemDatabase_->getLockHashBuckets();
}
Bucket* LockManager::getLockBucket(void *tuple)
{
   //Bucket* buckets = systemDatabase_->getLockHashBuckets();
   unsigned long key =(unsigned long)tuple ;
   int bucketNo = key % LOCK_BUCKET_SIZE;

   //Bucket *bucket = &(buckets[bucketNo]);
   printDebug(DM_Lock, "getLockBucket bucketno:%d",bucketNo);
   return &(lockBuckets[bucketNo]);
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
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
        DbRetVal rv = OK;
        LockHashNode *node = allocLockNode(linfo, tuple, &rv);
        if (NULL == node)
        {
            printError(rv, "Could not allocate Lock node");
            return rv;
        }
        printDebug(DM_Lock, "Bucket list is null: Allocating new LockHashNode %x", node);
        rv = OK;
        if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, node);
        if (rv !=OK) {
            deallocLockNode(node);
            printError(ErrLockTimeOut,"Unable to insert into hasList. Timeout.Retry...");
            return ErrLockTimeOut;
        }
        
        //bucket->bucketList_ = (void*)node; //make it as head
        int ret = Mutex::CASL((long*)&bucket->bucketList_, 0 , (long)node);
        if (ret != 0) {
            if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
            deallocLockNode(node);
            printError(ErrLockTimeOut, "Unable to set lock list head. Timeout. Retry...");
            return ErrLockTimeOut;
        }
        //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        printDebug(DM_Lock, "LockManager::getSharedLock End");
        return rv;
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

               //iter->lInfo_.waitReaders_++;
               int ret = Mutex::CASGen(&iter->lInfo_.waitReaders_, 
                                       iter->lInfo_.waitReaders_,
                                       iter->lInfo_.waitReaders_+1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to inc waitReaders:%d : Timeout. Retry..", iter->lInfo_.waitReaders_);
                   return ErrLockTimeOut;
               }
               cachedLockNode = iter;
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->updateWaitLock(iter);
               printDebug(DM_Lock, "lock node:%x exclusive locked",iter);
               break;
           }
           else if (iter->lInfo_.noOfReaders_ == 0)
           {
               if(iter->lInfo_.waitWriters_ >0)
               {
                   //iter->lInfo_.waitReaders_++;
                   int ret = Mutex::CASGen(&iter->lInfo_.waitReaders_, 
                                        iter->lInfo_.waitReaders_, 
                                        iter->lInfo_.waitReaders_+1);
                   if (ret !=0) {
                       printError(ErrLockTimeOut, "Unable to inc waitReaders:%d : Timeout. Retry..", iter->lInfo_.waitReaders_);
                       return ErrLockTimeOut;
                   }
                   cachedLockNode = iter;
                   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   if (trans != NULL) (*trans)->updateWaitLock(iter);
                   printDebug(DM_Lock, "lock node:%x Writers waiting.",iter);
                   break;
               }
               else
               {
                   DbRetVal rv = OK;
                   if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, iter);
                   if (rv != OK) {
                       printError(ErrLockTimeOut,"Unable to insert into hasList. Timeout. Retry..");
                       return ErrLockTimeOut;
                   }
                   //iter->lInfo_.noOfReaders_++;
                   int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, 
                                        iter->lInfo_.noOfReaders_, 
                                        iter->lInfo_.noOfReaders_+1);
                   if (ret !=0) {
                       if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
                       printError(ErrLockTimeOut, "Unable to inc noOfReaders:%d : Timeout. Retry..", iter->lInfo_.noOfReaders_);
                       return ErrLockTimeOut;
                   }
                   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "lock node:%x First to take shared lock",
                                                                          iter);
                   printDebug(DM_Lock, "LockManager::getSharedLock End");
                   return rv;
                }
           }else {
               DbRetVal rv = OK;
               if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, iter);
               if (rv != OK) {
                   printError(ErrLockTimeOut, "Unable to insert into hasList. Timeout : Retry..");
                   return ErrLockTimeOut;
               }
               //iter->lInfo_.noOfReaders_++;
               int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, 
                                        iter->lInfo_.noOfReaders_, 
                                        iter->lInfo_.noOfReaders_+1);
               if (ret !=0) {
                   if (trans!=NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
                   printError(ErrLockTimeOut, "Unable to take S lock. Timeout : Retry..");
                   return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "lock node:%x incr readers",iter);
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return rv;
           }
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   if (NULL == cachedLockNode)
   {
        DbRetVal rv =OK;
        LockHashNode *node = allocLockNode(linfo, tuple, &rv);
        if (NULL == node)
        {
            //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
            printError(rv, "Could not allocate Lock node");
            if (trans != NULL) (*trans)->removeWaitLock();
            return rv;
        }
        printDebug(DM_Lock,"Not Found.Created new lock node:%x",node);
        rv = OK;
        if (trans != NULL) 
          rv = (*trans)->insertIntoHasList(systemDatabase_, node);
        if (rv != OK) {
            deallocLockNode(node);
            if (trans != NULL) (*trans)->removeWaitLock();
            printError(ErrLockTimeOut, "Unable to add to hasList : Timeout. Retry..");
            return ErrLockTimeOut;
        }
        DbRetVal lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
        if (lockRet != OK)
        {
            printError(ErrLockTimeOut, "Unable to acquire bucket mutex");
            if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
            deallocLockNode(node);
            if (trans != NULL) (*trans)->removeWaitLock();
            return ErrLockTimeOut;
        }

        LockHashNode *it = (LockHashNode*) bucket->bucketList_;

        if (NULL == it) {
           int ret = Mutex::CASL((long*)&bucket->bucketList_, 0 , (long)node);
           if (ret != 0) {
               bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
               deallocLockNode(node);
               if (trans != NULL) (*trans)->removeWaitLock();
               printError(ErrLockTimeOut, "Unable to set Lock Bucket. Timeout: retry...");
               return ErrLockTimeOut;
           }
        } else { 
           while (NULL != it->next_) it = it->next_;
           //it->next_ = node;
           int ret = Mutex::CASL((long*)&it->next_, 0, (long)node);
           if (ret !=0) {
             bucket->mutex_.releaseLock(systemDatabase_->procSlot);
             if (trans !=NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
             deallocLockNode(node);
             if (trans != NULL) (*trans)->removeWaitLock();
             printError(ErrLockTimeOut, "Unable to add to lock table list : Retry..");
             return ErrLockTimeOut;
           }
        }
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->removeWaitLock();
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
       /*lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
       if (lockRet != 0)
       {
           printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           printError(ErrLockTimeOut, "Unable to get bucket mutex");
           if (trans != NULL) (*trans)->removeWaitLock();
           return ErrLockTimeOut;
       }*/
       InUse oldValue = cachedLockNode->lInfo_.noOfReaders_;
       if (cachedLockNode->lInfo_.noOfReaders_ == 0)
       {
           //if there are waiters allow then to take the lock
           if (cachedLockNode->lInfo_.waitWriters_ <0)
           {
               DbRetVal rv = OK;
               if (trans != NULL) rv=(*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
               if (rv !=OK) {
                   if (trans != NULL) (*trans)->removeWaitLock();
                   printError(ErrLockTimeOut, "Unable to add to hasList. TimeOut : Retry..");
                   return ErrLockTimeOut;
              
               }
               //cachedLockNode->lInfo_.noOfReaders_++;
               int ret = Mutex::CASGen(&cachedLockNode->lInfo_.noOfReaders_, 
                                   0,cachedLockNode->lInfo_.noOfReaders_+1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to take S lock. TimeOut : Retry..");
                   if (trans != NULL) (*trans)->removeWaitLock();
                   if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
                   return ErrLockTimeOut;
               }
               //cachedLockNode->lInfo_.waitReaders_--;
               ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitReaders_, 
                                        cachedLockNode->lInfo_.waitReaders_, 
                                        cachedLockNode->lInfo_.waitReaders_-1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Fatal:Unable to dec waitReaders. Timeout : Retry..");
                   //return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else if (cachedLockNode->lInfo_.noOfReaders_ == -1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else
       {
           DbRetVal rv =OK;
           if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
           if (rv !=OK) {
               if (trans != NULL) (*trans)->removeWaitLock();
               printError(ErrLockTimeOut, "Unable to add to hasList. Timeout : Retry..");
               return ErrLockTimeOut;
           }
           //cachedLockNode->lInfo_.noOfReaders_++;
           int ret = Mutex::CASGen(&cachedLockNode->lInfo_.noOfReaders_, 
                                        oldValue, oldValue+1);
           if (ret !=0) {
               printError(ErrLockTimeOut, "Unable to take S lock. Timeout : Retry..");
               if (trans != NULL) (*trans)->removeWaitLock();
               if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
               return ErrLockTimeOut;
           }
           //cachedLockNode->lInfo_.waitReaders_--;
           ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitReaders_, 
                                        cachedLockNode->lInfo_.waitReaders_, 
                                        cachedLockNode->lInfo_.waitReaders_-1);
           if (ret !=0) {
               printError(ErrLockTimeOut, "Unable to dec waitReaders timeout : Retry..");
               //return ErrLockTimeOut;
           }
           //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
           if (trans != NULL) (*trans)->removeWaitLock();
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           return OK;
       }

       //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",cachedLockNode, tries);
   }
   printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
   printDebug(DM_Lock, "LockManager::getSharedLock End");
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   if (trans != NULL) (*trans)->removeWaitLock();
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
   /*int lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Unable to acquire bucket mutex:May be deadlock");
       printError(ErrLockTimeOut, "Unable to acquire bucket mutex");
       return ErrLockTimeOut;
   }*/
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
        DbRetVal rv = OK;
        LockHashNode *node = allocLockNode(linfo, tuple, &rv);
        if (NULL == node) return rv;
        rv =OK;
        if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, node);
        if (rv !=OK) {
            printError(ErrLockTimeOut, "Unable to add to hasList. Timeout: retry...");
            deallocLockNode(node);
            return ErrLockTimeOut;
        }
        printDebug(DM_Lock, "No head. So new lock node allocated:%x",node);
        //bucket->bucketList_ = (void*)node; //make it as head
        int ret = Mutex::CASL((long*)&bucket->bucketList_, 0 , (long)node);
        if (ret != 0) {
            if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
            deallocLockNode(node);
            printError(ErrLockTimeOut, "Unable to set Lock Bucket. Timeout: retry...%x", tuple);
            return ErrLockTimeOut;
         }
        //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
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
               //iter->lInfo_.waitWriters_++;
               int ret = Mutex::CASGen(&iter->lInfo_.waitWriters_,
                                       iter->lInfo_.waitWriters_,
                                       iter->lInfo_.waitWriters_+1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to inc waitWriters. Timeout : Retry..");
                   return ErrLockTimeOut;
               }

               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->updateWaitLock(iter);
               cachedLockNode = iter;
               printDebug(DM_Lock, "Either some one has exclusive or shared lock:%x",iter);
               break;
           }
           else
           {
               DbRetVal rv =OK;
               if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, iter);
               if (rv != OK) {
                   printError(ErrLockTimeOut, "Unable to add to hasList. Timeout : Retry..");
                   return ErrLockTimeOut;
               }
               //iter->lInfo_.noOfReaders_ = -1;
               int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, 0, -1);
               if (ret !=0) {
                   if (trans!= NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
                   printError(ErrLockTimeOut, "Unable to take X lock on tuple. Timeout : Retry..");
                   return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return rv;
           }
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   if (NULL == cachedLockNode)
   {
        DbRetVal rv =OK;
        LockHashNode *node = allocLockNode(linfo, tuple, &rv);
        if (NULL == node)
        {
            //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
            if (trans != NULL) (*trans)->removeWaitLock();
            printError(rv, "Could not allocate Lock node");
            return rv;
        }
        printDebug(DM_Lock, "Not Found:Creating new lock node:%x",node);
        rv = OK;
        if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, node);
        if (rv != OK) {
            deallocLockNode(node);
            if (trans != NULL) (*trans)->removeWaitLock();
            printError(ErrLockTimeOut, "Unable to add to hasList. Timeout : Retry..");
            return ErrLockTimeOut;
        }
        int lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
        if (lockRet != 0)
        {
            printError(ErrLockTimeOut, "Unable to acquire bucket mutex");
            if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
            deallocLockNode(node);
            if (trans != NULL) (*trans)->removeWaitLock();
            return ErrLockTimeOut;
        }
        LockHashNode *it = (LockHashNode*) bucket->bucketList_;
        if (NULL == it) {
           int ret = Mutex::CASL((long*)&bucket->bucketList_, 0 , (long)node);
           if (ret != 0) {
               if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
               deallocLockNode(node);
               if (trans != NULL) (*trans)->removeWaitLock();
               printError(ErrLockTimeOut, "Unable to set Lock Bucket. Timeout: retry...");
               return ErrLockTimeOut;
           }
           

        } else {
           while (NULL != it->next_) it = it->next_;
           //it->next_ = node;
           int ret = Mutex::CASL((long*)&it->next_, 0, (long)node);
           if (ret !=0) {
              if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
              deallocLockNode(node);
              if (trans != NULL) (*trans)->removeWaitLock();
              bucket->mutex_.releaseLock(systemDatabase_->procSlot);
              printError(ErrLockTimeOut, "Unable to add to lock list. Timeout : Retry..");
              return ErrLockTimeOut;
           }
        }
        bucket->mutex_.releaseLock(systemDatabase_->procSlot);
        if (trans != NULL) (*trans)->removeWaitLock();
        printDebug(DM_Lock, "LockManager::getExclusiveLock End");
        return rv;
   }
   //bucket->mutex_.releaseLock();
   int tries = 0;
   int ret = 0;
   struct timeval timeout;
   timeout.tv_sec = Conf::config.getLockSecs();
   timeout.tv_usec = Conf::config.getLockUSecs();

   while (tries < Conf::config.getLockRetries())
   {
       /*lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
       if (lockRet != 0)
       {
           printError(ErrLockTimeOut, "Unable to get bucket mutex");
           return ErrLockTimeOut;
       }*/
       InUse oldValue = cachedLockNode->lInfo_.noOfReaders_;
       if (cachedLockNode->lInfo_.noOfReaders_ == 0)
       {
           DbRetVal rv ;
           if (trans != NULL) rv = (*trans)->insertIntoHasList(systemDatabase_, cachedLockNode);
           if (rv != OK) {
               if (trans != NULL) (*trans)->removeWaitLock();
               printError(ErrLockTimeOut, "Unable to add to hasList: Timeout: Retry..");
               return ErrLockTimeOut;
           }
           //cachedLockNode->lInfo_.noOfReaders_ = -1;
           int ret = Mutex::CASGen(&cachedLockNode->lInfo_.noOfReaders_,0,-1);
           if (ret !=0) {
               if (trans != NULL) (*trans)->removeFromHasList(systemDatabase_, tuple);
               if (trans != NULL) (*trans)->removeWaitLock();
               printError(ErrLockTimeOut, "Unable to take X lock: Timeout: Retry..");
               return ErrLockTimeOut;
           }

           //cachedLockNode->lInfo_.waitWriters_--;
           ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_-1);
           if (ret !=0) {
               printError(ErrLockTimeOut, "Fatal:Unable to dec waitWriters. TimeOut : Retry.. waitWriters:%d",cachedLockNode->lInfo_.waitWriters_);
               //do not do error return as this is OK to continue.
               //return ErrLockTimeOut;
           }
           //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
           if (trans != NULL) (*trans)->removeWaitLock();
           printDebug(DM_Lock, "LockManager::getExclusiveLock End");
           return rv;
       }else if ( cachedLockNode->lInfo_.noOfReaders_ == 1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               printDebug(DM_Lock, "upgrading shared to exclusive lock:%x",
                                                           cachedLockNode);
               //upgrade it to exclusive lock
               //cachedLockNode->lInfo_.noOfReaders_ = -1;
               int ret = Mutex::CASGen(&cachedLockNode->lInfo_.noOfReaders_, 1, -1);
               if (ret !=0) {
                   if (trans != NULL) (*trans)->removeWaitLock();
                   printError(ErrLockTimeOut, "Unable to upgrade lock. Timeout : Retry..");
                   return ErrLockTimeOut;
               }

               //cachedLockNode->lInfo_.waitWriters_--;
               ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_-1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Fatal:Unable to dec waitWriters:Timeout : Retry.. waitwriters:%d", cachedLockNode->lInfo_.waitWriters_);
                   //do not do error return as this is OK to contine
                   //return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
           if (trans ==NULL && ProcessManager::hasLockList.exists(cachedLockNode->ptrToTuple_))
           {
               printDebug(DM_Lock, "upgrading shared to exclusive lock:%x",
                                                           cachedLockNode);
               //upgrade it to exclusive lock
               //cachedLockNode->lInfo_.noOfReaders_ = -1;
               int ret = Mutex::CASGen(&cachedLockNode->lInfo_.noOfReaders_, 1, -1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to upgrade lock. Timeout : Retry..");
                   if (trans != NULL) (*trans)->removeWaitLock();
                   return ErrLockTimeOut;
               }

               //cachedLockNode->lInfo_.waitWriters_--;
               ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_-1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Fatal:Unable to dec waitWriters:Timeout : Retry.. waitwriters:%d", cachedLockNode->lInfo_.waitWriters_);
                   //do not do error return as this is OK to contine
                   //return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
	       if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }else if ( cachedLockNode->lInfo_.noOfReaders_ == -1)
       {
           if (trans !=NULL && (*trans)->findInHasList(systemDatabase_, cachedLockNode))
           {
               printDebug(DM_Lock, "You already have exclusive lock:%x",
                                                        cachedLockNode);
               //cachedLockNode->lInfo_.waitWriters_--;
               ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_-1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Fatal:Unable to dec waitWriters:Timeout : Retry.. waitwriters:%d", cachedLockNode->lInfo_.waitWriters_);
                   //do not do error return as this is OK to contine
                   //return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
           if (trans ==NULL && ProcessManager::hasLockList.exists(cachedLockNode->ptrToTuple_))
           {
               printDebug(DM_Lock, "You already have exclusive lock:%x",
                                                           cachedLockNode);
               //cachedLockNode->lInfo_.waitWriters_--;
               ret = Mutex::CASGen(&cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_,
                                        cachedLockNode->lInfo_.waitWriters_-1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Fatal:Unable to dec waitWriters:Timeout : Retry.. waitwriters:%d", cachedLockNode->lInfo_.waitWriters_);
                   //do not do error return as this is OK to contine
                   //return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               if (trans != NULL) (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }
       //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",cachedLockNode, tries);
   }
   printDebug(DM_Lock, "LockManager::getExclusiveLock End");
   if (trans != NULL) (*trans)->removeWaitLock();
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   return ErrLockTimeOut;
}

DbRetVal LockManager::releaseLock(void *tuple)
{
   printDebug(DM_Lock, "LockManager:releaseLock Start");
   Bucket *bucket = getLockBucket(tuple);
   printDebug(DM_Lock,"Bucket is %x", bucket);
   /*int lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
       printDebug(DM_Lock, "LockManager:releaseLock End");
       printError(ErrLockTimeOut, "Unable to get bucket mutex");
       return ErrLockTimeOut;
   }*/
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
       //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
       printDebug(DM_Lock, "LockManager:releaseLock End");
       //printError(ErrSysFatal, "Fatal:Lock Bucket and Element Not found for tuple: %x:", tuple);
       printStackTrace();
       printError(ErrSysFatal, "Fatal:Lock Bucket and Element Not found for tuple: %x:%d", tuple, *(int*)tuple);
       return ErrSysFatal;
   }
   DbRetVal rv = OK;
   LockHashNode *iter = lockNode;
   //Iterate though the list and find the element's lock info
   while(iter != NULL)
   {
       if(iter->ptrToTuple_ == tuple)
       {
           InUse oldValue = iter->lInfo_.noOfReaders_;
           if (iter->lInfo_.noOfReaders_ == -1)
           {
               //iter->lInfo_.noOfReaders_ = 0;
               int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, -1, 0);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to release X lock taken : Retry..");
                   return ErrLockTimeOut;
               }

               if (iter->lInfo_.waitWriters_ == 0 || iter->lInfo_.waitReaders_ ==0)
               {
                    //TODO::above condition is not atomic
                    //put waitReaders_, WaitReaders in one integer
                    DbRetVal lockRet = getBucketMutex(bucket,systemDatabase_->procSlot);
                    if (lockRet == OK) {
                      int tries = Conf::config.getMutexRetries();
                      do {
                        rv = deallocLockNode(iter, bucket);
                        if (tries == 0) {  
                            printError(ErrWarning, "Fatal:Leak: Unable to dealloc lock node %d tries", Conf::config.getMutexRetries());
                            break;
                        }
                        tries--;
                      }while (rv == ErrLockTimeOut);
                      bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                    }
                    printDebug(DM_Lock, "Releasing exclusive lock and dealloc node:%x", iter);
                    printDebug(DM_Lock, "LockManager:releaseLock End");
                    return OK;
               }
               else
               {
                   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "Releasing exclusive lock");
                   printDebug(DM_Lock, "LockManager:releaseLock End");
                   return OK;
               }
           }
           else if (iter->lInfo_.noOfReaders_ == 1)
           {
               //iter->lInfo_.noOfReaders_ = 0;
               int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, 1, 0);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to release S lock taken. Timeout : Retry..");
                   return ErrLockTimeOut;
               }
               if (iter->lInfo_.waitWriters_ == 0 || iter->lInfo_.waitReaders_ ==0)
               {
                  DbRetVal lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
                  if (lockRet == OK) {
                    int tries = Conf::config.getMutexRetries();
                    do {
                        rv = deallocLockNode(iter, bucket);
                        if (tries == 0) {  
                            printError(ErrWarning, "Fatal:Leak:Unable to dealloc lock node");
                        }
                        tries--;
                    }while (rv == ErrLockTimeOut);
                   bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                 }
                 printDebug(DM_Lock, "Releasing read lock and dealloc node:%x",iter);
                 printDebug(DM_Lock, "LockManager:releaseLock End");
                 return OK;
               }
               else
               {
                   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
                   printDebug(DM_Lock, "Releasing read lock");
                   printDebug(DM_Lock, "LockManager:releaseLock End");
                   return OK;
               }
           }
           else
           {
               //iter->lInfo_.noOfReaders_--;
               int ret = Mutex::CASGen(&iter->lInfo_.noOfReaders_, oldValue, oldValue - 1);
               if (ret !=0) {
                   printError(ErrLockTimeOut, "Unable to release S lock taken : Retry..");
                   return ErrLockTimeOut;
               }
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               printDebug(DM_Lock, "Decrementing read lock:%x",iter);
               printDebug(DM_Lock, "LockManager:releaseLock End");
               return OK;
           }

       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       iter = iter->next_;
   }
   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
   printError(ErrSysFatal, "Fatal:Lock Element Not found for tuple:%x", tuple);
   return ErrSysFatal;
}

DbRetVal LockManager::isExclusiveLocked(void *tuple, Transaction **trans, bool &status)
{
   Bucket *bucket = getLockBucket(tuple);
   printDebug(DM_Lock,"Bucket is %x", bucket);
   LockHashNode *lockNode = (LockHashNode*) bucket->bucketList_;
   if (NULL == lockNode)
   {
       printDebug(DM_Lock, "bucketList is empty. so data element not locked");
       status = false;
       return OK;
   }
   /*int lockRet = getBucketMutex(bucket, systemDatabase_->procSlot);
   if (lockRet != 0)
   {
       printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
       printDebug(DM_Lock, "LockManager:releaseLock End");
       printError(ErrLockTimeOut, "Unable to get bucket mutex");
       return ErrLockTimeOut;
   }*/

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
               //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
               return OK;
           }else break;
       }
       printDebug(DM_Lock, "Finding the lock node. iter:%x",iter);
       if (iter == iter->next_) {
           printError(ErrSysFatal, "Fatal:Unable to find lock node. cyclic list found");
           return ErrSysFatal;
       }
       iter = iter->next_;
   }
   //bucket->mutex_.releaseLock(systemDatabase_->procSlot);
   status = false;
   return OK;
}

LockHashNode* LockManager::allocLockNode(LockInfo &info, void *tuple, DbRetVal *rv)
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
void LockManager::deallocLockNode(LockHashNode *node)
{
    Chunk *chunk = systemDatabase_->getSystemDatabaseChunk(LockTableId);
    chunk->free(systemDatabase_, node);
    return;
}
DbRetVal LockManager::deallocLockNode(LockHashNode *node, Bucket *bucket)
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
       //bucket->bucketList_ = node->next_;
       if ( 0 != Mutex::CASL((long*)&bucket->bucketList_, (long)node, 
                                                        (long)node->next_)) {
           printError(ErrLockTimeOut, "Unable to remove lock node and set lock list head\n");
           return ErrLockTimeOut;
       }
       chunk->free(systemDatabase_, node);
       return OK;
    }
    void *val = NULL;
    while(iter != node)
    {
        if (iter == NULL) {
            printError(ErrSysFatal, "Fatal: Lock node not found in bucket");
            printStackTrace();
            return ErrSysFatal;
        }
        prev = iter;
        val = prev->next_;
        iter = iter->next_;
    }
    //delete the node by making previous element point to the next element 
    //of the deleted element in the list
    //prev->next_ = iter->next_;
    if ( 0 != Mutex::CASL((long*)&prev->next_, (long)val, (long)iter->next_)) {
        printError(ErrLockTimeOut, "Unable to remove lock node \n");
        return ErrLockTimeOut;
    }
    chunk->free(systemDatabase_, node);
    return OK;
}
DbRetVal LockManager::getBucketMutex(Bucket *bucket, int procSlot)
{
    struct timeval timeout, timeval;
    timeout.tv_sec = Conf::config.getMutexSecs();
    timeout.tv_usec = Conf::config.getMutexUSecs();
    int tries=0;
    int totalTries = Conf::config.getMutexRetries() *2;
    int ret =0;
    while (tries < totalTries)
    {
        ret = bucket->mutex_.getLock(procSlot, true);
        if (ret == 0) break;
        timeval.tv_sec = timeout.tv_sec;
        timeval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &timeval);
        tries++;
    }
    if (tries >= totalTries) return ErrLockTimeOut;
    return OK;

}

