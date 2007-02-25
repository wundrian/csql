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
#ifndef SESSION_H
#define SESSION_H
#include<DatabaseManager.h>
#include<UserManager.h>
#include<ErrorType.h>
class Session;

//Currently it suppors only READ REPEATABLE transaction isolation level.
//TODO::to implement READ COMMITTED and DIRTY READ isolation level
//NOT to DO: SERIALIZABLE isolation level
class Connection
{
    Session *session;
    public:
    Connection() { session = NULL; }
    ~Connection() { delete session; }
    DbRetVal open(const char*username, const char*password);
    DbRetVal close();
    DatabaseManager* getDatabaseManager();
    UserManager* getUserManager();
    DbRetVal startTransaction();
    DbRetVal commit();
    DbRetVal rollback();
};
class Session
{
    public:
    virtual DbRetVal open(const char*username, const char*password)=0;
    virtual DbRetVal close()=0;

    virtual DatabaseManager* getDatabaseManager()=0;
    virtual UserManager* getUserManager()=0;

    virtual DbRetVal startTransaction()=0;
    virtual DbRetVal commit()=0;
    virtual DbRetVal rollback()=0;
    //TODO:: virtual int setAutoCommit(bool flag)=0;
    //TODO::support for save points
    virtual ~Session() { }

};

#endif
