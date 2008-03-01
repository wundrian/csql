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

TCPClient::~TCPClient()
{
   if (isConnectedFlag) disconnect();
}
DbRetVal TCPClient::send(NetworkPacketType type, char *buf, int len)
{
    DbRetVal rv = OK;
    //printf("NW:TCP Send\n");
    return rv;
    
}
DbRetVal TCPClient::receive()
{
    DbRetVal rv = OK;
    //printf("NW:TCP receive\n");
    return rv;
}
DbRetVal TCPClient::connect()
{
    //printf("NW:TCP connect %s %d %d\n", hostName, port, networkid);
    
    //TODO::send endian to the peer site
    //do not do endian conversion here. it will be done at the server side


    isConnectedFlag = true;
    return OK;
}

DbRetVal TCPClient::disconnect()
{
    if (isConnectedFlag)
        printf("NW:TCP disconnect %s %d\n", hostName, port);

    isConnectedFlag = false;
    return OK;
}
