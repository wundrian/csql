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
#include <SqlNwConnection.h>
#include <Network.h>
#include<os.h>
#include <CSql.h>

DbRetVal SqlNwConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    if (isConnOpen) {
        printError(ErrAlready, "Connection is already open");
        return ErrAlready;
    }
    nwClient = new TCPClient();
    int bufsize = 2 * IDENTIFIER_LENGTH + sizeof(int);
    nwClient->setHost(hostname, port, 123);
    rv = nwClient->connect();
    if (rv != OK) {
        printError(rv, "Connection failed");
        return rv;
    }
    SqlPacketConnect *pkt = new SqlPacketConnect();
    pkt->setConnParam(user, pass, sqlApiImplType);
    pkt->setBufferSize(bufsize);
    char * buffer = (char *) malloc(bufsize);
    pkt->setBuffer(buffer);
    pkt->marshall();
    rv = send(SQL_NW_PKT_CONNECT, buffer, bufsize);
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        return rv;
    }
    int response = 0;
    rv = nwClient->receive();
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
    if (*ptr != 1) {
        printError(ErrPeerResponse, "%s", rpkt->errorString);
        nwClient->disconnect();
        delete nwClient; 
        delete pkt;
        return ErrPeerResponse;
    }
    isConnOpen = true;
    delete pkt;
    return rv;
}
DbRetVal SqlNwConnection::disconnect()
{
    DbRetVal rv = OK;
    if (! isConnOpen) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    rv = nwClient->disconnect();
    isConnOpen=false;
    delete nwClient; 
    return rv;
}

DbRetVal SqlNwConnection::beginTrans(IsolationLevel isoLevel, TransSyncMode mode)
{
   if (! isConnOpen) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    return OK;
}

DbRetVal SqlNwConnection::commit()
{
    if (! isConnOpen) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    DbRetVal rv = OK;
    rv = nwClient->send(SQL_NW_PKT_COMMIT, NULL, 0);
    int response = 0;
    return nwClient->receive();
}

DbRetVal SqlNwConnection::rollback()
{
    if (! isConnOpen) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    DbRetVal rv = OK;
    rv = nwClient->send(SQL_NW_PKT_ROLLBACK, NULL, 0);
    int response = 0;
    return nwClient->receive();
}

