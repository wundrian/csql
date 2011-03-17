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

DbRetVal UDPServer::start()
{
    DbRetVal rv = OK;
    if (port == 0 )
    {
        printError(ErrBadArg, "Set the port first before starting\n");
        return ErrBadArg;
    } 
    struct sockaddr_in my_addr; 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
       printError(ErrOS, "Unable to create socket\n");
       return ErrOS;
    }
    my_addr.sin_family = AF_INET; 
    my_addr.sin_port = htons(port); 
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8); 
    if (bind(sockfd, (struct sockaddr *)&my_addr,
                     sizeof(struct sockaddr)) == -1) {
        return ErrOS;
    }
    return rv;
    
}
DbRetVal UDPServer::stop()
{
    //TODO:: response timeout during socket read
    DbRetVal rv = OK;
    close(sockfd);
    return rv;
}
DbRetVal UDPServer::handleClient()
{   
   DbRetVal rv = OK;
   PacketHeader header;
   socklen_t addressLen = sizeof(struct sockaddr);
   //printf("UDP Server receives packet\n");
   int numbytes = recvfrom(sockfd, (char*) &header,  sizeof(PacketHeader), 0,
                        (struct sockaddr*) &clientAddress, &addressLen);
   if (numbytes == -1)
   {
       printf("Error reading from socket\n");
       return ErrOS;
   }
   //printf("HEADERINFO %d %d %d %d\n", header.packetType, header.packetLength,
   //                 header.srcNetworkID, header.version);
   if (header.packetType == NW_PKT_CONNECT)
   {
       int response =1;
       numbytes = sendto(sockfd, (const char*) &response, 4, 0,
              (struct sockaddr*) &clientAddress, addressLen);
       if (numbytes != 4)
       {
          printf("Error writing to socket\n");
          return ErrOS;
       }
       return OK;
   }
   char *buffer = (char*) malloc(header.packetLength);
    fd_set fdset; //TODO::Move it to UDPClient class
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getNetworkResponseTimeout();
    timeout.tv_usec = 0;
    int ret = os::select(sockfd+1, &fdset, 0, 0, &timeout);
    if (ret <= 0) {
        printError(ErrPeerTimeOut,"Response timeout for peer site\n");
        return ErrPeerTimeOut;
    }

   numbytes = recvfrom(sockfd, buffer, header.packetLength, 0,
                        (struct sockaddr*) &clientAddress,  &addressLen);

   //printf("Bytes read %d\n", numbytes);
   if (numbytes == -1)
   {
       printf("Error reading from socket\n");
       return ErrOS;
   }
   SqlNetworkHandler handler;
   // following line is changed may  not work
   void * response = (void *) handler.process(header, buffer); 
   numbytes = ::sendto(sockfd, (const char*) &response, 4, 0,
              (struct sockaddr*) &clientAddress, addressLen);
   if (numbytes != 4)
   {
      printf("Error writing to socket\n");
      return ErrOS;
   }
   return OK;
}
