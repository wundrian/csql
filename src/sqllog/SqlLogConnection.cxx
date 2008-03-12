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
List SqlLogConnection::cacheList;

DbRetVal SqlLogConnection::addPacket(BasePacket* pkt)
{
    logStore.append(pkt);
    return OK;
}
DbRetVal SqlLogConnection::addPreparePacket(PacketPrepare* pkt)
{
    prepareStore.append(pkt);
    return OK;
}

DbRetVal SqlLogConnection::removePreparePacket(int stmtid)
{
    ListIterator iter = prepareStore.getIterator();
    PacketPrepare *pkt = NULL, *dpkt=NULL;
    while (iter.hasElement())
    {
        pkt = (PacketPrepare*)iter.nextElement();
        if (pkt->stmtID == stmtid) dpkt = pkt;
    }
    if (dpkt == NULL)
    {
        printError(ErrNotFound, "Prepare packet not found in list for %d\n", stmtid);
        return ErrNotFound;
    }
    delete dpkt;
    prepareStore.remove(dpkt);
    return OK;
}

DbRetVal SqlLogConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    //printf("LOG: connect\n");
    if (innerConn) rv = innerConn->connect(user,pass);
    if (rv != OK) return rv;
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    //rv = nwTable.initialize();
    //if (rv !=OK) { innerConn->disconnect(); return rv; }
    //nwTable.connect();

    //populate cacheList if not populated by another thread in same process
    //TODO::cacheList requires mutex guard
    if (0 == cacheList.size()) rv = populateCachedTableList(); 
    return rv;
    
}
DbRetVal SqlLogConnection::disconnect()
{
    DbRetVal rv = OK;
    //printf("LOG: disconnect\n");
    if (innerConn) rv =innerConn->disconnect();
    if (rv != OK) return rv;
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    //nwTable.disconnect();
    //nwTable.destroy();
    return rv;
}
DbRetVal SqlLogConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode mode)
{
    DbRetVal rv = OK;
    if (innerConn) rv =  innerConn->beginTrans(isoLevel);
    if (rv != OK) return rv;
    /*rv  = nwTable.connectIfNotConnected(); 
    if (rv == OK) {
        //send all prepare packets to client
        ListIterator iter = prepareStore.getIterator();
        PacketPrepare *pkt;
        while (iter.hasElement())
        {
            pkt = (PacketPrepare*) iter.nextElement();
            rv = sendAndReceive(NW_PKT_PREPARE, pkt->getMarshalledBuffer(),
                                           pkt->getBufferSize());
            if (rv !=OK) return rv;
            delete pkt;
        }
        prepareStore.reset();
    }*/
    syncMode = mode;
    return OK;
}
DbRetVal SqlLogConnection::commit()
{
    DbRetVal rv = OK;
    //printf("LOG: commit %d\n", syncMode);
        if (innerConn) rv =  innerConn->commit();
        return rv; 

    //TODO::TSYNC MODE
    if (logStore.size() == 0) 
    { 
        //This means no execution for any non select statements in 
        //this transaction
        //rollback so that subsequent beginTrans will not report that
        //transaction is already started
        if (innerConn) rv =  innerConn->rollback();
        return rv; 
    }
    //create COMMIT packet
    PacketCommit *pkt = new PacketCommit();
    int tid = txnUID.getID();
    pkt->setExecPackets(tid, logStore);
    pkt->marshall();
    int *p = (int*) pkt->getMarshalledBuffer();
    NetworkClient *nwClient= nwTable.getNetworkClient();
    //for all three modes, need to send the sql logs
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
          return ErrPeerExecFailed;
        }
        //TODO::remove all sql logs nodes and the list which contains ptr to it
    }else //(syncMode == ASYNC)
    {
         //TODO:: add head of the list of sql logs (for one txn) to 
         //global log ship list
    }
    
    ListIterator logStoreIter = logStore.getIterator();
    PacketExecute *execPkt = NULL;
    while (logStoreIter.hasElement())
    {
        execPkt = (PacketExecute*)logStoreIter.nextElement();
        delete execPkt;
    }
    logStore.reset();
    if (innerConn) rv = innerConn->commit();
    return rv;
}
DbRetVal SqlLogConnection::rollback()
{
    DbRetVal rv = OK;
    //printf("LOG: rollback \n");
    if (innerConn) rv =  innerConn->rollback();
    if (rv != OK) return rv;
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
DbRetVal SqlLogConnection::populateCachedTableList()
{
    FILE *fp = NULL;
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cache.table file does not exist");
        return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    int cmode;
    CachedTable *node;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s\n", &cmode, tablename);
        node = new CachedTable();
        strcpy(node->tableName, tablename);
        cacheList.append(node);
    }
    fclose(fp);
    return OK;
}
bool SqlLogConnection::isTableCached(char *tblName)
{
    if (NULL == tblName)
    {
        printError(ErrBadArg, "tblName passed is NULL\n");
        return ErrBadArg;
    }
    ListIterator iter = cacheList.getIterator();
    CachedTable *node;
    while (iter.hasElement()) {
        node = (CachedTable*)iter.nextElement();
        if (strcmp(node->tableName, tblName) == 0)
        {
           return true;
        }
    }
    return false;
}


DbRetVal SqlLogConnection::sendAndReceive(NetworkPacketType type, char *packet, int length)
{
    NetworkClient* nwClient = nwTable.getNetworkClient();
    DbRetVal rv = OK, retRV=OK;
    //printf("isCacheClient %d\n", nwClient->isCacheClient());
    if (!nwClient->isConnected()) {
        if (nwClient->isCacheClient()) return ErrOS; 
        //TODO::put this packet in send buffer.
        return OK;
    }
    rv = nwClient->send(type, packet, length);
    if (rv != OK) 
    {
       printf("Unable to send pkt to peer with nwid %d\n", nwClient->getNetworkID());
       //TODO:: put this packet in resend buffer, so that it will sent later by another thread for repl mode
        nwClient->setConnectFlag(false);
        if (nwClient->isCacheClient()) return ErrOS; else return OK;
    }
    rv = nwClient->receive();
    if (rv != OK)
    {
        printf("Unable to receive ack pkt from peer with nwid %d\n", nwClient->getNetworkID());
        nwClient->setConnectFlag(false);
        if (nwClient->isCacheClient()) return ErrOS;
        //TODO:: put this packet to resend buffer so that it can be sent later
        //and call continue;
    }
    return OK;
}
