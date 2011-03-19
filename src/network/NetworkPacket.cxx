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
#include <CSql.h>
#include <Network.h>
#include <DataType.h>
//#include <SqlLogStatement.h>
#include <SqlNwStatement.h>
#ifndef CSQL_CLIENT_LIB
#include <SqlNetworkHandler.h>
#endif
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

SqlPacketExecute::SqlPacketExecute()
{
    buffer=NULL; bufferSize =0; pktType = NW_PKT_EXECUTE;
    paramValues = NULL; nullInfo = NULL;
    noParams=0; stmtID=0;
    for (int i=0; i < 10; i++) localBuf[i] =0;
}
SqlPacketExecute::~SqlPacketExecute()
{
    if(noParams >= 10) delete [] paramValues;
    if (nullInfo) { free(nullInfo); nullInfo = NULL; }
    free(buffer); 
    bufferSize =0;
    buffer = NULL;
}
void SqlPacketExecute::setParams(List list)
{
    paramList = list;
    noParams = list.size();
    if (!noParams) return;
    if (noParams <10) 
        paramValues = localBuf;
    else 
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
    return OK;
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
   printDebug(DM_Network, "SqlPacketConnect::marshall called");
   char *ptr = buffer; // moves over buffer
   strncpy(ptr, userName, IDENTIFIER_LENGTH);
   printDebug(DM_Network, "Username: %s", userName);
   ptr = buffer+IDENTIFIER_LENGTH-1;
   *ptr++ = '\0';
   strncpy(ptr, passWord, IDENTIFIER_LENGTH);
   printDebug(DM_Network, "Password: %s", passWord);
   ptr = ptr + IDENTIFIER_LENGTH-1;
   *ptr++ = '\0';
   *ptr++ = sqlApiImplType;  
   printDebug(DM_Network, "SqlPacketConnect::marshall Ended");
   return OK;
}

DbRetVal SqlPacketConnect::unmarshall()
{
   printDebug(DM_Network, "SqlPacketConnect::unmarshall called");
   char *ptr = buffer;

   strncpy(userName, ptr, IDENTIFIER_LENGTH);
   printDebug(DM_Network, "Username: %s", userName);
   ptr += IDENTIFIER_LENGTH;
   strncpy(passWord, ptr, IDENTIFIER_LENGTH);
   printDebug(DM_Network, "Password: %s", passWord);
   ptr += IDENTIFIER_LENGTH;
   sqlApiImplType = *ptr++;
   printDebug(DM_Network, "SqlPacketConnect::unmarshall Ended");
   return OK;
}

DbRetVal SqlPacketPrepare::marshall()
{
    printDebug(DM_Network, "PacketPrepare::marshall called\n");
    bufferSize  = sizeof(int) + stmtLength;
    printDebug(DM_Network, "Buffer size %d\n", bufferSize);
    printDebug(DM_Network, "stmt %s size %d\n", stmtString, strlen(stmtString));
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = stmtLength;
    char *bufIter = buffer + sizeof(int);
    strcpy(bufIter, stmtString);
    bufIter[strlen(stmtString)] = '\0';
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
    stmtString[strlen(stmtString)] = '\0';
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
    //allocate null info for setNull info for dml parameterized statements.
    if (noParams) bufferSize += os::align(noParams);
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
    if(noParams) memcpy(bufIter, nullInfo, os::align(noParams));
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
    if (noParams <10 )
        paramValues = localBuf;
    else 
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
    nullInfo = (char*) malloc(os::align(noParams));
    memcpy(nullInfo, bufIter, os::align(noParams));
    return OK;
}

DbRetVal SqlPacketParamMetadata::marshall()
{
#ifndef CSQL_CLIENT_LIB
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall called\n");
    bufferSize  = sizeof(int) * 2;
    printDebug(DM_Network, "NOOFPARAMS %d buffer size %d\n", noParams, bufferSize);
    printDebug(DM_Network, "noParams is %d\n", noParams);
    if (noParams >0) 
        bufferSize = bufferSize + sizeof(FieldInfo) * noParams;
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
    FieldInfo *fldInfo = new FieldInfo();
    for (int i=0; i <noParams; i++) {
        BindSqlField *bindField = (BindSqlField*) stmt->paramList.get(i+1);
        strcpy(fldInfo->fldName, bindField->fName);
        fldInfo->type = bindField->type;
        fldInfo->length = bindField->length;
        fldInfo->offset = bindField->offset;
        fldInfo->isNull = bindField->isNull;
        fldInfo->isPrimary = bindField->isPrimary;
        fldInfo->isDefault = bindField->isDefault;
        fldInfo->isUnique = bindField->isUnique;
        strcpy(fldInfo->defaultValueBuf, bindField->defaultValueBuf);
        *(FieldInfo *) bufIter = *fldInfo;
        bufIter += sizeof(FieldInfo);
    }     
    delete fldInfo;
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall ended\n");
#endif
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
    if(noParams > 0) data = bufIter;
    printDebug(DM_Network, "SqlPacketParamMetadata::unmarshall ended\n");
    return OK;
}

DbRetVal SqlPacketProjMetadata::marshall()
{
#ifndef CSQL_CLIENT_LIB
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall called\n");
    bufferSize  = sizeof(int) * 2;
    printDebug(DM_Network, "NOOFPROJS %d buffer size %d\n", noProjs, bufferSize);
    printDebug(DM_Network, "noParams is %d\n", noProjs);
    if (noProjs >0)
        bufferSize = bufferSize + sizeof(FieldInfo) * noProjs;
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
    FieldInfo *fldInfo = new FieldInfo();
    for (int i=0; i < noProjs; i++) {
        BindSqlProjectField *bindField = (BindSqlProjectField*) stmt->projList.get(i+1);
        strcpy(fldInfo->fldName, bindField->fName);
        fldInfo->type = bindField->type;
        fldInfo->length = bindField->length;
        fldInfo->offset = bindField->offset;
        fldInfo->isNull = bindField->isNull;
        fldInfo->isPrimary = bindField->isPrimary;
        fldInfo->isDefault = bindField->isDefault;
        fldInfo->isUnique = bindField->isUnique;
        strcpy(fldInfo->defaultValueBuf, bindField->defaultValueBuf);
        fldInfo->aType = bindField->aType;
        *(FieldInfo *) bufIter = *fldInfo;
        bufIter += sizeof(FieldInfo);
    }
    delete fldInfo;
    printDebug(DM_Network, "SqlPacketParamMetadata::marshall ended\n");
#endif
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
    if(noProjs > 0) data = bufIter;
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
    return OK;
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
    return OK;
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
    //allocate buffer for nullInfo
    bufferSize = bufferSize + os::align(noProjs);
    buffer = (char*) malloc(bufferSize);
    *(int*)buffer = hasData;
    char* bufIter = (char*) buffer + sizeof(int);
    *(int*)bufIter = noProjs;
    bufIter = (char*) bufIter + sizeof(int);
    for (int i = 0 ; i < noProjs; i++)
    {
        prjFld = (BindSqlProjectField*) projList.get(i+1);
        AllDataType::copyVal(bufIter, prjFld->value, prjFld->type, prjFld->length);
        bufIter = bufIter + AllDataType::size(prjFld->type, prjFld->length);
    }
    memcpy(bufIter, nullInfo, os::align(noProjs));
    return OK;
}

DbRetVal SqlPacketResultSet::unmarshall()
{
    hasData = *(int*)buffer;
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
    memcpy(nullInfo, bufIter, os::align(noProjs));
    return OK;
}

DbRetVal SqlPacketShowTables::marshall()
{
#ifndef CSQL_CLIENT_LIB
    bufferSize = numOfTables * IDENTIFIER_LENGTH;
    buffer = (char*) malloc(bufferSize);
    char *bufIter = buffer;
    Identifier *elem = NULL;
    ListIterator tblIter = SqlNetworkHandler::tableNameList.getIterator();
    while (tblIter.hasElement()) {
        elem = (Identifier*) tblIter.nextElement();
        strncpy(bufIter, elem->name, IDENTIFIER_LENGTH);
        bufIter += IDENTIFIER_LENGTH;
    }
#endif
    return OK;
}

DbRetVal SqlPacketShowTables::unmarshall()
{
    data = buffer;    
    return OK;
}

DbRetVal SqlPacketIsTablePresent::marshall()
{
    bufferSize = IDENTIFIER_LENGTH + sizeof(int);
    buffer = (char*) malloc(bufferSize);
    char *ptr = buffer;
    strncpy(ptr, tblName, IDENTIFIER_LENGTH);
    ptr += IDENTIFIER_LENGTH;
    return OK;
}

DbRetVal SqlPacketIsTablePresent::unmarshall()
{
    char *ptr = buffer;
    strncpy(tblName, buffer, IDENTIFIER_LENGTH);    
    ptr += IDENTIFIER_LENGTH;
    return OK;
}

DbRetVal SqlPacketGetRecords::marshall()
{
    printDebug(DM_Network, "SqlPacketGetRecords: marshall called");
    bufferSize = IDENTIFIER_LENGTH;
    printDebug(DM_Network, "Buffer Size = %d", bufferSize); 
    buffer = (char *) malloc(bufferSize);
    printDebug(DM_Network, "start of the buffer is %x", buffer);
    strncpy(buffer, tblName, IDENTIFIER_LENGTH);
    printDebug(DM_Network, "SqlPacketGetRecords: marshall Ended");
    return OK;
}

DbRetVal SqlPacketGetRecords::unmarshall()
{
    printDebug(DM_Network, "SqlPacketGetRecords: unmarshall called");
    strncpy(tblName, buffer, IDENTIFIER_LENGTH);
    printDebug(DM_Network, "TableName %s", buffer);
    printDebug(DM_Network, "SqlPacketGetRecords: unmarshall Ended");
    return OK;
}

DbRetVal SqlPacketLoadRecords::marshall()
{
    printDebug(DM_Network, "SqlPacketLoadRecords:marshall called");
    bufferSize = sizeof (int) + PAGE_SIZE * pages;
    printDebug(DM_Network, "Buffer Size = %d", bufferSize); 
    buffer = (char *) malloc(bufferSize);
    printDebug(DM_Network, "start of the buffer is %x", buffer);
    *(int *) buffer = pages;
    printDebug(DM_Network, "SqlPacketLoadRecords: marshall Ended");
    return OK;
}

DbRetVal SqlPacketLoadRecords::unmarshall()
{
    printDebug(DM_Network, "SqlPacketLoadRecords: unmarshall called");
    pages = *(int *) buffer;
    printDebug(DM_Network, "No of pages to be loaded: %d", pages);
    printDebug(DM_Network, "SqlPacketLoadRecords: unmarshall Ended");
    return OK;
}

