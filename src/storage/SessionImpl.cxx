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
#include<DatabaseManagerImpl.h>
#include<DatabaseManager.h>
#include<CatalogTables.h>
#include<Database.h>
#include<SessionImpl.h>
#include<UserManager.h>
#include<UserManagerImpl.h>
#include<Transaction.h>
#include<Debug.h>
#include<Config.h>
#include<Process.h>

#if (defined MMDB && defined EMBED)
int SessionImpl::noOfThreads = 0;
#endif

//Before calling this method, application is required to call readConfigValues
DbRetVal SessionImpl::initSystemDatabase()

{
    long value=0;
    
    DbRetVal rv = OK;
    rv = readConfigFile();
    if (rv != OK) 
    {
       printError(ErrSysInit, "Configuration file read failed\n");
       return ErrSysInit;
    }

   // Conf::config.print();

    if (dbMgr == NULL) dbMgr = new DatabaseManagerImpl();
    rv = dbMgr->createDatabase(SYSTEMDB, Conf::config.getMaxSysDbSize());
    if (OK != rv) return rv;
    
    dbMgr->setSysDb(dbMgr->db());
    dbMgr->setDb(NULL);

    Database *db = dbMgr->sysDb();

    rv = db->getXCheckpointMutex();
    if (OK != rv)
    {
        printError(ErrLockTimeOut, "Unable to get Database Mutex");
        return rv;
    }


    db->createAllCatalogTables();

    //create the default dba user
    CatalogTableUSER cUser(db);
    rv = cUser.insert(I_USER, I_PASS);
    if (OK != rv)
    {
        db->releaseCheckpointMutex();
        return rv;
    }

    rv = cUser.insert(DBAUSER, DBAPASS);
    if (OK != rv)
    {
        db->releaseCheckpointMutex();
        return rv;
    }
    void *ret = NULL;
    //Allocate space for the lock hash bucket
    ret = db->allocLockHashBuckets();
    if (NULL == ret)
    {
        db->releaseCheckpointMutex();
        printError(ErrSysInit, "Allocation of Lock buckets failed");
        return ErrSysInit;
    }
    Bucket* buckets = dbMgr->sysDb()->getLockHashBuckets();
    Bucket* bucket;
    char mutName[IDENTIFIER_LENGTH];
    for (int i =0; i< LOCK_BUCKET_SIZE; i++)
    {
       bucket = &(buckets[i]);
       sprintf(mutName, "LOCKBKT:%d", i);
       bucket->mutex_.init(mutName);
    }

    db->releaseCheckpointMutex();
#if !(defined MMDB && defined EMBED)
    printf("Sys_DB  [Size=%4.4ldMB] \nUser_DB [Size=%4.4ldMB]\n", Conf::config.getMaxSysDbSize()/1048576, Conf::config.getMaxDbSize()/1048576);
#endif
    //create user database
    rv = dbMgr->createDatabase("userdb", Conf::config.getMaxDbSize());
    if (OK != rv) return rv;
    return OK;
}

DbRetVal SessionImpl::destroySystemDatabase()
{
    DbRetVal rv = OK;
    rv = dbMgr->deleteDatabase(SYSTEMDB);
    if (OK != rv) return rv;
    rv = dbMgr->deleteDatabase("userdb");
    if (OK != rv) return rv;
    delete dbMgr;
    dbMgr = NULL;
    return OK;
}

DbRetVal SessionImpl::open(const char *username, const char *password)
{
#if (defined MMDB) && (defined EMBED)
    openEmbeddedConnection(username, password);
# else 
    DbRetVal rv = OK;
    rv = readConfigFile();
    if (rv != OK)
    {
       printError(ErrSysFatal, "Configuration file read failed\n");
       return ErrSysFatal;
    }

    if ( NULL == dbMgr)
    {
        dbMgr = new DatabaseManagerImpl();
    }
    int ret = ProcessManager::mutex.tryLock(10, 100);
    //If you are not getting lock ret !=0, it means somebody else is there.
    if (ret != 0)
    {
        printError(ErrSysInternal, "Another thread calling open:Wait and then Retry\n");
        return ErrSysInternal;
    }
    rv = dbMgr->openSystemDatabase();
    if (OK != rv)
    {
        printError(rv,"Unable to open the system database");
        ProcessManager::mutex.releaseLock(-1, false);
        return rv;
    }

    rv = authenticate(username, password);
    if (OK != rv)
    {
        dbMgr->closeSystemDatabase();
        delete dbMgr; dbMgr = NULL;
        ProcessManager::mutex.releaseLock(-1, false);
        return rv;
    }

    dbMgr->createTransactionManager();
    dbMgr->createLockManager();
    rv = dbMgr->registerThread();
    if (OK != rv)
    {
        printError(rv,"Unable to register to csql server");
        dbMgr->closeSystemDatabase();
        ProcessManager::mutex.releaseLock(-1, false);
        delete dbMgr; dbMgr = NULL;
        return rv;
    }
    rv = dbMgr->openDatabase("userdb");
    if (OK != rv) {
        dbMgr->closeSystemDatabase();
        ProcessManager::mutex.releaseLock(-1, false);
        delete dbMgr; dbMgr = NULL;
        return rv;
    }
    ProcessManager::mutex.releaseLock(-1, false);
    ((DatabaseManagerImpl*)dbMgr)->setProcSlot();
    //ProcessManager::systemDatabase = dbMgr->sysDb();
    isXTaken = false;
    return OK;
#endif
}
DbRetVal SessionImpl::authenticate(const char *username, const char *password)
{
    CatalogTableUSER cUser(dbMgr->sysDb());
    cUser.authenticate(username, password, isAuthenticated, isDba);
    strcpy(userName, username);
    if (!isAuthenticated)
    {
        printError(ErrNoPrivilege,"User Authentication failed");
        return ErrNoPrivilege;
    }
    return OK;
}
DbRetVal SessionImpl::getExclusiveLock()
{
   DbRetVal rv = dbMgr->sysDb()->getProcessTableMutex(true);
   if (OK != rv) {
      printError(ErrLockTimeOut, "Unable to acquire proc table mutex");
      return rv;
   }
   if (dbMgr->isAnyOneRegistered()) {
      printError(ErrLockTimeOut, "Unable to acquire exclusive lock. somebody is connected");
      dbMgr->sysDb()->releaseProcessTableMutex(true);
      return ErrLockTimeOut;
   }
   isXTaken = true;
   return rv;
}
DbRetVal SessionImpl::close()
{
# if (defined MMDB) && (defined EMBED)
    closeEmbeddedConnection();
# else
    DbRetVal rv = OK;
    if (isXTaken && dbMgr ) dbMgr->sysDb()->releaseProcessTableMutex(true);
    if (dbMgr)
    {
        int ret = ProcessManager::mutex.tryLock(10,100);
        //If you are not getting lock ret !=0, it means somebody else is there.
        if (ret != 0)
        {
           printError(ErrSysInternal, "Another thread calling open:Wait and then Retry\n");
           return ErrSysInternal;
        }

        rv = dbMgr->closeDatabase();
        if (rv != OK) { 
           ProcessManager::mutex.releaseLock(-1, false);
           return ErrBadCall;  
        }
        rv = dbMgr->deregisterThread();
        if (rv != OK) {  
           ProcessManager::mutex.releaseLock(-1, false);
           return ErrBadCall;  
        }
        rv = dbMgr->closeSystemDatabase();
        if (rv != OK) { 
             ProcessManager::mutex.releaseLock(-1, false);
             return ErrBadCall;  
        }
        ProcessManager::mutex.releaseLock(-1, false);
        delete dbMgr;
        dbMgr = NULL;
    }
    if (uMgr)
    {
        delete uMgr;
        uMgr = NULL;
    }
    isXTaken = false;
    return OK;
#endif
}

DatabaseManager* SessionImpl::getDatabaseManager()
{
    return dbMgr;
}

UserManager* SessionImpl::getUserManager()
{
    if (!isAuthenticated)
    {
        printError(ErrNoPrivilege, "Not Authenticated: Returning NULL");
        return NULL;
    }
    if (uMgr != NULL) return uMgr;
    UserManagerImpl *userMgr =  new UserManagerImpl();
    if(0 == strcmp(userName, DBAUSER))
        userMgr->setDba(true);
    else
        userMgr->setDba(false);

    userMgr->setSysDb(dbMgr->sysDb());

    userMgr->setUserName(userName);
    uMgr = userMgr;
    return userMgr;
}

DbRetVal SessionImpl::startTransaction(IsolationLevel level)
{
    if (NULL == dbMgr || NULL == dbMgr->txnMgr())
    {
        printError(ErrSysFatal, "Database Manager or Txn Manager object is NULL");
        return ErrSysFatal;
    }
    DbRetVal rv = OK;

    rv = dbMgr->txnMgr()->startTransaction(dbMgr->lockMgr(), level);
    return rv;
}


DbRetVal SessionImpl::commit()
{
    DbRetVal rv = OK;
    if (NULL == dbMgr || NULL == dbMgr->txnMgr())
    {
        printError(ErrSysFatal, "Database Manager or Txn Manager object is NULL");
        return ErrSysFatal;
    }
    rv = dbMgr->txnMgr()->commit(dbMgr->lockMgr());
    if (OK != rv)
    {
        printError(rv,"Transaction commit failed\n");
        return rv;
    }
    return OK;
}


DbRetVal SessionImpl::rollback()
{
    DbRetVal rv = OK;
    if (NULL == dbMgr || NULL == dbMgr->txnMgr())
    {
        printError(ErrSysFatal, "Database Manager or Txn Manager object is NULL");
        return ErrSysFatal;
    }
    rv = dbMgr->txnMgr()->rollback(dbMgr->lockMgr());
    if (OK != rv)
    {
        printError(rv, "Transaction rollback failed\n");
        return rv;
    }
    return OK;
}

DbRetVal SessionImpl::readConfigFile()
{
    // Check if env variable is set or not
    char *confFilename = os::getenv("CSQL_CONFIG_FILE");
    if (confFilename == NULL)
    {
        if (os::fileExists(DEFAULT_CONFIG_FILE)) {
           confFilename = DEFAULT_CONFIG_FILE;
        }
        else  {
           printError(ErrSysInit, "CSQL_CONFIG_FILE environment variable "
                                  "should be set.");
           return ErrSysInit;
        }
    }

    int  rv = Conf::config.readAllValues(confFilename);
    if (rv != 0) return ErrSysInit;
    return OK;
}
Database* SessionImpl::getSystemDatabase()
{
    return dbMgr->sysDb();
}

#if (defined MMDB && defined EMBED)
DbRetVal SessionImpl::openEmbeddedConnection(const char *username, const char *password)
{
    DbRetVal rv = OK;
    rv = readConfigFile();
    if (rv != OK)
    {
       printError(ErrSysFatal, "Configuration file read failed\n");
       return ErrSysFatal;
    }

    if ( NULL == dbMgr)
    {
        dbMgr = new DatabaseManagerImpl();
    }
    int ret = ProcessManager::mutex.tryLock(10, 100);
    //If you are not getting lock ret !=0, it means somebody else is there.
    if (ret != 0)
    {
        printError(ErrSysInternal, "Another thread calling open:Wait and then Retry\n");
        return ErrSysInternal;
    }

    if (!noOfThreads) {
        ret = initSystemDatabase();
        if (0  != ret) {
            printError(ErrSysInternal, "Unable to initialize the Database");
            ProcessManager::mutex.releaseLock(-1, false);
            return ErrSysInternal;
        }
        ProcessManager::systemDatabase = dbMgr->sysDb();
    } else {
        rv = dbMgr->openSystemDatabase();
        if (OK != rv)
        {
            printError(rv,"Unable to open the system database");
            ProcessManager::mutex.releaseLock(-1, false);
            return rv;
        }
    }

    rv = authenticate(username, password);
    if (OK != rv)
    {
        delete dbMgr; dbMgr = NULL;
        ProcessManager::mutex.releaseLock(-1, false);
        return rv;
    }

    dbMgr->createTransactionManager();
    dbMgr->createLockManager();
    if (noOfThreads) {
        rv = dbMgr->openDatabase("userdb");
        if (OK != rv) {
            dbMgr->closeSystemDatabase();
            ProcessManager::mutex.releaseLock(-1, false);
            delete dbMgr; dbMgr = NULL;
            return rv;
        }
    }

    rv = dbMgr->registerThread();
    if (OK != rv)
    {
        printError(rv,"Unable to register to csql server");
        ProcessManager::mutex.releaseLock(-1, false);
        delete dbMgr; dbMgr = NULL;
        return rv;
    }

    ProcessManager::mutex.releaseLock(-1, false);
    noOfThreads++;
    return OK;
}

DbRetVal SessionImpl::closeEmbeddedConnection()
{
    DbRetVal rv = OK;
    if (dbMgr)
    {
        int ret = ProcessManager::mutex.tryLock(10,100);
        //If you are not getting lock ret !=0, it means somebody else is there.
        if (ret != 0)
        {
           printError(ErrSysInternal, "Another thread calling open:Wait and then Retry\n");
           return ErrSysInternal;
        }

        rv = dbMgr->deregisterThread();
        if (rv != OK) {
           ProcessManager::mutex.releaseLock(-1, false);
           return ErrBadCall;
        }
        ProcessManager::mutex.releaseLock(-1, false);
    }
    if (uMgr)
    {
        delete uMgr;
        uMgr = NULL;
    }
    if(noOfThreads == 1) {
        destroySystemDatabase();
        Conf::logger.stopLogger();
    }
    noOfThreads--;
    return OK;
}
#endif
