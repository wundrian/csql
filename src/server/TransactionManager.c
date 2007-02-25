/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
DbRetVal TransactionManager::startTransaction()
{
    Transaction *iter = firstTrans;
    //get free slot from transaction table
    for (int i =0 ; i < MAX_TRANS; i++)
    {
            if (iter->status_ == TransNotUsed) break;
            iter++;
        }
    //Make this free slot, as the current transaction and
    //set the state
    trans = iter;
    trans->status_ = TransRunning;
    return OK;
}

void TransactionManager::setFirstTrans(Transaction *trans)
{
    firstTrans = trans;
}

DbRetVal TransactionManager::commit(LockManager *lockManager_)
{
    Database *sysdb = lockManager_->systemDatabase_;
    sysdb->getTransTableMutex();
    if (trans->status_ != TransRunning)
    {
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

    sysdb->getTransTableMutex();
    trans->status_ = TransNotUsed;
    sysdb->releaseTransTableMutex();
    printDebug(DM_Transaction, "Committed transaction:%x",trans);
    return OK;
}

DbRetVal TransactionManager::rollback(LockManager *lockManager_)
{
    Database *sysdb = lockManager_->systemDatabase_;
    sysdb->getTransTableMutex();
    if (trans->status_ != TransRunning)
    {
        printError(ErrBadCall, "Transaction is not in running state\n");
        return ErrBadCall;
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
