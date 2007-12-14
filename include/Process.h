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
#ifndef PROCESS_H
#define PROCESS_H

#include<os.h>
#include<ErrorType.h>
#include<Mutex.h>
#include<Transaction.h>

class ProcInfo
{
    public:

    pid_t pid_;

    int numThreads_;

};

struct ThreadTrans{
    pid_t pid_;
    pthread_t thrid_;
    Transaction *trans_;
    ThreadTrans() { pid_ =0; thrid_ =0; trans_ = NULL; }
    void init() { pid_ =0; thrid_ =0; trans_ = NULL; }
    void print();
};


class ThreadInfo
{
    public:

    pid_t pid_;

    pthread_t thrid_;

    ThreadTrans thrTrans_[MAX_THREADS_PER_PROCESS]; //list of thread specific transactions

    Mutex *want_;  //single mutex which we are waiting for.

    Mutex *has_[MAX_MUTEX_PER_THREAD];   //list of mutexes held
    void init();
    void print();

};
class Database;

class ProcessManager
{
    public:
    static int noThreads;
    static Mutex mutex;
    static caddr_t sysAddr;
    static caddr_t usrAddr;
    static Database *systemDatabase;
    //ThreadInfo *thrInfo;
    ProcessManager() { }
    DbRetVal registerThread();
    DbRetVal deregisterThread(int slot);
    static DbRetVal addMutex(Mutex *mutex, int pslot);
    static DbRetVal removeMutex(Mutex *mutex, int pslot);

    static DbRetVal setThreadTransaction(Transaction *trans, int pslot);
    static Transaction* getThreadTransaction(int pslot);
    static Transaction** getThreadTransAddr(int pslot);

    void printUsageStatistics();
    void printDebugInfo();
    int procSlot;
    int getProcSlot() { return procSlot; }
    bool isAnyOneRegistered();
};

#endif
