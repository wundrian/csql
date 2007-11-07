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
#ifndef PROCESS_H
#define PROCESS_H

#include<os.h>
#include<ErrorType.h>
#include<Mutex.h>

class ProcInfo
{
    public:

    pid_t pid_;

    int numThreads_;

};

class ThreadInfo
{
    public:

    pid_t pid_;

    pthread_t thrid_;

    void *want_;  //single mutex which we are waiting for.

    void *has_;   //list of mutexes held

};
class Database;

class ProcessManager
{
    public:
    static int noThreads;
    static Mutex mutex;
    static caddr_t sysAddr;
    static caddr_t usrAddr;
    Database *systemDatabase;
    //ProcInfo *procInfo;
    //ThreadInfo *thrInfo;
    ProcessManager(Database *sysdb) { systemDatabase = sysdb; //procInfo = NULL; thrInfo = NULL; 
    }
    DbRetVal registerThread();
    DbRetVal deregisterThread();
};

#endif
