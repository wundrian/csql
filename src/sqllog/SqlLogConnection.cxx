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
#include <os.h>
#include <SqlLogConnection.h>
#include <SqlLogStatement.h>
#include <CSql.h>
#include <Network.h>

GlobalUniqueID SqlLogConnection::txnUID;
List SqlLogConnection::cacheList;

DbRetVal SqlLogConnection::addPacket(BasePacket* pkt)
{
    logStore.append(pkt);
    return OK;
}
DbRetVal SqlLogConnection::addPreparePacket(PacketPrepare* pkt)
{
    curPrepareStore.append(pkt);
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
    if (dpkt == NULL) return OK;
    //TEMP:mask below error for now
    if (dpkt == NULL)
    {
        printError(ErrNotFound, "Prepare packet not found in list for %d\n", stmtid);
        return ErrNotFound;
    }
    delete dpkt;
    prepareStore.remove(dpkt);
    return OK;
}

DbRetVal SqlLogConnection::connect (char *user, char *pass)
{
    DbRetVal rv = OK;
    //printf("LOG: connect\n");
    if (innerConn) rv = innerConn->connect(user,pass);
    if (rv != OK) return rv;
    if (!Conf::config.useDurability()) return OK;

    //populate cacheList if not populated by another thread in same process
    //TODO::cacheList requires mutex guard
    if (0 == cacheList.size()) rv = populateCachedTableList(); 
    rv = SqlLogStatement::stmtUID.open();
    rv = SqlLogConnection::txnUID.open();
    return rv;
    
}
DbRetVal SqlLogConnection::disconnect()
{
    DbRetVal rv = OK;
    //printf("LOG: disconnect\n");
    if (innerConn) rv =innerConn->disconnect();
    if (rv != OK) return rv;
    if (!Conf::config.useDurability()) return OK;
    SqlLogStatement::stmtUID.close();
    return rv;
}
DbRetVal SqlLogConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode mode)
{
    DbRetVal rv = OK;
    if (innerConn) rv =  innerConn->beginTrans(isoLevel);
    if (rv != OK) return rv;
    syncMode = mode;
    txnID = SqlLogConnection::txnUID.getID(TXN_ID);
    return OK;
}
DbRetVal SqlLogConnection::commit()
{
    DbRetVal rv = OK;
    //printf("LOG: commit %d\n", syncMode);
    //if (innerConn) rv =  innerConn->commit();
    if (innerConn) rv = innerConn->commit();
    if (!Conf::config.useDurability()) return OK;
    
    if (execLogStore.size() == 0) { 
        //This means no execution for any non select statements in 
        //this transaction
        //rollback so that subsequent beginTrans will not report that
        //transaction is already started
        if (innerConn) {
            rv =  innerConn->rollback(); 
            //if (rv != OK) return rv;
            //rv = innerConn->beginTrans(READ_COMMITTED, syncMode);
        }
        return rv; 
    }

    //TODO::put the packet in global log store
    /*
    PacketCommit *pkt = new PacketCommit();
    int tid = txnUID.getID();
    pkt->setExecPackets(tid, logStore);
    pkt->marshall();
    int *p = (int*) pkt->getMarshalledBuffer();
    NetworkClient *nwClient= nwTable.getNetworkClient();
    if (syncMode == ASYNC) {
        rv = nwClient->send(NW_PKT_COMMIT, pkt->getMarshalledBuffer(), 
                                          pkt->getBufferSize());    
        if (rv !=OK) 
        {
            printError(ErrOS, "Unable to send SQL Logs to peer site\n");
            return ErrOS;
        }
        rv = nwClient->receive();    
        if (rv !=OK) 
        {
          printError(ErrOS, "Could not get acknowledgement from peer site\n");
          return ErrPeerExecFailed;
        }
        //TODO::remove all sql logs nodes and the list which contains ptr to it
        */
    int txnId = getTxnID(); 
    // len to be sent should also contain txnId 
    int len = 2 * sizeof(int) + os::align(getExecLogStoreSize());
    printDebug(DM_SqlLog, "commit: size of logstore: %d", len);
    int bufferSize = sizeof(long) + len;
    printDebug(DM_SqlLog, "commit: size of buffer: %d", bufferSize);
    void *buffer = malloc(bufferSize);
    printDebug(DM_SqlLog, "commit: buffer address: %x", buffer);
    char *ptr = (char *)buffer + sizeof(long); // long type is for msgtype
    char *data = ptr;
    printDebug(DM_SqlLog, "commit: data address: %x", data);
    *(int *) ptr = len; 
    ptr += sizeof(int);
    *(int *) ptr = txnId;
    ptr += sizeof(int);
    ListIterator logStoreIter = execLogStore.getIterator();
    ExecLogInfo *elInfo = NULL;
    while (logStoreIter.hasElement()) {
        elInfo = (ExecLogInfo *)logStoreIter.nextElement();
        printDebug(DM_SqlLog, "commit: elem from logstore:: %x", elInfo);
        *(int *) ptr = elInfo->stmtId;
        printDebug(DM_SqlLog, "commit: stmtId to marshall: %d", elInfo->stmtId);
        ptr += sizeof(int);
        *(int *) ptr = (int) elInfo->type;
        printDebug(DM_SqlLog, "commit: ExType to marshall: %d", elInfo->type);
        //printf("PRABA::type is %d\n" , *(int *) ptr);
        ptr += sizeof(int);
        if (elInfo->type == SETPARAM) {
            *(int *) ptr = elInfo->pos;
            printDebug(DM_SqlLog, "commit: PrmPos to marshall: %d", elInfo->pos);
            ptr += sizeof(int);
            *(int *) ptr = (int) elInfo->dataType;
            printDebug(DM_SqlLog, "commit: DtType to marshall: %d", elInfo->dataType);
            ptr += sizeof(int);
            *(int *) ptr = elInfo->len;
            printDebug(DM_SqlLog, "commit: length to marshall: %d", elInfo->len);
            ptr += sizeof(int);
            memcpy(ptr, &elInfo->value, elInfo->len);
            ptr += elInfo->len;
        }
    }
    commitLogs(len, data);
    execLogStore.reset();
    execLogStoreSize =0;
    //if (innerConn) rv = innerConn->commit();
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

    execLogStore.reset();
    execLogStoreSize =0;
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
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    int cmode;
    CachedTable *node;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s %s %s %s\n", &cmode, tablename,fieldname,condition,field);
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
