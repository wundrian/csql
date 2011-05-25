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
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (iter->status_ == TransNotUsed || iter->status_ == TransReserved) 
        {
            freeCount++; 
        }
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
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (iter->status_ == TransNotUsed || iter->status_ == TransReserved)
        {
            freeCount++; 
        }
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

    Chunk *chunk = sysdb->getSystemDatabaseChunk(UndoLogTableID);

    printf("  <UndoLogs>\n");
    printf("    <TotalNodes> %d </TotalNodes>\n", undoLogCount);
    printf("    <TotalPages> %d </TotalPages>\n", chunk->totalPages());
    printf("  </UndoLogs>\n");
    printf("</TransactionTable>\n");
}


DbRetVal TransactionManager::startTransaction(LockManager *lMgr, IsolationLevel level)
{
    Database *sysdb = lMgr->systemDatabase_;
    Transaction *trans = ProcessManager::getThreadTransaction(sysdb->procSlot);
    if (NULL != trans)
    {
        trans->printTotalNodes();
        if (trans->status_ != TransReserved) return ErrAlready;
        else if (trans->status_ == TransReserved) 
        { 
            //the previous transaction shall be used again
            //trans->status_ = TransRunning;
            if ( 0 != Mutex::CASGen(&trans->status_, TransReserved, TransRunning)) 
            {
                printError(ErrLockTimeOut, "unable to get lock to reuse the transaction");
                return ErrLockTimeOut;
            }
            trans->isoLevel_ = level;
            printDebug(DM_Transaction, "Using the same transaction slot\n");
            logFinest(Conf::logger, "Transaction Start:Reusing :%x", trans);
            return OK;
        }

    }

    DbRetVal rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(rv, "Unable to acquire transtable mutex");
        return rv;
    }
    Transaction *iter = firstTrans;
    int i;
    for (i =0 ; i < Conf::config.getMaxProcs(); i++)
    {
            if (iter->status_ == TransNotUsed) break;
            iter++;
    }
    // if Transaction table is full return error
    if (i == Conf::config.getMaxProcs()) {
        printError(ErrNoResource, "Transaction slots are full");
        sysdb->releaseTransTableMutex();
        return ErrNoResource;
    }
    printDebug(DM_Transaction, "Using transaction slot %d \n", i);

    //Make this free slot, as the current transaction and
    //set the state
    trans = iter;
    //trans->status_ = TransRunning;
    if ( 0 != Mutex::CASGen(&trans->status_ , TransNotUsed, TransRunning)) {
        printError(ErrLockTimeOut, "Unable to start transaction. Timeout. Retry..");
        sysdb->releaseTransTableMutex();
        return ErrLockTimeOut;
    }
    trans->isoLevel_ = level;
    ProcessManager::setThreadTransaction(trans, sysdb->procSlot);
    sysdb->releaseTransTableMutex();
    //trans->printTotalNodes();
    logFinest(Conf::logger, "Transaction Start:Using :%x", trans);
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
    DbRetVal rv = OK;
    if (NULL == trans)
    { 
       printError(ErrNotOpen, "No transaction started for this procSlot %d", sysdb->procSlot);
       return ErrNotOpen;
    }
    rv = trans->releaseAllLocks(lockManager);
    if (rv != OK) {
        printError(ErrSysInternal, "Fatal:Unable to release all the locks\n");
    }
    if(NULL != trans->waitLock_)
    {
        printError(ErrSysInternal, "Fatal:Trans WaitLock is not null\n");
    }
    trans->removeUndoLogs(sysdb);
    if ( 0 != Mutex::CASGen(&trans->status_, TransRunning, TransReserved))
    {
        printError(ErrSysFatal, "Transaction state corrupted %d\n", trans->status_);
        return ErrSysFatal;
    }
    printDebug(DM_Transaction, "Committed transaction:%x",trans);
    logFinest(Conf::logger, "Transaction Committed:%x", trans);
    return OK;
}

DbRetVal TransactionManager::rollback(LockManager *lockManager, Transaction *t)
{
    Database *sysdb = lockManager->systemDatabase_;
    Transaction *trans = NULL;
    DbRetVal rv = OK;
    if (t == NULL)
        trans = ProcessManager::getThreadTransaction(sysdb->procSlot);
    else
        trans = t;
    if (NULL == trans)
    { 
       return OK;
    }

    if (trans->status_ != TransRunning)
    {
        //sysdb->releaseTransTableMutex(); 
        //will be called during connection disconnect without starting transaction.
        return OK;
    }

    trans->applyUndoLogs(sysdb);
    rv = trans->releaseAllLocks(lockManager);
    if (rv != OK) {
        printError(ErrSysInternal, "Fatal:Unable to release all the locks");
    }
    if(NULL != trans->waitLock_)
    {
        printError(ErrSysInternal, "Fatal:Trans waitlock is not null");
        //return ErrSysInternal;
    }

    //trans->status_ = TransNotUsed;
    if ( 0 != Mutex::CASGen(&trans->status_, TransRunning, TransReserved))
    {
        printError(ErrSysFatal, "Fatal:Unable to abort transaction %d\n", trans->status_);
        return ErrSysFatal;
    }
    printDebug(DM_Transaction, "Aborted transaction:%x",trans);
    logFinest(Conf::logger, "Transaction Aborted:%x", trans);
    return OK;
}

bool TransactionManager::isTransactionConsistent(Database *sysdb)
{
    DbRetVal rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(rv, "Unable to acquire transtable mutex");
        return false;
    }
    Transaction *iter = firstTrans;
    int i;
    for (i =0 ; i < Conf::config.getMaxProcs(); i++)
    {
        if (iter->status_ == TransRunning && iter->noOfUndoLogs()) {
            printError( ErrSysInternal, "Transaction slot %d not consistent status:%d undoLogs:%d\n",i, iter->status_, iter->noOfUndoLogs()); 
            sysdb->releaseTransTableMutex();
            return false;
        }
        iter++;
    }
    sysdb->releaseTransTableMutex();
    return true;
}
