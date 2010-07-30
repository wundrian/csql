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

List SqlLogConnection::cacheList;

SqlLogConnection::~SqlLogConnection() 
{
    if (msgQSend) { delete msgQSend; msgQSend = NULL; }
    if (fileSend) { delete fileSend; fileSend = NULL; }
    if (offlineLog) { delete offlineLog; offlineLog = NULL; }
    txnUID.close();
    ListIterator iter = cacheList.getIterator();
    while(iter.hasElement()) delete (CachedTable *) iter.nextElement();
    cacheList.reset();
    ListIterator it = execLogStore.getIterator();
    while(it.hasElement()) ::free ((ExecLogInfo *) it.nextElement());
    execLogStore.reset();
} 

DbRetVal SqlLogConnection::connect (char *user, char *pass)
{
    DbRetVal rv = OK;
    if (innerConn) return innerConn->connect(user,pass);
    //populate cacheList if not populated by another thread in same process
    //TODO::cacheList requires mutex guard
    if (0 == cacheList.size()) rv = populateCachedTableList(); 
    return rv;
}

DbRetVal SqlLogConnection::disconnect()
{
    if (innerConn) innerConn->disconnect();
    return OK;
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
    if (innerConn) rv = innerConn->commit();
    if (!msgQSend && !fileSend && !offlineLog) return OK;
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
        ptr += sizeof(int);
        if (elInfo->type == SETPARAM) {
            *(int *) ptr = elInfo->pos;
            printDebug(DM_SqlLog, "commit: PrmPos to marshall: %d", elInfo->pos);
            ptr += sizeof(int);
            *(int *) ptr = elInfo->isNull;
            printDebug(DM_SqlLog, "commit: isNull to marshall: %d", elInfo->isNull);
            ptr += sizeof(int);
            if (elInfo->isNull == 0) {
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
    }
    commitLogs(len, data);
    ListIterator it = execLogStore.getIterator();
    while(it.hasElement()) ::free ((ExecLogInfo *) it.nextElement());
    execLogStore.reset();
    ::free(buffer);
    execLogStoreSize =0;
    return rv;
}
DbRetVal SqlLogConnection::rollback()
{
    DbRetVal rv = OK;
    if (innerConn) rv =  innerConn->rollback();
    if (rv != OK) return rv;
    if (!msgQSend && !fileSend && !offlineLog) return OK;
    ListIterator logStoreIter = execLogStore.getIterator();
    ExecLogInfo *elInfo = NULL;
    while (logStoreIter.hasElement())
    {
        elInfo = (ExecLogInfo *)logStoreIter.nextElement();
        ::free(elInfo);
    }
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
    char dsnName[IDENTIFIER_LENGTH];
    tablename[0] = '\0';
    fieldname[0] = '\0';
    condition[0] = '\0';
    field[0] = '\0';
    dsnName[0] = '\0';
    int cmode;
    CachedTable *node=NULL;
    while(!feof(fp))
    {
        int input = fscanf(fp, "%d %s %s %s %s %s\n", &cmode, tablename,fieldname,condition,field,dsnName);
        if (input != 6) break;
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

DbRetVal MsgQueueSend::prepare(int txnId, int stmtId, int len, char *stmt, 
                                                 char *tblName, bool hasParam) 
{
    //strlen is not included string is the last element in the following  
    //structure
    int datalen = 3 * sizeof(int) + IDENTIFIER_LENGTH + os::align(len); // for len + txnId + stmtId + tblName + string
    
    int buffer = sizeof(Message) - sizeof(void *) + datalen;
    Message *msg = (Message *) malloc(buffer);
    msg->mtype = 1;
    *(int *)&msg->data =  datalen;
    char *ptr = (char *) &msg->data + sizeof(int);
    *(int *)ptr = txnId;
    ptr += sizeof(int);
    *(int *)ptr = stmtId;
    ptr += sizeof(int);
    strncpy(ptr, tblName, IDENTIFIER_LENGTH);
    ptr[IDENTIFIER_LENGTH-1] ='\0';
    ptr +=IDENTIFIER_LENGTH;
    strncpy(ptr, stmt, len);
    printDebug(DM_SqlLog, "stmtstr = | %s |\n", ptr);
    printDebug(DM_SqlLog, "length of msg sent = %d\n", datalen);
    int ret = os::msgsnd(msgQId, msg, datalen, 0666);     
    if (ret != 0) { 
        printError(ErrSysInternal, "message send failed\n"); 
        ::free(msg);
        return ErrSysInternal; 
    }
    ::free(msg);
    return OK;
};

DbRetVal MsgQueueSend::commit(int len, void *data)
{
    Message *msg = (Message *) ((char *)data - sizeof (long));
    msg->mtype = 2;
    int ret = os::msgsnd(msgQId, msg, len, 0666);
    if (ret != 0) { 
        printError(ErrSysInternal, "message send failed\n"); 
        return ErrSysInternal; 
    }
    return OK;
}

DbRetVal MsgQueueSend::free(int txnId, int stmtId, bool hasParam)
{
    // data to be sent is len + txn id +  stmtId
    int dataLen = 3 * sizeof(int);
    int bufferSize = sizeof(Message) - sizeof(void *) + dataLen; 
    Message *msg = (Message *) malloc(bufferSize);
    msg->mtype = 3;
    *(int *) &msg->data = dataLen;
    char *ptr = (char *) &msg->data;
    ptr += sizeof(int);
    *(int *) ptr = txnId;
    ptr += sizeof(int);
    *(int *) ptr = stmtId;
    printDebug(DM_SqlLog, "stmtID sent = %d\n", *(int *) ptr);
    int ret = os::msgsnd(msgQId, msg, dataLen, 0666);
    if (ret != 0) { 
        printError(ErrSysInternal, "message send failed\n"); 
        ::free(msg);
        return ErrSysInternal; 
    }
    ::free(msg);
    return OK;
}
