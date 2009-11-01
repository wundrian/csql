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
#include<Config.h>
#include<ErrorType.h>
#include<Debug.h>

Config Conf::config;

int Config::readLine(FILE *fp, char * buffer)
{
  char c =0;
  int count =0;
  while (true)
  {
      c = fgetc(fp);
      if (c == '\n') break;
      if (c == EOF) return EOF;
      buffer[count++] = c;
  }
  return count;
}
int Config::storeKeyVal(char *key, char *value)
{
    if (os::os::strcasestr(key, "PAGE_SIZE") != NULL )
           { cVal.pageSize = atoi(value);  }
    else if (os::strcasestr(key, "MAX_PROCS") != NULL)
           { cVal.maxProcs = atoi(value);  }
    else if (os::strcasestr(key, "MAX_SYS_DB_SIZE") != NULL)
           { cVal.maxSysSize = atol(value);  }
    else if (os::strcasestr(key, "MAX_DB_SIZE") != NULL)
           { cVal.maxDbSize = atol(value);  }
    else if (os::strcasestr(key, "MMAP") != NULL)
           { cVal.mmap = os::atobool(value);  }
    else if (os::strcasestr(key, "SYS_DB_KEY") != NULL)
           { cVal.sysDbKey = atoi(value);  }
    else if (os::strcasestr(key, "USER_DB_KEY") != NULL)
           { cVal.userDbKey = atoi(value);  }
    else if (os::strcasestr(key, "LOG_FILE") != NULL)
           { strcpy(cVal.logFile , value);  }
    else if (os::strcasestr(key, "DATABASE_FILE") != NULL)
           { strcpy(cVal.dbFile , value);  }
    else if (os::strcasestr(key, "MAP_ADDRESS") != NULL)
           { cVal.mapAddr = atol(value);  }
    else if (os::strcasestr(key, "MUTEX_TIMEOUT_SECS") != NULL)
           { cVal.mutexSecs = atoi(value);  }
    else if (os::strcasestr(key, "MUTEX_TIMEOUT_USECS") != NULL)
           { cVal.mutexUSecs = atoi(value);  }
    else if (os::strcasestr(key, "MUTEX_TIMEOUT_RETRIES") != NULL)
           { cVal.mutexRetries = atoi(value);  }
    else if (os::strcasestr(key, "LOCK_TIMEOUT_SECS") != NULL)
           { cVal.lockSecs = atoi(value);  }
    else if (os::strcasestr(key, "LOCK_TIMEOUT_USECS") != NULL)
           { cVal.lockUSecs = atoi(value);  }
    else if (os::strcasestr(key, "LOCK_TIMEOUT_RETRIES") != NULL)
           { cVal.lockRetries = atoi(value);  }
    else if (os::strcasestr(key, "LOG_LEVEL") != NULL)
           { cVal.logLevel = atoi(value);  }
    else if (os::strcasestr(key, "DSN") != NULL)
           { strcpy(cVal.dsn , value);  }
    else if (os::strcasestr(key,"DS_CONFIG_FILE") !=NULL)
           { strcpy(cVal.dsConfigFile,value);}
    else if (os::strcasestr(key, "TABLE_CONFIG_FILE") != NULL)
           { strcpy(cVal.tableConfigFile , value);  }
    else if (os::strcasestr(key, "STDERR_FILE") != NULL)
           { strcpy(cVal.stderrFile, value);  }
    else if (os::strcasestr(key, "CONFL_RESOL_FILE") != NULL)
           { strcpy(cVal.conflResoFile , value);  }
    else if (os::strcasestr(key, "CACHE_TABLE") != NULL)
           { cVal.isCache = os::atobool(value); }
    else if (os::strcasestr(key, "CACHE_MODE") != NULL)
           {
               if (strcmp(value, "SYNC") == 0)
               {    cVal.mode = SYNC_MODE;    }
               else if (strcmp(value, "ASYNC") == 0)
               {    cVal.mode = ASYNC_MODE;   }
               else cVal.mode = UNKNOWN;
           }
    else if(os::strcasestr(key,"SITE_ID")!=NULL)
           { cVal.siteID = atoi(value);}
    else if (os::strcasestr(key, "DURABILITY") != NULL)
           { cVal.isDurable = os::atobool(value); }
    else if (os::strcasestr(key, "DURABLE_MODE") != NULL)
           { cVal.durableMode = ::atoi(value); }
    else if (os::strcasestr(key, "CSQL_SQL_SERVER") != NULL)
           { cVal.isCsqlSqlServer = os::atobool(value); }
    else if (os::strcasestr(key, "PORT") != NULL)
           { cVal.port = atoi(value); }
    else if (os::strcasestr(key, "MAX_QUEUE_LOGS") != NULL)
           { cVal.maxQueueLogs = atol(value);  }
    else if (os::strcasestr(key, "MSG_KEY") != NULL)
           { cVal.msgKey = atoi(value);  }
    else if (os::strcasestr(key, "ASYNC_MSGMAX") != NULL)
           { cVal.asyncMsgMax = atoi(value);  }
    else if (os::strcasestr(key, "ID_SHM_KEY") != NULL)
           { cVal.shmKeyForId = atoi(value);  }
    else if (os::strcasestr(key, "NETWORK_RESPONSE_TIMEOUT") != NULL)
           { cVal.nwResponseTimeout = atoi(value);  }
    else if (os::strcasestr(key, "NETWORK_CONNECT_TIMEOUT") != NULL)
           { cVal.nwConnectTimeout = atoi(value);  }
    else if (os::strcasestr(key, "ENABLE_BIDIRECTIONAL_CACHE") != NULL)
           { cVal.isTwoWay = os::atobool(value);  }
    else if (os::strcasestr(key, "CACHE_RECEIVER_WAIT_SECS") != NULL)
           { cVal.cacheWaitSecs = atoi(value);  }
    else if (os::strcasestr(key, "STMT_CACHE_SIZE") != NULL)
           { cVal.stmtCacheSize = atoi(value);  }
    else if (os::strcasestr(key, "STMT_CACHE_NOPARAM") != NULL)
           { cVal.isCacheNoParam = os::atobool(value);  }
    else if (os::strcasestr(key, "MONITOR_SERVERS") != NULL)
           { cVal.isMonitor = os::atobool(value);  }
    else if (os::strcasestr(key, "CHECKPOINT_SECS") != NULL)
           { cVal.chkptSecs = ::atoi(value);  }
    else if (os::strcasestr(key, "CHECKPOINT_LOG_SIZE") != NULL)
           { cVal.chkptRedoLimit = ::atoi(value);  }



    else  return 1;
    return 0;
}
int Config::validateValues()
{
    if (cVal.pageSize < 8192 || cVal.pageSize > 1024 * 1024 * 10 )
    {
        printError(ErrBadArg,  "PAGE_SIZE should be >= 8192 and <= 10 MB");
        return 1;
    }
    if (cVal.pageSize  % 1024 !=0 )
    {
        printError(ErrBadArg,  "PAGE_SIZE should be multiples of 1024");
        return 1;
    }
    if (cVal.maxProcs < 10 || cVal.maxProcs > 8192) 
    {
        printError(ErrBadArg,  "MAX_PROCS should be >= 10 and <= 8192");
        return 1;
    }
    if (cVal.maxSysSize < 1024 * 1024  || cVal.maxSysSize > 1024 *1024 *1024)
    {
        printError(ErrBadArg,  "MAX_SYS_DB_SIZE should be >= 1 MB and <= 1 GB");
        return 1;
    }
    if (cVal.maxSysSize % 8192 !=0 )
    {
        printError(ErrBadArg,  "MAX_SYS_DB_SIZE should be multiples of 8192");
        return 1;
    }

    #ifdef x86_64
    if (cVal.maxDbSize < 1024 * 1024  || cVal.maxDbSize > ( 100*1024*1024*1024L))
    {
        printError(ErrBadArg,  "MAX_DB_SIZE should be >= 1 MB and <= 100 GB");
        return 1;        
    }
    #else
    unsigned long maxVal = 2*1024*1024*1024L;
    if (cVal.maxDbSize < 1024 * 1024  || ((unsigned long)cVal.maxDbSize) > maxVal)
    {
        printError(ErrBadArg,  "MAX_DB_SIZE should be >= 1 MB and <= 2 GB");
        return 1;        
    }
    #endif
    if (cVal.maxDbSize % 8192 !=0)
    {
        printError(ErrBadArg,  "MAX_DB_SIZE should be multiples of 8192");
        return 1;
    }

    if (cVal.sysDbKey < 10 || cVal.sysDbKey > 8192)
    {
        printError(ErrBadArg,  "SYS_DB_KEY should be >= 10 and <= 8192");
        return 1;
    }
    if (cVal.userDbKey < 10 || cVal.userDbKey > 8192)
    {
        printError(ErrBadArg,  "USER_DB_KEY should be >= 10 and <= 8192");
        return 1;
    }
    if ( cVal.sysDbKey == cVal.userDbKey)
    {
        printError(ErrBadArg,  "USER_DB_KEY and SYS_DB_KEY have same value %d", cVal.userDbKey);
        return 1;
    }
    if (0 == strcmp(cVal.logFile,""))
    {
        //TODO::check whether file exists
        printError(ErrBadArg,  "LOG_FILE is set to NULL");
        return 1;
    }
    if (0 == strcmp(cVal.dbFile,""))
    {
        printError(ErrBadArg,  "LOG_FILE is set to NULL");
        return 1;
    }
#if (!defined __sparcv9)
    if (cVal.mapAddr < 400000000 || cVal.mapAddr > 2000000000)
    {
        printError(ErrBadArg,  "MAP_ADDRESS should be >= 400000000 and <= 2000000000");
        return 1;
    }	
#endif
    if (cVal.mutexSecs < 0 || cVal.mutexSecs > 360)
    {
        printError(ErrBadArg,  "MUTEX_TIMEOUT_SECS should be >= 0 and <= 360");
        return 1;
    }
    if (cVal.mutexUSecs < 0 || cVal.mutexUSecs > 1000000)
    {
        printError(ErrBadArg,  "MUTEX_TIMEOUT_USECS should be >= 0 and <= 1000000");
        return 1;
    }
    if (cVal.mutexRetries < 0 || cVal.mutexRetries > 100)
    {
        printError(ErrBadArg,  "MUTEX_TIMEOUT_RETRY should be >= 0 and <= 100");
        return 1;
    }
    if (cVal.lockSecs < 0 || cVal.lockSecs > 360)
    {
        printError(ErrBadArg,  "LOCK_TIMEOUT_SECS should be >= 0 and <= 360");
        return 1;
    }
    if (cVal.lockUSecs < 0 || cVal.lockUSecs > 1000000)
    {
        printError(ErrBadArg,  "LOCK_TIMEOUT_USECS should be >= 0 and <= 1000000");
        return 1;
    }
    if (cVal.lockRetries < 0 || cVal.lockRetries > 100)
    {
        printError(ErrBadArg,  "LOCK_TIMEOUT_RETRY should be >= 0 and <= 100");
        return 1;
    }
    if (cVal.logLevel < 0 || cVal.logLevel > 3) 
    {
        printError(ErrBadArg,  "LOG_LEVEL should be >= 0 and <= 3");
        return 1;
    }
    if (cVal.isCache) {
        if (0 == strcmp(cVal.dsn,""))
        {
            printError(ErrBadArg,  "DSN is set to NULL");
            return 1;
        }
    }
    if (cVal.isCache) {
        if (0 == strcmp(cVal.tableConfigFile,""))
        {
            //TODO::check whether file exists
            printError(ErrBadArg,  "TABLE_CONFIG_FILE is set to NULL");
            return 1;
        }
        /*FILE *fp = fopen(cVal.tableConfigFile,"r");
        if( fp == NULL ) {
            printError(ErrSysInit, "Invalid path/filename for TABLE_CONFIG_FILE.\n");
            return 1;
        }
        int count =0;
        int nwid, port;
        char hostname[IDENTIFIER_LENGTH];
        char nwmode;
 
        while(!feof(fp)) {
            fscanf(fp, "%d:%d:%s\n", &nwid, &port, hostname);
            count++;
        }*/

    }
    if (cVal.nwResponseTimeout <0 || cVal.nwResponseTimeout > 60)
    {
        printError(ErrBadArg,  "NETWORK_RESPONSE_TIMEOUT should be 0 to 60");
        return 1;
    }
    if (cVal.nwConnectTimeout <0 || cVal.nwConnectTimeout > 60)
    {
        printError(ErrBadArg,  "NETWORK_CONNECT_TIMEOUT should be 0 to 60");
        return 1;
    }
    if (cVal.cacheWaitSecs <1)
    {
        printError(ErrBadArg,  "CACHE_RECEIVER_WAIT_SECS should be >1");
        return 1;
    }
    if (cVal.port <= 1024)
    {
        printError(ErrBadArg, "Invalid Port Number");
        return 1;
    }
    if (cVal.durableMode < 1  || cVal.durableMode >4)
    {
        if (!cVal.isDurable) {
            printError(ErrBadArg, "Durability is not enabled but mode is set");
        } else {
            printError(ErrBadArg, "Durable Mode should be 1 to 4");
        }
        return 1;
    }
    if (cVal.stmtCacheSize < 0 || cVal.stmtCacheSize > 1024)
    {
        printError(ErrBadArg, "STMT_CACHE_SIZE should be >=0 and <1024");
        return 1;
    }
    if (cVal.chkptSecs < 1 || cVal.chkptSecs > 1000000)
    {
        printError(ErrBadArg, "CHECKPOINT_SECS should be >=1 and <1000000");
        return 1;
    }
    if (cVal.chkptRedoLimit < 1024 * 1024 || cVal.stmtCacheSize > 1024 * 1024 * 1024)
    {
        printError(ErrBadArg, "CHECKPOINT_LOG_SIZE should be >=1MB and <1 GB");
        return 1;
    }
    return 0;
}

int Config::readAllValues(char *fileName)
{
    if (isLoaded) return 0;
    FILE *fp;
    if (fileName == NULL || 0 == strcmp(fileName, "")) fileName = DEFAULT_CONFIG_FILE;
    fp = fopen(fileName,"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CSQL_CONFIG_FILE.");
	return 1;
    }

    int hasData = 1;
    char buffer[1024];
    char key[1024];
    char value[1024];
    while (hasData)
    {
        memset(buffer, 0, 1024);
        //int ret = fscanf(fp,"%s\r",buffer);
        int ret = readLine(fp, buffer);
        if (ret == EOF) break;
        bool isComment= false;
        int posEqual =0;
        for (int i = 0; i <1024; i++)
        {
              if (buffer[i] == '=' ) posEqual=i;
              else if (buffer[i] == '#' ) { isComment = true; break; }
              else if (buffer[i] == '\n') { break; }
              else if (buffer[i] == '\0') { break; }
        }
      if (isComment) continue;
      if (!posEqual) continue;
      strncpy(key, buffer, posEqual);
      key[posEqual] = '\0';
      posEqual++;
      strcpy(value, &buffer[posEqual]);
      storeKeyVal(key, value);
    }
    fclose(fp);
    if (validateValues())
    {
        return 1;
    }
    cVal.noOfProcessors = os::getNoOfProcessors();
    isLoaded = true;
    return 0;
}
void Config::logConfig()
{
    logFinest(Conf::logger, "Config: LOG_FILE %s", getLogFile());
    logFinest(Conf::logger, "Config: LOG_LEVEL %d", getLogLevel());
    logFinest(Conf::logger, "Config: DURABILITY %d", useDurability());
    logFinest(Conf::logger, "Config: MMAP %d", useMmap());
    logFinest(Conf::logger, "Config: DURABLE_MODE %d", getDurableMode());
    logFinest(Conf::logger, "Config: MUTEX_TIMEOUT_SECS %d", getMutexSecs());
    logFinest(Conf::logger, "Config: MUTEX_TIMEOUT_USECS %d", getMutexUSecs());
    logFinest(Conf::logger, "Config: MUTEX_TIMEOUT_RETRIES %d", getMutexRetries());
    logFinest(Conf::logger, "Config: LOCK_TIMEOUT_SECS %d", getLockSecs());
    logFinest(Conf::logger, "Config: LOCK_TIMEOUT_USECS %d", getLockUSecs());
    logFinest(Conf::logger, "Config: LOCK_TIMEOUT_RETRIES %d", getLockRetries());
}
void Config::print()
{
    printf("ConfigValues\n");
    printf(" getPageSize %d\n", getPageSize());
    printf(" getMaxProcs %d\n", getMaxProcs());
    printf(" getMaxSysDbSize %ld\n", getMaxSysDbSize());
    printf(" getMaxDbSize %ld\n", getMaxDbSize());
    printf(" getSysDbKey %d\n", getSysDbKey());
    printf(" getUserDbKey %d\n", getUserDbKey());
    printf(" getLogFile %s\n", getLogFile());
    printf(" getLogLevel %d\n", getLogLevel());
    printf(" getDatabaseFile %s\n", getDbFile());
    printf(" getMapAddress %ld\n", getMapAddress());
    printf(" getMutexSecs %d\n", getMutexSecs());
    printf(" getMutexUSecs %d\n", getMutexUSecs());
    printf(" getMutexRetries %d\n", getMutexRetries());
    printf(" getLockSecs %d\n", getLockSecs());
    printf(" getLockUSecs %d\n", getLockUSecs());
    printf(" getLockRetries %d\n", getLockRetries());
    printf(" useCache %d\n", useCache());
    printf(" getDSN %s\n", getDSN());
    printf(" getDsConfigFile %s\n",getDsConfigFile());
    printf(" getTableConfigFile %s\n", getTableConfigFile());
    printf(" isTwoWayCache %d\n", useTwoWayCache());
    printf(" getCacheMode %d\n", getCacheMode());
    printf(" getCacheWaitSecs %d\n", getCacheWaitSecs());
    printf(" useCsqlSqlServer %d\n", useCsqlSqlServer());
    printf(" getPort %d\n", getPort());
    printf(" isDurable %d\n", useDurability());
    printf(" getSiteID %d\n", getSiteID());
    printf(" getMsgKey %d\n", getMsgKey());
    printf(" getShmIDKey %d\n", getShmIDKey());
}
