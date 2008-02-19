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
   printf("Usage: cachetable [-u username] [-p passwd] -t tablename [-R] [-s] [-r]\n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   printf("       tablename -> table name to be cached in csql from target db.\n");
   printf("       R -> recover all cached tables from the target database.\n");
   printf("       s -> load only the records from target db. Assumes table is already created in csql\n");
   printf("       r -> reload the table. get the latest image of table from target db\n");
   printf("       u -> unload the table. also removes all the records in csql\n");
   printf("       no option -> get table definition and records from target db and create in csql.\n");


   return;
}

void addToCacheTableFile(char *tablename)
{
    FILE *fp;
    printf("CACHE_TABLE_FILE is %s\n", Conf::config.getCacheTableFile());
    fp = fopen(Conf::config.getCacheTableFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CACHE_TABLE_FILE.\nTable will not be"
                                "recovered in case of crash");
	return;
    }
    fprintf(fp, "%s\n", tablename);
    fclose(fp);
}
int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char tablename[IDENTIFIER_LENGTH];
    bool tableDefinition = true;
    while ((c = getopt(argc, argv, "U:P:t:Rsru?")) != EOF) 
    {
        switch (c)
        {
            case 'U' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'P' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tablename, argv[optind - 1]); opt = 2; break; }
            case '?' : { opt = 10; break; } //print help 
            case 'R' : { opt = 3; break; } //recover all the tables
            case 's' : { tableDefinition=false; break; } //do not get the schema information from target db
            case 'r' : { opt = 4; break; } //recover all the tables
            case 'u' : { opt = 5; break; } //recover all the tables
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
    if (opt==2) {
        cacheLoader.setTable(tablename);
        rv = cacheLoader.load(tableDefinition);
        if (rv != OK) exit (1);
        rv = cacheLoader.addToCacheTableFile();
        if (rv != OK) exit (2);
    }else if (opt==3) //recover
    {
        rv = cacheLoader.recoverAllCachedTables();
        if (rv != OK) exit (1);
    }else if (opt==4) //reload
    {
        cacheLoader.setTable(tablename);
        rv = cacheLoader.reload();
        if (rv != OK) exit (1);
    }else if (opt==5) //unload
    {
        rv = cacheLoader.unload();
        if (rv != OK) exit (1);
    }
    return 0;
}
