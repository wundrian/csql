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
#ifndef SQLNWCONNECTION_H
#define SQLNWCONNECTION_H
#include<CSql.h>
#include<Network.h>
#include<AbsSqlConnection.h>
#include<SqlFactory.h>

/**
* @class SqlNwConnection
*
*/
class SqlNwConnection : public AbsSqlConnection
{
    Connection dummyConn;
    bool isConnOpen;
    char hostname[128];
    int port;
    char sqlApiImplType;
    public:
    NetworkClient *nwClient;
    IsolationLevel prevIsoLevel;
    SqlNwConnection(SqlApiImplType tp) {
        nwClient = NULL; 
        innerConn = NULL; 
        isConnOpen = false; 
        sqlApiImplType = tp; 
    }

    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }
    NetworkClient* getNetworkClient() { return nwClient; }
    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();
    void setHost(char *host, int portNo)
    {
        port=portNo;
        strcpy(hostname,host);
    }

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel, TransSyncMode mode = OSYNC);

    DbRetVal send(NetworkPacketType type, char *buffer, size_t len)
    { return  nwClient->send(type, buffer, len); }
    DbRetVal send(NetworkPacketType type)
    { return  nwClient->send(type); }
    DbRetVal receive() { return nwClient->receive(); }
    void setIsConnectedFlag(bool fl) { nwClient->setIsConnectedFlag(fl); }
    bool isConOpen() { return isConnOpen; }
    void setConnClosed(bool status) { isConnOpen = status; }
    void * getResponsePacket() { return nwClient->getResponsePacket(); }
    ~SqlNwConnection() { if (isConnOpen) disconnect(); }
    friend class SqlFactory;
};

#endif
