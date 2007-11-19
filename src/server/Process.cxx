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


void ThreadInfo::init()
{
    pid_ = 0;
    thrid_ =0;
    trans_ = NULL;
    want_ = NULL;
    for (int i =0; i <MAX_MUTEX_PER_THREAD; i++) has_[i] = NULL;
}

//It does not check for re registering as well as deregistering unregistered threads.
//as it is handled in the connection class open and close methods.
DbRetVal ProcessManager::registerThread()
{
    mutex.getLock(false);
    noThreads++;
    mutex.releaseLock(false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
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
        systemDatabase->releaseProcessTableMutex();
        printError(ErrNoResource, "No free thread slot. Limit reached");
        return ErrNoResource;
    }
    //printf("Process slot used %d %x\n", i, pInfo);
    //TODO::make the above debug message
    //TODO:print it to the trace file
    pInfo->init();
    pInfo->pid_ = pid;
    pInfo->thrid_ = thrid;
    systemDatabase->releaseProcessTableMutex(false);
    return OK;
}
DbRetVal ProcessManager::deregisterThread()
{
    mutex.getLock(false);
    noThreads--;
    mutex.releaseLock(false);
    DbRetVal rv = systemDatabase->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
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
    }
    if (pInfo->trans_ && pInfo->trans_->status_ == TransRunning)
    {
        printError(ErrWarning, "Transaction is still running\n");
    }
    if (pInfo->want_ != NULL) 
    {
        printError(ErrSysFatal, "Probable data corruption.wants_ is not null\n");
        return ErrSysFatal;
    }
    for (int muti = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (pInfo->has_[muti] !=  NULL) 
        {
            printError(ErrSysFatal, "Probable data corruption.some mutexes are not freed\n");
            pInfo->has_[muti]->releaseLock(); 
            return ErrSysFatal;
        }
    }
    //printf("Slot freed %d %x %d %lu\n", i, pInfo, pid, thrid); 
    pInfo->init();
    return OK;
}

DbRetVal ProcessManager::addMutex(Mutex *mut)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }
    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }
    if (i == Conf::config.getMaxProcs())
    {
        printError(ErrSysFatal, "Logical Error pid %d thrid %lu not found in procTable while adding mutex %s", pid, thrid, mut->name);
        return ErrSysFatal;
    }
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (pInfo->has_[i] ==  NULL) 
        {
            pInfo->has_[i] = mut; 
            return OK;
        }
    }
    printError(ErrSysInternal, "All slots are full. Reached per thread mutex limit.");
    return ErrSysInternal;
}

DbRetVal ProcessManager::removeMutex(Mutex *mut)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }
    if (i == Conf::config.getMaxProcs())
    {
        printError(ErrSysFatal, "Logical Error pid %d thrid %lu not found in procTable", pid, thrid);
        return ErrSysFatal;
    }
    for (int i = 0 ;i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (pInfo->has_[i] ==  mut) 
        {
            pInfo->has_[i] = NULL; 
            return OK;
        }
    }
    printError(ErrSysInternal, "Mutex could not be found in the list");
    return ErrSysInternal;
}

DbRetVal ProcessManager::setTransaction(Transaction *trans)
{
    pid_t pid = os::getpid();
    pthread_t thrid = os::getthrid();
    if (systemDatabase == NULL)
    {
        return OK;
    }

    ThreadInfo* pInfo = systemDatabase->getThreadInfo(0);
    int i=0;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ == pid && pInfo->thrid_ == thrid) break;
        pInfo++;
    }
    if (i == Conf::config.getMaxProcs())
    {
        printError(ErrSysFatal, "Logical Error pid %d thrid %lu not found in procTable", pid, thrid);
        return ErrSysFatal;
    }
    pInfo->trans_ = trans;
    return OK;
}


