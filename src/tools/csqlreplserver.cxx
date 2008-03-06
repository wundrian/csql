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
#include <AbsSqlConnection.h>
#include <AbsSqlStatement.h>
#include <SqlConnection.h>
#include <SqlStatement.h>
#include <SqlFactory.h>
#include <CSql.h>
#include <Network.h>
#include <SqlLogStatement.h> //for BindSqlField
#include <SqlNetworkHandler.h>

int srvStop =0;
static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    srvStop = 1;
}

void printUsage()
{
   printf("Usage: csqlreplserver \n");
   printf("Description: Start the csql replication server.\n");
   return;
}
int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "?")) != EOF) 
    {
        switch (c)
        {
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 

        }
    }//while options

    if (opt == 10) {
        printUsage();
        return 0;
    }

    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);

    bool end = false;
    SqlNetworkHandler::type = CSql;
    SqlNetworkHandler::conn = SqlFactory::createConnection(CSql);
    DbRetVal rv = SqlNetworkHandler::conn->connect("root", "manager");
    if (rv != OK) return 1;
    if (!Conf::config.useReplication())
    {
        printf("Replication is set to OFF in csql.conf file\n");
        SqlNetworkHandler::conn->disconnect();
        return 1;
    } 
     
    
    FILE *fp = NULL;
    int nwid =0;
    char hostname[IDENTIFIER_LENGTH];
    char nwmode ='a';
    int port=0;
    fp = fopen(Conf::config.getReplConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename for REPL_CONFIG_FILE.\n");
        SqlNetworkHandler::conn->disconnect();
        return 1;
    }
    bool found =false;
    while(!feof(fp)) {
       fscanf(fp, "%d:%c:%d:%s\n", &nwid, &nwmode, &port, hostname);
       printf( "%d:%c:%d:%s\n", nwid, nwmode, port, hostname);
       if (nwid == Conf::config.getNetworkID()) { found = true; break;}
    }
    fclose(fp);
    if (!found)
    {
        printf("Info not found in REPL_CONFIG_FILE for nwid %d\n", 
               Conf::config.getNetworkID());
        SqlNetworkHandler::conn->disconnect();
        return 1;
    }
    NetworkServer *nwServer;
    if (nwmode == 'U')
    {
        nwServer = new UDPServer();
        
    }else if (nwmode =='T')
    {
        nwServer = new TCPServer();
    }
    
    nwServer->setServerPort(port);
    rv = nwServer->start();
    if (rv != OK) {
        printf("Unable to start the server\n");
        return 1;
    }
    printf("Replication server started\n");
    fd_set fdset;
    int ret = 0;
    struct timeval timeout, tval;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    while(!srvStop)
    {
        FD_ZERO(&fdset);
        FD_SET(nwServer->getSocket(), &fdset);
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        ret = os::select(nwServer->getSocket()+1, &fdset, 0, 0, &tval);
        if (ret > 0) {
            nwServer->handleClient();
        }
        printf("Server Waiting for clients\n");
    }
    printf("Replication Server Exiting\n");
    nwServer->stop();
    SqlNetworkHandler::conn->disconnect();
    delete SqlNetworkHandler::conn;
    return 0;
}
