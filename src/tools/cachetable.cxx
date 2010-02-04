/***************************************************************************
 *
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
#include <CacheTableLoader.h>
#include <TableConfig.h>

void printUsage()
{
   printf("Usage: cachetable [ -U <username> ] [ -P <password> ]\n");
   printf("                  [ -t <tblName> [-D] [ -c \"condition\" ]\n");
   printf("                                 [-f \"fieldListToCache\"]\n");
   printf("                                 [ -p <fieldName> [-F] ]\n");
   printf("                                 [ -u [-s] ]\n");
   printf("                                 [ -s | -r ] ]\n");
   printf("                  [ -S | -R ]\n\n");
   printf("       U -> Username to connect with csql.\n");
   printf("       P -> Password for above username.\n");
   printf("       t -> Table name to be cached in csql from target db.\n");
   printf("       D -> Enable direct access option to target database.\n");
   printf("       c -> Conditional expression used in std SQL WHERE clause.\n");
   printf("       f -> List of field names to be cached. Comma separated.\n");
   printf("       p -> Not Null unique index field name for Bidirectional\n");
   printf("            caching on which trigger needs to be run.\n");
   printf("       d -> Cache the tables from the specified DSN.\n");
   printf("       l -> Retrievs all the cached table names for the specified DSN.\n");
   printf("       F -> Forceful caching.\n");
   printf("       s -> Load only the records from target db.\n"); 
   printf("            Assumes table is already created in csql.\n");
   printf("       u -> Unload the table. If used with -s option,\n");
   printf("            removes only records and preserves the schema.\n");
   printf("       r -> Reload the table. Get the latest image of table from target db.\n");
   printf("       S -> Cache Description for cached tables.\n");
   printf("       R -> Recover all cached tables from the target database.\n");
   return;
}

int main(int argc, char **argv)
{
     DbRetVal rv = OK;   
     Connection conn;
     rv = conn.open(I_USER, I_PASS);
     if (rv != OK) return 1;
     os::signal(SIGCSQL1, SIG_IGN);
     if (!Conf::config.useCache())
     {
        printf("CACHE_TABLE is set to FALSE in csql.conf file.\n");
        conn.close();
        return 2;
     }
     else{ conn.close(); }
    
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    bool isDirect=false;
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char fieldlist[IDENTIFIER_LENGTH];
    char syncModeStr[IDENTIFIER_LENGTH];
    char dsnName[IDENTIFIER_LENGTH];
    bool Isuid=false;
    bool Ispid=false;
    bool conditionval = false;
    bool fieldlistval = false;
    bool tableDefinition = true;
    bool tableNameSpecified = false;
    bool fieldNameSpecified = false;
    bool forceEnable=false;
    bool isDsn=false;
    bool isDsnSpecified=false;

    while ((c = getopt(argc, argv, "U:P:t:d:f:c:p:l:FRDSsru?")) != EOF) 
    {
        switch (c)
        {
            case 'U' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'P' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tablename, argv[optind - 1]); 
                         if (opt==10) opt = 2; 
                         tableNameSpecified = true; 
                         break; 
                       }
            case 'd' : { strcpy(dsnName,argv[optind - 1]);
                         if(!tableNameSpecified)opt=50;
                         isDsn=true;break;
                       }
            case 'l' : {strcpy(dsnName,argv[optind - 1]); isDsnSpecified=true; opt=7; break;}
            case 'p' : { strcpy(fieldname, argv[optind - 1]);
                         if(opt==2){fieldNameSpecified = true;break;}
                       }

            case 'D' : {
                         if(opt==2) {isDirect=true;break;}
                       }
            case 'c' : {strcpy(condition,argv[optind - 1]); conditionval = true; break; }
	    case 'f' : {strcpy(fieldlist,argv[optind - 1]);fieldlistval = true ;break; }
            case 'F' : { if(opt==2 && fieldNameSpecified ) forceEnable=true; break;}
            case '?' : { opt = 10; break; } //print help 
            case 'R' : { opt = 3; break; } //recover all the tables
            case 's' : { tableDefinition=false; break; } //do not get the schema information from target db
            case 'r' : { opt = 4; break; } //reload the table
            case 'u' : { opt = 5; break; } //unload the table
            case 'S' : {opt=6;break;}
	    default: opt=10; 

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }
  
    if (username[0] == '\0' )
    {
        strcpy(username, I_USER);
        strcpy(password, I_PASS);
    }
    CacheTableLoader cacheLoader;
    cacheLoader.setConnParam(username, password);
    TableConf::config.setConnParam(username, password);
    if(conditionval){
        cacheLoader.setCondition(condition);// new one
        TableConf::config.setCondition(condition); 
    }
    
    if(isDsn){
        cacheLoader.setDsnName(dsnName);
        TableConf::config.setDsnName(dsnName); 
    }   
    
    if(fieldlistval) {
        cacheLoader.setFieldListVal(fieldlist);
        TableConf::config.setFieldListVal(fieldlist); 
    }
    if(forceEnable) {
        cacheLoader.setForceFlag(forceEnable);
        TableConf::config.setForceFlag(forceEnable);
    }
    bool isCached = false;
    unsigned int mode = TableConf::config.getTableMode(tablename);

    if (opt==2) {
        cacheLoader.setTable(tablename);
        TableConf::config.setTable(tablename);
	    if(fieldNameSpecified){ 
            cacheLoader.setFieldName(fieldname); 
            TableConf::config.setFieldName(fieldname);
        }

        isCached = TableConf::config.isTableCached(mode);
        if (isCached) {
             printf("Table is already cached, unload table by\n"); 
             printf("\"cachetable -t <tablename> -u\" and then try \n");
            return 3;
        }
        rv = cacheLoader.load(tableDefinition);
        if(rv != OK) return 4;
        TableConf::config.addToCacheTableFile(isDirect);
    } else if (opt==3) {//recover
        rv = cacheLoader.recoverAllCachedTables();
        if (rv != OK) return 5;
    } else if (opt==4) {//reload
        if (!tableNameSpecified) 
        {
            printf("Table name is not specified. Check usage with ? \n");
            return 6;
        }
        cacheLoader.setTable(tablename);
        TableConf::config.setTable(tablename);
        rv = cacheLoader.reload();
        if (rv != OK) return 7;
	
    } else if (opt==5) {//unload
        if (!tableNameSpecified) 
        {
            printf("Table name is not specified. Check usage with ? option\n");
            return 8;
        }
        cacheLoader.setTable(tablename);
        TableConf::config.setTable(tablename);
        isCached = TableConf::config.isTableCached(mode);
        if (!mode) {
            printError(ErrNotCached, "Table is not Cached");
            return 9;
        }
        TableConf::config.removeFromCacheTableFile();
    } else if(opt==6) {
        if(tableNameSpecified) {
	        cacheLoader.setTable(tablename);
	        TableConf::config.setTable(tablename);
	    }
        rv = TableConf::config.CacheInfo(tableNameSpecified);
	    if (rv !=OK) {
	        printf("\nError (%d): None of the table found in Cache,You need to cache the table from Target DB.\n\n",rv);
	        exit(2);
	    }
    }else if(opt==7){
         if(isDsnSpecified){
            cacheLoader.setDsnName(dsnName);
            TableConf::config.setDsnName(dsnName);
        }
        rv = TableConf::config.tablesOnDsn();
        if(rv != OK){
            printf("Error(%d):There is no cache table present in the specified(%s)DS.\n\n",rv,dsnName);
            return 10;
        }
    }else if(opt==50 && tableDefinition){
         if(conditionval || fieldlistval || tableNameSpecified){
            printf("Not a valid commnad. Use \"cachetable -d <dsName>\" to cache all tables.\n");
            return 12;
        }
        rv = cacheLoader.cacheAllTablesFromDs(dsnName,tableDefinition, isDirect,username,password);
        if(rv!=OK)return 12;
    }
    return 0;
}

