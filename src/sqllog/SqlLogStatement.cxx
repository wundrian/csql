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

UniqueID SqlLogStatement::stmtUID;

bool SqlLogStatement::isNonSelectDML(char *stmtstr)
{
    if (strlen(stmtstr) <= 6) return false;
    if (strncasecmp(stmtstr,"INSERT", 6) == 0) return true;
    else if (strncasecmp(stmtstr, "UPDATE", 6) ==0) return true;
    else if (strncasecmp(stmtstr, "DELETE", 6) ==0) return true;
    return false;
}

DbRetVal SqlLogStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    if (innerStmt) rv = innerStmt->prepare(stmtstr);
    if (rv != OK) return rv;

    isCached = false;
    //check if it is INSERT UPDATE DELETE statement
    //if not, then no need to generate logs
    if (!isNonSelectDML(stmtstr)) { return rv;}
    if (!Conf::config.useReplication() && !Conf::config.useCache()) return OK;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    if (!logConn->isTableCached(innerStmt->getTableName())) return ErrNotCached;
    isCached = true;
    return OK;

    sid  = SqlLogStatement::stmtUID.getID();
    //TODO::for TSYNC mode
    PacketPrepare *pkt = new PacketPrepare();
    pkt->stmtID= sid;
    pkt->syncMode = TSYNC;
    pkt->stmtString = stmtstr;
    pkt->noParams = innerStmt->noOfParamFields();
    FieldInfo *info = new FieldInfo();
    if (pkt->noParams > 0) {
      pkt->type = new int [pkt->noParams];
      pkt->length = new int [pkt->noParams];
      BindSqlField *bindField = NULL;
      for (int i = 0; i < innerStmt->noOfParamFields(); i++)
      {
        innerStmt->getParamFldInfo(i+1, info);
        bindField = new BindSqlField();
        bindField->type = info->type;
        bindField->length = info->length;
        pkt->type[i] =  info->type;
        pkt->length[i] =  info->length;
        bindField->value = AllDataType::alloc(info->type, info->length);
        paramList.append(bindField);
      }
    }
    pkt->marshall();
    //printf("Sending PREPARe packet of size %d\n", pkt->getBufferSize());
    rv = logConn->sendAndReceive(NW_PKT_PREPARE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    //printf("RV from PREPARE SQLLOG %d\n", rv);
    if (rv != OK) { 
       needLog = false; 
       logConn->addPreparePacket(pkt); 
       delete info; 
       return rv;
    }
    delete pkt;
    delete info;
    return rv;
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
    if (rv != OK) return rv;

    if (!needLog) return OK;
    //no need to generate log if it does not actually modify the table
    if (rowsAffected == 0 ) return OK;
    if (!isCached) return OK;
    if (logConn->getSyncMode() == OSYNC) return OK;

    //printf("LOG:execute\n");
    PacketExecute *pkt = new PacketExecute();
    pkt->stmtID= sid;
    pkt->noParams = innerStmt->noOfParamFields();
    pkt->setParams(paramList);
    pkt->marshall();
    int *p = (int*)pkt->getMarshalledBuffer();
    //printf("After EXEC packet marshall %d %d size %d\n", *p, *(p+1),
    //                pkt->getBufferSize());
   // printf("EXEC pkt ptr is %x\n", pkt);
    logConn->addPacket(pkt);
    return rv;
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

void* SqlLogStatement::fetchAndPrint()
{
    if (innerStmt) return innerStmt->fetchAndPrint();
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
    if (innerStmt) rv = innerStmt->free();
    //TODO::DEBUG::always innsrStmt->free() returns error
    //if (rv != OK) return rv;
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    if (sid != 0 ) logConn->removePreparePacket(sid);
    if (!needLog) return rv;

    //TODO
    //If statement is freed before the txn commits, it will lead to issue 
    //incase of async mode. when the other site goes down and comes back,
    //it will not have the cached SqlStatement objects, so in that case 
    //we need to send all the prepare packets again, so we should not free
    //the statement straight away in client side as well as in server side



    /*PacketFree *pkt = new PacketFree();
    pkt->stmtID= sid;
    pkt->marshall();
    SqlLogConnection* logConn = (SqlLogConnection*)con;
    logConn->sendAndReceiveAllPeers(NW_PKT_FREE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    delete pkt;*/
    needLog= false;
    sid = 0;
    paramList.reset();
    return OK;
}
void SqlLogStatement::setShortParam(int paramPos, short value)
{
    if (innerStmt) innerStmt->setShortParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeShort) return;
    *(short*)(bindField->value) = value;
    return;
}
void SqlLogStatement::setIntParam(int paramPos, int value)
{
    if (innerStmt) innerStmt->setIntParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeInt) return;
    *(int*)(bindField->value) = value;
    return;

}
void SqlLogStatement::setLongParam(int paramPos, long value)
{
    if (innerStmt) innerStmt->setLongParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeLong) return;
    *(long*)(bindField->value) = value;
    return;

}
void SqlLogStatement::setLongLongParam(int paramPos, long long value)
{
    if (innerStmt) innerStmt->setLongLongParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeLongLong) return;
    *(long long*)(bindField->value) = value;
    return;
}
void SqlLogStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (innerStmt) innerStmt->setByteIntParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeByteInt) return;
    *(char*)(bindField->value) = value;

}
void SqlLogStatement::setFloatParam(int paramPos, float value)
{
    if (innerStmt) innerStmt->setFloatParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeFloat) return;
    *(float*)(bindField->value) = value;

}
void SqlLogStatement::setDoubleParam(int paramPos, double value)
{
    if (innerStmt) innerStmt->setDoubleParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeDouble) return;
    *(double*)(bindField->value) = value;

}
void SqlLogStatement::setStringParam(int paramPos, char *value)
{
    if (innerStmt) innerStmt->setStringParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeString) return;
    char *dest = (char*)bindField->value;
    strncpy(dest, value, bindField->length);
    dest[ bindField->length - 1] ='\0';
    return;
}
void SqlLogStatement::setDateParam(int paramPos, Date value)
{
    if (innerStmt) innerStmt->setDateParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeDate) return;
    *(Date*)(bindField->value) = value;

}
void SqlLogStatement::setTimeParam(int paramPos, Time value)
{
    if (innerStmt) innerStmt->setTimeParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*)paramList.get(paramPos);
    if (bindField->type != typeTime) return;
    *(Time*)(bindField->value) = value;

}
void SqlLogStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (innerStmt) innerStmt->setTimeStampParam(paramPos,value);
    if (!needLog) return;
    BindSqlField *bindField = (BindSqlField*) paramList.get(paramPos);
    if (bindField->type != typeTimeStamp) return;
    *(TimeStamp*)(bindField->value) = value;
}
