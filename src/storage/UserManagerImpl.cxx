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
#include<UserManagerImpl.h>
#include<CatalogTables.h>
#include<Debug.h>
int UserManagerImpl::createUser(const char *name, const char *password)
{
    if (!isDba)
    {
        printError(ErrNoPrivilege,
                   "Only DBA privileged schema can create users");
        return ErrNoPrivilege;
    }
    int ret = 0;
    //add entry to USER table
    CatalogTableUSER cUser(systemDatabase_);
    ret = cUser.insert(name, password);
    if (0 != ret)
    {
        printError(ErrSysInternal,
                   "Catalog table insert failed for the user %s",name);
        return ErrSysInternal;
    }
    logFine(Conf::logger, "User Created %s" , name);
    return OK;
}

int UserManagerImpl::deleteUser(const char *name)
{
    if (!isDba)
    {
        printError(ErrNoPrivilege,
                   "Only DBA privileged schema can delete users");
        return ErrNoPrivilege;
    }
    int ret = 0;
    CatalogTableUSER cUser(systemDatabase_);
    ret = cUser.remove(name);
    if (0 != ret)
    {
        printError(ErrNotExists,
                           "User %s not exists",name);
        return ErrNotExists;
    }
    logFine(Conf::logger, "User Deleted %s" , name);
    return OK;
}

int UserManagerImpl::changePassword(const char *usrName, const char* newPasswd)
{
/*    if (!isDba)
    {
        printError(ErrNoPrivilege,
                   "Only DBA privileged schema can change password for other users");
        return ErrNoPrivilege;
    }*/
    int ret = 0;
    CatalogTableUSER cUser(systemDatabase_);
    ret = cUser.changePass(usrName, newPasswd );
    if (0 != ret)
    {
        printError(ErrSysInternal,
                   "Catalog table updation failed for user %s",usrName);
        return ErrSysInternal;
    }
    logFine(Conf::logger, "Password changed for  %s" ,usrName);
    return OK;
}


int UserManagerImpl::changePassword(const char* newPasswd)
{
    int ret = 0;
    CatalogTableUSER cUser(systemDatabase_);
    ret = cUser.changePass(userName, newPasswd );
    if (0 != ret)
    {
        printError(ErrSysInternal,
                   "Catalog table updation failed");
        return ErrSysInternal;
    }
    logFine(Conf::logger, "Password changed for  %s" ,userName);
    return OK;
}

List UserManagerImpl::getAllUserNames(int *retval)
{
    DbRetVal ret = OK;
    //to store the tuple pointer of the table
    void *tptr =NULL;
    CatalogTableUSER cUser(systemDatabase_);
    return cUser.getUserList();
}


