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
#ifndef CONFIG_H
#define CONFIG_H
#include<os.h>
class ConfigValues
{
    public:
    //All the members of the configuration file
    int pageSize;
    int maxTrans;
    int maxProcs;
    long maxSysSize;
    long maxDbSize;
    int sysDbKey;
    int userDbKey;
    char logFile[256];
    long mapAddr;
    int mutexSecs;
    int mutexUSecs;


    ConfigValues()
    {
        pageSize = 8192;
        maxTrans = 20;
        maxProcs = 20;
        maxSysSize = 1048576;
        maxDbSize = 1048576;
        sysDbKey = 2222;
        userDbKey = 5555;
        strcpy(logFile, "/tmp/log.out");
        mapAddr=400000000;
        mutexSecs=0;
        mutexUSecs=10;
    }
};

class Config
{
    ConfigValues cVal;
    int readLine(FILE *fp, char * buffer);
    int storeKeyVal(char *key, char *val);
    int validateValues();

    public:
    int readAllValues(char *filename);

    inline int getPageSize() { return cVal.pageSize; }
    inline int getMaxTrans() { return cVal.maxTrans; }
    inline int getMaxProcs() { return cVal.maxProcs; }
    inline long getMaxSysDbSize() { return cVal.maxSysSize; }
    inline long getMaxDbSize() { return cVal.maxDbSize; }
    inline int getSysDbKey() { return cVal.sysDbKey; }
    inline int getUserDbKey() { return cVal.userDbKey; }
    inline char* getLogFile() { return cVal.logFile; }
    inline long getMapAddress() { return cVal.mapAddr; }
    inline int getMutexSecs() { return cVal.mutexSecs; }
    inline int getMutexUSecs() { return cVal.mutexUSecs; }
};


//Global object
static Config config;


#endif
