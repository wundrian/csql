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
    nwTable.reset();
    rv = readNetworkConfig();
    return rv;
    
}
NetworkTable::~NetworkTable()
{
    //TODO::
    //traverse the nwTable and disconnect is connected
    //remove all elements from the nwTable
}
DbRetVal NetworkTable::readNetworkConfig()
{
    FILE *fp;
    int nwid;
    char hostname[IDENTIFIER_LENGTH];
    char nwmode;
    int port;
    fp = fopen(Conf::config.getReplConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename for REPL_CONFIG_FILE.\n");
        return ErrSysInit;
    }
    while(!feof(fp)) {
       fscanf(fp, "%d:%c:%d:%s\n", &nwid, &nwmode, &port, hostname);
       printf( "%d:%c:%d:%s\n", nwid, nwmode, port, hostname);
       NetworkClient* nwClient;
       if (nwid == Conf::config.getNetworkID()) continue;
       if (nwmode == 'U' ) 
          nwClient = NetworkFactory::createClient(UDP);
       else if (nwmode == 'T' ) 
          nwClient = NetworkFactory::createClient(TCP);
       else {
          fclose(fp);
          printError(ErrSysInit, "Mode %s not supported.\n", nwmode);
          return ErrSysInit;
       }
       nwClient->setHost(hostname, port, nwid);
       nwTable.append(nwClient);
    }
    fclose(fp);
    return OK;
}


//connect to all hosts in the table
void NetworkTable::connect()
{
    ListIterator iter = getIterator();
    NetworkClient* nwClient;
    DbRetVal rv = OK;
    while(iter.hasElement())
    {
        nwClient = (NetworkClient*) iter.nextElement();
        rv = nwClient->connect();
        if (rv != OK) {
            printf("Unable to connect to peer %d\n", nwClient->getNetworkID());
            nwClient->setConnectFlag(false);
            continue;
        }
    }
}

//disconnect from all hosts in the table
void NetworkTable::disconnect()
{
    ListIterator iter = getIterator();
    NetworkClient* nwClient;
    while(iter.hasElement())
    {
        nwClient = (NetworkClient*) iter.nextElement();
        if (nwClient->isConnected()) {
            nwClient->disconnect();
        }
    }
}
