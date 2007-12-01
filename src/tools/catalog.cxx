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
#include <DatabaseManagerImpl.h>
#include <Database.h>

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "u:p:lid?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : { strcpy(username , argv[optind - 1]); break; }
            case 'p' : { strcpy(password , argv[optind - 1]); break; }
            case 'l' : { opt = 2; break; } //list all the table with field info
            case 'i' : { opt = 3; break;  }//reinitialize the catalog table
            case 'd' : { opt = 4; break;  }//print db usage statistics
            case '?' : { opt = 10; break; } //print help 
            default: opt=1; //list all the tables

        }
    }//while options
    if (opt == 10) {
        printf("Usage: catalog [-u username] [-p passwd] [-l] [-i] [-d]\n");
        printf("       l -> list all table with field information\n");
        printf("       i -> reinitialize all the catalog tables\n");
        printf("       d -> print db usage statistics\n");

    }

    printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, "praba");
        strcpy(password, "manager");
    }
    
    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return 1;
    DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    List tableList = dbMgr->getAllTableNames();
    ListIterator iter = tableList.getIterator();
    Identifier *elem = NULL;
    if (opt == 1) {
        printf("List of Tables:\n");
        printf("---------------\n");
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            printf("%s\n", elem->name);
        }
        printf("---------------\n");
    }
    else if (opt ==2) 
    {
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            printf("Table Definition of %s :\n", elem->name);
            printf("------------------------------------------------------\n");
            Table *table = dbMgr->openTable(elem->name);
	    FieldInfo *info = new FieldInfo();
            List fNameList = table->getFieldNameList();
            ListIterator fNameIter = fNameList.getIterator();
            while (fNameIter.hasElement()) {
                 elem = (Identifier*) fNameIter.nextElement();
                 table->getFieldInfo((const char*)elem->name, info);
                 printf("%s %d %d %d %d %d %s\n",elem->name, 
                     info->type, info->length, info->isPrimary, info->isNull,
                     info->isDefault, info->defaultValueBuf);
            }
            delete info;
            dbMgr->closeTable(table);
        }
    }else if (opt == 3)
    {
        while (iter.hasElement())
        {
            elem = (Identifier*) iter.nextElement();
            printf("Dropping Table %s\n", elem->name);
            dbMgr->dropTable(elem->name);
        }
    }else if (opt == 4)
    {
        printf("Database Usage Statistics\n");
        printf("===========================\n");
        Database *db = dbMgr->sysDb();
        db->printStatistics();
        printf("===========================\n");
        db = dbMgr->db();
        db->printStatistics();
    }
    tableList.reset();
    conn.close();
    return 0;
}