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
    
    if (0 == strcmp(U_PUBLIC, name)) {
        printError(ErrBadArg, "User name %s is reserved", U_PUBLIC);
        return ErrBadArg;
    }

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
                   "Catalog table update failed for user %s",usrName);
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
                   "Catalog table update failed");
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

int UserManagerImpl::grantPrivilege(DclInfoNode info, int tblId, const PredicateImpl *rootPred, List conditionValues)
{
    CatalogTableGRANT cGrant(systemDatabase_);
    CatalogTableTABLE cTable(systemDatabase_);

    if (!(isDba
        || cTable.isOwner(tblId, userName)
        || info.privs == (info.privs & cGrant.getGrantablePrivs(tblId, userName))))
    {
        printError(ErrNoPrivilege, "You are not authorized to grant privileges on table %d", tblId);
        return ErrNoPrivilege;
    }

    int ret = cGrant.insert(info.privs, info.withGrantOpt, tblId, info.userName, rootPred, conditionValues);

    if (OK != ret)
    {
        printError(ErrSysInternal, "Granting privilege failed");
        return ErrSysInternal;
    }
    
    logFine(Conf::logger, "Granted privileges %d on table %d to %s", info.privs, tblId, info.userName.c_str());
    return OK;
}

int UserManagerImpl::revokePrivilege(DclInfoNode info, int tblId)
{
    CatalogTableGRANT cGrant(systemDatabase_);
    CatalogTableTABLE cTable(systemDatabase_);

    if (!isDba && !cTable.isOwner(tblId, userName))
    {
        printError(ErrNoPrivilege, "You are not authorized to revoke privileges on table %d", tblId);
        return ErrNoPrivilege;
    }

    int ret = cGrant.remove(info.privs, tblId, info.userName);
    
    if (OK != ret)
    {
        printError(ErrSysInternal, "Revoking privilege failed");
        return ErrSysInternal;
    }
    
    logFine(Conf::logger, "Revoked privileges %d on table %d from %s", info.privs, tblId, info.userName.c_str());
    return OK;
}

bool UserManagerImpl::isAuthorized(unsigned char priv, int tblId) const
{
    CatalogTableGRANT cGrant(systemDatabase_);
    CatalogTableTABLE cTable(systemDatabase_);
    
    /* owner is always granted access to her tables */
    bool allowed = (cTable.isOwner(tblId, userName)
            || (priv == (cGrant.getPrivileges(tblId, userName) & priv))
            || (priv == (cGrant.getPrivileges(tblId, U_PUBLIC) & priv)));

    return allowed;
}

bool UserManagerImpl::isAuthorized(unsigned char priv, const char *tblName) const
{
    void *chunkPtr, *tablePtr, *vcChunkPtr;
    CatalogTableTABLE cTable(systemDatabase_);

    if (OK != cTable.getChunkAndTblPtr(tblName, chunkPtr, tablePtr, vcChunkPtr))
        goto out;

    out:
    return (NULL == tablePtr) || isAuthorized(priv, ((CTABLE*)tablePtr)->tblID_);
}

int UserManagerImpl::getTableRestriction(int tblId, Predicate *&pred, List &conditionValues)
{
    CatalogTableGRANT cGrant(systemDatabase_);
    DbRetVal ret = cGrant.getPredicate(tblId, userName, pred, conditionValues);
    
    if (OK != ret)
    {
        printError(ret, "Failed to get table restriction for user %s", userName);
        return ret;
    }

    Predicate *publicPred;
    ret = cGrant.getPredicate(tblId, U_PUBLIC, publicPred, conditionValues);
    
    if (OK != ret)
    {
        if (NULL != publicPred) delete publicPred;
        printError(ret, "Failed to get table restriction for user %s", U_PUBLIC);
        return ret;
    }

    if (NULL != publicPred) {
        PredicateImpl *pImpl = new PredicateImpl();
        // the order MUST be the same as the deserialization calls above or conditionValues will get messed up
        pImpl->setTerm(pred, OpOr, publicPred);
        pred = pImpl;
    }

    return OK;
}
