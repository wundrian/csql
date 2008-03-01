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
    bufferSize  = sizeof(int) + sizeof(int) + strlen(stmtString);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    char *bufIter = buffer + sizeof(int);
    *(int*)bufIter = syncMode;
    bufIter = bufIter + sizeof(int); 
    strcpy(bufIter, stmtString);
    return OK;
}
DbRetVal PacketPrepare::unmarshall()
{
    stmtID = *(int*)buffer;
    syncMode = *(int*)(buffer+sizeof(int));
    stmtString = buffer +sizeof(int)+sizeof(int);
    return OK;
}
DbRetVal PacketFree::marshall()
{
    bufferSize  = sizeof(int);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtID;
    //printf("PacketFree marshall with stmtid %d\n", stmtID);
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
    //printf("noParams %d\n", noParams);
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
    //printf("PacketExecute marshall with stmtid %d\n", stmtID);
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
    //printf("PKTEXEC stmtid %d params %d\n", stmtID, noParams);
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
    //printf("totalstmts %d\n", noOfStmts);
    stmtBufSize = new int[noOfStmts];
    stmtBuffer = new char*[noOfStmts];
    PacketExecute* pkt = NULL;
    int totalSize =0;
    for (int i = 0 ; i < noOfStmts; i++)
    {
        pkt = (PacketExecute*) list.get(i+1);
        //printf("pkt ptr from PACKETCommit is %x\n", pkt);
        if (pkt == NULL) printf("pkt is null.should never happen\n");
        stmtBufSize[i] = pkt->getBufferSize();
        //printf("Inside loop exec pkt size is %d\n", stmtBufSize[i]);
        stmtBuffer[i] = pkt->getMarshalledBuffer();
        //printf("Inside loop exec %d %d\n", *(int*)stmtBuffer[i], 
        //                             *(int*)(((char*)stmtBuffer[i]) + 4));
        totalSize = totalSize + stmtBufSize[i];
        //printf(" stmt no %d totalSize = %d\n", i+1, totalSize);
    }
    totalSize = sizeof(int) + sizeof(int) + noOfStmts * sizeof(int) +
               totalSize;
    bufferSize = totalSize;
    return;
}
DbRetVal PacketCommit::marshall()
{
    //printf("Marshalling commit packet %d %d\n", txnID, noOfStmts);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = txnID;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noOfStmts;
    bufIter = (char*) bufIter + sizeof(int);
    memcpy(bufIter, stmtBufSize, noOfStmts*sizeof(int));
    bufIter = (char*) bufIter + noOfStmts* sizeof(int);
    for (int i=0; i < noOfStmts; i++)
    {
        //printf("stmtbufsize %d\n", stmtBufSize[i]);
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
       //printf("stmtbufsize %d\n", stmtBufSize[i]);
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
