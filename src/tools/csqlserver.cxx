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
char* version = "csql-linux-i686-3.0GA";
int srvStop =0;
pid_t asyncpid=0;
pid_t sqlserverpid=0;
pid_t cachepid=0;
pid_t chkptpid=0;
bool recoverFlag=false;
bool monitorServer= false;
SessionImpl *session = NULL;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
    monitorServer=false;
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
    if (ret == -1) {
       if (errno == EPERM) 
          printError(ErrWarning, "No permission to check process %d is alive.");
       else 
          return true;
    }
    return false;
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
    if (info->thrTrans_.trans_ != NULL && info->thrTrans_.trans_->status_ == TransRunning)
    {
        printf("Rollback Transaction %x\n", info->thrTrans_.trans_);
        tm->rollback(lm, info->thrTrans_.trans_);
        info->thrTrans_.trans_->status_ = TransNotUsed;
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


    ThreadInfo* tInfo = sysdb->getThreadInfo(0);
    int i=0;
    ThreadInfo* freeSlot = NULL;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        //check whether it is alive
        if (tInfo->pid_ !=0 && checkDead(tInfo->pid_)) releaseAllResources(sysdb, tInfo);
        tInfo++;
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
    ThreadInfo* tInfo = sysdb->getThreadInfo(0);
    int i=0, count =0;
    ThreadInfo* freeSlot = NULL;
    for (; i < Conf::config.getMaxProcs(); i++)
    {
        if (tInfo->pid_ !=0 ) {
           logFine(Conf::logger, "Registered Procs: %d %lu\n", tInfo->pid_, tInfo->thrid_);
           printf("Client process with pid %d is still registered\n", tInfo->pid_); 
           if( tInfo->pid_ != asyncpid && tInfo->pid_ != cachepid &&
               tInfo->pid_ != sqlserverpid)
               count++;
        }
        tInfo++;
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
void startCheckpointServer()
{
    char execName[1024];
    sprintf(execName, "%s/bin/csqlcheckpointserver", os::getenv("CSQL_INSTALL_ROOT"));
    if (srvStop) return;
    chkptpid = os::createProcess(execName, "csqlcheckpointserver");
    if (chkptpid != -1) {
        printf("Checkpoint Server Started [PID=%d]\n", chkptpid);
        logFine(Conf::logger, "Checkpoint Server Started pid:%d", chkptpid);
    }
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
        char dbRedoFileName[MAX_FILE_LEN];
        char dbChkptSchema[MAX_FILE_LEN];
        char dbChkptMap[MAX_FILE_LEN];
        char dbChkptData[MAX_FILE_LEN];
        char dbBackupFile[MAX_FILE_LEN];
        
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
        int chkptID= Database::getCheckpointID();
        sprintf(dbChkptData, "%s/db.chkpt.data%d", Conf::config.getDbFile(),
                                                   chkptID);
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
            DatabaseManager *dbMgr = session->getDatabaseManager();
            rv = dbMgr->checkPoint();
            if (rv != OK)
            {
                printError(ErrSysInternal, "checkpoint failed after redo log apply");
                Conf::logger.stopLogger();
                session->destroySystemDatabase();
                delete session;
                return 70;
            }
        }
    }
    bool isCacheReq = false, isSQLReq= false, isAsyncReq=false, isChkptReq=false;
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
        int msgid = os::msgget(Conf::config.getMsgKey(), 0666);
        if (msgid != -1) os::msgctl(msgid, IPC_RMID, NULL);
        isAsyncReq = true;
        startAsyncServer();
    }
    if (Conf::config.useCache() && Conf::config.useTwoWayCache()) {
        isCacheReq = true;
        startCacheServer();
    }
    if(Conf::config.useDurability())
    {
        isChkptReq = true;
        startCheckpointServer();
    }

    printf("Database Server Started...\n");
    logFine(Conf::logger, "Database Server Started");
    monitorServer= Conf::config.useMonitorServers();
       
reloop:
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
         
        //send signal to all the registered process..check they are alive
        cleanupDeadProcs(sysdb);
        if (srvStop) break;
        if (monitorServer) {
          if (isCacheReq && cachepid !=0  && checkDead(cachepid)) {
            logFine(Conf::logger, "Cache Receiver Died pid:%d", cachepid);
            startCacheServer();
          }
          if (isAsyncReq && asyncpid !=0  && checkDead(asyncpid)) {
            logFine(Conf::logger, "Async Server Died pid:%d", asyncpid);
            int msgid = os::msgget(Conf::config.getMsgKey(), 0666);
            if (msgid != -1) os::msgctl(msgid, IPC_RMID, NULL);
            startAsyncServer();
          }
          if (isSQLReq && sqlserverpid !=0  && checkDead(sqlserverpid)) {
            logFine(Conf::logger, "Network Server Died pid:%d", sqlserverpid);
            startServiceClient();
          }
          if (isChkptReq && chkptpid !=0  && checkDead(chkptpid)) {
            logFine(Conf::logger, "Checkpoint Server Died pid:%d", chkptpid);
            startCheckpointServer();
          }
       }
    }
    if (logActiveProcs(sysdb) != OK) {srvStop = 0; 
        monitorServer= Conf::config.useMonitorServers();
        goto reloop; 
    }
    if (cachepid) os::kill(cachepid, SIGTERM);
    if(asyncpid) os::kill(asyncpid, SIGTERM);
    if (sqlserverpid) os::kill(sqlserverpid, SIGTERM);
    if (chkptpid) os::kill(chkptpid, SIGTERM);
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
