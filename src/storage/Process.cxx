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
    thrTrans_.init();
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
    thrTrans_.print();
    printf("  </TRANSLIST>\n");
    printf("</THREADINFO>\n");

}

//It does not check for re registering as well as deregistering unregistered threads.
//as it is handled in the connection class open and close methods.
DbRetVal ProcessManager::registerThread()
{
    //mutex.getLock(-1, false);
    noThreads++;
   // mutex.releaseLock(-1, false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get mutex for registering");
        printError(rv,"Recovery may be going on. Retry after some time.");
     //   mutex.getLock(-1, false);
        noThreads--;
       // mutex.releaseLock(-1, false);
        return rv;
    }
    pid_t pid;
    pid = os::getpid();
    pthread_t thrid = os::getthrid();
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    ThreadInfo* freeSlot = NULL;
    int freeSlotPos =0;
    bool freeSlotSelected = false;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ == 0 ) break;
        tInfo++;
    }
    if ( i == Conf::config.getMaxProcs())
    {
        systemDatabase->releaseProcessTableMutex(false);
        printError(ErrNoResource, "No free thread slot. Limit reached");
        return ErrNoResource;
    }
    logFiner(Conf::logger, "Process slot taken: %d", i);
    tInfo->init();
    tInfo->pid_ = pid;
    tInfo->thrid_ = thrid;
    procSlot = i;
    printDebug(DM_Process, "Process %d %lu registered with slot %d\n", pid, thrid, procSlot);
    systemDatabase->releaseProcessTableMutex(false);
    return OK;
}
DbRetVal ProcessManager::deregisterThread(int procSlot)
{
    //mutex.getLock(-1, false);
    noThreads--;
    //mutex.releaseLock(-1, false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
    Transaction *trans = ProcessManager::getThreadTransaction(procSlot);
    if (NULL != trans)
    { 
       if (trans->status_ == TransRunning)
       {
           printError(ErrWarning, "Transaction is still running\n");
       }
       trans->status_ = TransNotUsed;
    }
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(procSlot);
    if (tInfo->want_ != NULL) 
    {
        printError(ErrSysFatal, "Fatal:wants_ is not null\n");
        systemDatabase->releaseProcessTableMutex(false);
        return ErrSysFatal;
    }
    for (int muti = 0 ;muti < MAX_MUTEX_PER_THREAD; muti++)
    {
        if (tInfo->has_[muti] !=  NULL) 
        {
            printError(ErrSysFatal, "Fatal:Some mutexes are not freed %x\n",tInfo->has_[muti] );
            tInfo->has_[muti]->print();
            tInfo->has_[muti]->releaseLock(procSlot); 
            systemDatabase->releaseProcessTableMutex(false);
            return ErrSysFatal;
        }
    }
    printDebug(DM_Process, "Process %d %lu deregistered slot %d\n", tInfo->pid_, tInfo->thrid_, procSlot);
    logFiner(Conf::logger, "ProcSlot Freed %d", procSlot);
    tInfo->init();
    systemDatabase->releaseProcessTableMutex(false);
    return OK;
}

DbRetVal ProcessManager::addMutex(Mutex *mut, int pslot)
{
    if (systemDatabase == NULL) return OK;
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(pslot);
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (tInfo->has_[i] ==  NULL) 
        {
            tInfo->has_[i] = mut; 
            printDebug(DM_Process, "procSlot %d acquiring %d mutex %x %s\n", pslot, i, mut, mut->name);
            logFinest(Conf::logger, "acquiring mutex %x %s", mut, mut->name);
            return OK;
        }
    }
    printError(ErrSysInternal, "All slots are full. Reached per thread mutex limit.");
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
       printError(ErrWarning, "mutex %d %x", i, tInfo->has_[i]);
       tInfo->has_[i]->print();
    }
    return ErrSysInternal;
}

DbRetVal ProcessManager::removeMutex(Mutex *mut, int pslot)
{
    if (systemDatabase == NULL) return OK; 
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(pslot);
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (tInfo->has_[i] ==  mut) 
        {
            tInfo->has_[i] = NULL; 
            printDebug(DM_Process, "procSlot %d releasing %d mutex %x %s\n", pslot, i, mut, mut->name);
            logFinest(Conf::logger, "releasing mutex %x %d", mut, mut->name);
            return OK;
        }
    }
    printError(ErrSysInternal, "Mutex could not be found in the list %s", mut->name);
    return ErrSysInternal;
}

DbRetVal ProcessManager::setThreadTransaction(Transaction *trans, int pslot)
{
    if (systemDatabase == NULL) return OK;
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();

    ThreadInfo* tInfo = systemDatabase->getThreadInfo(pslot);
    tInfo->thrTrans_.pid_ = pid;
    tInfo->thrTrans_.thrid_ = thrid;
    tInfo->thrTrans_.trans_ = trans;

    printDebug(DM_Process, "procSlot %d:  pid: %d thrid: %lu is set to use trans %x\n", pslot, 
                           pid, thrid, trans);
    return OK;
}

Transaction* ProcessManager::getThreadTransaction(int pslot)
{
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(pslot);
    return tInfo->thrTrans_.trans_;
}

Transaction** ProcessManager::getThreadTransAddr(int pslot)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return NULL;
    }

    ThreadInfo* tInfo = systemDatabase->getThreadInfo(pslot);

    printDebug(DM_Process, "procSlot %d:  pid: %d thrid: %lu is returning trans %x\n", pslot, 
                           pid, thrid, tInfo->thrTrans_.trans_);
    return &tInfo->thrTrans_.trans_;
}




void ProcessManager::printUsageStatistics()
{
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0 , freeCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ != 0 ) usedCount++; else freeCount++;
        tInfo++;
    }
    printf("<ProcTable>\n");
    printf("  <UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("  <FreeSlots> %d </FreeSlots>\n", freeCount);
    printf("</ProcTable>\n");

}

void ProcessManager::printDebugInfo()
{
    printf("<ProcTable>\n");
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0 , freeCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ != 0 ) {tInfo->print(); usedCount++;} else freeCount++;
        tInfo++;
    }
    printf("<UsedSlots> %d </UsedSlots>\n", usedCount);
    printf("<FreeSlots> %d </FreeSlots>\n", freeCount);
    printf("</ProcTable>\n");
}

//caller is expected to take proc mutex
bool ProcessManager::isAnyOneRegistered()
{
    //the process which calls this will have an entry in proc table. 
    //so checking for 1
    ThreadInfo* tInfo = systemDatabase->getThreadInfo(0);
    int i=0, usedCount =0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ != 0 ) usedCount++; 
        tInfo++;
    }
    if (usedCount == 1) return false; else return true;
}
