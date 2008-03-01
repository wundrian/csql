/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
  ***************************************************************************/
#ifndef NETWORK_H
#define NETWORK_H
#include <CSql.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <AbsSqlStatement.h>

enum DataSyncMode {
    NOSYNC=0,
    TSYNC=1,
    ASYNC=2
};
enum NetworkPacketType
{
    NW_PKT_PREPARE =1,
    NW_PKT_EXECUTE =2,
    NW_PKT_COMMIT =3,
    NW_PKT_FREE =4
};
class NetworkClient {
    protected:
    char hostName[IDENTIFIER_LENGTH];
    int port;
    int networkid;
    bool isConnectedFlag;
    int responseTimeout; //in secs
    int connectTimeout;
    bool encrypt;

    public:
    virtual DbRetVal send( NetworkPacketType type, char *buf, int len)=0;
    virtual DbRetVal receive()=0;
    virtual DbRetVal connect()=0;
    virtual DbRetVal disconnect()=0;
    virtual ~NetworkClient(){}
    void setHost(char *host, int portno, int nwid)
    {
        strcpy(hostName, host);
        port = portno;
        networkid = nwid;
    }
    int getNetworkID() { return networkid; }
    void setConnectionTimeout(int timeout) { connectTimeout=timeout;}
    void setResponseTimeout(int timeout) { responseTimeout=timeout;}
    void setEntryption(bool encr) { encrypt=encr;}
    void setConnectFlag(bool flag) { isConnectedFlag=flag;}
    bool isConnected() { return isConnectedFlag; }
};
class UDPClient : public NetworkClient{
    public:
    int sockfd;
    struct sockaddr_in srvAddr;
    struct sockaddr_in fromAddr;
    UDPClient(){ isConnectedFlag =false;}
    DbRetVal send(NetworkPacketType type, char *buf, int len);
    DbRetVal receive();
    DbRetVal connect();
    DbRetVal disconnect();
    ~UDPClient();
};
class TCPClient : public NetworkClient{
    public:
    TCPClient(){ isConnectedFlag =false;}
    DbRetVal send(NetworkPacketType type, char *buf, int len);
    DbRetVal receive();
    DbRetVal connect();
    DbRetVal disconnect();
    ~TCPClient();
};
enum NetworkMode
{
    UDP,
    TCP
};
class NetworkTable
{
    List nwTable;
    public:
    ~NetworkTable();
    DbRetVal initialize();
    void destroy(){}
    DbRetVal readNetworkConfig();
    ListIterator getIterator() { return nwTable.getIterator(); }
    void connect();
    void disconnect();
};
class NetworkFactory 
{
    public:
    static NetworkClient* createClient(NetworkMode mode)
    {
        NetworkClient* client = NULL;
        switch(mode)
        {
            case UDP:
                client = new UDPClient();
                break;
            case TCP:
                client = new TCPClient();
                break;
        }
        return client;
    }
};
class PacketHeader
{
    public:
    int packetType;
    int packetLength;
    int srcNetworkID;
    int version;
};
class BasePacket{
    protected:
    //TOTOD:: bool encrypt;
    char *buffer;
    int bufferSize; 
    NetworkPacketType pktType;
    public:
    //should be called after successful marshall call
    char* getMarshalledBuffer(){ return buffer; }
    int getBufferSize() { return bufferSize; }
    void setBuffer(char *buf) { buffer =  buf; }
    void setBufferSize(int bufSize) { bufferSize = bufSize; }

    virtual DbRetVal marshall()=0;
    virtual DbRetVal unmarshall()=0;
    virtual ~BasePacket(){};
};
class PacketPrepare:public BasePacket
{
    public:
    PacketPrepare() { buffer=NULL; bufferSize =0; pktType = NW_PKT_PREPARE;}
    ~PacketPrepare() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    int syncMode;
    char *stmtString;
    DbRetVal marshall();
    DbRetVal unmarshall();
};
class PacketFree : public BasePacket
{
    public:
    PacketFree() { buffer=NULL; bufferSize =0; pktType = NW_PKT_FREE;}
    ~PacketFree() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class PacketExecute : public BasePacket
{
    public:
    PacketExecute() { buffer=NULL; bufferSize =0; pktType = NW_PKT_EXECUTE;}
    ~PacketExecute() { free(buffer); bufferSize = 0; buffer = NULL; }
    //TODO::need to free paramvalues based on marshall or unmarshall

    int stmtID;
    int noParams;
    char **paramValues;

    List paramList;
    List stmtList;

    void setStatementList(List stmtlist);
    void setParams(List list);
  
    DbRetVal marshall();
    DbRetVal unmarshall();
};
class PacketCommit : public BasePacket
{
    public:
    PacketCommit() { txnID =0; noOfStmts = 0; stmtBufSize = NULL; stmtBuffer = NULL;
                     buffer = NULL; bufferSize = 0; pktType = NW_PKT_COMMIT; }
    ~PacketCommit() { free(buffer); bufferSize = 0; buffer = NULL; }
    int txnID;
    int noOfStmts;
    int *stmtBufSize;
    char **stmtBuffer;
    void setExecPackets(int tid, List list);
    void getExecPacketList(List stmtList, List &list);
    DbRetVal marshall();
    DbRetVal unmarshall();
};
class NetworkStmt
{
    public:
    int srcNetworkID;
    int stmtID;
    AbsSqlStatement *stmt;
    List paramList;

};
class NetworkServer
{
   protected:
   int sockfd;
   int port;
   public:
   void setServerPort(int p) { port = p; }
   int getSocket(){ return sockfd; }
   virtual DbRetVal start()=0;
   virtual DbRetVal stop()=0;
   virtual DbRetVal handleClient()=0;
 
};
class UDPServer : public NetworkServer
{
   struct sockaddr_in clientAddress;
   public:
   UDPServer() { port = 0; sockfd = -1; }
   DbRetVal start();
   DbRetVal stop();
   DbRetVal handleClient();
};
class TCPServer : public NetworkServer
{
   public:
   TCPServer() { port = 0; sockfd = -1; }
   DbRetVal start();
   DbRetVal stop();
   DbRetVal handleClient();
};

#endif
