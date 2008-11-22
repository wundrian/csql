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
    void setParamValues(AbsSqlStatement *stmt, int parampos, DataType type,
                        int length, char *value);
    public:
    static List stmtList;
    static AbsSqlConnection *conn;
    static SqlApiImplType type;
    static int stmtID;
    void *process(PacketHeader &header, char *buffer);
    void * processSqlConnect(PacketHeader &header, char *buffer);
    void * processSqlPrepare(PacketHeader &header, char *buffer);
    void * processSqlExecute(PacketHeader &header, char *buffer);
    void * processSqlFetch(PacketHeader &header, char *buffer);
    void * processSqlFree(PacketHeader &header, char *buffer);
    void * processSqlCommit(PacketHeader &header, char *buffer);
    void * processSqlRollback(PacketHeader &header, char *buffer);
    void * processPrepare(PacketHeader &header, char *buffer);
    void * processCommit(PacketHeader &header, char *buffer);
    void * processFree(PacketHeader &header, char *buffer);
    
    
};

#endif
