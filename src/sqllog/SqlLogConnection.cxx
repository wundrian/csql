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
#include <SqlLogConnection.h>
#include <CSql.h>
#include <Network.h>

UniqueID SqlLogConnection::txnUID;

DbRetVal SqlLogConnection::addPacket(BasePacket* pkt)
{
    logStore.append(pkt);
    return OK;
}
DbRetVal SqlLogConnection::setSyncMode(DataSyncMode mode)
{
    if (syncMode < mode) syncMode = mode;
    //printf("Current syncMode is  %d\n", syncMode);
    return OK;
}
DbRetVal SqlLogConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    //printf("LOG: connect\n");
    if (innerConn) rv = innerConn->connect(user,pass);
    if (rv != OK) return rv;
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    nwTable.initialize();
    nwTable.connect();
    return rv;
    
}
DbRetVal SqlLogConnection::disconnect()
{
    DbRetVal rv = OK;
    //printf("LOG: disconnect\n");
    if (innerConn) rv =innerConn->disconnect();
    if (rv != OK) return rv;
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    nwTable.disconnect();
    nwTable.destroy();
    return rv;
}
DbRetVal SqlLogConnection::beginTrans(IsolationLevel isoLevel)
{
    DbRetVal rv = OK;
    //printf("LOG: beginTrans\n");
    if (innerConn) rv =  innerConn->beginTrans(isoLevel);
    if (rv != OK) return rv;
    //reset the mode to the highest mode
    //SqlLogStatement will reduce the mode based on the tables it operate on
    //all the tables modified in this txn should be TSYNC for txn to be in TSYNC
    //if any one table is ASYNC, then it gets further downgraded to ASYNC
    syncMode = TSYNC;

    return rv;
}
DbRetVal SqlLogConnection::commit()
{
    DbRetVal rv = OK;
    //printf("LOG: commit %d\n", syncMode);
    if (innerConn) rv = innerConn->commit();
    if (rv != OK) return rv;
    if (logStore.size() == 0) return rv;
    //create COMMIT packet
    PacketCommit *pkt = new PacketCommit();
    int tid = txnUID.getID();
    pkt->setExecPackets(tid, logStore);
    pkt->marshall();
    //printf("After commit marshall tid %d\n", tid);
    int *p = (int*) pkt->getMarshalledBuffer();
    //printf("COMMIT MARSHALL %d %d %d %d size %d",*p , *(p+1), *(p+2), *(p+3), pkt->getBufferSize());
    NetworkClient *nwClient;
    ListIterator iter = nwTable.getIterator();
    while (iter.hasElement() ) {
       nwClient = (NetworkClient*) iter.nextElement();
       //for all three modes, need to sent the sql logs
       rv = nwClient->send(NW_PKT_COMMIT, pkt->getMarshalledBuffer(), 
                                          pkt->getBufferSize());    
       if (rv !=OK) 
       {
          printError(ErrOS, "Unable to send SQL Logs to peer site\n");
          return ErrOS;
       }
       if (syncMode == TSYNC)
       {
          rv = nwClient->receive();    
          if (rv !=OK) 
          {
            printError(ErrOS, "Could not get acknowledgement from peer site\n");
            return ErrOS;
          }
           //TODO::remove all sql logs nodes and the list which contains ptr to it
       }else //(syncMode == ASYNC)
       {
           //TODO:: add head of the list of sql logs (for one txn) to 
           //global log ship list
       }
    }
    ListIterator logStoreIter = logStore.getIterator();
    PacketExecute *execPkt = NULL;
    while (logStoreIter.hasElement())
    {
        execPkt = (PacketExecute*)logStoreIter.nextElement();
        delete execPkt;
    }
    logStore.reset();
    return rv;
}
DbRetVal SqlLogConnection::rollback()
{
    DbRetVal rv = OK;
    //printf("LOG: rollback \n");
    if (innerConn) rv =  innerConn->rollback();
    if (rv != OK) return rv;
    //TODO::remove all sql log nodes and the list which contains ptr to it
    return rv;
}
void SqlLogConnection::sendToAllPeers(NetworkPacketType type, char *packet, int length)
{
    ListIterator iter = nwTable.getIterator();
    NetworkClient* nwClient = NULL;
    DbRetVal rv = OK;
    while(iter.hasElement())
    {
        nwClient = (NetworkClient*) iter.nextElement();
        if (!nwClient->isConnected()) {
            //TODO:: put this packet in resend buffer, so that it will sent later by another thread
            continue;
        }
        rv = nwClient->send(type, packet, length);
        if (rv != OK) 
        {
            printf("Unable to send pkt to peer with nwid %d\n", nwClient->getNetworkID());
            //TODO:: put this packet in resend buffer, so that it will sent later by another thread
            nwClient->setConnectFlag(false);
            continue;
        }
    }
}
void SqlLogConnection::receiveFromAllPeers(NetworkPacketType type, char *pkt, int length)
{
    ListIterator iter = nwTable.getIterator();
    NetworkClient* nwClient = NULL;
    DbRetVal rv = OK;
    while(iter.hasElement())
    {
        nwClient = (NetworkClient*) iter.nextElement();
        if (!nwClient->isConnected()) {
            continue;
        }
        rv = nwClient->receive();
        if (rv != OK) 
        {
            printf("Unable to receive ack pkt from peer with nwid %d\n", nwClient->getNetworkID());
            //TODO:: put this packet in resend buffer, so that it will sent later by another thread
            nwClient->setConnectFlag(false);
            continue;
        }
    }
}
void SqlLogConnection::sendAndReceiveAllPeers(NetworkPacketType type, char *packet, int length)
{
    ListIterator iter = nwTable.getIterator();
    NetworkClient* nwClient = NULL;
    DbRetVal rv = OK;
    //TODO::currently it sends and receives ack from each peer one after the
    //another. instead send all at once and receive all ot once. this wil
    //be faster as the peer site gets time to process the request
    while(iter.hasElement())
    {
        nwClient = (NetworkClient*) iter.nextElement();
        if (!nwClient->isConnected()) {
            continue;
        }
        rv = nwClient->send(type, packet, length);
        if (rv != OK) 
        {
            printf("Unable to send pkt to peer with nwid %d\n", nwClient->getNetworkID());
            //TODO:: put this packet in resend buffer, so that it will sent later by another thread
            nwClient->setConnectFlag(false);
            continue;
        }
        rv = nwClient->receive();
        if (rv != OK)
        {
            printf("Unable to receive ack pkt from peer with nwid %d\n", nwClient->getNetworkID());
            //TODO:: put this packet in resend buffer, so that it will sent later by another thread
            nwClient->setConnectFlag(false);
            continue;
        }
    }
}
