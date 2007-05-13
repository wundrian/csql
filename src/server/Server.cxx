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
#include<CSql.h>
#include<SessionImpl.h>
#include<Debug.h>

int srvStop =0;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
}
//TODO::user process registration and deregistration
int main()
{
    SessionImpl session;
    DbRetVal rv = session.readConfigFile();
    if (rv != OK)
    {
        printf("Unable to read the configuration file \n");
        return 1;
    }
    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);
    rv = logger.startLogger(config.getLogFile(), true);
    if (rv != OK)
    {
        printf("Unable to start the logger\n");
        return 2;
    }

    logFinest(logger, "Server Started");
    int ret  = session.initSystemDatabase();
    if (0  != ret)
    {
        printf(" System Database Initialization failed\n");
        return 3;
    }
    printf("System Database initialized\n");


    printf("Database server started\n");
    bool end = false;

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    while(!srvStop)
    {
        os::select(0, 0, 0, 0, &timeout);
    }
    printf("Server Exiting\n");
    session.destroySystemDatabase();
    logFinest(logger, "Server Ended");
    return 0;
}
