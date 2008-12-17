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
#include <Parser.h>

/*enum DataSyncMode {
    NOSYNC=0,
    OSYNC=1,
    TSYNC=1,
    ASYNC=2
};
*/
enum NetworkPacketType
{
    NW_PKT_PREPARE =1,
    NW_PKT_EXECUTE =2,
    NW_PKT_COMMIT =3,
    NW_PKT_FREE =4,
    NW_PKT_CONNECT =5,
    NW_PKT_DISCONNECT =6,
    SQL_NW_PKT_CONNECT=101,
    SQL_NW_PKT_PREPARE=102,
    SQL_NW_PKT_PARAM_METADATA=103,
    SQL_NW_PKT_PROJ_METADATA=104,
    SQL_NW_PKT_EXECUTE=105,
    SQL_NW_PKT_FETCH=106,
    SQL_NW_PKT_RESULT_SET=107,
    SQL_NW_PKT_COMMIT=108,
    SQL_NW_PKT_ROLLBACK=109,
    SQL_NW_PKT_FREE=110,
    SQL_NW_PKT_DISCONNECT=111,
};

class ResponsePacket
{
    public:
    ResponsePacket()
    { stmtID = 0; retVal = 0; isSelect = false; rows=0; }
    ~ResponsePacket() { }
    int retVal; // will include for fetch end flag, params flag, proj flag
    int stmtID;
    int rows;
    bool isSelect;
    char errorString[ERROR_STRING_LENGTH];
    DbRetVal marshall();
    DbRetVal unmarshall();
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
    bool cacheClient;

    public:
    virtual DbRetVal send( NetworkPacketType type, char *buf, int len)=0;
    virtual DbRetVal receive()=0;
    virtual DbRetVal connect()=0;
    virtual DbRetVal disconnect()=0;
    virtual void * getResponsePacket()=0;
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
    void setCacheClient() { cacheClient = true; }
    bool isCacheClient() { return cacheClient; }
};
class UDPClient : public NetworkClient{
    public:
    int sockfd;
    struct sockaddr_in srvAddr;
    struct sockaddr_in fromAddr;
    UDPClient(){ isConnectedFlag =false; cacheClient = false;}
    DbRetVal send(NetworkPacketType type, char *buf, int len);
    DbRetVal receive();
    DbRetVal connect();
    DbRetVal disconnect();
    void * getResponsePacket() { return NULL; }
    ~UDPClient();
};
class TCPClient : public NetworkClient{
    public:
    int sockfd;
    struct sockaddr_in srvAddr;
    ResponsePacket *respPkt;
    TCPClient(){ isConnectedFlag =false; cacheClient = false; respPkt = new ResponsePacket(); }
    DbRetVal send(NetworkPacketType type, char *buf, int len);
    DbRetVal receive();
    DbRetVal connect();
    DbRetVal disconnect();
    void * getResponsePacket() { return respPkt; }
    ~TCPClient();
};
enum NetworkMode
{
    UDP,
    TCP
};
class NetworkTable
{
    NetworkClient* nwClient;
    public:
    ~NetworkTable();
    DbRetVal initialize();
    void destroy(){}
    DbRetVal readNetworkConfig();
    NetworkClient* getNetworkClient() { return nwClient; }
    DbRetVal connect();
    DbRetVal disconnect();
    DbRetVal connectIfNotConnected();
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
class SqlPacketHeader
{
    public:
    int packetType;
    int packetLength;
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
    PacketPrepare() { buffer=NULL; bufferSize =0; noParams = 0;
                      type = NULL; length = NULL; pktType = NW_PKT_PREPARE;}
    ~PacketPrepare() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    int syncMode;
    int stmtLength;
    int noParams;
    int *type;
    int *length;
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

class SqlPacketConnect : public BasePacket
{
    public:
    SqlPacketConnect()
    {
        strcpy(userName, "");
        strcpy(passWord, "");
        buffer = NULL;
        bufferSize = 0;
        pktType = SQL_NW_PKT_CONNECT;
   }
   ~SqlPacketConnect() { free(buffer); bufferSize = 0; buffer = NULL; }
   char userName[IDENTIFIER_LENGTH];
   char passWord[IDENTIFIER_LENGTH];
   void setConnParam(char *user, char *pass)
   { strcpy(userName, user); strcpy(passWord, pass); }
   DbRetVal marshall();
   DbRetVal unmarshall();
};

class SqlPacketPrepare : public BasePacket
{
    public:
    SqlPacketPrepare()
    { buffer=NULL; bufferSize =0; pktType = SQL_NW_PKT_PREPARE;}
    ~SqlPacketPrepare() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtLength;
    char *stmtString;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class SqlPacketExecute : public BasePacket
{
    public:
    SqlPacketExecute() { buffer=NULL; bufferSize =0; pktType = SQL_NW_PKT_EXECUTE;}
    ~SqlPacketExecute() { free(buffer); bufferSize = 0; buffer = NULL; paramValues = NULL; noParams = 0; }
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

class SqlPacketParamMetadata : public BasePacket
{
    public:
    SqlPacketParamMetadata()
    { buffer=NULL; bufferSize =0; noParams = 0;
      type = NULL; length = NULL; pktType = SQL_NW_PKT_PARAM_METADATA;}
    ~SqlPacketParamMetadata() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    int noParams;
    int *type;
    int *length;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class SqlPacketProjMetadata : public BasePacket
{
    public:
    SqlPacketProjMetadata() { buffer=NULL; bufferSize =0; noProjs = 0;
      type = NULL; length = NULL; pktType = SQL_NW_PKT_PROJ_METADATA; }
    ~SqlPacketProjMetadata() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    int noProjs;
    int *type;
    int *length;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class SqlPacketFetch : public BasePacket
{
    public:
    SqlPacketFetch() { buffer=NULL; bufferSize = 0;
                       pktType = SQL_NW_PKT_FETCH; }
    ~SqlPacketFetch() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class SqlPacketFree : public BasePacket
{
    public:
    SqlPacketFree() { buffer=NULL; bufferSize = 0;
                       pktType = SQL_NW_PKT_FREE; }
    ~SqlPacketFree() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class SqlPacketResultSet : public BasePacket
{
    public:
    SqlPacketResultSet() { buffer=NULL; bufferSize = 0; noProjs = 0;
                       projValues=NULL; pktType = SQL_NW_PKT_RESULT_SET; }
    ~SqlPacketResultSet() { free(buffer); bufferSize = 0; buffer = NULL; }
    int stmtID;
    int noProjs;
    char **projValues;
    List projList;
    void setProjList(List list);
    DbRetVal marshall();
    DbRetVal unmarshall();
};

class NetworkStmt
{
    public:
    int srcNetworkID;
    int stmtID;
    StatementType type;
    AbsSqlStatement *stmt;
    List paramList;
    List projList;
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
   virtual DbRetVal send(NetworkPacketType type, char *buf, int len)=0;
 
};
class UDPServer : public NetworkServer
{
   struct sockaddr_in clientAddress;
   public:
   UDPServer() { port = 0; sockfd = -1; }
   DbRetVal start();
   DbRetVal stop();
   DbRetVal handleClient();
   DbRetVal send(NetworkPacketType type, char *buf, int len) { }//dont know what to write
};

class TCPServer : public NetworkServer
{
   public:
   struct sockaddr_in clientAddress;
   int clientfd;
   TCPServer() { port = 0; sockfd = -1; clientfd = -1;}
   DbRetVal start();
   DbRetVal stop();
   DbRetVal handleClient();
   DbRetVal send(NetworkPacketType type, char *buf, int len);
};

#endif
