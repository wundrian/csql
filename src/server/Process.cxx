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
//It does not check for re registering as well as deregistering unregistered threads.
//as it is handled in the connection class open and close methods.
DbRetVal ProcessManager::registerThread()
{
    mutex.getLock();
    noThreads++;
    mutex.releaseLock();
    DbRetVal rv = systemDatabase->getProcessTableMutex();
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

    pInfo->pid_ = pid;
    pInfo->thrid_ = thrid;
    systemDatabase->releaseProcessTableMutex();
    return OK;
}
DbRetVal ProcessManager::deregisterThread()
{
    mutex.getLock();
    noThreads++;
    mutex.releaseLock();
    DbRetVal rv = systemDatabase->getProcessTableMutex();
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
    if (i == Conf::config.getMaxProcs()) 
    {
        systemDatabase->releaseProcessTableMutex();
        printError(ErrSysFatal, "Degistering process %d is not registered with csql", pid);
        return ErrNoResource;
    }
    pInfo->thrid_ = 0;
    pInfo->pid_ = 0;
    pInfo->want_ = NULL;
    pInfo->has_ = NULL;
    //TODO::check if wants_ is empty, if not report error

    //TODO::check if has_ is empty.If not report that and release all the mutexes in has_
    systemDatabase->releaseProcessTableMutex();
    return OK;
}

