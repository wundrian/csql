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
#include <Network.h>

void printUsage()
{
   printf("Usage: repltable [-U username] [-P passwd] -t tablename \n"
          "       [-m TSYNC|ASYNC>][-u] [-r] \n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   printf("       tablename -> table name to be replicated in csql with peers.\n");
   printf("       u -> unreplicate the table\n");
   printf("       r -> replicate and load all the records from peer site\n");
   printf("       m -> replication mode for the table\n");
   printf("         -> Modes could be one of TSYNC|ASYNC\n");
   printf("       no option -> replicates with default mode ASYNC\n");
   printf("       Note:Table should not have any records for this command to succeed\n");
   return;
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char tablename[IDENTIFIER_LENGTH];
    char syncModeStr[IDENTIFIER_LENGTH];
    bool tableNameSpecified = false;
    while ((c = getopt(argc, argv, "U:P:t:l:m:u?")) != EOF) 
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
            case '?' : { opt = 10; break; } //print help 
            case 'r' : { opt = 4; break; } //replicate the table
            case 'u' : { opt = 5; break; } //unreplicate the table
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
    if (opt==2) {
    }
    return 0;
}
