/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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

DbRetVal SessionImpl::initSystemDatabase()

{
    DbRetVal rv = OK;
    dbMgr = new DatabaseManagerImpl();
    //TODO:Size of system database 100 MB ->config parameter

    //TODO:No of chunks of system database->config parameter
    //This limits the total number of catalog tables system shall support.
    rv = dbMgr->createDatabase(SYSTEMDB, SYSTEM_DB_SIZE);
    if (OK != rv) return rv;
    dbMgr->setSysDb(dbMgr->db());
    dbMgr->setDb(NULL);

    Database *db = dbMgr->sysDb();

    db->getDatabaseMutex();

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
    rv = dbMgr->createDatabase("praba", SYSTEM_DB_SIZE);
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
    return OK;
}

DbRetVal SessionImpl::open(const char *username, const char *password)
{
    DbRetVal rv = OK;
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

    //TODO::process registration
    //pMgr = new ProcessManager();
    //pMgr->registerProcess();

    rv = dbMgr->sysDb()->getDatabaseMutex();
    if (OK != rv)
    {
        printError(rv,"Unable to get database mutex");
        return rv;
    }

    CatalogTableUSER cUser(dbMgr->sysDb());
    //cUser.authenticate(username, password, isAuthenticated, isDba );
    isAuthenticated=true;
    dbMgr->sysDb()->releaseDatabaseMutex();
    if (!isAuthenticated)
    {
        dbMgr->closeSystemDatabase();
        delete dbMgr;
        //delete pMgr;
        printError(ErrNoPrivilege,"User Authentication failed");
        return ErrNoPrivilege;
    }

    dbMgr->createTransactionManager();
    dbMgr->createLockManager();
    rv = dbMgr->openDatabase("praba");
    if (OK != rv) return rv;

    return OK;
}

DbRetVal SessionImpl::close()
{
    if (dbMgr)
    {
        dbMgr->closeDatabase();
        dbMgr->closeSystemDatabase();
        delete dbMgr;
            dbMgr = NULL;
    }
    //pMgr->deregisterProcess();
    //delete pMgr;
    //pMgr = NULL;
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

DbRetVal SessionImpl::startTransaction()
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
    rv = dbMgr->txnMgr()->startTransaction();
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
