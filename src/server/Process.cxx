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


//It does not check for re registering as well as deregistering unregistered threads.
//as it is handled in the connection class open and close methods.
DbRetVal ProcessManager::registerThread()
{
    DbRetVal rv = systemDatabase->getProcessTableMutex();
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
    pid_t pid;
    if (appPid == 0)
    {
        //first thread to register
        pid = os::getpid();
        appPid = pid;
    } else
    {
        pid = appPid;
    }
    pthread_t thrid = os::getthrid();
    printf("global pid is %d\n", appPid);
    ProcInfo* pInfo = systemDatabase->getProcInfo(0);
    int i=0;
    ProcInfo* freeSlot = NULL;
    int freeSlotPos =0;
    bool freeSlotSelected = false;
    for (; i < config.getMaxProcs(); i++)
    {
        //printf("Reg: Address %x, pid %d lpid %d:\n", pInfo, pInfo->pid_, pid);
        if (pInfo->pid_ == pid ) break;
        if (!freeSlotSelected && 0 == pInfo->pid_) 
        { 
            freeSlot = pInfo; 
            freeSlotPos = i;
            freeSlotSelected=true; 
        }
        pInfo++;
    }
    if (i == config.getMaxProcs()) 
    {
        //First thread to register.
        printf("Register: First thread to register pid %d\n", freeSlotPos);
        ThreadInfo *tInfo =systemDatabase->getThreadInfo(freeSlotPos, 0);
        tInfo->thrid_ = thrid;
        tInfo->pid_ = pid;
        freeSlot->pid_ = pid;
        //printf("Address:: %x\n", freeSlot);
        freeSlot->numThreads_ = 1;
    } else
    {
        ThreadInfo *tInfo = systemDatabase->getThreadInfo(i, 0);
        int j =0;
        for (; j < config.getMaxThreads(); j++)
        {
        printf("Reg: Address %x, tid %d :\n", tInfo, tInfo->thrid_);

            if (0 == tInfo->thrid_)
            {
                tInfo->thrid_ = thrid;
                tInfo->pid_ = pid;
                break;
            }
            tInfo++;
        }
        if ( j == config.getMaxThreads())
        {
            systemDatabase->releaseProcessTableMutex();
            printError(ErrNoResource, "No free thread slot. Limit reached");
            return ErrNoResource;
        }
        printf("Register:pid slot taken is %d and thrslot %d\n", i, j);

        pInfo->numThreads_++;
    }
    systemDatabase->releaseProcessTableMutex();
    return OK;
}
DbRetVal ProcessManager::deregisterThread()
{
    DbRetVal rv = systemDatabase->getProcessTableMutex();
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
    if (appPid == 0)
    {
        systemDatabase->releaseProcessTableMutex();
        printError(ErrSysInternal, "Process not registered\n");
        return ErrSysInternal;
    }
    pid_t pid = appPid;
    pthread_t thrid = os::getthrid();

    ProcInfo* pInfo = systemDatabase->getProcInfo(0);
    int i=0;
    for (; i < config.getMaxProcs(); i++)
    {
        //printf("Address %x, pid %d :", pInfo, pInfo->pid_);
        if (pInfo->pid_ == pid ) break;
        pInfo++;
    }
    if (i == config.getMaxProcs()) 
    {
        systemDatabase->releaseProcessTableMutex();
        printError(ErrSysFatal, "Degistering process %d is not registered with csql", pid);
        return ErrNoResource;
    }
    ThreadInfo *tInfo = systemDatabase->getThreadInfo(i, 0);
    printf("Deregister: pid slot taken is %d ", i);

    i=0;
    for (; i < config.getMaxThreads(); i++)
    {
        if (thrid == tInfo->thrid_)
        {
            tInfo->thrid_ = 0;
            tInfo->pid_ = 0;
            tInfo->want_ = NULL;
            tInfo->has_ = NULL;
            break;
        }
        tInfo++;
    }
    if ( i == config.getMaxThreads())
    {
        systemDatabase->releaseProcessTableMutex();
        printError(ErrSysFatal, "Degistering Pid %d Thread %d is not registered with csql", pid, thrid);
        return ErrNoResource;
    }
    pInfo->numThreads_--;
    printf("and thrslot %d nothreads %d\n", i ,pInfo->numThreads_ );

    if (0 == pInfo->numThreads_) pInfo->pid_ = 0;

    systemDatabase->releaseProcessTableMutex();
    return OK;
}

