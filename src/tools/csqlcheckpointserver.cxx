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
#include <AbsSqlConnection.h>
#include <AbsSqlStatement.h>
#include <SqlConnection.h>
#include <SqlStatement.h>
#include <SqlFactory.h>
#include <CSql.h>
#include <SessionImpl.h>
#include <NanoTimer.h>

int srvStop =0;
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


void printUsage()
{
   printf("Usage: csqlcheckpointserver \n");
   printf("Description: Start the csql checkpoint server.\n");
   return;
}
DbRetVal takeCheckpoint()
{
    char fileName[MAX_FILE_LEN];
    sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    if (::access(fileName, F_OK) != 0 ) return OK;
    int fileSize = os::getFileSize(fileName);
    logFine(Conf::logger, "Redo log file size %d", fileSize);
    if (fileSize < Conf::config.getChkptRedoLimit()) return  OK;

    Connection conn;
    DbRetVal rv = conn.open(I_USER, I_PASS);
    if (rv != OK) return rv;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    NanoTimer timer;
    timer.reset();
    timer.start();
    int tries = 0, totalTries=10;
    while(tries < totalTries) {
       rv = dbMgr->checkPoint();
           if (rv == ErrLoadingOn) {
           conn.close();
           timer.stop();
           return rv;
       }
       if (rv == ErrLockTimeOut) {
          os::sleep(1); //sleep for 1 second
       } else if (rv != OK) {
          printError(rv, "checkpoint: failed");
          conn.close();
          timer.stop();
          return rv;
       }else  if (rv == OK) break;
       tries++;
    }
    timer.stop();
    if (rv != ErrLockTimeOut) {
        logFine(Conf::logger, "Checkpoint taken %lld microsecs", timer.avg()/1000);
        //printf("Time Taken for checkpoint %lld\n", timer.avg()/1000/1000);
    } else {
        logFine(Conf::logger, "Checkpoint:Could not get TXN consistent point");
    }
    conn.close();
    return OK;
}
int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "?")) != EOF) 
    {
        switch (c)
        {
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 

        }
    }//while options

    if (opt == 10) {
        printUsage();
        return 0;
    }
    SessionImpl session;
    DbRetVal rv = session.readConfigFile();
    if (rv != OK)
    {
        printError(ErrSysInternal,"Unable to read the configuration file \n");
        return 1;
    }
    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    os::signal(SIGCHLD, sigChildHandler);

    if (!Conf::config.useDurability())
    {
        printError(ErrSysInternal, "Durablity is set to OFF in csql.conf file\n");
        return 1;
    } 
    logFine(Conf::logger, "CSQL Checkpoint server started");
    int ret = 0;
    struct timeval timeout, tval;
    timeout.tv_sec = Conf::config.getChkptSecs();
    tval.tv_usec = 0;
    
    while(!srvStop)
    {
        tval.tv_sec = timeout.tv_sec;
        ret = os::select(0, 0, 0, 0, &tval);
        if (srvStop) break;
        takeCheckpoint();
    }
    printf("Csql Checkpoint Daemon Exiting\n");
    logFine(Conf::logger, "CSQL Checkpoint server exiting");
    return 0;
}
