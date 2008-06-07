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
    void print() {
       printf("<UndoLogInfo>\n");
       printf("  <Size> %d </Size>\n", size_);
       printf("  <OperationType> %d </OperationType>\n", opType_);
       printf("  <TuplePtr> %x </TuplePtr>\n", ptrToTuple_);
       printf("</UndoLogInfo>\n");

    }
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
    DbRetVal removeFromHasList(Database *sysdb, void *tuple);
    bool findInHasList(Database *sysdb, LockHashNode *node);

    DbRetVal appendUndoLog(Database *sysdb, OperationType type, void *data, size_t size);
    DbRetVal appendLogicalUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size, void* indexPtr);
    UndoLogInfo* createUndoLog(Database *sysdb, OperationType type, void *data,
                       size_t size, DbRetVal *rv);
    void addAtBegin(UndoLogInfo* logInfo);

    UndoLogInfo* popUndoLog();
    DbRetVal removeUndoLogs(Database *sysdb);
    DbRetVal applyUndoLogs(Database *sysdb);
    int noOfUndoLogs();
    void printDebugInfo(Database *sysdb);
};

class TransactionManager
{
    public:
    TransactionManager() {  }
    ~TransactionManager() {}
    //Transaction *trans;

    Transaction *firstTrans;

    void setFirstTrans(Transaction *trans);
    void printUsageStatistics();
    void printDebugInfo(Database *sysdb);

    DbRetVal startTransaction(LockManager *lManager, IsolationLevel level);
    DbRetVal commit(LockManager *lManager);
    DbRetVal rollback(LockManager *lManager, Transaction *t=NULL);

};
#endif
