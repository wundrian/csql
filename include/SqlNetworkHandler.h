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
#ifndef SQLNWHDLR_H
#define SQLNWHDLR_H
#include<CSql.h>
#include<Network.h>
#include<AbsSqlConnection.h>
#include<SqlConnection.h>
class SqlNetworkHandler
{
    DbRetVal applyExecPackets(List sList, List pList);
    public:
    static List stmtList;
    static List tableNameList;
    static AbsSqlConnection *conn;
    static SqlApiImplType type;
    static int stmtID;
    static int sockfd;
    static bool isSqlLogNeeded;
    void * process(PacketHeader &header, char *buffer);
    DbRetVal servePacket(PacketHeader &header, void *rpkt);
    DbRetVal sendResponse(void *rpkt);
    void * processSqlConnect(PacketHeader &header, char *buffer);
    void * processSqlDisconnect(PacketHeader &header);
    void * processSqlExecuteDirect(PacketHeader &header, char *buffer);
    void * processSqlPrepare(PacketHeader &header, char *buffer);
    void * processSqlExecute(PacketHeader &header, char *buffer);
    void * processSqlFetch(PacketHeader &header);
    void * processSqlFree(PacketHeader &header, char *buffer);
    void * processSqlCommit(PacketHeader &header, char *buffer);
    void * processSqlRollback(PacketHeader &header, char *buffer);
    void * processPrepare(PacketHeader &header, char *buffer);
    void * processCommit(PacketHeader &header, char *buffer);
    void * processFree(PacketHeader &header, char *buffer);
    void * processSqlShowTables(PacketHeader &header, char *buffer);
    void * processSqlIsTablePresent(PacketHeader &header, char *buffer);
    void * processSqlLoadRecords(PacketHeader &header, char *buffer);
    void * processSqlLastAutoIncrementVal(PacketHeader &header);
    DbRetVal closeConnection();
    static AbsSqlConnection *createConnection(SqlApiImplType type);   
    static AbsSqlStatement *createStatement(SqlApiImplType type);   
    void fillErrorString(ResponsePacket *rpkt);
    DbRetVal send(NetworkPacketType type, char *buf, int len);
};

#endif
