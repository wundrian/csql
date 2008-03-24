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
#include <SqlNetworkHandler.h>
#include <AbsSqlConnection.h>
#include <SqlConnection.h>
#include <SqlOdbcConnection.h>
#include <AbsSqlStatement.h>
#include <SqlStatement.h>
#include <SqlOdbcStatement.h>

#include <SqlLogStatement.h>

List SqlNetworkHandler::stmtList;
AbsSqlConnection* SqlNetworkHandler::conn;
SqlApiImplType SqlNetworkHandler::type;

int SqlNetworkHandler::process(PacketHeader &header, char *buffer)
{
    switch(header.packetType)
    {
        case NW_PKT_PREPARE:
            return processPrepare(header, buffer);
            break;
        case NW_PKT_COMMIT:
            return processCommit(header, buffer);
            break;
    }
}

int SqlNetworkHandler::processCommit(PacketHeader &header, char *buffer)
{
    printf("COMMIT \n");
    PacketCommit *pkt = new PacketCommit();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    List pktList;
    pkt->getExecPacketList(stmtList, pktList);
    DbRetVal rv = applyExecPackets(stmtList, pktList);
    int response = 1;
    if (rv != OK)
    {
         printf("Unable to apply the exec packets\n");
         response =0;
    }
    return response;

}
int SqlNetworkHandler::processFree(PacketHeader &header, char *buffer)
{
    PacketFree *pkt = new PacketFree();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    //printf("FREE %d \n", pkt->stmtID);
    int response =1;
    //This wont work for two statement executed in same transaction using same SqlStatement object using free.
    //so do not delete now and put a flag 'readyfordelete' in NetworkStmt object and delete it during execute
    /*
    ListIterator iter = stmtList.getIterator();
    NetworkStmt *stmt, *removeStmt = NULL;
    while (iter.hasElement())
    {
       stmt = (NetworkStmt*)iter.nextElement();
       if (stmt->srcNetworkID == header.srcNetworkID
                && stmt->stmtID == pkt->stmtID)
       {
                  removeStmt = stmt;
                  break;
       }
    }
    if (removeStmt) stmtList.remove(removeStmt);
    else printf("Statement id %d not found in list \n",  pkt->stmtID);
    */
    return response;
}
int SqlNetworkHandler::processPrepare(PacketHeader &header, char *buffer) 
{
    PacketPrepare *pkt = new PacketPrepare();
    pkt->setBuffer(buffer);
    pkt->setBufferSize(header.packetLength);
    pkt->unmarshall();
    printf("PREPARE %d %s\n", pkt->stmtID, pkt->stmtString);
    //for (int i =0 ; i < pkt->noParams; i++)
        //printf("PREPARE type %d length %d \n", pkt->type[i], pkt->length[i]);
    int response =1;
    //TODO::add it to the SqlStatement list
    AbsSqlStatement *sqlstmt = SqlFactory::createStatement(type);
    sqlstmt->setConnection(conn);
    NetworkStmt *nwStmt = new NetworkStmt();
    printf("nwstmt in prepare %x %x\n", nwStmt, sqlstmt);
    printf("Statement string %s\n", pkt->stmtString);
    nwStmt->srcNetworkID = header.srcNetworkID;
    nwStmt->stmtID =  pkt->stmtID;
    nwStmt->stmt = sqlstmt;
    DbRetVal rv = sqlstmt->prepare(pkt->stmtString);
    if (rv != OK)
    {
        printError(ErrSysInit, "statement prepare failed\n");
        response = 0;
        return response;
    }
    BindSqlField *bindField = NULL;
    //populate paramList
    for (int i = 0; i < pkt->noParams; i++)
    {
             bindField = new BindSqlField();
             bindField->type = (DataType) pkt->type[i];
             bindField->length = pkt->length[i];
             bindField->value = AllDataType::alloc(bindField->type, 
                                                   bindField->length);
             nwStmt->paramList.append(bindField);
             printf("Adding element to paramList for type %d\n",bindField->type);
    }
    stmtList.append(nwStmt);
    return response;

}

DbRetVal SqlNetworkHandler::applyExecPackets(List sList, List pList)
{
    ListIterator stmtIter = sList.getIterator();
    NetworkStmt *nwstmt;
    DbRetVal rv = conn->beginTrans();
    if (rv != OK) return rv;
    ListIterator pktIter = pList.getIterator();
    PacketExecute *pkt;
    int i = 0;
    BindSqlField *bindField;
    while (pktIter.hasElement())
    {
        pkt = (PacketExecute*) pktIter.nextElement();
        printf("EXEC packt ptr %x in apply \n", pkt);
        stmtIter.reset();
        bool found = false;
        while (stmtIter.hasElement())
        {
            nwstmt = (NetworkStmt*) stmtIter.nextElement();
            if (nwstmt->stmtID == pkt->stmtID) {found = true ; break;}
        }
        if (!found) {
           printf("stmt not found in list. Negleting unreplicated table...\n"); 
           continue;
        }
        printf("nwstmt ptr in apply %x\n", nwstmt);
        ListIterator paramIter = nwstmt->paramList.getIterator();
        i = 0;
        while (paramIter.hasElement()) {
            bindField = (BindSqlField*) paramIter.nextElement();
            setParamValues(nwstmt->stmt, i+1,  bindField->type, bindField->length, pkt->paramValues[i]);
            printf("setting %d parameter of type %d\n", i, bindField->type);
            i++;
        }
        int rows= 0;
        DbRetVal rv = nwstmt->stmt->execute(rows);
        printf("sqlHandler rv ois %d\n", rv);
        if (rv != OK )
        {
            printf("sql execute failed with rv %d\n", rv);
            //TODO::log all things like SQL statements to a file
            SqlNetworkHandler::conn->rollback();
            printError(ErrPeerExecFailed, "Transaction Rolledback\n");
            return ErrPeerExecFailed;
        }
    }
    SqlNetworkHandler::conn->commit();
    printf("Transaction committed\n");
    return OK;
}

void SqlNetworkHandler::setParamValues(AbsSqlStatement *stmt, int parampos, DataType type,
                    int length, char *value)
{
    switch(type)
    {
        case typeInt:
            stmt->setIntParam(parampos, *(int*)value);
            break;
        case typeLong:
            stmt->setLongParam(parampos, *(long*)value);
            break;
        case typeLongLong:
            stmt->setLongLongParam(parampos, *(long long*)value);
            break;
        case typeShort:
            stmt->setShortParam(parampos, *(short*)value);
            break;
        case typeByteInt:
            stmt->setByteIntParam(parampos, *(char*)value);
            break;
        case typeDouble:
            stmt->setDoubleParam(parampos, *(double*)value);
            break;
        case typeFloat:
            stmt->setFloatParam(parampos, *(float*)value);
            break;
        case typeDate:
            stmt->setDateParam(parampos, *(Date*)value);
            break;
        case typeTime:
            stmt->setTimeParam(parampos, *(Time*)value);
            break;
        case typeTimeStamp:
            stmt->setTimeStampParam(parampos, *(TimeStamp*)value);
            break;
        case typeString:
            {
                char *d =(char*)value;
                d[length-1] = '\0';
                stmt->setStringParam(parampos, (char*)value);
                break;
            }
    }
    return;
}

