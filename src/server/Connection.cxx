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
#include<SessionImpl.h>
#include<Debug.h>
#include<os.h>
#include<Index.h>
#include<Config.h>
Connection::~Connection()
{ 
    delete session; 
    Index::destroy();
}

DbRetVal Connection::open(const char *username, const char *password)
{
    if (session == NULL) session = new SessionImpl();
    DbRetVal rv = logger.startLogger(config.getLogFile());
    if (rv != OK) { delete session; session = NULL; return rv; }
    logFinest(logger, "User logged in %s",username);
    return session->open(username, password);
}

DbRetVal Connection::close()
{
    if (session == NULL) return ErrNoConnection;
    logFinest(logger, "User logged out");
    logger.stopLogger();
    DbRetVal rv= session->close();
    delete session; 
    session = NULL;
    return rv;
}

DatabaseManager* Connection::getDatabaseManager()
{
    if (session == NULL) return NULL;
    return session->getDatabaseManager();
}

UserManager* Connection::getUserManager()
{
    if (session == NULL) return NULL;
    return session->getUserManager();
}

DbRetVal Connection::startTransaction(IsolationLevel level)
{
    if (session == NULL) return ErrNoConnection;
    return session->startTransaction(level);
}


DbRetVal Connection::commit()
{
    if (session == NULL) return ErrNoConnection;
    return session->commit();
}


DbRetVal Connection::rollback()
{
    if (session == NULL) return ErrNoConnection;
    return session->rollback();
}
