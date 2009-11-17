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
#ifndef CACHETABLELOADER_H
#define CACHETABLELOADER_H
#include <CSql.h>
#include <sql.h>
#include <sqlext.h>
#include <Network.h>

class CacheIndexInfo
{
    public:
    char indexName[IDENTIFIER_LENGTH];
    FieldNameList fieldList;
};

class CacheTableLoader
{
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    char userName[IDENTIFIER_LENGTH];
    char password[IDENTIFIER_LENGTH];
    char conditionVal[IDENTIFIER_LENGTH]; //added newly
    char fieldlistVal[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
   // char dsnId[IDENTIFIER_LENGTH];
   // char dsnPwd[IDENTIFIER_LENGTH];
    bool shouldForce;
    public:
    CacheTableLoader()
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
    DbRetVal checkSecondTimeSqlPrimaryKeys(SQLHSTMT hstmtmeta,char *tableName,char *ptr, HashIndexInitInfo *inf,bool &isPriIndex);
    DbRetVal createIndex(SQLHSTMT hstmtmeta, char *tableName, HashIndexInitInfo *inf,AbsSqlStatement *stmt,bool isPKFieldSpecified);
    void setForceFlag(bool flag){ shouldForce = flag;}
    void setConnParam(char *user, char *pass){ strcpy(userName, user); strcpy(password, pass); }
    void setTable(char *tablename) { strcpy(tableName,tablename); }
    void setCondition(char *condition){strcpy(conditionVal,condition);} //new one
    void setDsnName(char *dname) {strcpy(dsnName,dname);}
    
    //void setDsnId(char *dsnid) { strcpy(dsnId,dsnid); }
    //void setDsnPwd(char *dsnpwd){ strcpy(dsnPwd,dsnpwd);}
    void setFieldName(char *fldname){ strcpy(fieldName,fldname);}
    DbRetVal addToCacheTableFile(bool isDirect);
    void setFieldListVal(char *field) {strcpy(fieldlistVal,field);}

    DbRetVal addToCacheTableFile();
    DbRetVal removeFromCacheTableFile();
    DbRetVal load(bool tabDef=true);
    DbRetVal reload();
    DbRetVal unload(bool tabDefinition = true);
    DbRetVal refresh();
    DbRetVal recoverAllCachedTables();
    DbRetVal load(AbsSqlConnection *conn, AbsSqlStatement *stmt, bool tabDef);
    DbRetVal isTablePresent();// new one by :Jitendra
    DbRetVal CacheInfo(bool isTabPresent);
    DbRetVal tablesOnDsn();
    char *getConditionVal(char *condition);
    void setParamValues(AbsSqlStatement *stmt, int parampos, DataType type, int length, char *value);
    DbRetVal checkingSchema(SQLHDBC hdbc,SQLHSTMT hstmt,AbsSqlConnection *conn, AbsSqlStatement *stmt,TDBInfo tdbName);
    DbRetVal cacheAllTablesFromDs(char* tdbName,bool tableDefinition, bool isDirect,char *username,char *password);
 

};

class BindBuffer
{
    public:
    void *csql;
    void *targetdb;
    DataType type;
    int length;
    BindBuffer(){ csql = NULL; targetdb = NULL; type = typeUnknown; length =0; }
    ~BindBuffer() { ::free(csql); ::free(targetdb); }
};
class CacheTableInfo
{
    public:
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    char projFieldlist[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
     
    //char dsnId[IDENTIFIER_LENGTH];
    //char dsnPwd[IDENTIFIER_LENGTH];
    
    void setTableName(char *tblName){strcpy(tableName,tblName);}
    void setDsnName(char *dsnname) { strcpy(dsnName,dsnname); }
   // void setDsnId(char *dsnid) { strcpy(dsnId,dsnid); }
    //void setDsnPwd(char *dsnpwd){ strcpy(dsnPwd,dsnpwd);}
    
    void setFieldName(char *fldName){strcpy(fieldName,fldName);}
    void setProjFieldList(char *fieldlist){ strcpy(projFieldlist,fieldlist);}
    void setCondition(char *cond){ strcpy(condition,cond);}
    char *getTableName(){return tableName;}
    char *getFieldName(){return fieldName;}
    char *getCondition(){ return condition;}
    char *getProjFieldList(){return projFieldlist;}
};
#endif
