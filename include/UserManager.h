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
#ifndef USER_MANAGER_H
#define USER_MANAGER_H
class UserManager
{
    public:

    virtual int createUser(const char *name, const char *passwd)=0;
    virtual int deleteUser(const char *name)=0;
    virtual int changePassword(const char* newPasswd)=0;
    virtual int changePassword(const char *userName, const char* newPasswd)=0;
    virtual ~UserManager(){};
};
#endif
