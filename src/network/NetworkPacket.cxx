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
void PacketExecute::setStatementList(List stmtlist)
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
   ptr = buffer+IDENTIFIER_LENGTH;
   *ptr++ = '\0';
   strncpy(ptr, passWord, IDENTIFIER_LENGTH);
   ptr = ptr + IDENTIFIER_LENGTH;
   *ptr = '\0';
   return OK;
}

DbRetVal SqlPacketConnect::unmarshall()
{
   strncpy(userName, buffer, IDENTIFIER_LENGTH);
   *(buffer+IDENTIFIER_LENGTH) = '\0';
   strncpy(passWord, buffer + IDENTIFIER_LENGTH + 1, IDENTIFIER_LENGTH);
   *(buffer + 2 *IDENTIFIER_LENGTH + 2) = '\0';
   return OK;
}

DbRetVal SqlPacketPrepare::marshall()
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

DbRetVal SqlPacketPrepare::unmarshall()
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

DbRetVal SqlPacketCommit::marshall()
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
DbRetVal SqlPacketCommit::unmarshall()
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

