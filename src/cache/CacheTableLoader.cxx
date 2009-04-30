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
#include<CacheTableLoader.h>
#include<Util.h>
char *CacheTableLoader::getConditionVal(char *condition)
{
    char str[124];
    int i=0;
    char *ptr, *ptr1 = str;
    while(condition[i]!='\0')
    {
        if(condition[i] == ' ')
        {
            ptr = (condition+(i+1));
            if(strncasecmp(ptr,"and ",4)==0) {
                *ptr1='#';ptr1++; strncpy(ptr1,ptr,3);  ptr1+=3;
                *ptr1='#';ptr1++; i+=4;
            }
            else if(strncasecmp(ptr,"or ",3)==0) {
                 *ptr1='#';ptr1++;strncpy(ptr1,ptr,2);  ptr1+=2;
                 *ptr1='#';ptr1++; i+=3;
            }
	    else if(strncasecmp(ptr,"between ",8)==0) {
	         *ptr1='#';ptr1++;strncpy(ptr1,ptr,7);  ptr1+=7;
	         *ptr1='#';ptr1++; i+=8;
	    }
	    else if(strncasecmp(ptr,"in ",3)==0) {
	         *ptr1='#'; ptr1++; strncpy(ptr1,ptr,2);  ptr1+=2;
	         *ptr1='#';ptr1++; i+=3;
	    }
	    i++;
	}else{
	*ptr1 = condition[i++];
	ptr1++;
       }
    }
    *ptr1='\0';
    strcpy(condition,str);
    return condition;
}
char *CacheTableLoader::getRealConditionFromFile(char *condition)
{
   char str[124];
   int i=0;
   char *ptr = str;
   while(condition[i]!='\0')
   {
        if(condition[i]=='#'){
           *ptr=' ';
           ptr++;i++;
        }else{
             *ptr=condition[i];
              ptr++;
              i++;
        }
   }
   *ptr='\0';
    strcpy(condition,str);
//  printf("Condition %s\n",condition);
    return condition;
}


DbRetVal CacheTableLoader::addToCacheTableFile(bool isDirect)
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\nTable will not be"
                                "recovered in case of crash");
	return ErrSysInit;
    }
    //TODO::if already table present in the file, it means that the
    //table is replicated. in this case change mode from
    //2 to 3 (repl to replcache)
    if( strcmp(fieldName,"")==0 ){ strcpy(fieldName,"NULL"); }
    if(isDirect)
    { 
        if((strcmp(conditionVal,"")!=0)&&(strcmp(fieldlistVal,"")!=0))
        {
	    fprintf(fp,"%d:%s %s %s %s\n",6,tableName,fieldName,getConditionVal(conditionVal),fieldlistVal);
        }
        else if((strcmp(conditionVal,"")!=0)&&(strcmp(fieldlistVal,"")==0))
        {
	    strcpy(fieldlistVal,"NULL");
	    fprintf(fp,"%d:%s %s %s %s\n",6,tableName,fieldName,getConditionVal(conditionVal),fieldlistVal);
        }
        else if((strcmp(conditionVal,"")==0)&&(strcmp(fieldlistVal,"")!=0))
        {
    	     strcpy(conditionVal,"NULL");
	     fprintf(fp,"%d:%s %s %s %s\n",6,tableName,fieldName,conditionVal,fieldlistVal);
        }
        else 
        {
    	    strcpy(fieldlistVal,"NULL");
	    strcpy(conditionVal,"NULL");
	    fprintf(fp,"%d:%s %s %s %s\n",5,tableName,fieldName,conditionVal,fieldlistVal);
        }	
   }
   else
   {
       if((strcmp(conditionVal,"")!=0)&&(strcmp(fieldlistVal,"")!=0))
       {
           fprintf(fp,"%d:%s %s %s %s\n",2,tableName,fieldName,getConditionVal(conditionVal),fieldlistVal);
       }
       else if((strcmp(conditionVal,"")!=0)&&(strcmp(fieldlistVal,"")==0))
       {
           strcpy(fieldlistVal,"NULL");
           fprintf(fp,"%d:%s %s %s %s\n",2,tableName,fieldName,getConditionVal(conditionVal),fieldlistVal);
       }
       else if((strcmp(conditionVal,"")==0)&&(strcmp(fieldlistVal,"")!=0))
       {
            strcpy(conditionVal,"NULL");
            fprintf(fp,"%d:%s %s %s %s\n",2,tableName,fieldName,conditionVal,fieldlistVal);
       }
       else
       {
           strcpy(fieldlistVal,"NULL");
           strcpy(conditionVal,"NULL");
           fprintf(fp,"%d:%s %s %s %s\n",1,tableName,fieldName,conditionVal,fieldlistVal);
       }

   }
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::removeFromCacheTableFile()
{
    FILE *fp, *tmpfp;
    char tmpFileName[MAX_FILE_PATH_LEN];
    sprintf(tmpFileName, "%s.tmp", Conf::config.getTableConfigFile());
    tmpfp = fopen(tmpFileName,"w");
    if( tmpfp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\n");
	return ErrSysInit;
    }
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
	return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int mode;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s %s %s %s\n", &mode, tablename,fieldname,condition,field);
        if (strcmp (tablename, tableName) == 0) continue;
        fprintf(tmpfp, "%d:%s %s %s %s\n", mode, tablename,fieldname,condition,field);
    }
    fclose(tmpfp);
    fclose(fp);
    char sysCommand[MAX_FILE_PATH_LEN * 2];
    sprintf(sysCommand, "mv %s %s", tmpFileName, Conf::config.getTableConfigFile());
    int ret = system(sysCommand);
    if (ret != 0) 
    {
        printError(ErrSysInit, "Check csqltable.conf file permission. unable to remove %s from file", tableName);
	return ErrSysInit;
    }
    return OK;
}

// new function is added by: Jitendra 
DbRetVal CacheTableLoader :: isTablePresent()
{
	DbRetVal rv = OK;
        FILE *fp;
  	Connection conn;
	rv = conn.open(userName,password);
	if(rv !=OK) return ErrSysInit;
	// check for CACHE_TABLE variable
	
	
	fp = fopen(Conf :: config.getTableConfigFile(),"r");
	if(fp == NULL)
        {
 		printError(ErrSysInit, "cachetable.conf file does not exist");
		return OK;
	}
	conn.close();
	
	char tablename[IDENTIFIER_LENGTH];
	char condition[IDENTIFIER_LENGTH];
	char fieldname[IDENTIFIER_LENGTH];
	char field[IDENTIFIER_LENGTH];
	int mode;
	
	while(!feof(fp))
	{
		tablename[0] = '\0'; condition[0] = '\0';
		fscanf(fp,"%d:%s %s %s %s\n",&mode,tablename,fieldname,condition,field);
	
        	if(strcmp(tableName,tablename)==0)
        	{
                     fclose(fp);
                     return OK;
        	}
        }  
        fclose(fp);
	return ErrNotExists;
}



DbRetVal CacheTableLoader::load(bool tabDefinition)
{
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if (rv != OK) return ErrSysInit;
    // check for CACHE_TABLE variable
	  

    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printError(ErrSysInit, "Auth failed\n"); return ErrSysInit; }
    if (tabDefinition == false) {
        Table *tbl = dbMgr->openTable(tableName);
        if (tbl == NULL) {
            conn.close();
            return ErrNotExists;
        }
        if (tbl->numTuples()) {
            printError(ErrNotEmpty, "The table '\%s\' is not empty", tableName);
            dbMgr->closeTable(tbl);
            conn.close();
            return ErrNotEmpty;
        }
    }
    conn.startTransaction();
    rv = load(dbMgr, tabDefinition);
    conn.commit();
    conn.close();
    return rv;
}

DbRetVal CacheTableLoader::load(DatabaseManager *dbMgr, bool tabDefinition)
{
    char dsn[72];
    sprintf(dsn, "DSN=%s;", Conf::config.getDSN());
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    DbRetVal rv = OK;
    int retValue =0;
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", dsn);
    } else {
        fprintf(stderr, "Failed to connect to target database\n");
        return ErrSysInit;
    }

    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    char stmtBuf[1024];
    
    if(((strcmp(conditionVal,"")==0) || (strcmp(conditionVal,"NULL")==0)) && ((strcmp(fieldlistVal,"")==0) || (strcmp(fieldlistVal,"NULL")==0)))
    {
       sprintf(stmtBuf, "SELECT * FROM %s;", tableName);
    }
    else if(((strcmp(conditionVal,"")!=0) || (strcmp(conditionVal,"NULL")!=0)) && ((strcmp(fieldlistVal,"")==0) || (strcmp(fieldlistVal,"NULL")==0)))
    {
       sprintf(stmtBuf,"SELECT * FROM %s where %s;",tableName,conditionVal);

    }
    else if(((strcmp(conditionVal,"")==0) || (strcmp(conditionVal,"NULL")==0)) && ((strcmp(fieldlistVal,"")!=0) || (strcmp(fieldlistVal,"NULL")!=0)))
    {
    	sprintf(stmtBuf,"SELECT %s FROM %s;",fieldlistVal,tableName);
    }	
    else
        sprintf(stmtBuf,"SELECT %s FROM %s where %s;",fieldlistVal,tableName,conditionVal);

    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) {printError(ErrSysInit, "Unable to Prepare ODBC statement \n"); return ErrSysInit; }

    if (tabDefinition) {
        short totalFields=0;
        retValue = SQLNumResultCols (hstmt, &totalFields);
        if (retValue) {printError(ErrSysInit, "Unable to retrieve ODBC total columns\n"); return ErrSysInit; }
        UWORD                   icol;
        UCHAR                   colName[IDENTIFIER_LENGTH];
        SWORD                   colNameMax;
        SWORD                   nameLength;
        SWORD                   colType;
        SQLULEN                 colLength;
        SWORD                   scale;
        SWORD                   nullable;
        TableDef tabDef;
        icol = 1; colNameMax = IDENTIFIER_LENGTH;
	char columnname[IDENTIFIER_LENGTH];
        char indexname[IDENTIFIER_LENGTH];
        short type; short unique;
        SQLHSTMT hstmtmeta;
        retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmtmeta);
        if (retValue)
        {
            printError(ErrSysInit, "Unable to allocate ODBC handle \n");
            return ErrSysInit;
        }
        retValue=SQLPrimaryKeys(hstmtmeta, NULL, SQL_NTS, NULL, SQL_NTS, (SQLCHAR*) tableName, SQL_NTS);
        retValue = SQLBindCol(hstmtmeta, 4, SQL_C_CHAR,columnname, 129,NULL);
        HashIndexInitInfo *inf = new HashIndexInitInfo();
        bool isPriIndex=false;
        char indname[IDENTIFIER_LENGTH];
        if(SQLFetch( hstmtmeta ) == SQL_SUCCESS)
        {
               inf->list.append(columnname);
               while( SQLFetch( hstmtmeta ) == SQL_SUCCESS )
               {
                   inf->list.append(columnname);
               }
               inf->indType =  hashIndex;
               inf->bucketSize = 10007;
               inf->isUnique = true; inf->isPrimary = true;
               strcpy(inf->tableName, tableName);
               strcpy(indexname,"PRIMARY");
               sprintf(indname, "%s_%s", tableName, indexname);
               isPriIndex=true;
        }
        char *name = NULL;
        bool iskeyfieldExist=true;
        if(isPriIndex && (strcmp(fieldlistVal,"")!=0) && (strcmp(fieldlistVal,"NULL")!=0))
        {
            inf->list.resetIter();
            while ((name=inf->list.nextFieldName())!=NULL)
            {
                        iskeyfieldExist=isFieldExist(name);
                        if(!iskeyfieldExist) { break; }
            }
        }else if(!isPriIndex){iskeyfieldExist = false;}
        if(((strcmp(fieldName,"")!=0) && (strcmp(fieldName,"NULL")!=0)) && !(isFieldExist(fieldName)))
        {
            if(Conf::config.useTwoWayCache() && (strcmp(fieldlistVal,"")!=0) && (strcmp(fieldlistVal,"NULL")!=0))
            {
                 printError(ErrSysInit, "Bidirectonal caching fail for no primary key in %s \n", tableName);
                 return ErrSysInit;
            }
        }
        
        if(!iskeyfieldExist && ((strcmp(fieldName,"")==0) || (strcmp(fieldName,"NULL")==0)))
        {
            if(Conf::config.useTwoWayCache())
             {
                 printError(ErrSysInit, "Bidirectonal caching fail for no primary key in %s \n", tableName);
                 return ErrSysInit;
             }
        } 
        bool isKeyFld=false;
        bool isNullfld=false;
        while (icol <= totalFields) {
            retValue = SQLDescribeCol(hstmt, icol, colName, colNameMax,
                                        &nameLength, &colType, &colLength,
                                        &scale, &nullable);
            if (retValue) {printError(ErrSysInit, "Unable to retrieve ODBC column info\n"); return ErrSysInit; }

            printDebug(DM_Gateway, "Describe Column %s %d %d \n", colName, colType, colLength);
            icol++;
            if(strcmp((char*)colName,fieldName)== 0)
            {
                isKeyFld=true;
                isNullfld=true;
            }
            bool isPriFld=false;
            if (nullable) {
                inf->list.resetIter();
                while ((name=inf->list.nextFieldName())!=NULL)
                {
                        if(0==strcmp((char*)colName,name))
                        {
                                tabDef.addField((char*)colName, AllDataType::convertFromSQLType(colType), colLength +1, NULL, true);
                                isPriFld=true;
                                break;
                        }
                }
                if(!isPriFld) { 
                   if(!isNullfld)
                       tabDef.addField((char*)colName, AllDataType::convertFromSQLType(colType), colLength +1); 
                   else{
                       tabDef.addField((char*)colName, AllDataType::convertFromSQLType(colType), colLength +1, NULL, true);
                       isNullfld=false;
                   }
                }
            }
            else
                tabDef.addField((char*)colName, AllDataType::convertFromSQLType(colType), colLength +1, NULL, true);
        }
        if(((strcmp(fieldName,"")!=0) && (strcmp(fieldName,"NULL")!=0))&& !isKeyFld)
        {
            printError(ErrSysInit, "Unable to cache Table for %s with key field %s\n", tableName,fieldName);
            SQLDisconnect(hdbc);
            return ErrSysInit;
        }
        rv = dbMgr->createTable(tableName, tabDef);
        if (rv != OK)
        {
             printError(ErrSysInit, "Table creation failed in csql for %s\n", tableName);
             SQLDisconnect(hdbc);
             return ErrSysInit;
        }
        if(isPriIndex ){
        rv = dbMgr->createIndex(indname, inf);
               if (rv != OK)
               {
                   printError(ErrSysInit, "Index creation failed in csql for %s\n", tableName);
                   SQLDisconnect(hdbc);
                   return ErrSysInit;
               }
        }
        else
        {
             if(Conf::config.useTwoWayCache() && iskeyfieldExist)
             {
                 printError(ErrSysInit, "Bidirectonal caching fail for no primary key in %s \n", tableName);
                 return ErrSysInit;
             }
        }
        retValue = SQLCloseCursor(hstmtmeta);
        isKeyFld= false;
        retValue = SQLStatistics(hstmtmeta, NULL, 0, NULL, SQL_NTS,
                    (SQLCHAR*) tableName, SQL_NTS, SQL_INDEX_ALL, SQL_QUICK);
        retValue = SQLBindCol(hstmtmeta, 4, SQL_C_SHORT,
                          &unique, 2, NULL);
        retValue = SQLBindCol(hstmtmeta, 6, SQL_C_CHAR,
                          indexname, 129, NULL);
        retValue = SQLBindCol(hstmtmeta, 7, SQL_C_SHORT,
                          &type, 2, NULL);
        retValue = SQLBindCol(hstmtmeta, 9, SQL_C_CHAR,
                          columnname, 129,NULL);
        while ((retValue = SQLFetch(hstmtmeta)) == SQL_SUCCESS)
        {  //if (type != SQL_TABLE_STAT)
            {
                printDebug(DM_Gateway, "Column: %-18s Index Name: %-18s unique:%hd type:%hd\n",
                  columnname, indexname, unique, type);
            }
            if(0 == strcmp(columnname,fieldName)){isKeyFld=true;}
            bool isPrimary=false;
            inf->list.resetIter();
            while ((name=inf->list.nextFieldName())!=NULL)
            {
                if(0==strcmp(columnname,name))
                {
                        isPrimary=true;
                        break;
                }
            }
            if(isPrimary){continue;}
            if (type == 3) {
               HashIndexInitInfo *info = new HashIndexInitInfo();
               info->indType =  hashIndex;
               info->bucketSize = 10007;
               info->list.append(columnname);
               if (!unique) {info->isUnique = true; info->isPrimary = false;}
               strcpy(info->tableName, tableName);
               char indname[128];
               sprintf(indname, "%s_%s", tableName, indexname);
               rv = dbMgr->createIndex(indname, info);
               if (rv != OK)
               {
                  printError(ErrSysInit, "Index creation failed in csql for %s\n", tableName);
                  SQLDisconnect(hdbc);
                  return ErrSysInit;
               }
               delete info;
           } else {
               printError(ErrSysInit,"CSQL does not support this index type\n");
               SQLDisconnect(hdbc);
               return ErrSysInit;
           }
       }// while meta data fetch for index creation
       SQLCloseCursor (hstmtmeta);
       SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
       if( !isKeyFld && ((strcmp(fieldName,"")!=0) && (strcmp(fieldName,"NULL")!=0)))
       {
            printError(ErrSysInit, "Unable to cache Table for %s with key field %s\n", tableName,fieldName);
            dbMgr->dropTable(tableName);
            SQLDisconnect(hdbc);
            return ErrSysInit;
       }
    }
    Table *table = dbMgr->openTable(tableName);
    if (table == NULL) {
        printError(ErrSysInit,"unable to open table %s\n", tableName);
        dbMgr->closeTable(table);
        if (tabDefinition) dbMgr->dropTable(tableName);
        SQLDisconnect(hdbc);
        return ErrSysInit;
    }
    table->setUndoLogging(false);
    //rv = table->lock(false); //no need to release this lock as it is upgrade from S to X
    if (rv != OK)
    {
        dbMgr->closeTable(table);
        if (tabDefinition) dbMgr->dropTable(tableName);
        SQLDisconnect(hdbc);
        return ErrSysInit;
    }
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf; int fieldsize=0;
    Identifier *elem = NULL;

    BindBuffer *bBuf;
    List valBufList;
    SQLINTEGER len[IDENTIFIER_LENGTH];
    while (fNameIter.hasElement()) {
        elem = (Identifier*) fNameIter.nextElement();
        table->getFieldInfo((const char*)elem->name, info);
        valBuf = AllDataType::alloc(info->type, info->length);
        table->bindFld(elem->name, valBuf);
        fieldsize=0;
        switch( info->type) 
        {
            case typeString:
                fieldsize = info->length;
                break;
            case typeDate:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeDate;
                fieldsize = sizeof(DATE_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
            case typeTime:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeTime;
                fieldsize = sizeof(TIME_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
            case typeTimeStamp:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeTimeStamp;
                fieldsize = sizeof(TIMESTAMP_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
        }
        retValue = SQLBindCol (hstmt, fcount, AllDataType::convertToSQLType(info->type),
                               valBuf, fieldsize, &len[fcount]);
        fcount++;
        if (retValue) {printError(ErrSysInit, "Unable to bind columns in ODBC\n"); return ErrSysInit; }
    }
    delete info;
    retValue = SQLExecute (hstmt);
    if (retValue) {printError(ErrSysInit, "Unable to execute ODBC statement\n"); return ErrSysInit; }
    int fldpos=0;
    while(true)
    {
        retValue = SQLFetch (hstmt);
        if (retValue) break;
        ListIterator bindIter = valBufList.getIterator();
        while (bindIter.hasElement()) {
            bBuf = (BindBuffer*) bindIter.nextElement();
            switch (bBuf->type) {
                case typeDate: {
                    Date *dtCSQL = (Date*) bBuf->csql;
                    DATE_STRUCT *dtTarget = (DATE_STRUCT*) bBuf->targetdb;
                    dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                    break;
                }
                case typeTime: {
                    Time *dtCSQL = (Time*) bBuf->csql;
                    TIME_STRUCT *dtTarget = (TIME_STRUCT*) bBuf->targetdb;
                    dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                    break;
                }
                case typeTimeStamp: {
                    TimeStamp *dtCSQL = (TimeStamp*) bBuf->csql;
                    TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bBuf->targetdb;
                    dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                    dtCSQL->setTime(dtTarget->hour,dtTarget->minute,dtTarget->second, dtTarget->fraction);
                    break;
                }
            }
        }
        fldpos=0;
        table->resetNullinfo();
        while(fldpos < fcount-1)
        {
            if(len[++fldpos] == SQL_NULL_DATA){ 
                table->markFldNull(fldpos);
            }
        }
        
        table->insertTuple();
    }
    //TODO::leak:: valBufList and its targetdb buffer
    valBufList.reset();
    dbMgr->closeTable(table);
    SQLCloseCursor (hstmt);
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
    return OK;
}

DbRetVal CacheTableLoader::reload()
{
    DbRetVal rv = unload(false);
    if (rv != OK) return rv;
    rv = load(false);
    return rv;
}

DbRetVal CacheTableLoader::unload(bool tabDefinition)
{
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if (rv != OK) return ErrSysInit;
	  
    if (CacheTableLoader::isTableCached(tableName) != OK) {
        printError(ErrNotCached, "The table \'%s\' is not cached", tableName);
        return ErrNotCached;
    }
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printError(ErrSysInit, "Auth failed\n"); return ErrSysInit; }
    if (!tabDefinition)
    {
        Table *table = dbMgr->openTable(tableName);
        if (table == NULL) { conn.close(); return ErrBadCall; }
        rv = conn.startTransaction();
        if (rv != OK) { dbMgr->closeTable(table); conn.close(); return ErrBadCall; }
        table->truncate();
        conn.commit();
        dbMgr->closeTable(table);
    }
    else
    {
        rv = dbMgr->dropTable(tableName);
    }
    conn.close();

    return rv;
}

DbRetVal CacheTableLoader::refresh()
{
    return OK;
}

DbRetVal CacheTableLoader::recoverAllCachedTables()
{
    FILE *fp;
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if(rv !=OK) return ErrSysInit;

    //Note: if connection is not open, configuration veriables may be incorrect

    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cachetable.conf file does not exist");
	return OK;
    }
    conn.close();
    //TODO::take exclusive lock on database
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int mode;
    rv = OK;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s %s %s %s\n", &mode, tablename,fieldname,condition,field);
        //if (mode ==2 )  //just replicated table and not cached
        //continue;
        printDebug(DM_Gateway, "Recovering Table from target db: %s\n", tablename);
        setCondition(getRealConditionFromFile(condition));
        setTable(tablename);
        setFieldName(fieldname);
	setFieldListVal(field);
        printf("Recovering table %s %s %s\n", tablename,condition,field);
        rv = load();
        if (rv != OK) return rv;
    }
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::isTableCached(char *tabName)
{
    FILE *fp;
    char tmpFileName[MAX_FILE_PATH_LEN];
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int mode;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s %s %s %s\n", &mode, tablename,fieldname,condition,field);
        if (strcmp (tablename, tabName) == 0) {
            fclose(fp);
            return OK;
        }
    }
    fclose(fp);
    return ErrNotExists;
}

int CacheTableLoader::getTableMode(char *tabname)
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cachetable.conf file does not exist");
        fclose(fp);
        return 0;
    }
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int mode;
    while(!feof(fp))
    {
	fscanf(fp,"%d:%s %s %s %s\n",&mode,tablename,fieldname,fieldname,condition);
        if(0==strcmp(tabname,tablename)){
              fclose(fp);
              return mode;
        }
    }
   fclose(fp);
   return 0;
}


bool CacheTableLoader::isFieldExist(char *fieldname)
{
    char tmpfieldname[IDENTIFIER_LENGTH];
    int i=0,j=0;
    while(fieldlistVal[j]!=0)
    {
        if(fieldlistVal[j] != ',')
            tmpfieldname[i++]=fieldlistVal[j++];
        else
        {
           tmpfieldname[i]='\0';
           if(strcmp(fieldname,tmpfieldname)==0)
               return true;
           else { i=0; j++; }
        }   
    }
    tmpfieldname[i]='\0';
    if(strcmp(fieldname,tmpfieldname)==0)
        return true;
    else
        return false;
}

DbRetVal CacheTableLoader::CacheInfo(bool isTabPresent)  /* Cacheh Description using "-S" option */
{
 	   FILE *fp;
           fp = fopen(Conf::config.getTableConfigFile(),"r");
           if( fp == NULL ) {
           printError(ErrSysInit, "cachetable.conf file does not exist");
           fclose(fp);
           return OK;
           }
  
           char tablename[IDENTIFIER_LENGTH];
           char pkfield[IDENTIFIER_LENGTH];
           char condition[IDENTIFIER_LENGTH];
           char field[IDENTIFIER_LENGTH];
           int mode;
           printf("\n=================================================================================================================\n");
           printf("|\tMode\t|\tTable Name\t|\tPrimary Key\t|\tCondition\t|\tField List\t|\n");
           printf("=================================================================================================================\n");
 	   
	   while(!feof(fp))
	   {
	         fscanf(fp,"%d:%s %s %s %s\n",&mode,tablename,pkfield,condition,field);
	         if((mode<1) || (mode >6))
	         {return ErrNotFound;}
	    
	         if(isTabPresent)
	         {
	              if(strcmp(tableName,tablename)==0)
	              {
	                    printf("|%8d\t|%16s\t|%16s\t|%16s\t|%16s\t|\n",mode,tablename,pkfield,getRealConditionFromFile(condition),field);
	                    printf("-----------------------------------------------------------------------------------------------------------------\n\n");
	                    fclose(fp);
	                    return OK;
	               }
	          }
	          else
	          {
	             printf("|%8d\t|%16s\t|%16s\t|%16s\t|%16s\t|\n",mode,tablename,pkfield,getRealConditionFromFile(condition),field);
	             printf("-----------------------------------------------------------------------------------------------------------------\n");
	          }
	    }
	    printf("\n");
	    fclose(fp);
	    return OK;
}

