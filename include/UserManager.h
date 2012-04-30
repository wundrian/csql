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
#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include<Util.h>
#include <ParserDataTypes.h>

class Predicate;

/**
* @class UserManager
*
* @brief Interface for user management operations.
* This manages all the users in the system. Only default dba user <br/>
* can create and delete users in the system.<br/>
* If user wants to change his password, he should first get the connection and then call<br/>
* appropriate method in this object to change his password.<br/>
* <br/>
* Functionality: <br/>
*     1.Add and Delete Users<br/>
*     2.Change Password<br/>
* <br/>
* 
*/
class DllExport UserManager
{
    public:
    /** creates new User in the system.<br/>
    *   Only default dba user is allowed to call this method.
    *   @param name username to be created
    *   @param passwd password for the schema created
    *   @return int return code
    */
    virtual int createUser(const char *name, const char *passwd)=0;

    /** deleted user from the system <br/>
    *   Only default dba user is allowed to call this method.
    *   @param name username to be deleted
    *   @return int return code
    */
    virtual int deleteUser(const char *name)=0;

    /** changes password for self. Logged in user password is set to <br/>
    *   specified password.
    *   @param newPasswd new password to be set.
    *   @return int return code
    */
    virtual int changePassword(const char* newPasswd)=0;

    /** changes the password for specified user.
    *   Only default dba user is allowed to call this method.
    *   @param username username for authentication
    *   @param password password for authentication
    *   @return int return code
    */
    virtual int changePassword(const char *userName, const char* newPasswd)=0;

    virtual List getAllUserNames(int *rv=0)=0;
    virtual ~UserManager(){};
    
    /**
     * Grant a bitmask of privileges on a table to a certain user.
     * The privilege may be further restricted by a predicate clause.
     * 
     * @param priv The list of privileges to grant (must be a bitmask of PrivilegeType)
     * @param tblId The id of the table to grant privileges on
     * @param grantee The name of the user to grant privileges to
     * @param pred (optional) row level restriction predicate
     * @param conditionValues concrete values for pred
     * @return status code (OK or error indicator)
     */
    virtual int grantPrivilege(unsigned char priv, int tblId, std::string grantee, const Predicate* pred, FieldConditionValMap &conditionValues)=0;
    
    /**
     * Revoke the given bitmask of privileges on a table from a certain user.
     * 
     * @param priv The list of privileges to be revoked (must be a bitmask of PrivilegeType)
     * @param tblId The id of the table to act on
     * @param grantee The name of the user to revoke privileges from
     * @return status code (OK or error indicator)
     */
    virtual int revokePrivilege(unsigned char priv, int tblId, std::string grantee)=0;
    
    /**
     * This ONLY returns true if the current user has ALL permissions in priv on tblId, a subset is not sufficient.
     * 
     * @param priv The privileges the current user should have as a bitmask
     * @param tblId The id of the table the current user should have privileges on
     * @return true if the current user has priv on tblId
     */
    virtual bool isAuthorized(unsigned char priv, int tblId) const =0;
    
    /**
     * Grab the Predicate constraining the current user on table tblId.
     * If pred equals the NULL-Pointer, conditionValues must be disregarded.
     * 
     * @param tblId Identifies the table to get restrictions for
     * @param pred An OUT parameter that gets a copy of the restriction for table tblId
     * @return status code (OK or error indicator)
     */
    virtual int getTableRestriction(int tblId, Predicate *pred, FieldConditionValMap &conditionValues)=0;
};
#endif
