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
#include<os.h>
#include <SqlNwConnection.h>
#include <Network.h>
#include <CSql.h>

DbRetVal SqlNwConnection::connect (char *user, char * pass)
{
    DbRetVal rv = OK;
    if (isConnOpen) {
        printError(ErrAlready, "Connection is already open");
        return ErrAlready;
    }
    if (nwClient == NULL)  nwClient = new TCPClient();
    int bufsize = 2 * IDENTIFIER_LENGTH + sizeof(int);
    nwClient->setHost(hostname, port, 123);
    rv = nwClient->connect();
    if (rv != OK) {
        printError(rv, "Connection failed");
        delete nwClient;
        nwClient = NULL;
        return rv;
    }
    SqlPacketConnect *pkt = new SqlPacketConnect();
    pkt->setConnParam(user, pass, sqlApiImplType);
    pkt->setBufferSize(bufsize);
    char * buffer = (char *) malloc(bufsize);
    pkt->setBuffer(buffer);
    pkt->marshall();
    rv = nwClient->send(SQL_NW_PKT_CONNECT, buffer, bufsize);
    if (rv != OK) {
        printError(rv, "Data could not be sent");
        delete pkt;
        delete nwClient; 
        nwClient = NULL;
        return rv;
    }
    rv = nwClient->receive();
    if (rv == ErrPeerTimeOut) { 
        delete pkt;
        delete nwClient; 
        nwClient = NULL;
        return ErrNoConnection; 
    }
    ResponsePacket *rpkt = (ResponsePacket *) ((TCPClient *)nwClient)->respPkt;
    char *ptr = (char *) &rpkt->retVal;
/*    if (*ptr != 1) {
        printError(ErrPeerResponse, "%s", rpkt->errorString);
        delete pkt;
        nwClient->disconnect();
        delete nwClient; 
        nwClient = NULL;
        return ErrPeerResponse;
    }*/
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
    nwClient = NULL;
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
    rv = nwClient->send(SQL_NW_PKT_COMMIT);
    if (rv == ErrNoConnection) {
        setConnClosed(false);
        return rv;
    }
    rv = nwClient->receive();
    if (rv == ErrNoConnection || rv == ErrPeerTimeOut) {
        setConnClosed(false);
        return ErrNoConnection;
    }
    return rv;
}

DbRetVal SqlNwConnection::rollback()
{
    if (! isConnOpen) {
        printError(ErrNoConnection, "No connection present");
        return ErrNoConnection;
    }
    DbRetVal rv = OK;
    rv = nwClient->send(SQL_NW_PKT_ROLLBACK);
    if (rv == ErrNoConnection) {
        setConnClosed(false);
        return rv;
    }
    rv = nwClient->receive();
    if (rv == ErrNoConnection || rv == ErrPeerTimeOut) {
        setConnClosed(false);
        return ErrNoConnection;
    }
    return rv;

}
