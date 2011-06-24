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
    lockTable.setDb(sysDb_);
}

void LockManager::printUsageStatistics()
{
    lockTable.printUsageStatistics();
}

void LockManager::printDebugInfo()
{
    lockTable.printDebugInfo();
}
void LockManager::printMutexInfo()
{
    lockTable.printMutexInfo();
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
   DbRetVal rv = OK;
   if (NULL == trans) {
       printError(ErrSysFatal, "Fatal:Trans is null");
       printStackTrace();
       os::sleep(1000);
   }
   LockHashNode *iter = lockTable.getLockNode(tuple, rv, true);
   if (NULL ==  iter)
   {
       if (ErrLockTimeOut == rv) return rv;
       if (ErrNotFound == rv)
         rv =  lockTable.addNewLockNode(tuple, trans, linfo);
       lockTable.releaseBucketMutex();
       return rv;
   }
   LockHashNode *node = NULL;
   if (iter->lInfo_.noOfReaders_ == -1)
   {
       iter->lInfo_.waitReaders_++;
       node = iter;
       (*trans)->updateWaitLock(iter);
       printDebug(DM_Lock, "lock node:%x exclusive locked",iter);
   }
   else if (iter->lInfo_.noOfReaders_ == 0)
   {
       if(iter->lInfo_.waitWriters_ >0)
       {
           iter->lInfo_.waitReaders_++;
           node = iter;
           (*trans)->updateWaitLock(iter);
           printDebug(DM_Lock, "lock node:%x Writers waiting.",iter);
       }
       else
       {
           DbRetVal rv = OK;
           (*trans)->insertIntoHasList(systemDatabase_, iter);
           iter->lInfo_.noOfReaders_++;
           lockTable.releaseBucketMutex();
           printDebug(DM_Lock, "lock node:%x First to take shared lock", iter);
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           return rv;
       }
   }else {
       (*trans)->insertIntoHasList(systemDatabase_, iter);
       iter->lInfo_.noOfReaders_++;
       lockTable.releaseBucketMutex();
       printDebug(DM_Lock, "lock node:%x incr readers",iter);
       printDebug(DM_Lock, "LockManager::getSharedLock End");
       return OK;
   }
   lockTable.releaseBucketMutex();
   return retrySharedLock(trans, node);
}

DbRetVal LockManager::retrySharedLock(Transaction **trans, LockHashNode *node )
{
   int tries = 0;
   int ret = 0;
   struct timeval timeout;
   timeout.tv_sec = Conf::config.getLockSecs();
   timeout.tv_usec = Conf::config.getLockUSecs();

   //printDebug(DM_Lock, "Trying to get mutex: for bucket %x\n", bucket);
   while (tries < Conf::config.getLockRetries())
   {
       int lockRet = lockTable.getBucketMutex();
       if (lockRet != 0)
       {
           printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           printError(ErrLockTimeOut, "Unable to get bucket mutex");
           (*trans)->removeWaitLock();
           return ErrLockTimeOut;
       }
       if (node->lInfo_.noOfReaders_ == 0)
       {
           //if there are waiters allow then to take the lock
           if (node->lInfo_.waitWriters_ <0)
           {
               (*trans)->insertIntoHasList(systemDatabase_, node);
               node->lInfo_.noOfReaders_++;
               node->lInfo_.waitReaders_--;
               lockTable.releaseBucketMutex();
               (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else if (node->lInfo_.noOfReaders_ == -1)
       {
           if ((*trans)->findInHasList(systemDatabase_, node))
           {
               lockTable.releaseBucketMutex();
               (*trans)->removeWaitLock();
               printDebug(DM_Lock, "LockManager::getSharedLock End");
               return OK;
           }
       } else
       {
           DbRetVal rv =OK;
           (*trans)->insertIntoHasList(systemDatabase_, node);
           node->lInfo_.noOfReaders_++;
           node->lInfo_.waitReaders_--;
           lockTable.releaseBucketMutex();
           (*trans)->removeWaitLock();
           printDebug(DM_Lock, "LockManager::getSharedLock End");
           return OK;
       }
       lockTable.releaseBucketMutex();
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",node, tries);
   }
   printDebug(DM_Lock, "Mutex is waiting for long time:May be deadlock");
   printDebug(DM_Lock, "LockManager::getSharedLock End");
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   (*trans)->removeWaitLock();
   return ErrLockTimeOut;
}

DbRetVal LockManager::getExclusiveLock(void *tuple, Transaction **trans)
{
   if (trans == NULL) {
        printf("Transaction is NULL\n");
        printStackTrace();
        os:sleep(5000);
   }
   DbRetVal rv = OK;
   LockInfo linfo;
   linfo.noOfReaders_ = -1;
   //printf("DEBUG:getExclusiveLock Called\n");
   printDebug(DM_Lock, "LockManager::getExclusiveLock Begin");
   //keeping it ready for the allocation, because when
   //lock node is not present in the list, then it means we are the first
   //to acquire lock so for sure we will get it.

   LockHashNode *node = lockTable.getLockNode(tuple, rv, true);
   if (NULL == node)
   {
      if (ErrLockTimeOut == rv) return rv;
      if (ErrNotFound == rv)
          rv =  lockTable.addNewLockNode(tuple, trans, linfo);
      lockTable.releaseBucketMutex();
      return rv;
   }
   if (node->lInfo_.noOfReaders_ != 0)
   {
      node->lInfo_.waitWriters_++;
      (*trans)->updateWaitLock(node);
      printDebug(DM_Lock, "Either some one has exclusive or shared lock:%x",node);
   }
   else
   {
       DbRetVal rv =OK;
       (*trans)->insertIntoHasList(systemDatabase_, node);
       node->lInfo_.noOfReaders_ = -1;
       lockTable.releaseBucketMutex();
       printDebug(DM_Lock, "LockManager::getExclusiveLock End");
       return rv;
   }
   lockTable.releaseBucketMutex();
   return retryExclusiveLock(trans, node);
}

bool LockManager::takeXLockOneReader(Transaction **trans, LockHashNode *node)
{
   bool satisfy = false;
   if ((*trans)->findInHasList(systemDatabase_, node))
   {
       satisfy = true;
       printDebug(DM_Lock, "upgrading shared to exclusive lock:%x", node);
       //upgrade it to exclusive lock
       node->lInfo_.noOfReaders_ = -1;
       node->lInfo_.waitWriters_--;
       (*trans)->removeWaitLock();
   }
   return satisfy;
}

bool LockManager::takeXLockOneWriter(Transaction **trans, LockHashNode *node)
{
   bool satisfy = false;
   if ((*trans)->findInHasList(systemDatabase_, node))
   {
       satisfy = true;
       printDebug(DM_Lock, "You already have exclusive lock:%x", node);
       node->lInfo_.waitWriters_--;
       (*trans)->removeWaitLock();
   }
   return satisfy;
}

DbRetVal LockManager::takeXLockNotInUse(Transaction **trans, LockHashNode *node)
{
   (*trans)->insertIntoHasList(systemDatabase_, node);
   node->lInfo_.noOfReaders_ = -1;
   node->lInfo_.waitWriters_--;
   (*trans)->removeWaitLock();
   return OK;
}

DbRetVal LockManager::retryExclusiveLock(Transaction **trans,  LockHashNode *node )
{
   int tries = 0;
   int ret = 0;
   int lockRet =0;
   struct timeval timeout;
   timeout.tv_sec = Conf::config.getLockSecs();
   timeout.tv_usec = Conf::config.getLockUSecs();

   while (tries < Conf::config.getLockRetries())
   {
       lockRet = lockTable.getBucketMutex();
       if (lockRet != 0)
       {
           os::select(0,0,0,0, &timeout);
           tries++;
           continue;
       }
       if (node->lInfo_.noOfReaders_ == 0)
       {
           takeXLockNotInUse(trans, node);
           lockTable.releaseBucketMutex();
           printDebug(DM_Lock, "LockManager::getExclusiveLock End");
           return OK;
       }else if ( node->lInfo_.noOfReaders_ == 1)
       {
           bool satisfy = takeXLockOneReader(trans, node);
           if (satisfy) {
               lockTable.releaseBucketMutex();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }else if ( node->lInfo_.noOfReaders_ == -1)
       {
           bool satisfy = takeXLockOneWriter(trans, node);
           if (satisfy) {
               lockTable.releaseBucketMutex();
               printDebug(DM_Lock, "LockManager::getExclusiveLock End");
               return OK;
           }
       }
       lockTable.releaseBucketMutex();
       os::select(0, 0, 0, 0, &timeout);
       tries++;
       printDebug(DM_Lock, "Trying to lock the lock node:%x iteration:%d",node, tries);
   }
   printDebug(DM_Lock, "LockManager::getExclusiveLock End");
   (*trans)->removeWaitLock();
   printError(ErrLockTimeOut, "Unable to acquire lock for long time.Timed out");
   return ErrLockTimeOut;
}

DbRetVal LockManager::releaseLock(void *tuple)
{
   printDebug(DM_Lock, "LockManager:releaseLock Start");
   DbRetVal rv = OK;
   LockHashNode *node = lockTable.getLockNode(tuple, rv, true);
   if (NULL == node)
   {
       if (ErrLockTimeOut == rv) return rv;
       lockTable.releaseBucketMutex();
       printError(ErrSysFatal, "Fatal:Lock Element Not found for tuple:%x %d", tuple, *(int*)tuple);
       printStackTrace();
       return ErrSysFatal;
   }
   if (node->lInfo_.noOfReaders_ == -1)
   {
       //exclusive lock release
       lockTable.releaseLock(node);
   }
   else if (node->lInfo_.noOfReaders_ == 1)
   {
       //single shared lock release
       lockTable.releaseLock(node);
   }
   else if (node->lInfo_.noOfReaders_ == 0)
   {
       lockTable.releaseBucketMutex();
       printError(ErrSysFatal, "Fatal:Lock Element found for tuple:%x with noOfReaders:%d ", tuple, node->lInfo_.noOfReaders_);
       return ErrSysFatal;
   }
   else
   {
       //+ve value means taken in shared mode
       node->lInfo_.noOfReaders_--;
       printDebug(DM_Lock, "Decrementing read lock:%x",node);
   }
   lockTable.releaseBucketMutex();
   printDebug(DM_Lock, "LockManager:releaseLock End");
   return OK;
}

DbRetVal LockManager::isExclusiveLocked(void *tuple, Transaction **trans, bool &status)
{
   if (trans == NULL) {
        printf("Transaction is NULL\n");
        printStackTrace();
        os:sleep(5000);
   }
   DbRetVal rv = OK;
   LockHashNode *lockNode = lockTable.getLockNode(tuple, rv, true);
   if (NULL == lockNode)
   {
       if (ErrLockTimeOut == rv) return rv;
       lockTable.releaseBucketMutex();
       printDebug(DM_Lock, "LockNode not found in bucket");
       status = false;
       return OK;
   }
   if (lockNode->lInfo_.noOfReaders_ == -1)
   {
       if((*trans)->findInHasList(systemDatabase_, lockNode))
       {
           printDebug(DM_Lock, "You already have exclusive Lock: %x", lockNode);
           status = false;
       }
       else
           status = true;
       lockTable.releaseBucketMutex();
       return OK;
   }
   lockTable.releaseBucketMutex();
   status = false;
   return OK;
}

