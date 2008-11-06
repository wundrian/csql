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
#include <Network.h>

class CacheTableLoader
{
    char tableName[IDENTIFIER_LENGTH];
    char userName[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];
    char conditionVal[IDENTIFIER_LENGTH]; //added newly
    char fieldlistVal[IDENTIFIER_LENGTH];
    public:
    CacheTableLoader()
    {
        strcpy(tableName,"");
        strcpy(conditionVal,"");
	strcpy(fieldlistVal,"");
    }
    void setConnParam(char *user, char *pass){ strcpy(userName, user); strcpy(password, pass); }
    void setTable(char *tablename) { strcpy(tableName,tablename); }
    void setCondition(char *condition){strcpy(conditionVal,condition);} //new one
    void setField(char *field) {strcpy(fieldlistVal,field);}
    DbRetVal addToCacheTableFile();
    DbRetVal removeFromCacheTableFile();
    DbRetVal load(bool tabDef=true);
    DbRetVal reload();
    DbRetVal unload(bool tabDefinition = true);
    DbRetVal refresh();
    DbRetVal recoverAllCachedTables();
    DbRetVal load(DatabaseManager *dbMgr, bool tabDef);
    DbRetVal isTableCached();
    DbRetVal isTablePresent(char *table,char *condition,char *field);// new one by :Jitendra
};

class BindBuffer
{
    public:
    void *csql;
    void *targetdb;
    DataType type;
};

