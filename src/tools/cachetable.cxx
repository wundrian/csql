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
#include <CacheTableLoader.h>

void printUsage()
{
   printf("Usage: cachetable [-U username] [-P passwd] -t tablename[-D] -c \"condition\" -f \"selected field names\" -p fieldname\n"
          "       [-R] [-s] [-r]\n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   printf("       tablename -> table name to be cached in csql from target db.\n");
   printf("       fieldname -> field name to be specified for the bidirectional caching on which trigger to be run .\n");
   printf("       R -> recover all cached tables from the target database.\n");
   printf("       s -> load only the records from target db. Assumes table is already created in csql\n");
   printf("       r -> reload the table. get the latest image of table from target db\n");
   printf("       u -> unload the table. if used with -s option, removes only records and preserves the schema\n");
   printf("       no option -> get table definition and records from target db and create in csql.\n");
   printf("       D -> Enable direct access option to target database\n");
   return;
}

int main(int argc, char **argv)
{
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
    bool conditionval = false;
    bool fieldlistval = false;
    bool tableDefinition = true;
    bool tableNameSpecified = false;
    bool fieldNameSpecified = false;
    while ((c = getopt(argc, argv, "U:P:t:f:c:p:RDsru?")) != EOF) 
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
            case 'p' : { strcpy(fieldname, argv[optind - 1]);
                         if(opt==2){fieldNameSpecified = true;break;}
                       }

            case 'D' : {
                         if(opt==2) {isDirect=true;break;}
                       }
            case 'c' : {strcpy(condition,argv[optind - 1]); conditionval = true; break; }// condition for selelcted records by :Jitendra
	    case 'f' : {strcpy(fieldlist,argv[optind - 1]);fieldlistval = true ;break; }
            case '?' : { opt = 10; break; } //print help 
            case 'R' : { opt = 3; break; } //recover all the tables
            case 's' : { tableDefinition=false; break; } //do not get the schema information from target db
            case 'r' : { opt = 4; break; } //reload the table
            case 'u' : { opt = 5; break; } //unload the table
            default: opt=10; 

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, "root");
        strcpy(password, "manager");
    }
    DbRetVal rv = OK;
    CacheTableLoader cacheLoader;
    cacheLoader.setConnParam(username, password);
    
    if(conditionval){
    cacheLoader.setCondition(condition);}// new one
    if(fieldlistval){
    cacheLoader.setFieldListVal(fieldlist);}
    if (opt==2) {
        cacheLoader.setTable(tablename);
        if(fieldNameSpecified){ cacheLoader.setFieldName(fieldname); }
        rv = CacheTableLoader::isTableCached(tablename);
        if(rv!=OK){
            rv = cacheLoader.load(tableDefinition);
            if(rv == OK){
               cacheLoader.addToCacheTableFile(isDirect);
            }else exit(2);
        } else
        {
            printf("Table is already cached, unload table by \" cachetable -t <tablename> -u\" and then try \n");
            exit(3);
        }
    }else if (opt==3) //recover
    {
        rv = cacheLoader.recoverAllCachedTables();
        if (rv != OK) exit (1);
    }else if (opt==4) //reload
    {
        if (!tableNameSpecified) 
        {
            printf("Table name is not specified. Check usage with ? \n");
            return 1;
        }
        cacheLoader.setTable(tablename);
        rv = cacheLoader.reload();
        if (rv != OK) exit (1);
    }else if (opt==5) //unload
    {
        if (!tableNameSpecified) 
        {
            printf("Table name is not specified. Check usage with ? option\n");
            return 1;
        }
        cacheLoader.setTable(tablename);
        rv = cacheLoader.unload(tableDefinition);
        if (rv != OK) exit (1);
        rv = cacheLoader.removeFromCacheTableFile();
        if (rv != OK) exit (2);

    }
    return 0;
}
