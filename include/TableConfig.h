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

#define    SIMPLE_CACHE    0x01
#define    CONDNL_CACHE    0x02
#define    FLDLVL_CACHE    0x04
#define    DIRECT_CACHE    0x08


class DllExport TableConfig
{
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    char userName[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
  //  char dsnId[IDENTIFIER_LENGTH];
   // char dsnPwd[IDENTIFIER_LENGTH];

    char conditionVal[IDENTIFIER_LENGTH]; //added newly
    char fieldlistVal[IDENTIFIER_LENGTH];
    bool shouldForce;
    public:
    TableConfig()
    {
        strcpy(tableName,"");
        strcpy(conditionVal,"");
        strcpy(fieldName,"");
	strcpy(fieldlistVal,"");
        strcpy(dsnName,"");
	//strcpy(dsnId,"");
	//strcpy(dsnPwd,"");
	shouldForce = false;
    }
    void init()
    {
        strcpy(tableName,"");
        strcpy(conditionVal,"");
        strcpy(fieldName,"");
        strcpy(fieldlistVal,"");
        strcpy(dsnName,"");
        shouldForce =false;
    }
    void setForceFlag(bool flag){ shouldForce = flag;}
    void setConnParam(char *user, char *pass){ strcpy(userName, user); strcpy(password, pass); }
    void setTable(char *tablename) { strcpy(tableName,tablename); }
    void setDsnName(char *dsnname) { strcpy(dsnName,dsnname);}
    //void setDsnId(char *dsnid) { strcpy(dsnId,dsnid); }
    //void setDsnPwd(char *dsnpwd){ strcpy(dsnPwd,dsnpwd);}

    void setCondition(char *condition){strcpy(conditionVal,condition);} //new one
    void setFieldName(char *fldname){ strcpy(fieldName,fldname);}
    DbRetVal addToCacheTableFile(bool isDirect);
    unsigned int getTableMode(char  *tabname);
    void setFieldListVal(char *field) {strcpy(fieldlistVal,field);}
    
    DbRetVal addToCacheTableFile();
    DbRetVal removeFromCacheTableFile();
    DbRetVal updateIntoCacheTableFile(bool upgrade, bool isDirect=false);
//    DbRetVal load(bool tabDef=true);
//    DbRetVal reload();
//    DbRetVal unload(bool tabDefinition = true);
//    DbRetVal refresh();
//    DbRetVal recoverAllCachedTables();
//    DbRetVal load(DatabaseManager *dbMgr, bool tabDef);

    DbRetVal isTableCached(char *tablename);
    inline bool isTableCached(unsigned int mode) 
    {
        return (mode & SIMPLE_CACHE || mode & CONDNL_CACHE || 
                mode & FLDLVL_CACHE || mode & DIRECT_CACHE);
    }
    inline void unsetCacheMode(unsigned int *mode)
    { 
        *mode &= ~(SIMPLE_CACHE | CONDNL_CACHE | FLDLVL_CACHE | DIRECT_CACHE);
        return;
    }

    DbRetVal isTablePresent();// new one by :Jitendra
    bool isFieldExist(char *fieldname);
    DbRetVal CacheInfo(bool isTabPresent);
    DbRetVal tablesOnDsn();
    char *getRealConditionFromFile(char *condition);
    char *getConditionVal(char *condition);
    static DbRetVal getDsnAndTdb(char *dsn,char *newdsn, char *tdb);
    DbRetVal getDsnForTable(char *tabname, char *dsn);
};

class TableConf
{
    public:
    static TableConfig config;
};

