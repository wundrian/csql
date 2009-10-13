/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H
#include<os.h>
#include<Util.h>

enum CacheMode {
    SYNC_MODE=0,
    ASYNC_MODE=1,
    UNKNOWN=100
};
enum TDBInfo
{
    mysql=0,
    postgres
};

class ConfigValues
{
    public:
    //All the members of the configuration file
    char logFile[MAX_FILE_PATH_LEN];
    char dbFile[MAX_FILE_PATH_LEN];
    char tableConfigFile[MAX_FILE_PATH_LEN];
    char dsConfigFile[MAX_FILE_PATH_LEN];// DSN Config file
    char stderrFile[MAX_FILE_PATH_LEN];
    char conflResoFile[MAX_FILE_PATH_LEN];
    
    bool isDurable;
    bool mmap;
    bool isCsqlSqlServer;
    bool isCache;
    bool isTwoWay;
    
    int siteID;
    int sysDbKey;
    int userDbKey;
    long maxSysSize;
    long maxDbSize;
    int pageSize;
    int maxProcs;

    long mapAddr;
    
    int mutexSecs;
    int mutexUSecs;
    int mutexRetries;
    int lockSecs;
    int lockUSecs;
    int lockRetries;
    int logLevel;
    
    int durableMode;
    char dsn[IDENTIFIER_LENGTH];
    CacheMode mode;
    int cacheWaitSecs;
    
    int port;
    int nwResponseTimeout;
    int nwConnectTimeout;

    int msgKey;
    int asyncMsgMax;
    int shmKeyForId;
    long maxQueueLogs;
    int noOfProcessors;
    int stmtCacheSize;
    bool isCacheNoParam;


    ConfigValues()
    {
        strcpy(logFile, "/tmp/log/log.out");
        strcpy(dbFile, "/tmp/csql/db");
        strcpy(tableConfigFile, "/tmp/csql/csqltable.conf");
        strcpy(dsConfigFile,"/tmp/csql/csqlds.conf"); // DSN Config file
        strcpy(stderrFile, "stderr");
        strcpy(conflResoFile, "/tmp/csql/ConflResoFile.txt");
        
        isDurable = false;        
        mmap = false;
        isCsqlSqlServer = false;
        isCache = false;
        isTwoWay=false;
       
        siteID=1;
        sysDbKey = 2222;
        userDbKey = 5555;
        maxSysSize = 10485760;
        maxDbSize = 104857600;
        pageSize = 8192;
        maxProcs = 20;
        
        mapAddr=400000000;
 
        mutexSecs=0;
        mutexUSecs=10;
        mutexRetries = 10;
        lockSecs =0;
        lockUSecs = 10;
        lockRetries = 10;
        logLevel = 0;
        
        durableMode=1;
        strcpy(dsn,"myodbc3");
        mode = SYNC_MODE;
        cacheWaitSecs =10;
        
        port = 5678;
        nwResponseTimeout=3;
        nwConnectTimeout=5;
        msgKey=-1;
        asyncMsgMax = 8192; //default for linux 
        shmKeyForId = -1;
        maxQueueLogs = 100;
        noOfProcessors = 1;
        stmtCacheSize = 10;
        isCacheNoParam = false;

    }
};

class Config
{
    ConfigValues cVal;
    bool isLoaded;
    int readLine(FILE *fp, char * buffer);
    int storeKeyVal(char *key, char *val);
    int validateValues();

    public:
    Config() { isLoaded = false; }
    int readAllValues(char *filename);
    void print();
    void logConfig();
    inline int getPageSize() { return cVal.pageSize; }
    inline int getMaxProcs() { return cVal.maxProcs; }
    inline long getMaxSysDbSize() { return cVal.maxSysSize; }
    inline long getMaxDbSize() { return cVal.maxDbSize; }
    inline int getSysDbKey() { return cVal.sysDbKey; }
    inline int getUserDbKey() { return cVal.userDbKey; }
    inline bool useMmap() { return cVal.mmap; }
    inline char* getLogFile() { return cVal.logFile; }
    inline char* getDbFile() { return cVal.dbFile; }
    inline long getMapAddress() { return cVal.mapAddr; }
    inline int getMutexSecs() { return cVal.mutexSecs; }
    inline int getMutexUSecs() { return cVal.mutexUSecs; }
    inline int getMutexRetries() { return cVal.mutexRetries; }
    inline int getLockSecs() { return cVal.lockSecs; }
    inline int getLockUSecs() { return cVal.lockUSecs; }
    inline int getLockRetries() { return cVal.lockRetries; }
    inline int getSiteID(){ return cVal.siteID;}
    inline bool useCache() { return cVal.isCache; }
    inline int getCacheMode() { return (int) cVal.mode; }
    inline char* getDSN() { return cVal.dsn; }
    inline char* getDsConfigFile() { return cVal.dsConfigFile; } 
    inline char* getTableConfigFile() { return cVal.tableConfigFile; }
    inline char* getStderrFile() { return cVal.stderrFile; }
    inline bool useDurability() { return cVal.isDurable; }
    inline int getDurableMode() { return cVal.durableMode; }
    inline bool useCsqlSqlServer() { return cVal.isCsqlSqlServer; }
    inline int getPort() { return cVal.port; }
    inline char* getConflResoFile() { return cVal.conflResoFile; }
    inline long getMaxQueueLogs() { return cVal.maxQueueLogs; }
    inline int getMsgKey() { return cVal.msgKey; }
    inline int getAsyncMsgMax() { return cVal.asyncMsgMax; }
    inline int getShmIDKey() { return cVal.shmKeyForId; }
    inline int getNetworkResponseTimeout() { return cVal.nwResponseTimeout; }
    inline int getNetworkConnectTimeout() { return cVal.nwConnectTimeout; }
    inline bool useTwoWayCache() { return cVal.isTwoWay; }
    inline int getCacheWaitSecs() { return cVal.cacheWaitSecs; }
    inline int getLogLevel() { return cVal.logLevel; }
    inline int getNoOfProcessors() { return cVal.noOfProcessors; }
    inline int getStmtCacheSize() { return cVal.stmtCacheSize; }
    inline bool useCacheNoParam() { return cVal.isCacheNoParam; }

};

class Conf
{
    public:
    static Config config;
    static Logger logger;
};

#endif
