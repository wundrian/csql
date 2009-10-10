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
#include <os.h>
#include <CSql.h>
#include <TableConfig.h>

void printUsage()
{
   printf("Usage: csqlds [-U username] [-P passwd] [-D dsnname] [-N tdbname] \n"
          "       [-a] [-r] \n");
   printf("       username -> Username of TDB .\n");
   printf("       passwd -> Password of TDB.\n");
   printf("       dsnname -> DSN to connect to tdb.\n");
   printf("       tdbname -> Name of Target database\n");
   printf("       -a -> Add entry to csqlds.conf\n");
   printf("       -r -> Remove entry from csqlds.conf\n");
   return;
}
DbRetVal removeEntryFromCsqlds(char *dsn);
DbRetVal addEntryToCsqlds(char *dsn, char *uname, char *pwd, char *tbdname);
Config Conf::config;
int shouldadd=0;
int main(int argc, char **argv)
{
    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char dsn[IDENTIFIER_LENGTH];
    char tdbname[IDENTIFIER_LENGTH];
    bool isUserNameSpecified=false;
    bool isPasswordSpecified=false;
    bool isTDBSpecified=false;
    bool isDSNSpecified=false;
    bool showmsg=false;
    while ((c = getopt(argc, argv, "U:P:D:N:ar?")) != EOF) 
    {
        switch (c)
        {
            case 'U' : { strcpy(username, argv[optind - 1]);
                         isUserNameSpecified=true; opt=10; break; }
            case 'P' : { strcpy(password, argv[optind - 1]); 
                         isPasswordSpecified=true;opt=10; break; }
            case 'D' : { strcpy(dsn, argv[optind - 1]); 
                         opt = 2; 
                         isDSNSpecified = true; 
                         break; 
                       }
            case 'N' : { strcpy(tdbname, argv[optind - 1]); 
                         if(opt == 2) opt=3; 
                         else opt=10;
                         isTDBSpecified = true; 
                         break; 
                       }
            case '?' : {showmsg=true; break; } //print help 
            case 'a' : { shouldadd=1; break; } 
            case 'r' : { shouldadd=2; break;} 
            default: opt=10; 
        }
    }//while options
    if (opt == 10 || true==showmsg) {
        printUsage();
        return 0;
    }

    if( !isUserNameSpecified || !isPasswordSpecified)
    {
        strcpy(username, "NULL");
        strcpy(password, "NULL");
    }
    
    if(shouldadd == 1)
    {
        if(opt==3){
            addEntryToCsqlds( dsn,username,password,tdbname);
        }
        else{
            printUsage();
            return 0;
        }
           
    }else if (shouldadd == 2)
    {
        removeEntryFromCsqlds(dsn);
    }else
    {
        printf("Invalid option passed\n");
        printUsage();
    }
    return 0;
}

DbRetVal addEntryToCsqlds(char *dsn, char *uname, char *pwd, char *tbdname)
{
   FILE *fp = fopen(Conf::config.getDsConfigFile(), "a+");
   if (NULL == fp) {
       printError(ErrSysInit, "Invalid path/filename in DS_CONFIG_FILE.\n");
       return ErrOS;
   }
   bool isDsnExist=false;
   char usertmp[IDENTIFIER_LENGTH];
   char pwdtmp[IDENTIFIER_LENGTH];
   char dsntmp[IDENTIFIER_LENGTH];
   char tdbname[IDENTIFIER_LENGTH];
   while(!feof(fp))
   {
        fscanf(fp, "%s %s %s %s\n",dsntmp,usertmp,pwdtmp,tdbname );
        if (strcmp (dsn, dsntmp) == 0) {
            isDsnExist=true; 
            printf("Applied DSN already Exists\n");
            return ErrAlready;
        }
   }
   fprintf(fp,"%s %s %s %s\n",dsn, uname, pwd, tbdname);
   fclose(fp);
   return OK;
}

DbRetVal removeEntryFromCsqlds(char *dsn)
{
   FILE  *fp,*tmpfp;
   char tmpFileName[MAX_FILE_PATH_LEN];
   sprintf(tmpFileName, "%s.tmp", Conf::config.getDsConfigFile());
   char usertmp[IDENTIFIER_LENGTH];
   char pwdtmp[IDENTIFIER_LENGTH];
   char dsntmp[IDENTIFIER_LENGTH];
   char tdbname[IDENTIFIER_LENGTH];
   tmpfp = fopen(tmpFileName,"w");
   if( tmpfp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\n");
        return ErrSysInit;
   }
   fp = fopen(Conf::config.getDsConfigFile(),"r");
   if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return ErrSysInit;
   }
    
   while(!feof(fp))
   {
        fscanf(fp, "%s %s %s %s\n",dsntmp,usertmp,pwdtmp,tdbname );
        if (strcmp (dsn, dsntmp) == 0) continue;
        fprintf(tmpfp, "%s %s %s %s\n",dsntmp,usertmp,pwdtmp,tdbname);
   }
   fclose(fp);
   fclose(tmpfp);
   char sysCommand[MAX_FILE_PATH_LEN * 2];
   sprintf(sysCommand, "mv %s %s", tmpFileName, Conf::config.getDsConfigFile());
   int ret = system(sysCommand);
   if (ret != 0)
   {
       printError(ErrSysInit, "Check csqltable.conf file permission. unable to remove %s from file", dsn);
       return ErrSysInit;
   }
   return OK;
}
