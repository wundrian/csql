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
#include <SqlLogStatement.h>
#include <TableConfig.h>

bool SqlLogStatement::isNonSelectDML(char *stmtstr)
{
    if (strlen(stmtstr) <= 6) return false;
    if (strncasecmp(stmtstr,"INSERT", 6) == 0) return true;
    else if (strncasecmp(stmtstr, "UPDATE", 6) ==0) return true;
    else if (strncasecmp(stmtstr, "DELETE", 6) ==0) return true;
    return false;
}

DbRetVal SqlLogStatement::executeDirect(char *stmtstr)
{
    DbRetVal rv = OK;
    int rows = 0;
    rv = prepare(stmtstr); if (rv != OK)  return rv;
    rv = execute(rows); if (rv != OK) return rv;
    return rv;
}

DbRetVal SqlLogStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    SqlLogConnection *conn = (SqlLogConnection *)con;
    if (innerStmt) {
       rv = innerStmt->prepare(stmtstr);
       if (rv != OK) { isNonSelDML = false; return rv; }
       if (innerStmt->getStmtType() == SelectStatement) {
           isNonSelDML = false; return rv;
       }
    }
    bool hasParam = false;
    if (innerStmt->noOfParamFields() >0) hasParam = true;

    if (Conf::config.useDurability()) {
        if (strlen(stmtstr) > 6 && ((strncasecmp(stmtstr,"CREATE", 6) == 0) ||
                                    (strncasecmp(stmtstr,"DROP", 4) == 0)   ||
                                    (strncasecmp(stmtstr,"RENAME", 6) == 0) ||
                                     (strncasecmp(stmtstr,"ALTER", 5) == 0))) {
            sid  = SqlLogStatement::stmtUID.getID(STMT_ID);
            printDebug(DM_SqlLog, "CREATE|DROP: stmt id = %d\n", sid);
            conn->fileLogPrepare(0, sid, strlen(stmtstr)+1, stmtstr, NULL, hasParam);
            isNonSelDML = false;
            return OK;
        }
    } 
    if (!isNonSelectDML(stmtstr)) { isNonSelDML = false; return rv;}
    char *tblName = NULL;
    if (innerStmt) {
        tblName = innerStmt->getTableName();
        unsigned int mode = TableConf::config.getTableMode(tblName);
        if (TableConf::config.isTableCached(mode)) isCached = true;
    }
    isPrepared = true;
    if (strncasecmp(stmtstr,"CACHE", 5) == 0 ||
                                      strncasecmp(stmtstr,"UNCACHE", 7) == 0) {
        isNonSelDML = false;
        return OK;
    }
    if (conn->isNoLogRequired()) { isNonSelDML = false; return OK; }

    needLog = true; isNonSelDML = true;
    int txnId=conn->getTxnID();
    sid = stmtUID.getID(STMT_ID);
    printDebug(DM_SqlLog, "stmt id = %d\n", sid);
    if (conn->isMsgQReqd() && !conn->noMsgLog && isCached) 
        conn->msgPrepare(txnId, sid, strlen(stmtstr) + 1, stmtstr, 
                                                            tblName, hasParam);
    if (conn->isFileLogReqd()) 
        conn->fileLogPrepare(txnId, sid, strlen(stmtstr) + 1, stmtstr, 
                                                               NULL, hasParam);
    if (conn->isOfflineLogReqd() && !conn->noOfflineLog)
        conn->offlineLogPrepare(txnId, sid, strlen(stmtstr) + 1, stmtstr, 
                                                               NULL, hasParam);
    return OK;
}

bool SqlLogStatement::isSelect()
{
    if (innerStmt) return innerStmt->isSelect();
    return false;
}

DbRetVal SqlLogStatement::execute(int &rowsAffected)
{
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    DbRetVal rv = OK;
    if (innerStmt) rv = innerStmt->execute(rowsAffected);
    if (!isNonSelDML) return rv;
    if ( rv != OK) return rv;
    if (!needLog) return rv;
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (sizeof(ExecLogInfo));
    elInfo->stmtId = sid;
    printDebug(DM_SqlLog, "Execute: stmtID: %d", elInfo->stmtId);
    elInfo->type = EXECONLY;
    printDebug(DM_SqlLog, "Execute: ExType: %d", elInfo->type);
    logConn->addExecLog(elInfo);
    printDebug(DM_SqlLog, "Execute: elem address: %x", elInfo);
    int size = 2 * sizeof(int);
    logConn->addToExecLogSize(size);
    printDebug(DM_SqlLog, "Execute: log length: %d", size);
    return OK;
}

DbRetVal SqlLogStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    if (innerStmt) rv = innerStmt->bindParam(pos,value);
    if (rv != OK) return rv;
    printError(ErrWarning, "Deprecated and does not replicate or cache");
    return rv;
}

DbRetVal SqlLogStatement::bindField(int pos, void* value)
{
    DbRetVal rv = OK;
    if (innerStmt) rv = innerStmt->bindField(pos,value);
    if (rv != OK) return rv;
    return rv;
}
void* SqlLogStatement::fetch()
{
    if (innerStmt) return innerStmt->fetch();
    return NULL;
}

void* SqlLogStatement::fetch(DbRetVal &rv)
{
    if (innerStmt) return innerStmt->fetch(rv);
    return NULL;
}

void* SqlLogStatement::fetchAndPrint(bool SQL)
{
    if (innerStmt) return innerStmt->fetchAndPrint(SQL);
    return NULL;
}

void* SqlLogStatement::next()
{
    if (innerStmt) return innerStmt->next();
    return NULL;
}

DbRetVal SqlLogStatement::close()
{
    if (innerStmt) return innerStmt->close();
    return OK;
}

void* SqlLogStatement::getFieldValuePtr( int pos )
{
    if (innerStmt) return innerStmt->getFieldValuePtr(pos);
    return NULL;
}
void* SqlLogStatement::getFieldValuePtr( char *name )
{
    if (innerStmt) return innerStmt->getFieldValuePtr(name);
    return NULL;
}

void SqlLogStatement::getProjFieldType(int *data)
{
    if (innerStmt) return innerStmt->getProjFieldType(data);
    return;
}

int SqlLogStatement::noOfProjFields()
{
    if (innerStmt) return innerStmt->noOfProjFields();
    return 0;
}

int SqlLogStatement::noOfParamFields()
{
    if (innerStmt) return innerStmt->noOfParamFields();
    return 0;
}

DbRetVal SqlLogStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    if (innerStmt) return innerStmt->getProjFldInfo(projpos, fInfo);
    return OK;
}

DbRetVal SqlLogStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    if (innerStmt) return innerStmt->getParamFldInfo(parampos, fInfo);
    return OK;
}

DbRetVal SqlLogStatement::free()
{
    DbRetVal rv = OK;
    bool hasParam = false;
    if (innerStmt) {
        if (innerStmt->noOfParamFields() >0) hasParam = true;
        rv = innerStmt->free();
    }
    if (!isPrepared) return OK;
    if (!needLog) { isPrepared = false; return rv; }
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    if (sid != 0) logConn->freeLogs(sid, hasParam);
    sid = 0;
    isNonSelDML = false;
    isPrepared = false;
    return rv;
}
void SqlLogStatement::setShortParam(int paramPos, short value)
{
    if (innerStmt) innerStmt->setShortParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(short);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    printDebug(DM_SqlLog, "setShort: stmtID: %d", elInfo->stmtId);
    elInfo->type = SETPARAM;
    printDebug(DM_SqlLog, "setShort: ExecTp: %d", elInfo->type);
    elInfo->pos = paramPos;
    printDebug(DM_SqlLog, "setShort: PrmPos: %d", elInfo->pos);
    elInfo->dataType = typeShort;
    printDebug(DM_SqlLog, "setShort: DtType: %d", elInfo->dataType);
    elInfo->len = sizeof (short);
    printDebug(DM_SqlLog, "setShort: Length: %d", elInfo->len);
    *(short *)&elInfo->value = value;
    printDebug(DM_SqlLog, "setShort: Value : %d", *(short *)&elInfo->value);
    logConn->addExecLog(elInfo);
    printDebug(DM_SqlLog, "appended elem addr: %x", elInfo);
    logConn->addToExecLogSize(buffer);
    printDebug(DM_SqlLog, "appended bufsize: %d", buffer);
    return;
}
void SqlLogStatement::setIntParam(int paramPos, int value)
{
    if (innerStmt) innerStmt->setIntParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(int);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    printDebug(DM_SqlLog, "setInt: stmtID: %d", elInfo->stmtId);
    elInfo->type = SETPARAM;
    printDebug(DM_SqlLog, "setInt: ExecTp: %d", elInfo->type);
    elInfo->pos = paramPos;
    printDebug(DM_SqlLog, "setInt: PrmPos: %d", elInfo->pos);
    elInfo->dataType = typeInt;
    printDebug(DM_SqlLog, "setInt: DtType: %d", elInfo->dataType);
    elInfo->len = sizeof(int);
    printDebug(DM_SqlLog, "setInt: Length: %d", elInfo->len);
    *(int *)&elInfo->value = value;
    printDebug(DM_SqlLog, "setInt: Value : %d", *(int *)&elInfo->value);
    logConn->addExecLog(elInfo);
    printDebug(DM_SqlLog, "appended elem addr: %x", elInfo);
    logConn->addToExecLogSize(buffer);
    printDebug(DM_SqlLog, "appended bufsize: %d", buffer);
    return;
}
void SqlLogStatement::setLongParam(int paramPos, long value)
{
    if (innerStmt) innerStmt->setLongParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(long);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeLong;
    elInfo->len = sizeof(long);
    *(long *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setLongLongParam(int paramPos, long long value)
{
    if (innerStmt) innerStmt->setLongLongParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(long long);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeLongLong;
    elInfo->len = sizeof (long long);
    *(long long *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (innerStmt) innerStmt->setByteIntParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(ByteInt);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeByteInt;
    elInfo->len = sizeof(ByteInt);
    *(ByteInt *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setFloatParam(int paramPos, float value)
{
    if (innerStmt) innerStmt->setFloatParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(float);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeFloat;
    elInfo->len = sizeof(float);
    *(float *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setDoubleParam(int paramPos, double value)
{
    if (innerStmt) innerStmt->setDoubleParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(double);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeDouble;
    elInfo->len = sizeof(double);
    *(double *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setStringParam(int paramPos, char *value)
{
    if (innerStmt) innerStmt->setStringParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + os::align(strlen(value) + 1);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos;
    elInfo->dataType = typeString;
    elInfo->len = os::align(strlen(value) + 1);
    strcpy((char *) &elInfo->value, value);
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setDateParam(int paramPos, Date value)
{
    if (innerStmt) innerStmt->setDateParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(Date);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos; 
    elInfo->dataType = typeDate;
    elInfo->len = sizeof(Date);
    *(Date *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setTimeParam(int paramPos, Time value)
{
    if (innerStmt) innerStmt->setTimeParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(Time);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos; 
    elInfo->dataType = typeTime;
    elInfo->len = sizeof (Time);
    *(Time *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (innerStmt) innerStmt->setTimeStampParam(paramPos,value);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + sizeof(TimeStamp);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos; 
    elInfo->dataType = typeTimeStamp;
    elInfo->len = sizeof(TimeStamp);
    *(TimeStamp *)&elInfo->value = value;
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
void SqlLogStatement::setBinaryParam(int paramPos, void *value, int length)
{
    if (innerStmt) innerStmt->setBinaryParam(paramPos,value, length);
    if (!isNonSelDML) return; 
    if (!needLog) return;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    int buffer = sizeof(ExecLogInfo) - sizeof(int) + os::align(length);
    ExecLogInfo *elInfo = (ExecLogInfo *) malloc (buffer);
    elInfo->stmtId = sid;
    elInfo->type = SETPARAM;
    elInfo->pos = paramPos; 
    elInfo->dataType = typeBinary;
    elInfo->len = os::align(length);
    memcpy(&elInfo->value, value, length);
    logConn->addExecLog(elInfo);
    logConn->addToExecLogSize(buffer);
    return;
}
bool SqlLogStatement::isFldNull(int pos)
{
    return innerStmt->isFldNull(pos);
}
void SqlLogStatement::setNull(int pos)
{
   if(innerStmt) innerStmt->setNull(pos);
}

List SqlLogStatement::getAllTableNames(DbRetVal &ret)
{
   if(innerStmt) return innerStmt->getAllTableNames(ret); 
}

List SqlLogStatement::getAllUserNames(DbRetVal &ret)
{
   if(innerStmt) return innerStmt->getAllUserNames(ret);
}

