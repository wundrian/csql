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
    char fieldName[IDENTIFIER_LENGTH];
    char userName[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];
    char conditionVal[IDENTIFIER_LENGTH]; //added newly
    char fieldlistVal[IDENTIFIER_LENGTH];
    public:
    CacheTableLoader()
    {
        strcpy(tableName,"");
        strcpy(conditionVal,"");
        strcpy(fieldName,"");
	strcpy(fieldlistVal,"");
    }
    void setConnParam(char *user, char *pass){ strcpy(userName, user); strcpy(password, pass); }
    void setTable(char *tablename) { strcpy(tableName,tablename); }
    void setCondition(char *condition){strcpy(conditionVal,condition);} //new one
    void setFieldName(char *fldname){ strcpy(fieldName,fldname);}
    DbRetVal addToCacheTableFile(bool isDirect);
    static int getTableMode(char  *tabname);
    void setFieldListVal(char *field) {strcpy(fieldlistVal,field);}

    DbRetVal addToCacheTableFile();
    DbRetVal removeFromCacheTableFile();
    DbRetVal load(bool tabDef=true);
    DbRetVal reload();
    DbRetVal unload(bool tabDefinition = true);
    DbRetVal refresh();
    DbRetVal recoverAllCachedTables();
    DbRetVal load(DatabaseManager *dbMgr, bool tabDef);
    static DbRetVal isTableCached(char *tablename);
    DbRetVal isTablePresent();// new one by :Jitendra
    bool isFieldExist(char *fieldname);
};

class BindBuffer
{
    public:
    void *csql;
    void *targetdb;
    DataType type;
};
class CacheTableInfo
{
    public:
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    char projFieldlist[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];

    void setTableName(char *tblName){strcpy(tableName,tblName);}
    void setFieldName(char *fldName){strcpy(fieldName,fldName);}
    void setProjFieldList(char *fieldlist){ strcpy(projFieldlist,fieldlist);}
    void setCondition(char *cond){ strcpy(condition,cond);}
    char *getTableName(){return tableName;}
    char *getFieldName(){return fieldName;}
    char *getCondition(){ return condition;}
    char *getProjFieldList(){return projFieldlist;}
};
