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
#include<sys/wait.h> //TODO::move this to os.h
char* version = "csql-linux-i686-3.0GA";
int srvStop =0;
pid_t asyncpid=0;
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
static void sigChildHandler(int sig)
{
    os::signal(SIGCHLD, sigChildHandler);
    int stat;
    waitpid(-1, &stat, WNOHANG);
    //TODO::move waitpid to os wrapper
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
           if( pInfo->pid_ != asyncpid && pInfo->pid_ != cachepid &&
               pInfo->pid_ != sqlserverpid)
               count++;
        }
        pInfo++;
    }
    sysdb->releaseProcessTableMutex(false);
    if (count) return ErrSysInternal; else return OK;
}
void startCacheServer()
{
     char execName[1024];
     sprintf(execName, "%s/bin/csqlcacheserver", os::getenv("CSQL_INSTALL_ROOT"));
     if (srvStop) return;
     //printf("filename is %s\n", execName);
     cachepid = os::createProcess(execName, "csqlcacheserver");
     if (cachepid != -1)
     printf("Cache Receiver Started\t   [PID=%d]\n",cachepid);
     return;
}

void startServiceClient()
{
     char execName[1024];
     sprintf(execName, "%s/bin/csqlsqlserver", os::getenv("CSQL_INSTALL_ROOT"));
     //printf("filename is %s\n", execName);
     if (srvStop) return;
     sqlserverpid = os::createProcess(execName, "csqlsqlserver");
     if (sqlserverpid != -1)
     printf("Network Server Started\t   [PID=%d] [PORT=%d]\n", sqlserverpid,Conf::config.getPort());

     return;
}

void startAsyncServer()
{
     char execName[1024];
     sprintf(execName, "%s/bin/csqlasyncserver", os::getenv("CSQL_INSTALL_ROOT"));
     //printf("filename is %s\n", execName);
     if (srvStop) return;
     asyncpid = os::createProcess(execName, "csqlasyncserver");
     if (asyncpid != -1)
         printf("Async Cache Server Started [PID=%d]\n", asyncpid);
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
    int c = 0,opt = 0;
    char cmd[1024];
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
    os::signal(SIGCHLD, sigChildHandler);
    rv = Conf::logger.startLogger(Conf::config.getLogFile(), true);
    if (rv != OK)
    {
        printf("Unable to start the Conf::logger\n");
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
    }
    bool end = false;
    struct timeval timeout, tval;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    Database* sysdb = session->getSystemDatabase();
    recoverFlag = false;
    
    GlobalUniqueID UID;
    if (isInit) UID.create();

    if(isInit && Conf::config.useDurability())
    {
        char dbRedoFileName[1024];
        char dbChkptSchema[1024];
        char dbChkptMap[1024];
        char dbChkptData[1024];
        char dbBackupFile[1024];
        
        //check for check point file if present recover 
        sprintf(dbChkptSchema, "%s/db.chkpt.schema1", Conf::config.getDbFile());
        if (FILE *file = fopen(dbChkptSchema, "r")) {
            fclose(file);
            sprintf(cmd, "cp -f %s %s/db.chkpt.schema", dbChkptSchema, Conf::config.getDbFile());
            int ret = system(cmd);
            if (ret != 0) {
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 20;
            }
        }
        sprintf(dbChkptMap, "%s/db.chkpt.map1", Conf::config.getDbFile());
        if (FILE *file = fopen(dbChkptMap, "r")) {
            fclose(file);
            sprintf(cmd, "cp -f %s %s/db.chkpt.map", dbChkptMap, Conf::config.getDbFile());
            int ret = system(cmd);
            if (ret != 0) {
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 30;
            }
        }
        sprintf(dbChkptData, "%s/db.chkpt.data", Conf::config.getDbFile());
        sprintf(dbBackupFile, "%s/db.chkpt.data1", Conf::config.getDbFile());
        FILE *fl = NULL;
        if (!Conf::config.useMmap() && (fl = fopen(dbBackupFile, "r"))) {
            fclose(fl);
            sprintf(cmd, "cp %s/db.chkpt.data1 %s", Conf::config.getDbFile(), dbChkptData);
            int ret = system(cmd);
            if (ret != 0) {
                printError(ErrOS, "Unable to take backup for chkpt data file");
                return 40;
            }
        }
        if (FILE *file = fopen(dbChkptData, "r")) {
            fclose(file);
            int ret = system("recover");
            if (ret != 0) {
                printf("Recovery failed\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 50;
            }
        }

        //check for redo log file if present apply redo logs
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
                return 60;
            }

            // take check point at this moment 
            sprintf(dbChkptSchema, "%s/db.chkpt.schema", Conf::config.getDbFile());
            sprintf(dbChkptMap, "%s/db.chkpt.map", Conf::config.getDbFile());
            sprintf(dbChkptData, "%s/db.chkpt.data", Conf::config.getDbFile());
            ret = system("checkpoint");
            if (ret != 0) {
                printf("Unable to create checkpoint file. Database corrupted.\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 70;
            }
            ret = unlink(dbRedoFileName);
            if (ret != 0) { 
                printf("Unable to delete redo log file. Delete and restart the server\n");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 80;
            }
        }
    }
    bool isCacheReq = false, isSQLReq= false;
    recoverFlag = true;
    if (opt == 1 && isInit && ! Conf::config.useDurability()) {
        if (Conf::config.useCache()) {
            printf("Database server recovering cached tables...\n");
            int ret = system("cachetable -R");
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
    //TODO:: kill all the child servers and restart if !isInit
    
    if(Conf::config.useCsqlSqlServer()) {
        isSQLReq = true;
        startServiceClient();
    }
    if ( (Conf::config.useCache() && 
           Conf::config.getCacheMode()==ASYNC_MODE)) {
        startAsyncServer();
    }
    if (Conf::config.useCache() && Conf::config.useTwoWayCache()) {
        isCacheReq = true;
        startCacheServer();
    }
    printf("Database Server Started...\n");
       
reloop:
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
         
        //send signal to all the registered process..check they are alive
        cleanupDeadProcs(sysdb);
        if (srvStop) break;
        //TODO::if it fails to start 5 times, exit
        if (isCacheReq && cachepid !=0  && checkDead(cachepid)) 
              startCacheServer();
    }
    if (logActiveProcs(sysdb) != OK) {srvStop = 0; goto reloop; }
    if (cachepid) os::kill(cachepid, SIGTERM);
    if(asyncpid) os::kill(asyncpid, SIGTERM);
    if (sqlserverpid) os::kill(sqlserverpid, SIGTERM);
    //if (recoverFlag) dumpData();
    if (Conf::config.useDurability() && Conf::config.useMmap()) {
        //ummap the memory 
        char *startAddr = (char *) sysdb->getMetaDataPtr();
        msync(startAddr + Conf::config.getMaxSysDbSize(),Conf::config.getMaxDbSize(), MS_SYNC);
        munmap(startAddr + Conf::config.getMaxSysDbSize(), Conf::config.getMaxDbSize());
    }
    logFine(Conf::logger, "Server Exiting");
    printf("Server Exiting\n");
    logFine(Conf::logger, "Server Ended");
    UID.destroy();
    session->destroySystemDatabase();
    Conf::logger.stopLogger();
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
