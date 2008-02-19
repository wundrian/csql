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
#include <CSql.h>
#include <sql.h>
#include <sqlext.h>

class CacheTableLoader
{
    char tableName[IDENTIFIER_LENGTH];
    public:
    CacheTableLoader(){strcpy(tableName,"");}
    void setTable(char *tablename) { strcpy(tableName,tablename); }
    DbRetVal addToCacheTableFile();
    DbRetVal removeFromCacheTableFile();
    DbRetVal load(char *user, char *pass);
    DbRetVal load(DatabaseManager *dbMgr);

    DbRetVal reload();
    DbRetVal unload();
    DbRetVal refresh();
    DbRetVal recoverAllCachedTables(char *user, char *pass);

};
