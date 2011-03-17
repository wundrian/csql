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
    int on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                                   (char *)&on, sizeof(on) );
    

    if (bind(sockfd, (struct sockaddr *)&my_addr,
                    sizeof(struct sockaddr)) == -1) {
        printError(ErrOS, "bind failed for port %d",port);
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
   printf("DEBUG::handling client\n");
   DbRetVal rv = OK;
   socklen_t addressLen = sizeof(struct sockaddr);
   clientfd = accept(sockfd, (struct sockaddr*) &clientAddress, (int*)&addressLen);
   int ret = os::fork();
   if (ret) {
       //parent
       close(clientfd);
       return OK;
   }else if (ret == 0) {
       int on = 1; 
       setsockopt(clientfd, IPPROTO_TCP, TCP_NODELAY, 
                                   (char *)&on, sizeof(on) );  

       //child
       int response = 1;
       int ret = os::send(clientfd, &response, 4, 0); 
       if (ret == -1)
       {
           printError(ErrOS, "Unable to communicate to peer\n");
           return ErrOS;
       }
//       printf("sent connect ack packet to client\n");
       fd_set fdset; 
       struct timeval timeout;
       SqlNetworkHandler handler;
       handler.sockfd = clientfd;
       PacketHeader header;
       while(true) {
           FD_ZERO(&fdset);
           FD_SET(clientfd, &fdset);
           timeout.tv_sec = 5;
           timeout.tv_usec = 0;
           int ret = os::select(clientfd+1, &fdset, 0, 0, &timeout);
           if (ret > 0) {
//                printf("something in fd\n");
               int numbytes = os::recv(clientfd,&header,sizeof(PacketHeader),0);
               if (!numbytes) { 
                   close(clientfd); 
                   handler.closeConnection(); 
                   exit(1);
               }
               if (numbytes == -1)
               {
                   printError(ErrOS, "Error reading from socket");
                   handler.closeConnection();
                   exit(1); 
               }
//               printf("HEADER says packet type is %d\n", header.packetType);
               char *buffer = NULL;
               if (header.packetType != SQL_NW_PKT_DISCONNECT && 
                   header.packetType != SQL_NW_PKT_COMMIT     &&
                   header.packetType != SQL_NW_PKT_ROLLBACK   &&
                   header.packetType != SQL_NW_PKT_FETCH      && 
                   header.packetType != SQL_NW_PKT_SHOWTABLES &&
                   header.packetType != SQL_NW_PKT_LASTAIVAL )
               {
                   buffer = (char*) malloc(header.packetLength);
                   numbytes = os::recv(clientfd,buffer,header.packetLength,0);
                   if (numbytes == -1)
                   {
                       printError(ErrOS, "Error reading from socket");
                       handler.closeConnection();
                       exit(1); 
                   }
               }
               ResponsePacket *rpkt = (ResponsePacket *) 
                                               handler.process(header, buffer);
               if (rpkt != NULL) rv = handler.servePacket(header, rpkt);
           } 
       }
   } else {
        printError(ErrOS, "Unable to fork new process");
        return ErrOS;
   } 
   return OK;
}
