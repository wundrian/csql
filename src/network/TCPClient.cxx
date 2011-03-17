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
#include <Parser.h>
#if defined(SOLARIS)
#define MSG_NOSIGNAL 0
#endif
TCPClient::TCPClient()
{
    isConnectedFlag =false; 
    cacheClient = false; 
    sockfd = -1;
    respPkt = new ResponsePacket(); 
    pktHdr = new PacketHeader();
}

TCPClient::~TCPClient()
{
   if (isConnectedFlag) disconnect();
   delete respPkt;
   delete pktHdr;
}
DbRetVal TCPClient::send(NetworkPacketType type)
{
    DbRetVal rv = OK;
    if (sockfd == -1) {
        printError(ErrNoConnection, "Connection lost with the peer.");
        return ErrNoConnection;
    }
    pktHdr->packetType = type;
    pktHdr->packetLength = 0;
    int numbytes=0;
    if ((numbytes=os::send(sockfd, pktHdr, sizeof(PacketHeader), MSG_NOSIGNAL)) == -1) {
        if (errno == EPIPE) {
            printError(ErrNoConnection, "connection not present");
            isConnectedFlag = false;
            return ErrNoConnection;
        }
        printError(ErrOS, "Unable to send the packet");
        os::close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrNoConnection;
    }
    return rv;
}

DbRetVal TCPClient::send(NetworkPacketType type, int stmtid)
{
    DbRetVal rv = OK;
    if (sockfd == -1) {
        printError(ErrNoConnection, "Connection lost with the peer.");
        return ErrNoConnection;
    }
    pktHdr->packetType = type;
    pktHdr->packetLength = 0;
    pktHdr->stmtID = stmtid;
    int numbytes=0;
    if ((numbytes=os::send(sockfd, pktHdr, sizeof(PacketHeader), MSG_NOSIGNAL)) == -1) {
        if (errno == EPIPE) {
            printError(ErrNoConnection, "connection not present");
            isConnectedFlag = false;
            return ErrNoConnection;
        }
        printError(ErrOS, "Unable to send the packet");
        close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrNoConnection;
    }
    return rv;
}
DbRetVal TCPClient::send(NetworkPacketType type, char *buf, int len)
{
    DbRetVal rv = OK;
    if (sockfd == -1) {
        printError(ErrNoConnection, "Connection lost with the peer.");
        return ErrNoConnection;
    }
//    printf("NW:TCP Send\n");
    //void* totalBuffer = malloc(sizeof(PacketHeader)+ len);
    //PacketHeader *hdr=  new PacketHeader();
    pktHdr->packetType = type;
    pktHdr->packetLength = len;
    pktHdr->srcNetworkID = networkid;
    pktHdr->version = 1;
    pktHdr->stmtID = 0;
    //memcpy(((char*)totalBuffer) + sizeof(PacketHeader) , buf, len);
    int numbytes=0;
    if ((numbytes=os::send(sockfd, pktHdr, sizeof(PacketHeader), MSG_NOSIGNAL)) == -1) {
        if (errno == EPIPE) {
            printError(ErrNoConnection, "connection not present");
            isConnectedFlag = false;
            return ErrNoConnection;
        }
        printError(ErrOS, "Unable to send the packet");
        close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrNoConnection;
    }
//    printf("Sent bytes %d\n", numbytes);
    if ((numbytes=os::send(sockfd, buf, len, MSG_NOSIGNAL)) == -1) {
        if (errno == EPIPE) {
            printError(ErrNoConnection, "connection not present");
            isConnectedFlag = false;
            return ErrNoConnection;
        }
        printError(ErrOS, "Unable to send the packet");
        close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrNoConnection;
    }
//    printf("Sent bytes %d\n", numbytes);
    //free(totalBuffer);
    //delete hdr;
    return rv;
}
DbRetVal TCPClient::receive()
{
    DbRetVal rv = OK;
//    printf("NW:TCP receive\n");
    fd_set fdset; 
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getNetworkResponseTimeout();
    timeout.tv_usec = 0;
    int ret = os::select(sockfd+1, &fdset, 0, 0, &timeout);
    if (ret <= 0) {
        printError(ErrPeerTimeOut,"Response timeout for peer site");
        os::close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrPeerTimeOut;
    }
    socklen_t len = sizeof(struct sockaddr);
    int numbytes = os::recv(sockfd, respPkt, sizeof(ResponsePacket), 0);
    if (numbytes == -1)
    {
       printError(ErrOS, "Unable to receive response from peer");
        os::close(sockfd);
        sockfd = -1;
        isConnectedFlag = false;
        return ErrNoConnection;
    }
    return respPkt->errRetVal;
}

DbRetVal TCPClient::connect()
{
    //printf("NW:TCP connect %s %d %d\n", hostName, port, networkid);
    //TODO::send endian to the peer site
    //do not do endian conversion here. it will be done at the server side
    isConnectedFlag = false;
    struct hostent *he;
    int numbytes;
    if ((he=gethostbyname(hostName)) == NULL) { // get the host info
        printError(ErrOS,"Unable to get the peer host name");
        return ErrOS;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printError(ErrOS,"Unable to create socket to peer host name");
        return ErrOS;
    }
    srvAddr.sin_family = AF_INET; // host byte order
    srvAddr.sin_port = htons(port); // short, network byte order
    srvAddr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(srvAddr.sin_zero), '\0', 8); // zero the rest of the struct
    if (::connect(sockfd, (struct sockaddr*) & srvAddr, sizeof(struct sockaddr))
         == -1)
    {
        printError(ErrOS, "Unable to connect to peer site");
        return ErrOS;
    }
//    printf("NW:TCP connecting\n");
    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getNetworkConnectTimeout();
    timeout.tv_usec = 0;
    int ret = os::select(sockfd+1, &fdset, 0, 0, &timeout);
    if (ret <= 0) {
        printError(ErrPeerTimeOut,"Response timeout for peer site");
        return ErrPeerTimeOut;
    }
    int response=0;
    socklen_t len = sizeof(struct sockaddr);
    numbytes = os::recv(sockfd, &response, 4, 0);
    if (numbytes !=4)
    {
       printError(ErrOS, "Unable to receive response from peer");
       return ErrOS;
    }
//    printf("Response from peer site is %d\n", response);
//    if (response != 1) return ErrPeerResponse;

    //packet header information
    pktHdr->srcNetworkID = networkid;
    pktHdr->version = 1;
    isConnectedFlag = true;
    return OK;
}

DbRetVal TCPClient::disconnect()
{
    if (isConnectedFlag) {
//        printf("NW:TCP disconnect %s %d\n", hostName, port);
        pktHdr->packetType = SQL_NW_PKT_DISCONNECT;
        pktHdr->packetLength = 0;
        int numbytes=0;
        if ((numbytes=os::send(sockfd, pktHdr, sizeof(PacketHeader), MSG_NOSIGNAL)) == -1) {
            if (errno == EPIPE) {
                printError(ErrNoConnection, "connection not present");
                isConnectedFlag = false;
                return ErrNoConnection;
            }
            printError(ErrOS, "Unable to send the packet");
            close(sockfd);
            sockfd = -1;
            isConnectedFlag = false;
            return ErrNoConnection;   
        } else {
//            printf("Sent bytes %d\n", numbytes);
            DbRetVal rv = receive();
            isConnectedFlag = false;
            close(sockfd);
            sockfd = -1;
        }
    }
    return OK;
}
