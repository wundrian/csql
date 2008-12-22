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
#include <CSql.h>
#include <Network.h>
#include <DataType.h>
#include <SqlLogStatement.h>
#include <SqlNwStatement.h>
#include <SqlNetworkHandler.h>

DbRetVal PacketPrepare::marshall()
{
    printDebug(DM_Network, "PacketPrepare::marshall called\n");
    bufferSize  = sizeof(int) * 4 + strlen(stmtString) + 1;
    printDebug(DM_Network, "NOOFPARAMS %d buffer size %d\n", noParams, bufferSize);
    printDebug(DM_Network, "stmt %s size %d\n", stmtString, strlen(stmtString));
    printDebug(DM_Network, "noParams is %d\n", noParams);
    if (noParams >0)
        bufferSize = bufferSize + 2 * sizeof(int) * noParams;
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char *bufIter = buffer + sizeof(int);
    *(int*)bufIter = syncMode;
    bufIter = bufIter + sizeof(int); 
    *(int*)bufIter = strlen(stmtString);
    bufIter = bufIter + sizeof(int);
    *(int*)bufIter = noParams;
    bufIter = bufIter + sizeof(int); 
    if (noParams >0) { 
       memcpy(bufIter, type, sizeof(int) * noParams);
       bufIter = bufIter + sizeof(int)* noParams; 
       memcpy(bufIter, length, sizeof(int) * noParams);
       bufIter = bufIter + sizeof(int)* noParams; 
    }
    strcpy(bufIter, stmtString);
    printDebug(DM_Network, "PacketPrepare::marshall ended\n");
    return OK;
}
DbRetVal PacketPrepare::unmarshall()
{
    printDebug(DM_Network, "PacketPrepare::unmarshall called\n");
    stmtID = *(int*)buffer;
    printDebug(DM_Network, "start of the buffer is %x\n", buffer);
    char *bufIter = buffer + sizeof (int);
    syncMode = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    stmtLength = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    noParams = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    if (noParams >0) { 
        type = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noParams;
        length = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noParams;
    }
    stmtString = bufIter;
    printDebug(DM_Network, "stmtString ptr is %x\n", stmtString);
    stmtString[stmtLength+1] = '\0';
    printDebug(DM_Network, "PacketPrepare::unmarshall ended\n");
    return OK;
}
DbRetVal PacketFree::marshall()
{
    bufferSize  = sizeof(int);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    return OK;
}
DbRetVal PacketFree::unmarshall()
{
    stmtID = *(int*)buffer;
    return OK;
}
void PacketExecute::setParams(List list)
{
    paramList = list;
    noParams = list.size();
    paramValues = new char*[noParams];
    BindSqlField* bindField = NULL;
    for (int i = 0 ; i < noParams; i++)
    {
        bindField = (BindSqlField*) paramList.get(i+1);
        paramValues[i] = (char*) bindField->value;
    }
    return; 
}

void SqlPacketExecute::setParams(List list)
{
    paramList = list;
    noParams = list.size();
    if (!noParams) return;
    paramValues = new char*[noParams];
    BindSqlField* bindField = NULL;
    for (int i = 0 ; i < noParams; i++)
    {
        bindField = (BindSqlField*) paramList.get(i+1);
        paramValues[i] = (char*) bindField->value;
    }
    return;
}

void SqlPacketResultSet::setProjList(List list)
{
    projList = list;
    noProjs = list.size();
    projValues = new char*[noProjs];
    BindSqlProjectField* prjFld = NULL;
    for (int i = 0 ; i < noProjs; i++)
    {
        prjFld = (BindSqlProjectField*) projList.get(i+1);
        projValues[i] = (char*) prjFld->value;
    }
    return;
}

void PacketExecute::setStatementList(List stmtlist)
{
    stmtList = stmtlist;
    return; 
}

void SqlPacketExecute::setStatementList(List stmtlist)
{
    stmtList = stmtlist;
    return; 
}

DbRetVal PacketExecute::marshall()
{
    bufferSize  = sizeof(int)+ sizeof(int);
    BindSqlField* bindField = NULL;
    for (int i = 0 ; i < noParams; i++)
    {
        bindField = (BindSqlField*) paramList.get(i+1);
        bufferSize = bufferSize + AllDataType::size(bindField->type, bindField->length);
    }
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noParams;
    bufIter = (char*) bufIter + sizeof(int);
    for (int i = 0 ; i < noParams; i++)
    {
        bindField = (BindSqlField*) paramList.get(i+1);
        AllDataType::copyVal(bufIter, bindField->value, bindField->type,bindField->length);
        bufIter = bufIter + AllDataType::size(bindField->type, bindField->length);
    }
    return OK;
}
DbRetVal PacketExecute::unmarshall()
{
    stmtID = *(int*)buffer;
    char *bufIter = buffer + sizeof(int);
    noParams = *(int*)bufIter;
    bufIter = bufIter +sizeof(int);
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check teh srcNetworkID
       if (stmt->stmtID == stmtID ) break;
    } 
    if (noParams == 0) return OK;
    paramValues = new char*[noParams];
    ListIterator paramIter = stmt->paramList.getIterator();
    BindSqlField *bindField = NULL;
    for (int i=0; i <noParams; i++)
    { 
        paramValues[i] = bufIter;
        bindField = (BindSqlField*) stmt->paramList.get(i+1);
        bufIter = bufIter + AllDataType::size(bindField->type, bindField->length);
    }
    return OK;
}

void PacketCommit::setExecPackets(int tid, List list)
{
    txnID = tid;
    noOfStmts = list.size();
    stmtBufSize = new int[noOfStmts];
    stmtBuffer = new char*[noOfStmts];
    PacketExecute* pkt = NULL;
    int totalSize =0;
    for (int i = 0 ; i < noOfStmts; i++)
    {
        pkt = (PacketExecute*) list.get(i+1);
        if (pkt == NULL) printError(ErrSysFatal, "pkt is null.should never happen\n");
        stmtBufSize[i] = pkt->getBufferSize();
        stmtBuffer[i] = pkt->getMarshalledBuffer();
        //                             *(int*)(((char*)stmtBuffer[i]) + 4));
        totalSize = totalSize + stmtBufSize[i];
    }
    totalSize = sizeof(int) + sizeof(int) + noOfStmts * sizeof(int) +
               totalSize;
    bufferSize = totalSize;
    return;
}
DbRetVal PacketCommit::marshall()
{
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = txnID;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noOfStmts;
    bufIter = (char*) bufIter + sizeof(int);
    memcpy(bufIter, stmtBufSize, noOfStmts*sizeof(int));
    bufIter = (char*) bufIter + noOfStmts* sizeof(int);
    for (int i=0; i < noOfStmts; i++)
    {
        memcpy(bufIter, stmtBuffer[i], stmtBufSize[i]);
        bufIter = bufIter + stmtBufSize[i];
    }
    return OK;
}
DbRetVal PacketCommit::unmarshall()
{
    txnID = *(int*)buffer;
    char *bufIter = buffer + sizeof(int);
    noOfStmts = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    stmtBufSize = new int[noOfStmts];
    memcpy(stmtBufSize, bufIter, noOfStmts*sizeof(int));
    bufIter = bufIter + noOfStmts * sizeof(int);
    stmtBuffer = new char*[noOfStmts];
    for (int i = 0 ; i  <noOfStmts; i++)
    {
       stmtBuffer[i] = bufIter;
       bufIter = bufIter + stmtBufSize[i];
    }
}
//call unmarshall  before calling this
void PacketCommit::getExecPacketList(List stmtList, List &list)
{
    PacketExecute* pkt = NULL;
    for (int i = 0 ; i < noOfStmts; i++)
    {
        pkt = new PacketExecute();
        pkt->setBuffer(stmtBuffer[i]);
        pkt->setBufferSize(stmtBufSize[i]);
        pkt->setStatementList(stmtList);
        pkt->unmarshall();
        list.append(pkt);
    }
}

DbRetVal SqlPacketConnect::marshall()
{
   char *ptr = buffer; // moves over buffer
   strncpy(ptr, userName, IDENTIFIER_LENGTH);
   ptr = buffer+IDENTIFIER_LENGTH-1;
   *ptr++ = '\0';
   strncpy(ptr, passWord, IDENTIFIER_LENGTH);
   ptr = ptr + IDENTIFIER_LENGTH-1;
   *ptr = '\0';
   return OK;
}

DbRetVal SqlPacketConnect::unmarshall()
{
   strncpy(userName, buffer, IDENTIFIER_LENGTH);
   strncpy(passWord, buffer + IDENTIFIER_LENGTH, IDENTIFIER_LENGTH);
   return OK;
}

DbRetVal SqlPacketPrepare::marshall()
{
    printDebug(DM_Network, "PacketPrepare::marshall called\n");
    bufferSize  = sizeof(int) + strlen(stmtString) + 1;
    printDebug(DM_Network, "Buffer size %d\n", bufferSize);
    printDebug(DM_Network, "stmt %s size %d\n", stmtString, strlen(stmtString));
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = strlen(stmtString) + 1;
    char *bufIter = buffer + sizeof(int);
    strcpy(bufIter, stmtString);
    printDebug(DM_Network, "PacketPrepare::marshall ended\n");
    return OK;
}

DbRetVal SqlPacketPrepare::unmarshall()
{
    printDebug(DM_Network, "PacketPrepare::unmarshall called\n");
    printDebug(DM_Network, "start of the buffer is %x\n", buffer);
    stmtLength = *(int*)buffer;
    char *bufIter = buffer + sizeof(int);
    stmtString = bufIter;
    printDebug(DM_Network, "stmtString ptr is %x\n", stmtString);
    stmtString[stmtLength] = '\0';
    printDebug(DM_Network, "PacketPrepare::unmarshall ended\n");
    return OK;
}

// the following marshall and unmarshall function is modified to accommodate 
// the fix for MySQL Bug:1382 
// SQLDescribeParam returns the same type information
// by sending type and length in exec packets.
DbRetVal SqlPacketExecute::marshall()
{
    bufferSize  = sizeof(int)+ sizeof(int);
    BindSqlField* bindField = NULL;
    for (int i = 0 ; i < noParams; i++)
    {
        bufferSize = bufferSize + 2 * sizeof(int);
        bindField = (BindSqlField*) paramList.get(i+1);
        if (bindField->type == typeBinary)
            bufferSize = bufferSize + 2 * AllDataType::size(bindField->type, bindField->length);
        else 
            bufferSize = bufferSize + AllDataType::size(bindField->type, bindField->length);
    }
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noParams;
    bufIter = (char*) bufIter + sizeof(int);
    for (int i = 0 ; i < noParams; i++)
    {
        bindField = (BindSqlField*) paramList.get(i+1);
        if (bindField->type == typeBinary) {
            *(int *)bufIter = typeBinary;
            bufIter = (char*) bufIter + sizeof(int);
            *(int *)bufIter = AllDataType::size(bindField->type, bindField->length);
            bufIter = (char*) bufIter + sizeof(int); 
            AllDataType::copyVal(bufIter, bindField->value, bindField->type, 2 * bindField->length);
            bufIter = bufIter + 2 * AllDataType::size(bindField->type, bindField->length);
        } else {
            *(int *)bufIter = bindField->type;
            bufIter = (char*) bufIter + sizeof(int);
            *(int *)bufIter = AllDataType::size(bindField->type, bindField->length);
            bufIter = (char*) bufIter + sizeof(int); 
            AllDataType::copyVal(bufIter, bindField->value, bindField->type, bindField->length);
            bufIter = bufIter + AllDataType::size(bindField->type, bindField->length);
        } 
    }
    return OK;
}

DbRetVal SqlPacketExecute::unmarshall()
{
    stmtID = *(int*)buffer;
    char *bufIter = buffer + sizeof(int);
    noParams = *(int*)bufIter;
    bufIter = bufIter +sizeof(int);
    ListIterator stmtIter = stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       //TODO::Also check teh srcNetworkID
       if (stmt->stmtID == stmtID ) break;
    }
    if (noParams == 0) return OK;
    paramValues = new char*[noParams];
    ListIterator paramIter = stmt->paramList.getIterator();
    BindSqlField *bindField = NULL;
    for (int i=0; i <noParams; i++)
    {
        bindField = (BindSqlField*) stmt->paramList.get(i+1);
        bindField->type = (DataType) *(int *)bufIter;
        bufIter = (char*) bufIter + sizeof(int);
        bindField->length = *(int *)bufIter;
        bufIter = (char*) bufIter + sizeof(int);
        paramValues[i] = bufIter;
        bindField->value = paramValues[i];
        if (bindField->type == typeBinary)
            bufIter = bufIter + 2 * AllDataType::size(bindField->type, bindField->length);
        else
            bufIter = bufIter + AllDataType::size(bindField->type, bindField->length);
    }
    return OK;
}

DbRetVal SqlPacketParamMetadata::marshall()
{
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall called\n");
    bufferSize  = sizeof(int) * 2;
    printDebug(DM_Network, "NOOFPARAMS %d buffer size %d\n", noParams, bufferSize);
    printDebug(DM_Network, "noParams is %d\n", noParams);
    if (noParams >0) 
        bufferSize = bufferSize + 2 * sizeof(int) * noParams;
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char *bufIter = buffer + sizeof(int);
    *(int*)bufIter = noParams;
    bufIter = bufIter + sizeof(int);
    ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       if (stmt->stmtID == stmtID ) break;
    }
    for (int i=0; i <noParams; i++) {
        BindSqlField *bindField = (BindSqlField*) stmt->paramList.get(i+1);
        *(int *) bufIter = bindField->type;
        bufIter = bufIter + sizeof(int);
    }
    for (int i=0; i <noParams; i++) {
        BindSqlField *bindField = (BindSqlField*) stmt->paramList.get(i+1);
        *(int *) bufIter = bindField->length; 
        bufIter = bufIter + sizeof(int);
    }
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall ended\n");
    return OK;
}

DbRetVal SqlPacketParamMetadata::unmarshall()
{
    printDebug(DM_Network, "SqlPacketParamMetadata::unmarshall called\n");
    stmtID = *(int*)buffer;
    printDebug(DM_Network, "start of the buffer is %x\n", buffer);
    char *bufIter = buffer + sizeof (int);
    noParams = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    if(noParams > 0) {
        type = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noParams;
        length = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noParams;
    }
    printDebug(DM_Network, "SqlPacketParamMetadata::unmarshall ended\n");
    return OK;
}

DbRetVal SqlPacketProjMetadata::marshall()
{
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall called\n");
    bufferSize  = sizeof(int) * 2;
    printDebug(DM_Network, "NOOFPROJS %d buffer size %d\n", noProjs, bufferSize);
    printDebug(DM_Network, "noParams is %d\n", noProjs);
    if (noProjs >0)
        bufferSize = bufferSize + 2 * sizeof(int) * noProjs;
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char *bufIter = buffer + sizeof(int);
    *(int*)bufIter = noProjs;
    bufIter = bufIter + sizeof(int);
    ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
    NetworkStmt *stmt;
    while (stmtIter.hasElement())
    {
       stmt = (NetworkStmt*) stmtIter.nextElement();
       if (stmt->stmtID == stmtID ) break;
    }
    for (int i=0; i <noProjs; i++) {
        BindSqlProjectField *prjFld = (BindSqlProjectField*) stmt->projList.get(i+1);
        *(int *) bufIter = prjFld->type;
        bufIter = bufIter + sizeof(int);
    }
    for (int i=0; i <noProjs; i++) {
        BindSqlProjectField *prjFld = (BindSqlProjectField*) stmt->projList.get(i+1);
        *(int *) bufIter = prjFld->length;
        bufIter = bufIter + sizeof(int);
    }
    printDebug(DM_Network, "SqlPacketProjMetadata::marshall ended\n");
    return OK;
}

DbRetVal SqlPacketProjMetadata::unmarshall()
{
    printDebug(DM_Network, "SqlPacketProjMetadata::unmarshall called\n");
    stmtID = *(int*)buffer;
    printDebug(DM_Network, "start of the buffer is %x\n", buffer);
    char *bufIter = buffer + sizeof (int);
    noProjs = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    if(noProjs > 0) {
        type = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noProjs;
        length = (int*) bufIter;
        bufIter = bufIter + sizeof(int) * noProjs;
    }
    printDebug(DM_Network, "SqlPacketProjMetadata::unmarshall ended\n");
    return OK;
}

DbRetVal SqlPacketFetch::marshall()
{
    bufferSize  = sizeof(int);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    return OK;
}

DbRetVal SqlPacketFetch::unmarshall()
{
    stmtID = *(int *)buffer;
}

DbRetVal SqlPacketFree::marshall()
{
    bufferSize  = sizeof(int);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    return OK;
}

DbRetVal SqlPacketFree::unmarshall()
{
    stmtID = *(int *)buffer;
}

DbRetVal SqlPacketResultSet::marshall()
{
    bufferSize  = sizeof(int)+ sizeof(int);
    BindSqlProjectField* prjFld = NULL;
    for (int i = 0 ; i < noProjs; i++)
    {
        prjFld = (BindSqlProjectField*) projList.get(i+1);
        bufferSize = bufferSize + AllDataType::size(prjFld->type, prjFld->length);
    }
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noProjs;
    bufIter = (char*) bufIter + sizeof(int);
    for (int i = 0 ; i < noProjs; i++)
    {
        prjFld = (BindSqlProjectField*) projList.get(i+1);
        AllDataType::copyVal(bufIter, prjFld->value, prjFld->type, prjFld->length);
        bufIter = bufIter + AllDataType::size(prjFld->type, prjFld->length);
        
    }
    return OK;
}

DbRetVal SqlPacketResultSet::unmarshall()
{
    stmtID = *(int*)buffer;
    char *bufIter = buffer + sizeof(int);
    noProjs = *(int*)bufIter;
    bufIter = bufIter + sizeof(int);
    BindSqlProjectField *prjFld = NULL;
    for (int i=0; i <noProjs; i++)
    {
        prjFld = (BindSqlProjectField*) projList.get(i+1);
        AllDataType::copyVal(prjFld->value, bufIter, prjFld->type, prjFld->length);
        bufIter = bufIter + AllDataType::size(prjFld->type, prjFld->length);
        
    }
    return OK;
}
