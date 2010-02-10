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
#include<SqlFactory.h>
#include<Util.h>
#include<Network.h>

/**
* @class SqlLogConnection
*
*/

typedef struct my_msgbuffer {
    long mtype;
    char data[1];
} Message;

class AbsSqlLogSend
{
    public:
    virtual DbRetVal prepare(int tId, int sId, int len, char *st, char *tn)=0;
    virtual DbRetVal commit(int len, void *data)=0;
    virtual DbRetVal free(int txnId, int stmtId)=0;
};

class MsgQueueSend : public AbsSqlLogSend
{
    int msgQId;
    public:
    MsgQueueSend() { msgQId = os::msgget(Conf::config.getMsgKey(), 0666); }
    DbRetVal prepare(int tId, int sId, int len, char *stmt, char *tn);
    DbRetVal commit(int len, void *data);
    DbRetVal free(int txnId, int stmtId);
};

class FileSend : public AbsSqlLogSend
{
    int fdRedoLog;
    public:
    FileSend();
    ~FileSend();
    DbRetVal openRedoFile();
    DbRetVal prepare(int txnId, int stmtId, int len, char *stmt, char*tn);
    DbRetVal commit(int len, void *data);
    DbRetVal free(int txnId, int stmtId);
};

class OfflineLog : public AbsSqlLogSend
{
    int fdOfflineLog;
    void *metadata;
    int fileSize;
    DbRetVal createMetadataFile();
    void *openMetadataFile();
    public:
    OfflineLog();
    ~OfflineLog();
    DbRetVal openOfflineLogFile();
    DbRetVal prepare(int txnId, int stmtId, int len, char *stmt, char*tn);
    DbRetVal commit(int len, void *data);
    DbRetVal free(int txnId, int stmtId);
};



enum ExecType
{
    EXECONLY = 0,
    SETPARAM
};

class ExecLogInfo
{
    public:
    ExecLogInfo() : pos(0), len(0) {}
    int stmtId;
    ExecType type;
    int pos;
    DataType dataType;
    int len;
    int value; //Extendible value as per parameter type size
};

class SqlLogConnection : public AbsSqlConnection
{
    Connection dummyConn;

    //stores all the sql log packets to be shipped to peers
    List logStore;
    
    List execLogStore;
    int execLogStoreSize;

    //stores all the prepare log packets to be shipped to peers
    //as soon as connection is reestablished to cache server
    List prepareStore;

    //stores all the prepare log packets to be shipped between two
    //consecutive commits. Commit() call sends first all the stmts
    //prepared during the course and then sends the exec pkts
    List curPrepareStore;

    //sync mode of the current transaction
    TransSyncMode syncMode;

    //stores client objects in it for peer
    NetworkTable nwTable;
    AbsSqlLogSend *msgQSend;
    AbsSqlLogSend *fileSend;
    AbsSqlLogSend *offlineLog;

    GlobalUniqueID txnUID;
    static List cacheList;
    int txnID;
    DbRetVal populateCachedTableList();
    public:
    SqlLogConnection() {
        innerConn = NULL; syncMode = ASYNC; 
        if (Conf::config.useCache() && Conf::config.getCacheMode()==ASYNC_MODE) 
               msgQSend = new MsgQueueSend();
        else msgQSend = NULL;
        if (Conf::config.useDurability()) { fileSend = new FileSend(); } 
        else fileSend = NULL;
        if (Conf::config.useCache() && 
                                   Conf::config.getCacheMode() == OFFLINE_MODE)
            offlineLog = new OfflineLog;
        else offlineLog = NULL;
        txnUID.open();
        execLogStoreSize =0;
        noMsgLog = false;
        noOfflineLog = false;
    }
    ~SqlLogConnection();
    bool isTableCached(char *name);
    bool noMsgLog;
    bool noOfflineLog;
    //Note::forced to implement this as it is pure virtual in base class
    Connection& getConnObject(){  return dummyConn; }

    DbRetVal connect (char *user, char * pass);

    DbRetVal disconnect();

    DbRetVal commit();

    DbRetVal rollback();

    DbRetVal beginTrans (IsolationLevel isoLevel, TransSyncMode mode);

    DbRetVal msgPrepare(int tId, int sId, int len, char *stmt, char *tname)
    {
        return msgQSend->prepare(tId, sId, len, stmt, tname);
    }
    DbRetVal fileLogPrepare(int tId, int sId, int len, char *stmt, char *tname)
    {
        return fileSend->prepare(tId, sId, len, stmt, tname);
    }
    DbRetVal offlineLogPrepare(int tId, int sId, int len, char *st, char *tnm)
    {
        return offlineLog->prepare(tId, sId, len, st, tnm);
    }
    DbRetVal commitLogs(int logSize, void *data) 
    {  
        int txnId = getTxnID();
        if (((Conf::config.useCache() && 
             Conf::config.getCacheMode() == ASYNC_MODE)) && !noMsgLog) 
            msgQSend->commit(logSize, data); 
        if (Conf::config.useDurability()) fileSend->commit(logSize, data);
        if (Conf::config.useCache() && 
                               Conf::config.getCacheMode()==OFFLINE_MODE &&
                                                                 !noOfflineLog)
            offlineLog->commit(logSize, data);
        return OK;
    }
    DbRetVal freeLogs(int stmtId)
    {
        int txnId = getTxnID(); 
        if ( ((Conf::config.useCache() &&
             Conf::config.getCacheMode() == ASYNC_MODE)) && !noMsgLog)
            msgQSend->free(txnId, stmtId);
        if (Conf::config.useDurability()) fileSend->free(txnId, stmtId);
        if (Conf::config.useCache() && 
                            Conf::config.getCacheMode()==OFFLINE_MODE &&
                                                                 !noOfflineLog)
            offlineLog->free(txnId, stmtId);
        return OK;
    }
    void addExecLog(ExecLogInfo *info) { execLogStore.append(info); }
    void addToExecLogSize(int size){ execLogStoreSize += size; }
    int getExecLogStoreSize() { return execLogStoreSize; }
    List getExecLogList() { return execLogStore; }
    DbRetVal addPacket(BasePacket *pkt);
    DbRetVal addPreparePacket(PacketPrepare *pkt);
    DbRetVal removePreparePacket(int stmtid);

    DbRetVal setSyncMode(TransSyncMode mode);
    void setNoMsgLog(bool nmlog) { noMsgLog = nmlog; }
    void setNoOfflineLog(bool nolog) { noOfflineLog = nolog; }
    TransSyncMode getSyncMode() { return syncMode; }
    int getTxnID() { return txnID; }
    DbRetVal connectIfNotConnected() { return nwTable.connectIfNotConnected(); }
    DbRetVal sendAndReceive(NetworkPacketType type, char *packet, int length);
    friend class SqlFactory;
};

#endif
