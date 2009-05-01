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
#include <Process.h>
#include <Debug.h>
#include <Database.h>
#include <Config.h>
#include <ErrorType.h>
#include <Globals.h>
#include <Mutex.h>

int ProcessManager::noThreads=0;
Mutex ProcessManager::mutex;
caddr_t ProcessManager::sysAddr=0;
caddr_t ProcessManager::usrAddr=0;
Database* ProcessManager::systemDatabase=NULL;
List ProcessManager::hasLockList;

void ThreadInfo::init()
{
    pid_ = 0;
    thrid_ =0;
    want_ = NULL;
    for (int i =0; i <MAX_MUTEX_PER_THREAD; i++) has_[i] = NULL;
    for (int i =0; i <MAX_THREADS_PER_PROCESS; i++)  thrTrans_[i].init();
}
void ThreadTrans::print()
{
    if (pid_ ==0) return;
    printf("<THREADTRANS>\n");
    printf("  <PID> %d </PID>\n", pid_);
    printf("  <THRID> %lu </THRID>\n", thrid_);
    printf("  <TRANSACTION> %x </TRANSACTION>\n");
    printf("</THREADTRANS>\n");
}
void ThreadInfo::print()
{
    printf("<THREADINFO>\n");
    printf("  <PID> %d </PID>\n", pid_);
    printf("  <THRID> %lu </THRID>\n", thrid_);
    printf("  <WAIT> %x </WAIT>\n", want_);
    printf("  <MUTEXLIST>\n");
    for (int i =0; i <MAX_MUTEX_PER_THREAD; i++) if (has_[i]) printf("    <MUTEX> %x </MUTEX>\n", has_[i]);
    printf("  </MUTEXLIST>\n");
    printf("  <TRANSLIST>\n");
    for (int i =0; i <MAX_THREADS_PER_PROCESS; i++) thrTrans_[i].print();
    printf("  </TRANSLIST>\n");
    printf("</THREADINFO>\n");

}

//It does not check for re registering as well as deregistering unregistered threads.
//as it is handled in the connection class open and close methods.
DbRetVal ProcessManager::registerThread()
{
    mutex.getLock(-1, false);
    noThreads++;
    mutex.releaseLock(-1, false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        printError(rv,"Recovery may be going on. Retry after some time.");
        mutex.getLock(-1, false);
        noThreads--;
        mutex.releaseLock(-1, false);
        return rv;
    }
    pid_t pid;
    pid = os::getpid();
    pthread_t thrid = os::getthrid();
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    ThreadInfo* freeSlot = NULL;
    int freeSlotPos =0;
    bool freeSlotSelected = false;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == 0 ) break;
        pInfo++;
    }
    if ( i == Conf::config.getMaxProcs())
    {
        systemDatabase->releaseProcessTableMutex(false);
        printError(ErrNoResource, "No free thread slot. Limit reached");
        return ErrNoResource;
    }
    //printf("Process slot used %d %x\n", i, pInfo);
    //TODO::make the above debug message
    //TODO:print it to the trace file
    pInfo->init();
    pInfo->pid_ = pid;
    pInfo->thrid_ = thrid;
    procSlot = i;
    printDebug(DM_Process, "Process %d %lu registered with slot %d\n", pid, thrid, procSlot);
    systemDatabase->releaseProcessTableMutex(false);
    return OK;
}
DbRetVal ProcessManager::deregisterThread(int procSlot)
{
    mutex.getLock(-1, false);
    noThreads--;
    mutex.releaseLock(-1, false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }/*
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }

    systemDatabase->releaseProcessTableMutex(false);
    if (i == Conf::config.getMaxProcs()) 
    {
        printError(ErrSysFatal, "Degistering process %d is not registered with csql", pid);
        return ErrNoResource;
    }*/
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(procSlot);
    Transaction *trans = ProcessManager::getThreadTransaction(procSlot);
    if (NULL != trans)
    { 
       if (trans->status_ == TransRunning)
       {
           printError(ErrWarning, "Transaction is still running\n");
       }
    }
    if (pInfo->want_ != NULL) 
    {
        printError(ErrSysFatal, "Probable data corruption.wants_ is not null\n");
        return ErrSysFatal;
    }
    for (int muti = 0 ;muti < MAX_MUTEX_PER_THREAD; muti++)
    {
        if (pInfo->has_[muti] !=  NULL) 
        {
            printError(ErrSysFatal, "Probable data corruption.some mutexes are not freed %x \n",  pInfo->has_[muti]);
            pInfo->has_[muti]->releaseLock(procSlot); 
            return ErrSysFatal;
        }
    }
    printDebug(DM_Process, "Process %d %lu deregistered slot %d\n", pInfo->pid_, pInfo->thrid_, procSlot);

    //printf("Slot freed %d %x %d %lu\n", i, pInfo, pid, thrid); 
    pInfo->init();
    systemDatabase->releaseProcessTableMutex(false);
    return OK;
}

DbRetVal ProcessManager::addMutex(Mutex *mut, int pslot)
{
    //pid_t pid = os::getpid();
    //pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(pslot);
    int i=0;
    /*for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }
    if (i == Conf::config.getMaxProcs())
    {
        printError(ErrSysFatal, "Logical Error pid %d thrid %lu not found in procTable while adding mutex %s", pid, thrid, mut->name);
        return ErrSysFatal;
    }*/
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (pInfo->has_[i] ==  NULL) 
        {
            pInfo->has_[i] = mut; 
            printDebug(DM_Process, "procSlot %d acquiring %d mutex %x %s\n", pslot, i, mut, mut->name);
            return OK;
        }
    }
    printError(ErrSysInternal, "All slots are full. Reached per thread mutex limit.");
    return ErrSysInternal;
}

DbRetVal ProcessManager::removeMutex(Mutex *mut, int pslot)
{
    //pid_t pid = os::getpid();
    //pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(pslot);
    int i=0;
    /*for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }
    if (i == Conf::config.getMaxProcs())
    {
        printError(ErrSysFatal, "Logical Error pid %d thrid %lu not found in procTable", pid, thrid);
        return ErrSysFatal;
    }*/
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (pInfo->has_[i] ==  mut) 
        {
            pInfo->has_[i] = NULL; 
            printDebug(DM_Process, "procSlot %d releasing %d mutex %x %s\n", pslot, i, mut, mut->name);
            return OK;
        }
    }
    printError(ErrSysInternal, "Mutex could not be found in the list %s", mut->name);
    void *array[10];
    size_t size;
    size = backtrace(array, 10);
    backtrace_symbols_fd(array, size, 2);
    return ErrSysInternal;
}

DbRetVal ProcessManager::setThreadTransaction(Transaction *trans, int pslot)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(pslot);
    int i=0;

    for (int i = 0 ;i < MAX_THREADS_PER_PROCESS; i++)
    {
        if (pInfo->thrTrans_[i].pid_ != 0) continue;
    }
    if (i == MAX_THREADS_PER_PROCESS)
    {
        printError(ErrSysInternal, "Max thread limit reached.");
        return ErrSysInternal;
    }
    pInfo->thrTrans_[i].pid_ = pid;
    pInfo->thrTrans_[i].thrid_ = thrid;
    pInfo->thrTrans_[i].trans_ = trans;

    printDebug(DM_Process, "procSlot %d:  pid: %d thrid: %lu is set to use trans %x\n", pslot, 
                           pid, thrid, trans);
    //pInfo->trans_ = trans;
    return OK;
}

Transaction* ProcessManager::getThreadTransaction(int pslot)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return NULL;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(pslot);
    int i=0;

    for (i = 0; i < MAX_THREADS_PER_PROCESS; i++)
    {
        if (pInfo->thrTrans_[i].pid_ == pid && pInfo->thrTrans_[i].thrid_ == thrid) break;
    }
    if (i == MAX_THREADS_PER_PROCESS)
    {
        printDebug(DM_Process, "Thread specific trans could not be found in list");
        return NULL;
    }

    printDebug(DM_Process, "procSlot %d:  pid: %d thrid: %lu is returning trans %x\n", pslot, 
                           pid, thrid, pInfo->thrTrans_[i].trans_);
    //pInfo->trans_ = trans;
    return pInfo->thrTrans_[i].trans_;
}

Transaction** ProcessManager::getThreadTransAddr(int pslot)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return NULL;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(pslot);
    int i=0;

    for (int i = 0 ;i < MAX_THREADS_PER_PROCESS; i++)
    {
        if (pInfo->thrTrans_[i].pid_ == pid && pInfo->thrTrans_[i].thrid_ == thrid) break;
    }
    if (i == MAX_THREADS_PER_PROCESS)
    {
        printDebug(DM_Process, "Thread specific trans could not be found in list");
        return NULL;
    }

    printDebug(DM_Process, "procSlot %d:  pid: %d thrid: %lu is returning trans %x\n", pslot, 
                           pid, thrid, pInfo->thrTrans_[i].trans_);
    return &pInfo->thrTrans_[i].trans_;
}




void ProcessManager::printUsageStatistics()
{
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0 , freeCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ != 0 ) usedCount++; else freeCount++;
        pInfo++;
    }
    printf("<ProcTable>\n");
    printf("  <UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("  <FreeSlots> %d </FreeSlots>\n", freeCount);
    printf("</ProcTable>\n");

}

void ProcessManager::printDebugInfo()
{
    printf("<ProcTable>\n");
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0 , freeCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ != 0 ) {pInfo->print(); usedCount++;} else freeCount++;
        pInfo++;
    }
    printf("<UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("<FreeSlots> %d </FreeSlots>\n", freeCount);
    printf("</ProcTable>\n");
}


bool ProcessManager::isAnyOneRegistered()
{
    //the process which calls this will have an entry in proc table. 
    //so checking for 1
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ != 0 ) usedCount++; 
        pInfo++;
    }
    if (usedCount == 1) return false; else return true;
}
