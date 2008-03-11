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
    int maxProcs;
    long maxSysSize;
    long maxDbSize;
    int sysDbKey;
    int userDbKey;
    char logFile[MAX_FILE_PATH_LEN];
    long mapAddr;
    int mutexSecs;
    int mutexUSecs;
    int mutexRetries;
    int lockSecs;
    int lockUSecs;
    int lockRetries;

    bool isCache;
    char dsn[IDENTIFIER_LENGTH];
    char tableConfigFile[MAX_FILE_PATH_LEN];

    bool isReplication;
    char replConfigFile[MAX_FILE_PATH_LEN];
    int networkID;
    int cacheNetworkID;

    long logStoreSize;
    int nwResponseTimeout;
    int nwConnectTimeout;

    ConfigValues()
    {
        pageSize = 8192;
        maxProcs = 20;
        maxSysSize = 10485760;
        maxDbSize = 104857600;
        sysDbKey = 2222;
        userDbKey = 5555;
        strcpy(logFile, "/tmp/log/log.out");
        mapAddr=400000000;
        mutexSecs=0;
        mutexUSecs=10;
        mutexRetries = 10;
        lockSecs =0;
        lockUSecs = 10;
        lockRetries = 10;
        isCache = false;
        cacheNetworkID =-1;
        strcpy(dsn, "myodbc3");
        strcpy(tableConfigFile, "/tmp/csql/csqltable.conf");
        isReplication = false;
        strcpy(replConfigFile, "/tmp/csql/csqlnw.conf");
        logStoreSize = 10485760;
        networkID=-1;
        nwResponseTimeout=3;
        nwConnectTimeout=5;
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
    void print();

    inline int getPageSize() { return cVal.pageSize; }
    inline int getMaxProcs() { return cVal.maxProcs; }
    inline long getMaxSysDbSize() { return cVal.maxSysSize; }
    inline long getMaxDbSize() { return cVal.maxDbSize; }
    inline int getSysDbKey() { return cVal.sysDbKey; }
    inline int getUserDbKey() { return cVal.userDbKey; }
    inline char* getLogFile() { return cVal.logFile; }
    inline long getMapAddress() { return cVal.mapAddr; }
    inline int getMutexSecs() { return cVal.mutexSecs; }
    inline int getMutexUSecs() { return cVal.mutexUSecs; }
    inline int getMutexRetries() { return cVal.mutexRetries; }
    inline int getLockSecs() { return cVal.lockSecs; }
    inline int getLockUSecs() { return cVal.lockUSecs; }
    inline int getLockRetries() { return cVal.lockRetries; }
    inline bool useCache() { return cVal.isCache; }
    inline char* getDSN() { return cVal.dsn; }
    inline char* getTableConfigFile() { return cVal.tableConfigFile; }
    inline bool useReplication() { return cVal.isReplication; }
    inline char* getReplConfigFile() { return cVal.replConfigFile; }
    inline long getMaxLogStoreSize() { return cVal.logStoreSize; }
    inline int getNetworkID() { return cVal.networkID; }
    inline int getCacheNetworkID() { return cVal.cacheNetworkID; }
    inline int getNetworkResponseTimeout() { return cVal.nwResponseTimeout; }
    inline int getNetworkConnectTimeout() { return cVal.nwConnectTimeout; }
};

class Conf
{
    public:
    static Config config;
};


#endif
