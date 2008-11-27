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
#include <SqlNetworkHandler.h>

DbRetVal TCPServer::start()
{
    DbRetVal rv = OK;
    if (port == 0 )
    {
        printError(ErrBadArg, "Set the port first before starting\n");
        return ErrBadArg;
    } 
    struct sockaddr_in my_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       printError(ErrOS, "Unable to create socket\n");
       return ErrOS;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);
    if (bind(sockfd, (struct sockaddr *)&my_addr,
                     sizeof(struct sockaddr)) == -1) {
        printError(ErrOS, "bind failed");
        return ErrOS;
    }
    if (listen(sockfd, 10) == -1) {
        printError(ErrOS, "listen failed");
        return ErrOS;
    }
    return rv;
    
}
DbRetVal TCPServer::stop()
{
    DbRetVal rv = OK;
    close (sockfd);
    return rv;
}
DbRetVal TCPServer::handleClient()
{   
   printf("PRABA::handling client \n");
   DbRetVal rv = OK;
   socklen_t addressLen = sizeof(struct sockaddr);
   clientfd = accept(sockfd, (struct sockaddr*) &clientAddress, &addressLen);
   int ret = os::fork();
   if (ret) {
       //parent
       os::signal(SIGCHLD, SIG_IGN);
       close(clientfd);
       return OK;
   }else if (ret == 0) {
       //child
       int response = 1;
       int ret = os::send(clientfd, &response, 4, 0); 
       if (ret == -1)
       {
           printError(ErrOS, "Unable to communicate to peer\n");
           return ErrOS;
       }
       printf("sent connect ack packet to client\n");
       fd_set fdset; 
       struct timeval timeout;
       SqlNetworkHandler handler;
       PacketHeader header;
       while(true) {
           FD_ZERO(&fdset);
           FD_SET(clientfd, &fdset);
           timeout.tv_sec = 5;
           timeout.tv_usec = 0;
           int ret = os::select(clientfd+1, &fdset, 0, 0, &timeout);
           if (ret > 0) {
                printf("something in fd\n");
               int numbytes = os::recv(clientfd,&header,sizeof(PacketHeader),0);
               if (numbytes == -1)
               {
                   printError(ErrOS, "Error reading from socket\n");
                   return ErrOS;
               }
               printf("HEADER says packet type is %d\n", header.packetType);
               char *buffer = NULL;
               if (header.packetType != SQL_NW_PKT_DISCONNECT && 
                   header.packetType != SQL_NW_PKT_COMMIT     &&
                   header.packetType != SQL_NW_PKT_ROLLBACK)
               {
                   buffer = (char*) malloc(header.packetLength);
                   numbytes = os::recv(clientfd,buffer,header.packetLength,0);
                   if (numbytes == -1)
                   {
                       printError(ErrOS, "Error reading from socket\n");
                       return ErrOS;
                   }
               }
               ResponsePacket *rpkt = (ResponsePacket *) handler.process(header, buffer);
               numbytes = os::send(clientfd, rpkt, sizeof(ResponsePacket), 0);
               if (numbytes == -1)
               {
                   printError(ErrOS, "Error writing to socket\n");
                   return ErrOS;
               }
               char *ptr = (char *)&rpkt->retVal;
               if (*ptr==0) continue;
               if (*(ptr + 1)  == 1) continue; // for end of fetch
               NetworkStmt *stmt=NULL;
               int params =  *(ptr + 2);
               int proj = *(ptr + 3);  
               if ((header.packetType == SQL_NW_PKT_PREPARE && params != 0) ||
                   (header.packetType == SQL_NW_PKT_PREPARE && proj != 0)) {
                   if (params) {     
                       SqlPacketParamMetadata *prmpkt = new SqlPacketParamMetadata();
                       prmpkt->stmtID = rpkt->stmtID; 
                       ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
                       while (stmtIter.hasElement()) {
                           stmt = (NetworkStmt*) stmtIter.nextElement();
                           if (stmt->stmtID == prmpkt->stmtID) break;
                       }
                       prmpkt->noParams = stmt->paramList.size();
                       rv = prmpkt->marshall();
                       if (rv != OK) {
                           printf("marshall failed\n");
                       }
                       rv = send(SQL_NW_PKT_PARAM_METADATA, prmpkt->getMarshalledBuffer(), prmpkt->getBufferSize()); 
                       if (rv != OK) {
                           printf("Error in sending the metadata to the client\n");
                           exit(1);
                       }
                   }
                   if (proj) {
                       //fill projection list and send it to client   
                       SqlPacketProjMetadata *prjpkt = new SqlPacketProjMetadata();
                       prjpkt->stmtID = rpkt->stmtID;
                       ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
                       while (stmtIter.hasElement()) {
                           stmt = (NetworkStmt*) stmtIter.nextElement();
                           if (stmt->stmtID == prjpkt->stmtID) break;
                       }
                       prjpkt->noProjs = stmt->projList.size();
                       rv = prjpkt->marshall();
                       if (rv != OK) {
                           printf("marshall failed\n");
                       }
                       rv = send(SQL_NW_PKT_PROJ_METADATA, prjpkt->getMarshalledBuffer(), prjpkt->getBufferSize());
                       if (rv != OK) {
                           printf("Error in sending the metadata to the client\n");
                           exit(1);
                       }
                   }
               }   
               if (header.packetType == SQL_NW_PKT_FETCH) {
                   SqlPacketResultSet *rspkt = new SqlPacketResultSet();
                   rspkt->stmtID = rpkt->stmtID;
                   ListIterator stmtIter = SqlNetworkHandler::stmtList.getIterator();
                   while (stmtIter.hasElement()) {
                       stmt = (NetworkStmt*) stmtIter.nextElement();
                       if (stmt->stmtID == rspkt->stmtID) break;
                   }
                   rspkt->noProjs = stmt->projList.size();
                   rspkt->setProjList(stmt->projList);
                   rspkt->marshall();
                   if (rv != OK) { printf("marshall failed\n"); }
                   rv = send(SQL_NW_PKT_RESULT_SET, rspkt->getMarshalledBuffer(), rspkt->getBufferSize());
                   if (rv != OK) {
                       printf("Error in sending the metadata to the client\n");
                       exit(1);
                   }
               }    
               if (header.packetType == SQL_NW_PKT_DISCONNECT) { 
                   exit(0); 
               }
           } else printf("Nothing in fd %d\n", ret);
       }
   }else {
        printError(ErrOS, "Unable to fork new process");
        return ErrOS;
   } 
   return OK;
}

DbRetVal TCPServer::send(NetworkPacketType type, char *buf, int len)
{
    DbRetVal rv = OK;
    void* totalBuffer = malloc(sizeof(PacketHeader)+ len);
    PacketHeader *hdr=  new PacketHeader();
    hdr->packetType = type;
    hdr->packetLength = len;
    hdr->srcNetworkID = 0;//networkid;
    hdr->version = 1;
    memcpy(((char*)totalBuffer) + sizeof(PacketHeader) , buf, len);
    int numbytes=0;
    if ((numbytes=os::send(clientfd, hdr, sizeof(PacketHeader), 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    printf("Sent bytes %d\n", numbytes);
    if ((numbytes=os::send(clientfd, buf, len, 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    printf("Sent bytes %d\n", numbytes);
    free(totalBuffer);
    return rv;
}
