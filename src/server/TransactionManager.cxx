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
#include<Config.h>
#include<Process.h>

void TransactionManager::printUsageStatistics()
{
    Transaction *iter = firstTrans;
    int i=0, usedCount =0, freeCount =0, undoLogCount=0;
    for (; i < Conf::config.getMaxTrans(); i++)
    {
            if (iter->status_ == TransNotUsed) freeCount++; 
            else 
            { 
                usedCount++;
                undoLogCount += iter->noOfUndoLogs();
            }
            iter++;
    }
    printf("<TransactionTable>\n");
    printf("  <UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("  <FreeSlots> %d </FreeSlots>\n", freeCount);

    printf("  <UndoLogs>\n");
    printf("    <TotalNodes> %d </TotalNodes>\n", undoLogCount);
    printf("  </UndoLogs>\n");
    printf("</TransactionTable>\n");

}

void TransactionManager::printDebugInfo(Database *sysdb)
{
    Transaction *iter = firstTrans;
    int i=0, usedCount =0, freeCount =0, undoLogCount=0;
    printf("<TransactionTable>\n");
    for (; i < Conf::config.getMaxTrans(); i++)
    {
            if (iter->status_ == TransNotUsed) freeCount++; 
            else 
            { 
                usedCount++;
                undoLogCount += iter->noOfUndoLogs();
                iter->printDebugInfo(sysdb);
            }
            iter++;
    }

    printf("  <UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("  <FreeSlots> %d </FreeSlots>\n", freeCount);

    printf("  <UndoLogs>\n");
    printf("    <TotalNodes> %d </TotalNodes>\n", undoLogCount);
    printf("  </UndoLogs>\n");
    printf("</TransactionTable>\n");
}


DbRetVal TransactionManager::startTransaction(LockManager *lMgr, IsolationLevel level)
{
    Database *sysdb = lMgr->systemDatabase_;
    Transaction *trans = ProcessManager::getThreadTransaction(sysdb->procSlot);
    if (NULL != trans)
    {
        if (trans->status_ != TransNotUsed) return ErrAlready; 
        else {
            //the previous transaction shall be used again
            trans->status_ = TransRunning;
            trans->isoLevel_ = level;
            printDebug(DM_Transaction, "Using the same transaction slot\n");
            return OK;
        }

    }

    DbRetVal rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }
    Transaction *iter = firstTrans;
    int i;
    for (i =0 ; i < Conf::config.getMaxTrans(); i++)
    {
            if (iter->status_ == TransNotUsed) break;
            iter++;
    }
    // if Transaction table is full return error
    if (i == Conf::config.getMaxTrans()) {
        printError(ErrNoResource, "Transaction slots are full");
        sysdb->releaseTransTableMutex();
        return ErrNoResource;
    }
    printDebug(DM_Transaction, "Using transaction slot %d \n", i);

    //Make this free slot, as the current transaction and
    //set the state
    trans = iter;
    trans->status_ = TransRunning;
    trans->isoLevel_ = level;
    sysdb->releaseTransTableMutex();
    ProcessManager::setThreadTransaction(trans, sysdb->procSlot);
    return OK;
}

void TransactionManager::setFirstTrans(Transaction *trans)
{
    firstTrans = trans;
}


DbRetVal TransactionManager::commit(LockManager *lockManager)
{
    Database *sysdb = lockManager->systemDatabase_;
    Transaction *trans = ProcessManager::getThreadTransaction(sysdb->procSlot);
    if (NULL == trans)
    { 
       printError(ErrNotOpen, "No transaction started for this procSlot %d", sysdb->procSlot);
       return ErrNotOpen;
    }
    DbRetVal rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }

    if (trans->status_ != TransRunning)
    {
        sysdb->releaseTransTableMutex(); 
        printError(ErrBadCall, "Transaction is not in running state\n");
        return ErrBadCall;
    }
    trans->status_ = TransCommitting;
    sysdb->releaseTransTableMutex();

    trans->releaseAllLocks(lockManager);
    if(NULL != trans->waitLock_)
    {
            printError(ErrSysInternal, "Trans WaitLock is not null\n");
            return ErrSysInternal;
    }
    //TODO::flush all redo logs to disk
    //TODO::remove all the logs in memory
    trans->removeUndoLogs(sysdb);
    rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }
    trans->status_ = TransNotUsed;
    sysdb->releaseTransTableMutex();
    printDebug(DM_Transaction, "Committed transaction:%x",trans);
    return OK;
}

DbRetVal TransactionManager::rollback(LockManager *lockManager, Transaction *t)
{
    Database *sysdb = lockManager->systemDatabase_;
    Transaction *trans;
    if (t == NULL)
        trans = ProcessManager::getThreadTransaction(sysdb->procSlot);
    else
        trans = t;
    if (NULL == trans)
    { 
       return OK;
    }
    DbRetVal rv= sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }

    if (trans->status_ != TransRunning)
    {
        sysdb->releaseTransTableMutex(); 
        //will be called during connection disconnect without starting transaction.
        return OK;
    }
    trans->status_ = TransAborting;
    sysdb->releaseTransTableMutex();

    trans->applyUndoLogs(sysdb);
    //TODO::remove all the logs in memory
    trans->releaseAllLocks(lockManager);
    if(NULL != trans->waitLock_)
    {
       printError(ErrSysInternal, "Trans waitlock is not null");
       return ErrSysInternal;
    }

    sysdb->getTransTableMutex();
    trans->status_ = TransNotUsed;
    sysdb->releaseTransTableMutex();
    printDebug(DM_Transaction, "Aborted transaction:%x",trans);

    return OK;
}
