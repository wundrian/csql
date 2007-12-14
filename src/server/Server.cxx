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
#include<CSql.h>
#include<SessionImpl.h>
#include<Debug.h>
#include<Process.h>
#include<Database.h>
#include<Transaction.h>
#include<Lock.h>

int srvStop =0;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
}

bool checkDead(pid_t  pid)
{
    int ret = os::kill(pid, 0);
    if (ret == -1) return true; else return false;
}

DbRetVal releaseAllResources(Database *sysdb, ThreadInfo *info )
{
    printf("Releasing all the resources for process %d %lu\n", info->pid_, info->thrid_);
    //recover for all the mutexes in has_
    for (int i =0;  i < MAX_MUTEX_PER_THREAD; i++)
    {
        if (info->has_[i] != NULL) 
        {
            printf("Dead Procs: %d %lu holding mutex %x %s) \n", info->pid_, info->thrid_, info->has_[i], info->has_[i]->name);
            logFine(logger, "Dead Procs: %d %lu holding mutex %x %s) \n", info->pid_, info->thrid_, info->has_[i], info->has_[i]->name);
            //TODO::recovery of mutexes 
            //info->has_[i]->recoverMutex();
            srvStop = 1;
        }
    }
    TransactionManager *tm = new TransactionManager();
    LockManager *lm = new LockManager(sysdb);
    for (int i = 0 ;i < MAX_THREADS_PER_PROCESS; i++)
    {
        if (info->thrTrans_[i].trans_ != NULL && info->thrTrans_[i].trans_->status_ == TransRunning)
        {
            printf("Rollback Transaction %x\n", info->thrTrans_[i].trans_);
            tm->rollback(lm, info->thrTrans_[i].trans_);
        }
    }
    info->init();
    delete tm;
    delete lm;
    return OK;
}

DbRetVal cleanupDeadProcs(Database *sysdb)
{
    DbRetVal rv = sysdb->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
    pid_t pid;
    pid = os::getpid();
    pthread_t thrid = os::getthrid();


    ThreadInfo* pInfo = sysdb->getThreadInfo(0);
    int i=0;
    ThreadInfo* freeSlot = NULL;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        //check whether it is alive
        if (pInfo->pid_ !=0 && checkDead(pInfo->pid_)) releaseAllResources(sysdb, pInfo);
        pInfo++;
    }
    sysdb->releaseProcessTableMutex(false);
    return OK;
}


DbRetVal logActiveProcs(Database *sysdb)
{
    DbRetVal rv = sysdb->getProcessTableMutex(false);
    if (OK != rv)
    {
        printError(rv,"Unable to get process table mutex");
        return rv;
    }
    ThreadInfo* pInfo = sysdb->getThreadInfo(0);
    int i=0;
    ThreadInfo* freeSlot = NULL;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ !=0 )  logFine(logger, "Registered Procs: %d %lu\n", pInfo->pid_, pInfo->thrid_);
        pInfo++;
    }
    sysdb->releaseProcessTableMutex(false);
    return OK;
}



int main()
{
    SessionImpl session;
    DbRetVal rv = session.readConfigFile();
    if (rv != OK)
    {
        printf("Unable to read the configuration file \n");
        return 1;
    }
    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    rv = logger.startLogger(Conf::config.getLogFile(), true);
    if (rv != OK)
    {
        printf("Unable to start the logger\n");
        return 2;
    }

    logFine(logger, "Server Started");
    int ret  = session.initSystemDatabase();
    if (0  != ret)
    {
        printf(" System Database Initialization failed\n");
        return 3;
    }
    printf("System Database initialized\n");


    printf("Database server started\n");
    bool end = false;

    struct timeval timeout, tval;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    Database* sysdb = session.getSystemDatabase();

    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
        
        //send signal to all the registered process..check they are alive
        cleanupDeadProcs(sysdb);
        
    }
   
    logFine(logger, "Server Exiting");
    logActiveProcs(sysdb);
    printf("Server Exiting\n");
    logFine(logger, "Server Ended");
    logger.stopLogger();
    session.destroySystemDatabase();
    return 0;
}
