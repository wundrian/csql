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
#include<os.h>
#include<CSql.h>
#include<SessionImpl.h>
#include<Debug.h>
#include<Process.h>
#include<Database.h>
#include<Transaction.h>
#include<Lock.h>
#include<CacheTableLoader.h>
char* version = "csql-linux-i686-2.0GA";
int srvStop =0;
pid_t sqlserverpid=0;
pid_t cachepid=0;
bool recoverFlag=false;
void dumpData();
SessionImpl *session = NULL;
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
            printf("Dead Procs: %d %lu holding mutex %x %s \n", info->pid_, info->thrid_, info->has_[i], info->has_[i]->name);
            logFine(Conf::logger, "Dead Procs: %d %lu holding mutex %x %s \n", info->pid_, info->thrid_, info->has_[i], info->has_[i]->name);
            //TODO::recovery of mutexes 
            sysdb->recoverMutex(info->has_[i]);
            //srvStop = 1;
            //return ErrSysFatal;
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
            info->thrTrans_[i].trans_->status_ = TransNotUsed;
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
    int i=0, count =0;
    ThreadInfo* freeSlot = NULL;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (pInfo->pid_ !=0 ) {
           logFine(Conf::logger, "Registered Procs: %d %lu\n", pInfo->pid_, pInfo->thrid_);
           printf("Client process with pid %d is still registered\n", pInfo->pid_); 
           count++;
        }
        pInfo++;
    }
    sysdb->releaseProcessTableMutex(false);
    if (count) return ErrSysInternal; else return OK;
}
void startCacheServer()
{
     printf("Starting Cache Recv Server\n");
     char execName[1024];
     sprintf(execName, "%s/bin/csqlcacheserver", os::getenv("CSQL_INSTALL_ROOT"));
     printf("filename is %s\n", execName);
     cachepid = os::createProcess(execName, "csqlcacheserver");
     if (cachepid != -1)
         printf("Cache Recv Server Started pid=%d\n", cachepid);
     return;
}

void startServiceClient()
{
     printf("Starting Csql Network Daemon\n");
     char execName[1024];
     sprintf(execName, "%s/bin/csqlsqlserver", os::getenv("CSQL_INSTALL_ROOT"));
     printf("filename is %s\n", execName);
     sqlserverpid = os::createProcess(execName, "csqlsqlserver");
     if (sqlserverpid != -1)
         printf("Csql Network Daemon Started pid=%d\n", sqlserverpid);
     return;
}

void printUsage()
{
   printf("Usage: csqlserver [-c] [-v]\n");
   printf("       v -> print the version.\n");
   printf("       c -> recover all cached tables from the target database.\n");
   printf("Description: Start the csql server and initialize the database.\n");
   return;
}
int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "cv?")) != EOF) 
    {
        switch (c)
        {
            case '?' : { opt = 10; break; } //print help 
            case 'c' : { opt = 1; break; } //recover all the tables from cache
            case 'v' : { opt = 2; break; } //print version
            default: opt=10; 

        }
    }//while options

    if (opt == 10) {
        printUsage();
        return 0;
    }else if (opt ==2) {
        printf("%s\n",version);
        return 0;
    }
    session = new SessionImpl();
    DbRetVal rv = session->readConfigFile();
    if (rv != OK)
    {
        printf("Unable to read the configuration file \n");
        return 1;
    }
    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    rv = Conf::logger.startLogger(Conf::config.getLogFile(), true);
    if (rv != OK)
    {
        printf("Unable to start the logger\n");
        return 2;
    }
    bool isInit = true;
    logFine(Conf::logger, "Server Started");
    int ret  = session->initSystemDatabase();
    if (0  != ret)
    {
        //printf(" System Database Initialization failed\n");
        printf("Attaching to exising database\n");
        isInit = false;
        delete session;
        session = new SessionImpl();
        ret = session->open(DBAUSER, DBAPASS);
        if (ret !=0) {
            printf("Unable to attach to existing database\n");
            return 3;
        }
    }else { 
        printf("System Database initialized\n");
    }

    bool end = false;
    struct timeval timeout, tval;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    Database* sysdb = session->getSystemDatabase();
    recoverFlag = false;
    if(isInit && Conf::config.useDurability())
    {
        char dbChkptFileName[1024];
        char dbRedoFileName[1024];
        char cmd[1024];
        sprintf(dbChkptFileName, "%s/csql.db.chkpt", Conf::config.getDbFile());
        if (FILE *file = fopen(dbChkptFileName, "r"))
        {
            fclose(file);
            sprintf(cmd, "csql -X -s %s",dbChkptFileName); 
            int ret = system(cmd);
            if (ret != 0) { 
                printf("Tables cannot be recovered. chkpt file corrupted\n");
            }
        }
        sprintf(dbRedoFileName, "%s/csql.db.cur", Conf::config.getDbFile());
        if (FILE *file = fopen(dbRedoFileName, "r"))
        {
            fclose(file);
            int ret = system("redo -a");
            if (ret != 0) { 
                printf("Recovery failed. Redo log file corrupted\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 10;
            }
        //TODO::generate checkpoint file
            sprintf(cmd, "csqldump -X > %s",dbChkptFileName); 
            ret = system(cmd);
            if (ret != 0) { 
                printf("Unable to create checkpoint file\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 11;
            }
            ret = unlink(dbRedoFileName);
            if (ret != 0) { 
                printf("Unable to delete redo log file. Delete and restart the server\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 11;
            }
        }
    }
    recoverFlag = true;
    if (opt == 1 && isInit && ! Conf::config.useDurability()) {
        if (Conf::config.useCache()) {
            printf("Database server recovering cached tables...\n");
            int ret = system("cachetable -U root -P manager -R");
            if (ret != 0) { 
                printf("Cached Tables recovery failed %d\n", ret);
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 2;
            }
            printf("Cached Tables recovered\n");
        } else {
            printf("Cache mode is not set in csql.conf. Cannot recover\n");
            Conf::logger.stopLogger();
            session->destroySystemDatabase();
            delete session;
            return 1;
        }
    }
    GlobalUniqueID UID;
    if (isInit) UID.create();
    //TODO:: kill all the child servers and restart if !isInit
    
    bool isCacheReq = false, isSQLReq= false;
    if(Conf::config.useCsqlSqlServer()) {
        isSQLReq = true;
        startServiceClient();
    }
    if (Conf::config.useCache() && Conf::config.useTwoWayCache()) {
        isCacheReq = true;
        startCacheServer();
    }
    printf("Database server started\n");
reloop:
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
        
        //send signal to all the registered process..check they are alive
        cleanupDeadProcs(sysdb);

        //TODO::if it fails to start 5 times, exit
        if (isCacheReq && cachepid !=0  && checkDead(cachepid)) 
              startCacheServer();
        if (isSQLReq && sqlserverpid !=0  && checkDead(sqlserverpid)) 
              startServiceClient();
    }
    if (logActiveProcs(sysdb) != OK) {srvStop = 0; goto reloop; }
    os::kill(cachepid, SIGTERM);
    os::kill(sqlserverpid, SIGTERM);
    //if (recoverFlag) dumpData();
    logFine(Conf::logger, "Server Exiting");
    printf("Server Exiting\n");
    logFine(Conf::logger, "Server Ended");
    UID.destroy();
    Conf::logger.stopLogger();
    session->destroySystemDatabase();
    delete session;
    return 0;
}
void dumpData()
{
    char cmd[1024];
    //TODO::TAKE exclusive lock
    sprintf(cmd, "csqldump >%s/csql.db.chkpt.1",Conf::config.getDbFile()); 
    int ret = system(cmd);
    if (ret != 0) return;
    sprintf(cmd, "rm -rf %s/csql.db.cur", Conf::config.getDbFile());
    if (ret != 0) return;
    sprintf(cmd, "mv %s/csql.db.chkpt.1 %s/csql.db.chkpt", Conf::config.getDbFile());
    if (ret != 0) return;
    return;
}
