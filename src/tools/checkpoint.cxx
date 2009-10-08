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
#include<CSql.h>
//#include<DatabaseManagerImpl.h>
//#include <Statement.h>
#include <SqlFactory.h>
#include <SqlConnection.h>
//#include <SqlNwConnection.h>
//#include <SqlNwStatement.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#define SQL_STMT_LEN 1024

//FILE *fp;

AbsSqlConnection *conn = NULL;
AbsSqlStatement *stmt = NULL;

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    char filename[512];
    filename [0] ='\0';
    int c = 0, opt=0;
    int connOpt = 0;
/*    while ((c = getopt(argc, argv, "u:p:")) != EOF) 
    {
        switch (c)
        {
            case 'u' : strcpy(username , argv[optind - 1]); break;
            case 'p' : strcpy(password , argv[optind - 1]); break;
            default: printf("Wrong args\n"); exit(1);
        }

    }*/
  

    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(I_USER, I_PASS);
    if (rv != OK) {
        delete conn;
        return 1;
    }
    SqlConnection *sqlcon = (SqlConnection *) conn; 
    rv = sqlcon->getExclusiveLock();
    if (rv != OK) {
        conn->disconnect();
        delete conn;
        return 2;
    }
    DatabaseManager *dbMgr = conn->getConnObject().getDatabaseManager();
    rv = dbMgr->checkPoint();
    if (rv != OK) {
        printError(rv, "checkpoint: failed");
        conn->disconnect();
        return 3;
    }
    conn->disconnect();
    delete conn;
    return 0;
}
