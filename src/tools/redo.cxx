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
#include <Statement.h>
#include <SqlFactory.h>
#include <SqlStatement.h>
#include <Recover.h>

AbsSqlConnection *conn;
bool list = false;
bool interactive=false;
char fileName[MAX_FILE_LEN];

int main(int argc, char **argv)
{
    strcpy(fileName, "");
    int c = 0, opt=0; 
    while ((c = getopt(argc, argv, "f:ail?")) != EOF) {
        switch (c) {
            case '?' : { opt = 1; break; } //print help 
            case 'a' : { opt = 2; break; } 
            case 'i' : { interactive = true; break; }
            case 'l' : { list = true; break; }
            case 'f' : {strcpy(fileName , argv[optind - 1]); break;}
            default: printf("Wrong args\n"); exit(1);

        }
    }//while options
    if (2 !=opt) {
       printf("This is an internal csql command with i and f <filename> options.");
       exit(1);
    }
    char *verbose =  os::getenv("CSQL_INTERACTIVE");
    if (verbose !=NULL && strcmp(verbose, "true") == 0)
    {
        printf("VERBOSE ON %s\n", verbose);
        interactive=true;
    }
    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(I_USER, I_PASS);
    if (rv != OK) {
        printError(ErrNoConnection, "REDO: could not connect to DB.");
        delete conn;
        return 2;
    }
 
    if (strcmp(fileName, "") ==0) {
        sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    }
    SqlConnection *sCon = (SqlConnection*) conn;
    if(!list) rv = sCon->getExclusiveLock();
    //during connection close, this exclusive lock will be automatically released
    if (rv != OK) {
        conn->disconnect();
        delete conn;
        return 4;
    }
    Recovery recovery;
    int retVal = recovery.applyRedoLogs(fileName, conn, list, interactive);
    conn->disconnect();
    delete conn;
    return retVal;
}
