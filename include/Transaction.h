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
#ifndef TXN_H
#define TXN_H
#include<os.h>
#include<Debug.h>
#include<Session.h>
class LockHashNode;

enum TransStatus
{
    TransNotUsed          =  0,
    TransCommitting       =  1,
    TransAborting         =  2,
    TransRunning          =  3,
    TransUnknown          =  4
};
class TransHasNode;
class LockManager;
class Database;

enum OperationType
{
    InsertOperation = 0,
    DeleteOperation = 1,
    UpdateOperation = 2,
    InsertHashIndexOperation = 3,
    UpdateHashIndexOperation = 4,
    DeleteHashIndexOperation = 5
};
class UndoLogInfo
{
    public:
    int size_;
    OperationType opType_;
    void *ptrToTuple_;
    UndoLogInfo *next_;
};

class Transaction
{
    public:
    int status_;

    IsolationLevel isoLevel_;

    TransHasNode *hasLockList_;

    UndoLogInfo *firstUndoLog_;

    LockHashNode *waitLock_;

    DbRetVal releaseAllLocks(LockManager *lockManager_);

    void updateWaitLock(LockHashNode *node) { waitLock_ = node; }
    void removeWaitLock() { waitLock_ = NULL; }
    DbRetVal insertIntoHasList(Database *sysdb, LockHashNode *node);

    bool findInHasList(Database *sysdb, LockHashNode *node);

    void appendUndoLog(Database *sysdb, OperationType type, void *data, size_t size);
    void appendLogicalUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size, void* indexPtr);
    UndoLogInfo* createUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size);
    void addAtBegin(UndoLogInfo* logInfo);

    UndoLogInfo* popUndoLog();
    DbRetVal removeUndoLogs(Database *sysdb);
    DbRetVal applyUndoLogs(Database *sysdb);
};

class TransactionManager
{
    public:
    TransactionManager() { trans = NULL; }
    Transaction *trans;
    Transaction *firstTrans;

    void setFirstTrans(Transaction *trans);

    DbRetVal startTransaction(IsolationLevel level);
    DbRetVal commit(LockManager *lManager_);
    DbRetVal rollback(LockManager *lManager_);

};
#endif
