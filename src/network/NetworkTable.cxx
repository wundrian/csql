/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <CSql.h>
#include <Network.h>

DbRetVal NetworkTable::initialize()
{
    DbRetVal rv = OK;
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    rv = readNetworkConfig();
    return rv;
    
}
NetworkTable::~NetworkTable()
{
    //TODO::
}
DbRetVal NetworkTable::readNetworkConfig()
{
    FILE *fp;
    int nwid;
    char hostname[IDENTIFIER_LENGTH];
    int port;
    fp = fopen(Conf::config.getReplConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename for NETWORK_CONFIG_FILE.\n");
        return ErrSysInit;
    }
    int count = 0;
    while(!feof(fp)) {
       if (count >=1) 
       {
           fclose(fp);
           printError(ErrNotYet, "Only 2 hosts are allowed in this version"); 
           return ErrNotYet;
       }
       printf("Count is %d\n", count);
       fscanf(fp, "%d:%d:%s\n", &nwid, &port, hostname);
       printf( "%d:%d:%s\n", nwid, port, hostname);
       NetworkClient* nClient;
       if (nwid == Conf::config.getNetworkID()) continue;

       nClient = NetworkFactory::createClient(TCP);

       printf("nwid %d getCacheNetworkID %d\n", nwid,  Conf::config.getCacheNetworkID());
       if (nwid == Conf::config.getCacheNetworkID()) nClient->setCacheClient();
       nClient->setHost(hostname, port, nwid);
       nwClient = nClient;
       count++;
    }
    fclose(fp);
    return OK;
}


//connect to peer hosts 
DbRetVal  NetworkTable::connect()
{
    DbRetVal rv = nwClient->connect();
    if (rv != OK) {
        printError(ErrOS, "Unable to connect to peer %d\n", nwClient->getNetworkID());
        nwClient->setConnectFlag(false);
    }
    return rv;
}
DbRetVal NetworkTable::connectIfNotConnected()
{
   DbRetVal rv = OK;
   if (!nwClient->isConnected()) rv = nwClient->connect(); else rv =ErrAlready;
   printf("PRABA:connectIfNotConnected  rv is %d\n", rv);
   return rv;
}
//disconnect from all hosts in the table
DbRetVal NetworkTable::disconnect()
{
    if (nwClient->isConnected()) {
        nwClient->disconnect();
    }
    return OK;
}
