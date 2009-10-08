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
#include<os.h>
#include<TableConfig.h>
#include<Util.h>

TableConfig TableConf::config;

char *TableConfig::getConditionVal(char *condition)
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
//    printf("Condition %s\n",condition);
    return condition;
}

char *TableConfig::getRealConditionFromFile(char *condition)
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
//    printf("Condition %s\n",condition);
    return condition;
}

DbRetVal TableConfig::addToCacheTableFile(bool isDirect)
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\nTable will not be recovered in case of crash");
        return ErrSysInit;
    }
    unsigned int mode = 0;
    bool isFldName = strcmp(fieldName,"") != 0;
    bool isCondVal = strcmp(conditionVal,"") != 0;
    bool isFldListVal = strcmp(fieldlistVal,"") != 0; 
    bool isDsn = strcmp(dsnName,"") != 0;
    
    if (!isCondVal && !isFldListVal && !isDirect) 
        mode |= SIMPLE_CACHE;
    if (isCondVal) mode |= CONDNL_CACHE;
    if (isDirect) mode |= DIRECT_CACHE;
    if (isFldListVal) mode |= FLDLVL_CACHE; 
    
    if (!isFldName) strcpy(fieldName,"NULL"); 
    bool isCached = isTableCached(mode);
    if (!isCached) strcpy(dsnName, "NULL"); 
    else if (!isDsn && isCached) strcpy(dsnName, Conf::config.getDSN()); 
   
    if (isCondVal && isFldListVal) {
        fprintf(fp,"%d %s %s %s %s %s \n", mode, tableName, fieldName,
                         getConditionVal(conditionVal), fieldlistVal, dsnName);
    }
    else if (isCondVal && !isFldListVal) {
        strcpy(fieldlistVal,"NULL");
        fprintf(fp,"%d %s %s %s %s %s \n", mode, tableName, fieldName,
                         getConditionVal(conditionVal), fieldlistVal, dsnName);
    }
    else if (!isCondVal && isFldListVal) {
        strcpy(conditionVal,"NULL");
        fprintf(fp,"%d %s %s %s %s %s \n", mode, tableName, fieldName,
                                          conditionVal, fieldlistVal, dsnName);
    } else {
        strcpy(fieldlistVal,"NULL");
        strcpy(conditionVal,"NULL");
        fprintf(fp,"%d %s %s %s %s %s \n", mode, tableName, fieldName,
                                          conditionVal, fieldlistVal, dsnName);
    } 
    fclose(fp);
    return OK;
}

DbRetVal TableConfig::removeFromCacheTableFile()
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
    char dsnName[IDENTIFIER_LENGTH];

    unsigned int mode;
    while(!feof(fp))
    {
        fscanf(fp, "%d %s %s %s %s %s \n", &mode, tablename,fieldname,condition,field,dsnName);
        if (strcmp (tablename, tableName) == 0) continue;
        fprintf(tmpfp, "%d %s %s %s %s %s \n", mode, tablename,fieldname,condition,field,dsnName);
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
    ret = unlink(tmpFileName);
    return OK;
}

DbRetVal TableConfig::updateIntoCacheTableFile(bool upgrade, bool isDirect)
{
    FILE *fp, *tmpfp;
    char tmpFileName[MAX_FILE_PATH_LEN];
    sprintf(tmpFileName, "%s.tmp", Conf::config.getTableConfigFile());
    tmpfp = fopen(tmpFileName,"w");
    if( tmpfp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\n");
        return ErrSysInit;
    }
    fp = fopen(Conf::config.getTableConfigFile(),"r+");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return ErrSysInit;
    }
    
    unsigned int mode = 0;
    bool isFldName = strcmp(fieldName,"") != 0;
    bool isCondVal = strcmp(conditionVal,"") != 0;
    bool isFldListVal = strcmp(fieldlistVal,"") != 0; 
    bool isDsn = strcmp(dsnName,"") != 0;
    
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];

    char updtablename[IDENTIFIER_LENGTH];
    char updfieldname[IDENTIFIER_LENGTH];
    char updcondition[IDENTIFIER_LENGTH];
    char updfield[IDENTIFIER_LENGTH];
    char upddsnName[IDENTIFIER_LENGTH];
    
    unsigned int tblMode = 0;
    unsigned int modeToUpd = 0;
    bool found = false;
    //if (mode == 1 && upgrade) updMode = 8;
    //else if (mode == 8 && !upgrade) updMode = -8;
    //else if( mode == 1 && !upgrade) updMode = -1;
    while(!feof(fp))
    {
        fscanf(fp, "%d %s %s %s %s %s \n", &tblMode, tablename,fieldname,condition,field,dsnName);
        if (strcmp (tablename, tableName) == 0) {
            modeToUpd = tblMode;
            strcpy(updtablename, tablename);
            strcpy(updfieldname, fieldname);
            strcpy(updcondition, condition);
            strcpy(updfield, field);
            strcpy(upddsnName, dsnName);
            //else strcpy(upddsnName, "NULL");
            found = true;
            continue;
        }
        fprintf(tmpfp, "%d %s %s %s %s %s \n", tblMode, tablename,fieldname,condition,field,dsnName);
    }
    if (found) {
        bool isCached = isTableCached(modeToUpd);
        if (isCached) { 
            unsetCacheMode(&modeToUpd);
            strcpy(updfieldname, "NULL");
            strcpy(updcondition, "NULL");
            strcpy(updfield, "NULL"); 
            strcpy(upddsnName, "NULL");
        }
        
        fprintf(tmpfp, "%d %s %s %s %s %s\n", modeToUpd, updtablename, 
                             updfieldname, updcondition, updfield, upddsnName);
        fclose(tmpfp);
        fclose(fp);
        char sysCommand[MAX_FILE_PATH_LEN * 2];
        sprintf(sysCommand, "mv %s %s", tmpFileName, 
                                            Conf::config.getTableConfigFile());
        int ret = system(sysCommand);
        if (ret != 0)
        {
            printError(ErrSysInit, "Check csqltable.conf file permission. unable to remove %s from file", tableName);
            return ErrSysInit;
        }
    } else { fclose (fp); fclose(tmpfp); }
    unlink(tmpFileName);
    return OK;
}

// new function is added by: Jitendra 
DbRetVal TableConfig :: isTablePresent()
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
	char dsnName[IDENTIFIER_LENGTH];
	int mode;
	
	while(!feof(fp))
	{
		tablename[0] = '\0'; condition[0] = '\0';
		fscanf(fp,"%d %s %s %s %s %s \n",&mode,tablename,fieldname,condition,field,dsnName);
	
        	if(strcmp(tableName,tablename)==0)
        	{
                     fclose(fp);
                     return OK;
        	}
        }  
        fclose(fp);
	return ErrNotExists;
}


DbRetVal TableConfig::isTableCached(char *tabName)
{
    FILE *fp;
    char tmpFileName[MAX_FILE_PATH_LEN];
    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH]; tablename[0]='\0';
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
    unsigned int tabMode = 0;

    while(!feof(fp))
    {
        fscanf(fp, "%d %s %s %s %s %s \n", &tabMode, tablename,fieldname,
                                                      condition,field,dsnName);
        if (strcmp (tablename, tabName) == 0) {
            fclose(fp);
            bool isCached = isTableCached(tabMode);
            if (isCached) return OK;
            else return ErrNotCached;
        }
    }
    fclose(fp);
    return ErrNotCached;
}


unsigned int TableConfig::getTableMode(char *tabname)
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cachetable.conf file does not exist");
        fclose(fp);
        return 0;
    }
    char tablename[IDENTIFIER_LENGTH]; tablename[0] = '\0';
    char fieldname[IDENTIFIER_LENGTH]; 
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
    unsigned int tabMode=0;
    while(!feof(fp)) {
	    fscanf(fp,"%d %s %s %s %s %s \n",&tabMode,tablename,fieldname,
                                                  fieldname,condition,dsnName);
        if (0 == strcmp(tabname,tablename)) {
            fclose(fp);
            return tabMode;
        }
    }
    fclose(fp);
    return 0;
}


bool TableConfig::isFieldExist(char *fieldname)
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
DbRetVal TableConfig::CacheInfo(bool isTabPresent)
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
	 char dsnName[IDENTIFIER_LENGTH];
	 unsigned int mode = 0;

	 printf("\n=================================================================================================================\n");
	 printf("|Mode|\tTable Name\t|\tPrimary Key\t|\tCondition\t|\tField List\t|\tDSN\t|\n");
	 printf("=================================================================================================================\n");
	 while(!feof(fp))
	 { 
	       fscanf(fp,"%d %s %s %s %s %s \n",&mode,tablename,pkfield,condition,field,dsnName);
	       if(!mode) {
               printf("|                                Cached table does not exist.                                                   |\n");
		       printf("=================================================================================================================\n");
               return OK;
           }
	                     
	       if(isTabPresent)
	       {
		  if(strcmp(tableName,tablename)==0)
		  {
		    printf("|%2d  |%16s\t|%16s\t|%16s\t|%16s\t|%10s\t|\n",mode,tablename,pkfield,getRealConditionFromFile(condition),field,dsnName);
		    printf("-----------------------------------------------------------------------------------------------------------------\n\n");
		    fclose(fp);
		    return OK;
	          }
	       }
               else
	       {
		    
		    printf("|%2d  |%16s\t|%16s\t|%16s\t|%16s\t|%10s\t|\n",mode,tablename,pkfield,getRealConditionFromFile(condition),field,dsnName);
		    printf("-----------------------------------------------------------------------------------------------------------------\n");
               }
	 }
	 printf("\n");
	 fclose(fp);
	 return OK;
}

DbRetVal TableConfig::getDsnAndTdb(char *dsn,char *newdsn, char *tdb)
{
    char dsnId[IDENTIFIER_LENGTH]; dsnId[0]='\0';
    char user[IDENTIFIER_LENGTH]; user[0] = '\0';
    char passwd[IDENTIFIER_LENGTH]; passwd[0] = '\0';
    char tdbname[IDENTIFIER_LENGTH]; tdbname[0]='\0';
    FILE *fp=NULL;
    bool isDSNExist=false;
    fp = fopen(Conf :: config.getDsConfigFile(),"r");
    if(fp==NULL)
    {
        printError(ErrSysInit, "csqlds.conf file does not exist");
        return ErrSysInit;
    }
    while(!feof(fp)) {
        fscanf(fp,"%s %s %s %s\n",dsnId,user,passwd,tdbname);
        if(strcmp(dsnId,dsn)==0) {   
            if( strcmp(user,"NULL")!=0 && strcmp(passwd,"NULL")!=0) {
                sprintf(newdsn,"DSN=%s;UID=%s;PWD=%s;",dsn,user,passwd);isDSNExist=true; break;
            }
            else
            {
                sprintf(newdsn,"DSN=%s;",dsn);  isDSNExist=true;break;
            }
        }
    }

    fclose(fp);
    if(isDSNExist)
    {
        strcpy(tdb, tdbname);
        return OK;
    }
    else
    {
        printError(ErrNotExists,"dsn is not present in the csqlds.conf file\n");
        return ErrNotExists;
    }
}

//get the DSN for respective cached table.
//This function is used in "SqlGwStatement.cxx:prepare()"
DbRetVal TableConfig::getDsnForTable(char *tab, char *dsnname)
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL){
        printError(ErrSysInit, "cachetable.conf file does not exist");
        fclose(fp);
        return ErrOS;
     }
     char tablename[IDENTIFIER_LENGTH];tablename[0]='\0';
     char pkfield[IDENTIFIER_LENGTH];pkfield[0]='\0';
     char condition[IDENTIFIER_LENGTH];condition[0]='\0';
     char field[IDENTIFIER_LENGTH];field[0]='\0';
     char dsnName[IDENTIFIER_LENGTH];dsnName[0]='\0';
     int mode;
     char *dsn=NULL;
     
     while(!feof(fp)){
         fscanf(fp,"%d %s %s %s %s %s \n",&mode,tablename,pkfield,condition,field,dsnName);
         if(strcmp(tab,tablename)==0){
             strcpy(dsnname, dsnName);
             fclose(fp);
             return OK;
         }
         
      }   
      fclose(fp);
      return ErrNotFound;
}
