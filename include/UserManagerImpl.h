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
#ifndef USER_MANAGER_IMPL_H
#define USER_MANAGER_IMPL_H
#include<UserManager.h>
#include<os.h>
#include <ParserDataTypes.h>
class Database;
class DllExport UserManagerImpl: public UserManager
{
    private:
    bool isDba;
    char userName[IDENTIFIER_LENGTH];
    Database *systemDatabase_;

    public:

    UserManagerImpl(){}
    ~UserManagerImpl(){}

    void setSysDb(Database *db) { systemDatabase_ = db; }
    void setDba(bool flag) { isDba = flag; }
    void setUserName(const char *name){ strcpy( userName, name); }
    int createUser(const char *name, const char *passwd);

    int deleteUser(const char *name);

    int changePassword(const char* newPasswd);

    int changePassword(const char *userName, const char* newPasswd);
    List getAllUserNames(int *rv=NULL);

    int grantPrivilege(unsigned char priv, int tblId, std::string grantee, const PredicateImpl *rootPred, List conditionValues);
    int revokePrivilege(unsigned char priv, int tblId, std::string grantee);
    bool isAuthorized(unsigned char priv, int tblId) const;
    bool isAuthorized(unsigned char priv, const char *tblName) const;
    int getTableRestriction(int tblId, Predicate *&pred, List &conditionValues);
};


#endif
