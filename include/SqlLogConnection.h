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
#ifndef SQLLOGCONNECTION_H
#define SQLLOGCONNECTION_H
#include<CSql.h>
#include<AbsSqlConnection.h>
#include<SqlFactory.h>
#include<Util.h>
#include<Network.h>

/**
* @class SqlLogConnection
*
*/
class SqlLogConnection : public AbsSqlConnection
{
    Connection dummyConn;

    //stores all the sql log packets to be shipped to peers
    List logStore;

    //sync mode of the current transaction
    //will be modified by the SqlLogStatement based on the table
    DataSyncMode syncMode;

    //stores list of client objects in it for each peer
    //List NWClientList;
    NetworkTable nwTable;

    static UniqueID txnUID;

    public:
    SqlLogConnection(){innerConn = NULL; syncMode = TSYNC;}

    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }

    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel);

    DbRetVal addPacket(BasePacket *pkt);

    DbRetVal setSyncMode(DataSyncMode mode);
    DataSyncMode getSyncMode() { return syncMode; }
    void sendToAllPeers(NetworkPacketType type, char *packet, int length);
    void receiveFromAllPeers(NetworkPacketType type, char *packet, int length);
    void sendAndReceiveAllPeers(NetworkPacketType type, char *packet, int length);
    friend class SqlFactory;
};

#endif
