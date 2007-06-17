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
DbRetVal TransactionManager::startTransaction(IsolationLevel level)
{
    if (NULL != trans)
    {
        if (trans->status_ == TransNotUsed)
        {
            //the previous transaction shall be used again
            trans->status_ = TransRunning;
            trans->isoLevel_ = level;
            return OK;
        }
    }
    Transaction *iter = firstTrans;
    int i;
    for (i =0 ; i < config.getMaxTrans(); i++)
    {
            if (iter->status_ == TransNotUsed) break;
            iter++;
    }
    // if Transaction table is full return error
    if (i == config.getMaxTrans()) {
        printError(ErrNoResource, "Transaction slots are full");
        return ErrNoResource;
    }

    //Make this free slot, as the current transaction and
    //set the state
    trans = iter;
    trans->status_ = TransRunning;
    trans->isoLevel_ = level;
    return OK;
}

void TransactionManager::setFirstTrans(Transaction *trans)
{
    firstTrans = trans;
}

DbRetVal TransactionManager::commit(LockManager *lockManager_)
{
    Database *sysdb = lockManager_->systemDatabase_;
    DbRetVal rv = sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }
    if (NULL == trans) 
    {
        sysdb->releaseTransTableMutex(); 
        printError(ErrNotOpen, "Transaction Not open");
        return ErrNotOpen;
    }
    if (trans->status_ != TransRunning)
    {
        sysdb->releaseTransTableMutex(); 
        printError(ErrBadCall, "Transaction is not in running state\n");
        return ErrBadCall;
    }
    trans->status_ = TransCommitting;
    sysdb->releaseTransTableMutex();

    trans->releaseAllLocks(lockManager_);
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

DbRetVal TransactionManager::rollback(LockManager *lockManager_)
{
    Database *sysdb = lockManager_->systemDatabase_;
    DbRetVal rv= sysdb->getTransTableMutex();
    if (OK != rv)
    {
        printError(ErrSysInternal, "Unable to acquire transtable mutex");
        return ErrSysInternal;
    }
    if (NULL == trans) 
    {
        sysdb->releaseTransTableMutex(); 
        return OK;
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
    trans->releaseAllLocks(lockManager_);
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
