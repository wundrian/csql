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

//Before calling this method, application is required to call readConfigValues
DbRetVal SessionImpl::initSystemDatabase()

{
    DbRetVal rv = OK;
    rv = readConfigFile();
    if (rv != OK) 
    {
       printError(ErrSysInit, "Configuration file read failed\n");
       return ErrSysInit;
    }
    printf("ConfigValues\n");
    printf(" getPageSize %d\n", Conf::config.getPageSize());
    printf(" getMaxTrans %d\n", Conf::config.getMaxTrans());
    printf(" getMaxProcs %d\n", Conf::config.getMaxProcs());
    printf(" getMaxSysDbSize %ld\n", Conf::config.getMaxSysDbSize());
    printf(" getMaxDbSize %ld\n", Conf::config.getMaxDbSize());
    printf(" getSysDbKey %d\n", Conf::config.getSysDbKey());
    printf(" getUserDbKey %d\n", Conf::config.getUserDbKey());
    printf(" getLogFile %s\n", Conf::config.getLogFile());
    printf(" getMapAddress %ld\n", Conf::config.getMapAddress());
    printf(" getMutexSecs %d\n", Conf::config.getMutexSecs());
    printf(" getMutexUSecs %d\n", Conf::config.getMutexUSecs());


    dbMgr = new DatabaseManagerImpl();

    //TODO:Size of system database 100 MB ->config parameter

    //TODO:No of chunks of system database->config parameter
    //This limits the total number of catalog tables system shall support.
    rv = dbMgr->createDatabase(SYSTEMDB, Conf::config.getMaxSysDbSize());
    if (OK != rv) return rv;
    dbMgr->setSysDb(dbMgr->db());
    dbMgr->setDb(NULL);

    Database *db = dbMgr->sysDb();

    rv = db->getDatabaseMutex();
    if (OK != rv)
    {
        printError(ErrLockTimeOut, "Unable to get Database Mutex");
        return rv;
    }


    db->createAllCatalogTables();

    //create the default dba user
    CatalogTableUSER cUser(db);
    rv = cUser.insert(DBAUSER, DBAPASS);
    if (OK != rv)
    {
        db->releaseDatabaseMutex();
        return rv;
    }
    void *ret = NULL;
    //Allocate space for the lock hash bucket
    ret = db->allocLockHashBuckets();
    if (NULL == ret)
    {
        db->releaseDatabaseMutex();
        printError(ErrSysInit, "Allocation of Lock buckets failed");
        return ErrSysInit;
    }

    db->releaseDatabaseMutex();

    //create user database
    rv = dbMgr->createDatabase("praba", Conf::config.getMaxDbSize());
    if (OK != rv) return rv;
    return OK;
}

DbRetVal SessionImpl::destroySystemDatabase()
{
    DbRetVal rv = OK;
    rv = dbMgr->deleteDatabase(SYSTEMDB);
    if (OK != rv) return rv;
    rv = dbMgr->deleteDatabase("praba");
    if (OK != rv) return rv;
    delete dbMgr;
    dbMgr = NULL;
    return OK;
}

DbRetVal SessionImpl::open(const char *username, const char *password)
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
        rv = dbMgr->openSystemDatabase();
    }
    if (OK != rv)
    {
        printError(rv,"Unable to open the system database");
        return rv;
    }


    rv = dbMgr->sysDb()->getDatabaseMutex();
    if (OK != rv)
    {
        printError(rv,"Unable to get database mutex");
        return rv;
    }

    CatalogTableUSER cUser(dbMgr->sysDb());
    cUser.authenticate(username, password, isAuthenticated, isDba);
    strcpy(userName, username);
    //isAuthenticated=true;
    dbMgr->sysDb()->releaseDatabaseMutex();
    if (!isAuthenticated)
    {
        dbMgr->deregisterThread();
        dbMgr->closeSystemDatabase();
        delete dbMgr;
        dbMgr = NULL;
        printError(ErrNoPrivilege,"User Authentication failed");
        return ErrNoPrivilege;
    }

    dbMgr->createTransactionManager();
    dbMgr->createLockManager();
    rv = dbMgr->openDatabase("praba");
    if (OK != rv) return rv;

    rv = dbMgr->registerThread();
    if (OK != rv)
    {
        printError(rv,"Unable to register to csql server");
        return rv;
    }
    return OK;
}

DbRetVal SessionImpl::close()
{
    DbRetVal rv = OK;
    if (dbMgr)
    {
        rv = dbMgr->closeDatabase();
        if (rv != OK) return ErrBadCall;
        rv = dbMgr->closeSystemDatabase();
        if (rv != OK) return ErrBadCall;
        rv = dbMgr->deregisterThread();
        if (rv != OK) return ErrBadCall;
        delete dbMgr;
        dbMgr = NULL;
    }
    if (uMgr)
    {
        delete uMgr;
        uMgr = NULL;
    }
    return OK;
}

DatabaseManager* SessionImpl::getDatabaseManager()
{
    if (isAuthenticated) return dbMgr;
    printError(ErrNoPrivilege, "Not Authenticated: Returning NULL");
    return NULL;
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
    rv = dbMgr->sysDb()->getTransTableMutex();
    if (OK != rv)
    {
        printError(rv,"Unable to get TransTable mutex\n");
        return rv;
    }
    rv = dbMgr->txnMgr()->startTransaction(level);
    dbMgr->sysDb()->releaseTransTableMutex();
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
        printError(rv,"Unable to get TransTable mutex\n");
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
        printError(rv,"Unable to get TransTable mutex\n");
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
        printError(ErrSysInit, "CSQL_CONFIG_FILE environment variable should be set.");
        return ErrSysInit;
    }

    int  rv = Conf::config.readAllValues(confFilename);
    if (rv != 0) return ErrSysInit;
    return OK;
}

