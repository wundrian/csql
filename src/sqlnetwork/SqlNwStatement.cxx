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
#include <SqlNwStatement.h>
#include <Network.h>

DbRetVal SqlNwStatement::prepare(char *stmtstr)
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    //if (isPrepared) free(); 
    SqlPacketPrepare *pkt = new SqlPacketPrepare();
    pkt->stmtString = stmtstr;
    pkt->stmtLength = strlen(stmtstr) + 1;
    pkt->marshall(); 
    rv = conn->send(SQL_NW_PKT_PREPARE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    int response = 0;
    rv = conn->receive();
    if (rv != OK) { 
        printError(rv, "Prepare failed");
        return rv;
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if(rv != OK) return rv;
    StatementType tp = (StatementType) *(ptr + 1);
    int params = *(ptr + 2);
    int proj = *(ptr + 3);
    stmtID = rpkt->stmtID;
    char *buffer = NULL;
    if (params) {
        PacketHeader header;
        int fd = ((TCPClient *)(conn->nwClient))->sockfd;
        int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        printf("HEADER says packet type is %d\n", header.packetType);
        buffer = (char*) malloc(header.packetLength);
        numbytes = os::recv(fd,buffer,header.packetLength,0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        SqlPacketParamMetadata *mdpkt = new SqlPacketParamMetadata();
        mdpkt->setBuffer(buffer);
        mdpkt->unmarshall();
        BindSqlField *bindField=NULL;
        for (int i=0; i < mdpkt->noParams; i++) {
            bindField = new BindSqlField();
            bindField->type = (DataType) mdpkt->type[i];
            bindField->length = mdpkt->length[i];
            bindField->value = AllDataType::alloc(bindField->type, bindField->length);
            paramList.append(bindField);
        }
    }
    if (proj) {
        PacketHeader header;
        int fd = ((TCPClient *)(conn->nwClient))->sockfd;
        int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        printf("HEADER says packet type is %d\n", header.packetType);
        buffer = (char*) malloc(header.packetLength);
        numbytes = os::recv(fd,buffer,header.packetLength,0);
        if (numbytes == -1) {
            printError(ErrOS, "Error reading from socket\n");
            return ErrOS;
        }
        SqlPacketProjMetadata *prjmdpkt = new SqlPacketProjMetadata();
        prjmdpkt->setBuffer(buffer);
        prjmdpkt->unmarshall();
        BindSqlProjectField *prjFld=NULL;
        for (int i=0; i < prjmdpkt->noProjs; i++) {
            prjFld = new BindSqlProjectField();
            prjFld->type = (DataType) prjmdpkt->type[i];
            prjFld->length = prjmdpkt->length[i];
            prjFld->value = AllDataType::alloc(prjFld->type, prjFld->length);
            bindList.append(prjFld);
        }
    }
    isPrepared = true;
    return rv;
}

bool SqlNwStatement::isSelect()
{
    //TODO
    return false;
}

DbRetVal SqlNwStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    if (!isPrepared) return ErrNotPrepared;
    SqlPacketExecute *pkt = new SqlPacketExecute();
    pkt->stmtID = getStmtID();
    pkt->noParams=paramList.size();
    printf("noParams = %d\n", pkt->noParams);
    pkt->setParams(paramList);
    pkt->marshall();
    rv = conn->send(SQL_NW_PKT_EXECUTE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    rv = conn->receive();
    if (rv != OK) return rv; 
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr != 1) {
        printf("there is some error\n");        
        return ErrPeerResponse;
    }
    return rv;
}

DbRetVal SqlNwStatement::bindParam(int pos, void* value)
{
    DbRetVal rv = OK;
    printError(ErrWarning, "Deprecated. Use setParamXXX instead\n");
    return rv;
}

DbRetVal SqlNwStatement::bindField(int pos, void* value)
{
    if (!isPrepared) return OK;
    BindSqlProjectField *prjFld = (BindSqlProjectField *) bindList.get(pos);
    prjFld->value = value;
    return OK;
}
void* SqlNwStatement::fetch()
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return NULL;
    }
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;
    SqlPacketFetch *pkt = new SqlPacketFetch();
    pkt->stmtID = getStmtID();
    pkt->marshall();
    rv = conn->send(SQL_NW_PKT_FETCH, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return NULL;
    }
    rv = conn->receive();
    if (rv != OK) {
        printError(rv, "Unable to receive from Network");
        return NULL;
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*(ptr+1) == 1) {
        rv = OK;
        return NULL;
    }
    PacketHeader header;
    int fd = ((TCPClient *)(conn->nwClient))->sockfd;
    int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        return NULL;
    }
    printf("HEADER says packet type is %d\n", header.packetType);
    char *buffer = (char*) malloc(header.packetLength);
    numbytes = os::recv(fd,buffer,header.packetLength,0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        return NULL;
    }
    SqlPacketResultSet *rspkt = new SqlPacketResultSet();
    rspkt->setBuffer(buffer);
    rspkt->setProjList(bindList);
    rspkt->noProjs = bindList.size();
    rspkt->unmarshall();
    ptrToFirstField = bindList.get(1);
    return ptrToFirstField;
}

void* SqlNwStatement::fetch(DbRetVal &ret)
{
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        ret = ErrNoConnection;
        return NULL;
    }
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;
    SqlPacketFetch *pkt = new SqlPacketFetch();
    pkt->stmtID = getStmtID();
    pkt->marshall();
    DbRetVal rv = conn->send(SQL_NW_PKT_FETCH, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return NULL;
    }
    rv = conn->receive();
    if (rv != OK) {
        printError(rv, "Unable to receive from Network");
        return NULL;
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr == 0) { ret = ErrPeerResponse; return NULL; }
    if (*(ptr+1) == 1) { ret = OK; return NULL; }
    
    PacketHeader header;
    int fd = ((TCPClient *)(conn->nwClient))->sockfd;
    int numbytes = os::recv(fd, &header, sizeof(PacketHeader), 0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        return NULL;
    }
    printf("HEADER says packet type is %d\n", header.packetType);
    char *buffer = (char*) malloc(header.packetLength);
    numbytes = os::recv(fd,buffer,header.packetLength,0);
    if (numbytes == -1) {
        printError(ErrOS, "Error reading from socket\n");
        return NULL;
    }
    SqlPacketResultSet *rspkt = new SqlPacketResultSet();
    rspkt->setBuffer(buffer);
    rspkt->setProjList(bindList);
    rspkt->noProjs = bindList.size();
    rspkt->unmarshall();
    ptrToFirstField = bindList.get(1);
    return ptrToFirstField;
}


void* SqlNwStatement::fetchAndPrint(bool SQL)
{
    if (!isPrepared) return NULL;
    void *ptrToFirstField = NULL;
    //TODO
    return ptrToFirstField;
}

void* SqlNwStatement::next()
{
    return fetch();
}

DbRetVal SqlNwStatement::close()
{
    if (!isPrepared) return OK;
    //TODO
    return OK;
}

void* SqlNwStatement::getFieldValuePtr( int pos )
{
    return NULL;
}

int SqlNwStatement::noOfProjFields()
{
    if (!isPrepared) return 0;
    //TODO
    return 0;
}

int SqlNwStatement::noOfParamFields()
{
    if (!isPrepared) return 0;
    //TODO
    return 0;
}

DbRetVal SqlNwStatement::getProjFldInfo (int projpos, FieldInfo *&fInfo)
{
    //TODO
    return ErrNotFound;
}

DbRetVal SqlNwStatement::getParamFldInfo (int parampos, FieldInfo *&fInfo)
{
    //TODO
    return ErrNotFound;
}

DbRetVal SqlNwStatement::free()
{
    DbRetVal rv = OK;
    SqlNwConnection *conn = (SqlNwConnection*)con;
    if (! conn->isConOpen()) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    if (!isPrepared) return OK;
    SqlPacketFree *pkt = new SqlPacketFree();
    pkt->stmtID = getStmtID();
    pkt->marshall();
    rv = conn->send(SQL_NW_PKT_FREE, pkt->getMarshalledBuffer(), pkt->getBufferSize());
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    rv = conn->receive();
    if (rv != OK) return rv;
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)conn->nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr != 1) {
        printf("there is some error\n");
        return ErrPeerResponse;
    }
    ListIterator itprm = paramList.getIterator();
    BindSqlField *fld = NULL;
    while((fld = (BindSqlField *) itprm.nextElement()) != NULL) {
        delete fld;
    }
    paramList.reset();
    ListIterator itprj = bindList.getIterator();
    BindSqlProjectField *pfld = NULL;
    while((pfld = (BindSqlProjectField *) itprj.nextElement()) != NULL) {
        delete pfld;
    }
    bindList.reset();
    return rv;
}

void SqlNwStatement::setShortParam(int paramPos, short value)
{
    if (!isPrepared) return;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(short *) bindField->value = value;
    return;
}

void SqlNwStatement::setIntParam(int paramPos, int value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(int *) bindField->value = value;
    return;
}

void SqlNwStatement::setLongParam(int paramPos, long value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(long *) bindField->value = value;
    return;

}

void SqlNwStatement::setLongLongParam(int paramPos, long long value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(long long *) bindField->value = value;
    return;
}

void SqlNwStatement::setByteIntParam(int paramPos, ByteInt value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(ByteInt *) bindField->value = value;
    return;
}

void SqlNwStatement::setFloatParam(int paramPos, float value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(float *) bindField->value = value;
    return;
}

void SqlNwStatement::setDoubleParam(int paramPos, double value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(double *) bindField->value = value;
    return;
}

void SqlNwStatement::setStringParam(int paramPos, char *value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    strcpy((char *) bindField->value, value);
    return;
}

void SqlNwStatement::setDateParam(int paramPos, Date value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(Date *)bindField->value = value;
    return;
}

void SqlNwStatement::setTimeParam(int paramPos, Time value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    * (Time *) bindField->value = value;
    return;
}

void SqlNwStatement::setTimeStampParam(int paramPos, TimeStamp value)
{
    if (!isPrepared) return ;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    *(TimeStamp *) bindField->value = value;
    return;
}

void SqlNwStatement::setBinaryParam(int paramPos, void *value)
{
    if (!isPrepared) return;
    if (paramPos <= 0) return;
    BindSqlField *bindField = (BindSqlField *) paramList.get(paramPos);
    memcpy(bindField->value, value, 2 * bindField->length);
    return;
}

void SqlNwStatement::getPrimaryKeyFieldName(char *tablename, char *pkfieldname)
{
    if (pkfieldname == NULL) return;
    //TODO
    return;
}
